#pragma once

#include "Board.h"
#include "Position.h"

#include <optional>
#include "Moverecord.h"

namespace xiangqi {

enum class FpgaEventType {
    CursorChanged,
    SelectionChanged,
    BoardState,
    MoveResult,
    GameReset
};

struct FpgaEvent {
    FpgaEventType type;
    Position position{};
    bool selected = false;
    std::optional<Board> snapshot{};
    std::optional<MoveRecord> moveRecord{};
};

}