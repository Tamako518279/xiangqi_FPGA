#include "BoardView.h"
#include <cmath>

namespace xiangqi {

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

    void DrawCursor(Position position) {
    const Vector2 center = BoardToScreen(position.row, position.col);
    DrawCircleLinesV(center, 39.0f, BLUE);
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


namespace xiangqi {

// 将棋子类型转换为显示字符
namespace {

    const char* GetPieceSymbol(PieceType type) {

        switch (type) {

            case PieceType::General: return "G";
            case PieceType::Advisor: return "A";
            case PieceType::Elephant: return "E";
            case PieceType::Horse: return "H";
            case PieceType::Chariot: return "R";
            case PieceType::Cannon: return "C";
            case PieceType::Soldier: return "S";

            default: return "?";
        }
    }

    // 根据阵营确定棋子颜色
    Color GetSideColor(Side side) {

        if (side == Side::Red) {
            return Color{190, 35, 35, 255};
        }

        return Color{45, 45, 45, 255};
    }
}

// 根据棋盘数据绘制所有棋子
void DrawPieces(const Board& board) {

    for (int row = 0; row < BOARD_ROWS; row++) {

        for (int col = 0; col < BOARD_COLS; col++) {

            // 获取当前位置的数据
            const auto& cell = board.GetPiece(row, col);

            // 如果没有棋子，跳过
            if (!cell.has_value()) {
                continue;
            }

            const Piece& piece = cell.value();

            // 获取屏幕坐标
            Vector2 center = xiangqi::BoardToScreen(row, col);

            // 确定棋子颜色
            Color sideColor = GetSideColor(piece.side);

            // 绘制棋子背景
            DrawCircleV(
                center,
                29,
                Color{247, 232, 200, 255}
            );

            // 绘制棋子外圈
            DrawCircleLines(
                (int)center.x,
                (int)center.y,
                29,
                sideColor
            );

            DrawCircleLines(
                (int)center.x,
                (int)center.y,
                24,
                sideColor
            );

            // 绘制棋子标识
            const char* symbol = GetPieceSymbol(piece.Type);

            int fontSize = 22;
            int textWidth = MeasureText(symbol, fontSize);

            DrawText(
                symbol,
                (int)center.x - textWidth / 2,
                (int)center.y - fontSize / 2,
                fontSize,
                sideColor
            );
        }
    }
}

}
