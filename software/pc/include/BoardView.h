
#pragma once

#include "raylib.h"

namespace Xiangqi {

    // 棋盘基本参数
    inline constexpr int BOARD_ROWS = 10;
    inline constexpr int BOARD_COLS = 9;

    inline constexpr float CELL_SIZE = 80.0f;
    inline constexpr float BOARD_LEFT = 180.0f;
    inline constexpr float BOARD_TOP = 90.0f;

    // 棋盘逻辑坐标转屏幕坐标
    Vector2 BoardToScreen(int row, int col);

    // 屏幕坐标转棋盘逻辑坐标
    bool ScreenToBoard(Vector2 mouse, int& row, int& col);

    // 绘制棋盘
    void DrawXiangqiBoard();

}
