#include "BoardView.h"
#include <cmath>

namespace Xiangqi {

    Vector2 BoardToScreen(int row, int col) {
        return {
            BOARD_LEFT + col * CELL_SIZE,
            BOARD_TOP + row * CELL_SIZE
        };
    }

    bool ScreenToBoard(Vector2 mouse, int& row, int& col) {
         // 找到最近的交叉点
    int candidateCol = static_cast<int>(
        std::lround((mouse.x - BOARD_LEFT) / CELL_SIZE)
    );

    int candidateRow = static_cast<int>(
        std::lround((mouse.y - BOARD_TOP) / CELL_SIZE)
    );

    // 检查行列是否越界
    if (candidateRow < 0 || candidateRow >= BOARD_ROWS ||
        candidateCol < 0 || candidateCol >= BOARD_COLS) {
        return false;
    }

    // 获取最近交叉点的屏幕坐标
    Vector2 point = BoardToScreen(candidateRow, candidateCol);

    // 计算鼠标与交叉点的距离
    float dx = mouse.x - point.x;
    float dy = mouse.y - point.y;

    // 只允许鼠标靠近交叉点时识别成功
    if (dx * dx + dy * dy > 18.0f * 18.0f) {
        return false;
    }

    row = candidateRow;
    col = candidateCol;

    return true;
    }

    void DrawXiangqiBoard() {
         Color boardColor = {238, 214, 176, 255};
    Color lineColor = {80, 55, 35, 255};

    const int left = static_cast<int>(BOARD_LEFT);
    const int top = static_cast<int>(BOARD_TOP);

    const int right = left + (BOARD_COLS - 1) * 80;
    const int bottom = top + (BOARD_ROWS - 1) * 80;

    // 绘制棋盘背景
    DrawRectangle(
        left - 25,
        top - 25,
        right - left + 50,
        bottom - top + 50,
        boardColor
    );

    // 绘制横线
    for (int row = 0; row < BOARD_ROWS; row++) {

        int y = top + row * 80;

        DrawLine(left, y, right, y, lineColor);
    }

    // 绘制纵线
    for (int col = 0; col < BOARD_COLS; col++) {

        int x = left + col * 80;

        if (col == 0 || col == BOARD_COLS - 1) {

            // 左右边界线贯穿整个棋盘
            DrawLine(x, top, x, bottom, lineColor);

        } else {

            // 其他纵线在河界处断开
            DrawLine(x, top, x, top + 4 * 80, lineColor);

            DrawLine(x, top + 5 * 80, x, bottom, lineColor);
        }
    }

    // 绘制上方九宫斜线
    DrawLine(
        left + 3 * 80, top,
        left + 5 * 80, top + 2 * 80,
        lineColor
    );

    DrawLine(
        left + 5 * 80, top,
        left + 3 * 80, top + 2 * 80,
        lineColor
    );

    // 绘制下方九宫斜线
    DrawLine(
        left + 3 * 80, top + 7 * 80,
        left + 5 * 80, bottom,
        lineColor
    );

    DrawLine(
        left + 5 * 80, top + 7 * 80,
        left + 3 * 80, bottom,
        lineColor
    );

    // 绘制河界文字
    DrawText("CHU RIVER", 300, top + 4 * 80 + 25, 20, lineColor);
    DrawText("HAN BORDER", 550, top + 4 * 80 + 25, 20, lineColor);
    }

}