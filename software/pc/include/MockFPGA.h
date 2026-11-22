#pragma once

#include "FPGAEvent.h"

#include <vector>
#include "Moverecord.h"

namespace xiangqi {

enum class InputAction {
    Up,
    Down,
    Left,
    Right,
    Confirm,
    Reset
};

class MockFpga {
public:
    std::vector<FpgaEvent> InitialEvents() const;
    std::vector<FpgaEvent> Press(InputAction action);

private:
    Board board_;
    Position cursor_{BOARD_ROWS - 1, 0};
    Position selectedPosition_{};
    MoveRecord move;

    std::vector<FpgaEvent> MoveCursor(int rowChange, int colChange);
    std::vector<FpgaEvent> Confirm();
};

}