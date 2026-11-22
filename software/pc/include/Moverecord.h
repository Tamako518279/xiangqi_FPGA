#pragma once

#include "Position.h"
#include "Piece.h"
#include <optional>
namespace xiangqi{
struct MoveRecord {
    Position from;
    Position to;

    Piece movedPiece;

    std::optional<Piece> capturedPiece;
};
}