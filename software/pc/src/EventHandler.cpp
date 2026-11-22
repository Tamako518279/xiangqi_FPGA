#include "EventHandler.h"
#include "Movehistory.h"

namespace xiangqi {
namespace {

bool IsOnBoard(Position position) {
    return position.row >= 0 && position.row < BOARD_ROWS &&
           position.col >= 0 && position.col < BOARD_COLS;
}

}
//在事件类型不同的情况下，Position的意义也不一样
void HandleFpgaEvent(AppState& app, const FpgaEvent& event) {
    switch (event.type) {
        case FpgaEventType::CursorChanged:
            if (IsOnBoard(event.position)) {
                app.cursor = event.position;
                
            }
        break;

        case FpgaEventType::SelectionChanged:
            if (!event.selected) {
                app.hasSelection = false;//单独构造没有其他参数的SelectionChanged事件，selected为默认
                app.selectedPosition = {};//值-1，此时将会进入这个分支，对应MockFPGA模块移动成功后的第二
            } else if (IsOnBoard(event.position)) {//个事件
                app.hasSelection = true;
                app.selectedPosition = event.position;
            }
            break;

        case FpgaEventType::BoardState:
            if (event.snapshot) {
                app.board = *event.snapshot;//更新棋盘
                app.boardSynchronized = true;
            }
            break;
        
        case FpgaEventType::MoveResult:
            if(event.moveRecord)
            app.moveHistory.Add(*event.moveRecord);
            break;

        case FpgaEventType::GameReset:
             app.moveHistory.Clear();
             break;
             
             
    }
}

}