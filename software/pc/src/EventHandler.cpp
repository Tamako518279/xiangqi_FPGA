#include "EventHandler.h"

namespace xiangqi {
namespace {

bool IsOnBoard(Position position) {
    return position.row >= 0 && position.row < BOARD_ROWS &&
           position.col >= 0 && position.col < BOARD_COLS;
}

}

void HandleFpgaEvent(AppState& app, const FpgaEvent& event) {
    switch (event.type) {
        case FpgaEventType::CursorChanged:
            if (IsOnBoard(event.position)) {
                app.cursor = event.position;
            }
            break;

        case FpgaEventType::SelectionChanged:
            if (!event.selected) {
                app.hasSelection = false;
                app.selectedPosition = {};
            } else if (IsOnBoard(event.position)) {
                app.hasSelection = true;
                app.selectedPosition = event.position;
            }
            break;

        case FpgaEventType::BoardState:
            if (event.snapshot) {
                app.board = *event.snapshot;
                app.boardSynchronized = true;
            }
            break;
    }
}

}