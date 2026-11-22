#include "MockFPGA.h"

#include <algorithm>

namespace xiangqi {

std::vector<FpgaEvent> MockFpga::InitialEvents() const {
    return {
        {FpgaEventType::BoardState, {}, false, board_},
        {FpgaEventType::CursorChanged, cursor_},
        {FpgaEventType::SelectionChanged}
    };
}

std::vector<FpgaEvent> MockFpga::Press(InputAction action) {
    switch (action) {
        case InputAction::Up:    return MoveCursor(-1, 0);
        case InputAction::Down:  return MoveCursor(1, 0);
        case InputAction::Left:  return MoveCursor(0, -1);
        case InputAction::Right: return MoveCursor(0, 1);
        case InputAction::Confirm: return Confirm();
        case InputAction::Reset: {
             board_.Reset();
             cursor_ = {BOARD_ROWS - 1, 0};
             selectedPosition_ = {};

             auto events = InitialEvents();  // 开局棋盘、光标位置、未选中
             events.push_back({FpgaEventType::GameReset});
             return events;
}
    }
    return {};
}

std::vector<FpgaEvent> MockFpga::MoveCursor(int rowChange, int colChange) {
    Position next{
        std::clamp(cursor_.row + rowChange, 0, BOARD_ROWS - 1),//clamp的作用是当值超出边界时，返回最近的边界值
        std::clamp(cursor_.col + colChange, 0, BOARD_COLS - 1)
    };
    if (next.row == cursor_.row && next.col == cursor_.col) {
        return {};
    }
    cursor_ = next;
    return {{FpgaEventType::CursorChanged, cursor_}};//MoveCursor实际上跟CursorChanged是等价的
    //只不过为了将Press返回值的形式统一为一个事件表，同时进行位置移动判断，又进行了一次封装
}

std::vector<FpgaEvent> MockFpga::Confirm() {
    const auto& target = board_.GetPiece(cursor_.row, cursor_.col);
    if (selectedPosition_.row == -1) {//如果没有已经选择的棋子
        if (!target) {//如果选择的位置没有棋子，这里返回的是std::optional<Piece>的空指针
            return {};
        }
        selectedPosition_ = cursor_;//第一次选择成功
        return {{FpgaEventType::SelectionChanged, selectedPosition_, true}};
    }

    const Position from = selectedPosition_;//已经选择过棋子
    const auto& source = board_.GetPiece(from.row, from.col);
    if (!source || (from.row == cursor_.row && from.col == cursor_.col)) {
        selectedPosition_ = {};
        return {{FpgaEventType::SelectionChanged}};//选择的位置与上次相同，取消选中
    }

    if (target && target->side == source->side) {
        selectedPosition_ = cursor_;
        return {{FpgaEventType::SelectionChanged, selectedPosition_, true}};
    }//新选择位置的棋子的阵营与之前相同，改变选中对象

     const MoveRecord record{from, cursor_, *source, target};
    
     if (!board_.MovePieces(from.row, from.col, cursor_.row, cursor_.col)) {
        return {};
    }
//上面枚举了所有移动失败的情况，下面的代码只有在移动成功时执行
    
    move = record;
    
    FpgaEvent moveEvent{FpgaEventType::MoveResult};
    moveEvent.moveRecord = record;
    
    selectedPosition_ = {};
    return {
        moveEvent,
        {FpgaEventType::BoardState, {}, false, board_},//更新棋盘状态
        {FpgaEventType::SelectionChanged}//更新为未选中状态
    };
}
}