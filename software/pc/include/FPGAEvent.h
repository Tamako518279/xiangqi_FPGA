#pragma once

#include "Board.h"
#include "Position.h"

#include <optional>

namespace xiangqi {

enum class FpgaEventType {
    CursorChanged,
    SelectionChanged,
    BoardState
};

struct FpgaEvent {
    FpgaEventType type;
    Position position{};
    bool selected = false;
    std::optional<Board> snapshot{};
};

}