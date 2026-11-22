#pragma once

#include <vector>
#include "Movehistory.h"

namespace xiangqi{
    void MoveHistory::Add(const MoveRecord& move)
    {
        moves_.push_back(move);
    }

    void MoveHistory::Clear()
    {
        moves_.clear();
    }

    const std::vector<MoveRecord>& MoveHistory::GetMoves() const
    {
        return moves_;
    }




    
}