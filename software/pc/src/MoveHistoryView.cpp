#include "MoveHistoryView.h"

#include <algorithm>
#include <vector>

namespace xiangqi {
namespace {

constexpr int PANEL_X = 890;
constexpr int PANEL_Y = 65;
constexpr int PANEL_W = 478;
constexpr int PANEL_H = 770;

constexpr int LEFT = PANEL_X + 22;
constexpr int RED_X = LEFT + 60;
constexpr int BLACK_X = LEFT + 248;
constexpr int TABLE_W = PANEL_W - 44;
constexpr int ROW_TOP = 292;
constexpr int ROW_H = 46;
constexpr int VISIBLE_ROWS = 10;

constexpr Color PAPER{250, 247, 240, 255};
constexpr Color LINE{217, 207, 190, 255};
constexpr Color STRIPE{244, 237, 225, 255};
constexpr Color INK{55, 44, 34, 255};
constexpr Color DIM{109, 99, 88, 255};
constexpr Color RED_INK{171, 48, 43, 255};

struct HistoryRow {
    const MoveRecord* red = nullptr;
    const MoveRecord* black = nullptr;
};

void Label(Font font, const char* text, int x, int y, float size, Color color) {
    DrawTextEx(font, text,
               {static_cast<float>(x), static_cast<float>(y)},
               size, 0.0f, color
              );
}

const char* PieceName(const Piece& piece) {
 
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
void DrawMove(Font font, const MoveRecord* move, int x, int y, Color color) 
{
    if (!move) {
        return;
    }

    Label(font, TextFormat(u8"%s (%d,%d)→(%d,%d)",
                          PieceName(move->movedPiece),
                          move->from.row, move->from.col,
                          move->to.row, move->to.col),
          x, y + 5, 19.0f, color);

    if (move->capturedPiece) {
        Label(font, TextFormat(u8"吃%s", PieceName(*move->capturedPiece)),
              x, y + 25, 16.0f, DIM);
    }
}

}

Font LoadMoveHistoryFont() {
    const char* characters =
        u8" 0123456789(),-:/→?对局信息行棋方红黑钟记录合回暂无"
        u8"将士象马车炮卒吃键盘模拟已同步等待串口未接入"
        u8"楚河汉界帅仕相兵";
    int count = 0;
    int* codepoints = LoadCodepoints(characters, &count);
    std::sort(codepoints, codepoints + count);
    const int uniqueCount = static_cast<int>(
        std::unique(codepoints, codepoints + count) - codepoints
    );//保证每个字符只在codepoints数组里存一次对应编码

    const Font font = LoadFontEx("C:/Windows/Fonts/simhei.ttf", 32,
                                 codepoints, uniqueCount);
    UnloadCodepoints(codepoints);
    if (font.texture.id != 0) {
        SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
    }
    return font;
}

void DrawMoveHistoryPanel(const MoveHistory& history, bool boardSynchronized,
                          Font font, float& rowsFromBottom) 
{
    DrawRectangle(PANEL_X, PANEL_Y, PANEL_W, PANEL_H, PAPER);
    DrawRectangleLines(PANEL_X, PANEL_Y, PANEL_W, PANEL_H, LINE);

    if (font.texture.id == 0 || font.texture.id == GetFontDefault().texture.id) 
    {
        DrawText("Could not load C:/Windows/Fonts/simhei.ttf",
                 LEFT, PANEL_Y + 22, 18, MAROON);
        return;
    }

    Label(font, u8"对局信息", LEFT, 83, 27.0f, INK);
    Label(font, u8"行棋方  --", LEFT, 119, 19.0f, DIM);
    Label(font, u8"红方棋钟  --:--", LEFT, 158, 20.0f, RED_INK);
    Label(font, u8"黑方棋钟  --:--", BLACK_X, 158, 20.0f, INK);
    DrawLine(LEFT, 202, LEFT + TABLE_W, 202, LINE);

    Label(font, u8"行棋记录", LEFT, 220, 25.0f, INK);
    DrawRectangle(LEFT, 256, TABLE_W, 34, STRIPE);
    Label(font, u8"回合", LEFT + 8, 262, 19.0f, INK);
    Label(font, u8"红方", RED_X, 262, 19.0f, RED_INK);
    Label(font, u8"黑方", BLACK_X, 262, 19.0f, INK);

    // 按走子顺序组装表格行，每条记录按实际阵营入列。
    std::vector<HistoryRow> rows;
    for (const auto& move : history.GetMoves()) {
        if (move.movedPiece.side == Side::Red) {
            rows.push_back({&move, nullptr});
        } else {
            if (rows.empty() || rows.back().black) {
                rows.push_back({});
            }
            rows.back().black = &move;
        }
    }

    const int rowCount = static_cast<int>(rows.size());
    const int maxOffset = std::max(0, rowCount - VISIBLE_ROWS);
    const Rectangle historyArea{
        static_cast<float>(LEFT), 256.0f,
        static_cast<float>(TABLE_W),
        static_cast<float>(ROW_TOP - 256 + VISIBLE_ROWS * ROW_H)
    };

    if (CheckCollisionPointRec(GetMousePosition(), historyArea)) {
        rowsFromBottom += GetMouseWheelMove();
    }
    rowsFromBottom = std::clamp(rowsFromBottom, 0.0f, static_cast<float>(maxOffset));

    if (rows.empty()) {
        Label(font, u8"暂无行棋记录", LEFT + 8, ROW_TOP + 14, 19.0f, DIM);
    }

    const int first = maxOffset - static_cast<int>(rowsFromBottom);
    const int end = std::min(first + VISIBLE_ROWS, rowCount);
    for (int i = first; i < end; ++i) {
        const int y = ROW_TOP + (i - first) * ROW_H;
        if (i % 2 == 0) {
            DrawRectangle(LEFT, y, TABLE_W, ROW_H, STRIPE);
        }
        Label(font, TextFormat("%d", i + 1), LEFT + 8, y + 5, 19.0f, DIM);
        DrawMove(font, rows[i].red, RED_X, y, RED_INK);
        DrawMove(font, rows[i].black, BLACK_X, y, INK);
    }

    DrawLine(LEFT, 764, LEFT + TABLE_W, 764, LINE);
    Label(font, boardSynchronized ? u8"棋盘已同步" : u8"等待棋盘同步",
          LEFT, 779, 18.0f, INK);
    Label(font, u8"键盘模拟  /  串口未接入", LEFT, 805, 17.0f, DIM);
}

}