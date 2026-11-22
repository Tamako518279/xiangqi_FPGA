#pragma once

#include "Board.h"
#include "Position.h"
#include "Movehistory.h"

namespace xiangqi {

struct AppState {
    Board board;
    Position cursor{BOARD_ROWS - 1, 0};
    bool hasSelection = false;
    Position selectedPosition{};//这个Position变量负责存储之前选中的位置信息
    bool boardSynchronized = false;
    MoveHistory moveHistory;
};

}