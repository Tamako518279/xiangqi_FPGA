#pragma once

#include "Board.h"
#include "Position.h"

namespace xiangqi {

struct AppState {
    Board board;
    Position cursor{BOARD_ROWS - 1, 0};
    bool hasSelection = false;
    Position selectedPosition{};
    bool boardSynchronized = false;
};

}