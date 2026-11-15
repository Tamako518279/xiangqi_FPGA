#pragma once

namespace xiangqi {
    enum class PieceType{
       General,
       Advisor,
       Elephant,
       Horse,
       Chariot,
       Cannon,
       Soldier
    };

    enum class Side{
        Red,
        Black
    };

    struct Piece{
        PieceType Type;
        Side side;
    };
    
}