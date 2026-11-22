#include "BoardView.h"
#include <cmath>


namespace xiangqi {

  namespace 
  {

    void DrawCenteredText(Font font, const char* text, Vector2 center,
                      float size, float spacing, Color color) 
    {
        const Vector2 extent = MeasureTextEx(font, text, size, spacing);
        DrawTextEx(font, text,
               {center.x - extent.x / 2.0f, center.y - extent.y / 2.0f},
               size, spacing, color);
    }

   }

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
    }//这个函数现在已经不起具体作用了，它之前用于在main函数中把鼠标在屏幕上的位置转换为棋盘上
     //的具体坐标 ，但现在使用键盘控制后棋盘光标已经交由app.cursor控制
    void DrawCursor(Position position) {
    const Vector2 center = BoardToScreen(position.row, position.col);
    DrawCircleLinesV(center, 39.0f, BLUE);
}

    void DrawXiangqiBoard(Font font) {
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
    const float riverY = BOARD_TOP + 4.5f * CELL_SIZE;
    DrawCenteredText(font, u8"\u695A \u6CB3",
                 {BOARD_LEFT + 2.0f * CELL_SIZE, riverY}, 28.0f, 6.0f, lineColor);
    DrawCenteredText(font, u8"\u6C49 \u754C",
                 {BOARD_LEFT + 6.0f * CELL_SIZE, riverY}, 28.0f, 6.0f, lineColor);
    }

}


namespace xiangqi {

// 将棋子类型转换为显示字符
namespace {

    const char* GetPieceSymbol(const Piece& piece) {
    const bool red = (piece.side == Side::Red);
    switch (piece.Type) {
        case PieceType::General:  return red ? u8"\u5E05" : u8"\u5C06";
        case PieceType::Advisor:  return red ? u8"\u4ED5" : u8"\u58EB";
        case PieceType::Elephant: return red ? u8"\u76F8" : u8"\u8C61";
        case PieceType::Horse:    return u8"\u9A6C";
        case PieceType::Chariot:  return u8"\u8F66";
        case PieceType::Cannon:   return u8"\u70AE";
        case PieceType::Soldier:  return red ? u8"\u5175" : u8"\u5352";
    }
    return "?";
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
void DrawPieces(const Board& board,Font font) {

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
            DrawCenteredText(font, GetPieceSymbol(piece), center, 28.0f, 0.0f, sideColor);

           
        }
    }
}

}
