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
        case InputAction::Reset:
            board_.Reset();
            cursor_ = {BOARD_ROWS - 1, 0};
            selectedPosition_ = {};
            return InitialEvents();
    }
    return {};
}

std::vector<FpgaEvent> MockFpga::MoveCursor(int rowChange, int colChange) {
    Position next{
        std::clamp(cursor_.row + rowChange, 0, BOARD_ROWS - 1),
        std::clamp(cursor_.col + colChange, 0, BOARD_COLS - 1)
    };
    if (next.row == cursor_.row && next.col == cursor_.col) {
        return {};
    }
    cursor_ = next;
    return {{FpgaEventType::CursorChanged, cursor_}};
}

std::vector<FpgaEvent> MockFpga::Confirm() {
    const auto& target = board_.GetPiece(cursor_.row, cursor_.col);
    if (selectedPosition_.row == -1) {
        if (!target) {
            return {};
        }
        selectedPosition_ = cursor_;
        return {{FpgaEventType::SelectionChanged, selectedPosition_, true}};
    }

    const Position from = selectedPosition_;
    const auto& source = board_.GetPiece(from.row, from.col);
    if (!source || (from.row == cursor_.row && from.col == cursor_.col)) {
        selectedPosition_ = {};
        return {{FpgaEventType::SelectionChanged}};
    }

    if (target && target->side == source->side) {
        selectedPosition_ = cursor_;
        return {{FpgaEventType::SelectionChanged, selectedPosition_, true}};
    }

    if (!board_.MovePieces(from.row, from.col, cursor_.row, cursor_.col)) {
        return {};
    }

    selectedPosition_ = {};
    return {
        {FpgaEventType::BoardState, {}, false, board_},
        {FpgaEventType::SelectionChanged}
    };
}

}