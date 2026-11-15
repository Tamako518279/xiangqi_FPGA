
#pragma once

#include "raylib.h"
#include "Board.h"

namespace xiangqi {

// 棋盘几何参数
inline constexpr float CELL_SIZE = 80.0f;

inline constexpr float BOARD_LEFT = 180.0f;
inline constexpr float BOARD_TOP = 90.0f;

// 坐标转换
Vector2 BoardToScreen(int row, int col);

bool ScreenToBoard(
    Vector2 mouse,
    int& row,
    int& col
);

// 棋盘绘制
void DrawXiangqiBoard();

// 棋子绘制
void DrawPieces(const Board& board);

}
