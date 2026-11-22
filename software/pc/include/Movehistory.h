#pragma once

#include "Moverecord.h"
#include <vector>

namespace xiangqi{
class MoveHistory {
public:
    void Add(const MoveRecord& move);

    void Clear();

    const std::vector<MoveRecord>& GetMoves() const;

private:
    std::vector<MoveRecord> moves_;
};
}