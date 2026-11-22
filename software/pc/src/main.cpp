#include "raylib.h"

#include "BoardView.h"
#include "EventHandler.h"
#include "MockFPGA.h"

#include <optional>
#include "MoveHistoryView.h"

namespace {

std::optional<xiangqi::InputAction> ToInputAction(int key) {
    using xiangqi::InputAction;

    switch (key) {
        case KEY_UP:    return InputAction::Up;
        case KEY_DOWN:  return InputAction::Down;
        case KEY_LEFT:  return InputAction::Left;
        case KEY_RIGHT: return InputAction::Right;
        case KEY_ENTER: return InputAction::Confirm;
        case KEY_R:     return InputAction::Reset;
        default:        return std::nullopt;
    }
}

}

int main() {
    InitWindow(1400, 900, "Xiangqi - Keyboard");
    SetTargetFPS(60);

    const Font historyFont = xiangqi::LoadMoveHistoryFont();
    float historyRowsFromBottom = 0.0f;

    xiangqi::AppState app;
    xiangqi::MockFpga mock;
    for (const auto& event : mock.InitialEvents()) {
        xiangqi::HandleFpgaEvent(app, event);
    }

    while (!WindowShouldClose()) {
        int key = GetKeyPressed();
        while (key != 0) {
            auto action = ToInputAction(key);
            if (action) {
                for (const auto& event : mock.Press(*action)) {
                    xiangqi::HandleFpgaEvent(app, event);
                }
            }
            key = GetKeyPressed();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        xiangqi::DrawXiangqiBoard(historyFont);
        if (app.boardSynchronized) {
            xiangqi::DrawPieces(app.board,historyFont);
        }
        xiangqi::DrawCursor(app.cursor);//注意虽然是app.cursor，但是这里实际上是该函数的位置坐标参数

        if (app.hasSelection) {
            const auto& selected = app.selectedPosition;
            const Vector2 center = xiangqi::BoardToScreen(selected.row, selected.col);
            DrawCircleLinesV(center, 35.0f, RED);
            DrawText(TextFormat("Selected: (%d, %d)", selected.row, selected.col),
                     20, 45, 20, RED);
        }

        DrawText("Arrows: move cursor / Enter: confirm / R: reset",
                 20, 15, 20, DARKGRAY);
        DrawText(TextFormat("Pieces: %d", app.board.CountPieces()), 20, 75, 20, DARKGRAY);

        xiangqi::DrawMoveHistoryPanel(
            app.moveHistory, 
            app.boardSynchronized, 
            historyFont, 
            historyRowsFromBottom
        );

        EndDrawing();
    }

    if (historyFont.texture.id != 0 && 
        historyFont.texture.id != GetFontDefault().texture.id) 
        { 
            UnloadFont(historyFont); 
        }

    CloseWindow();
    return 0;
}



    