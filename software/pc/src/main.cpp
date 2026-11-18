#include "raylib.h"

#include "BoardView.h"
#include "EventHandler.h"
#include "MockFPGA.h"

#include <optional>

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
    InitWindow(1000, 900, "Xiangqi - Keyboard");
    SetTargetFPS(60);

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

        xiangqi::DrawXiangqiBoard();
        if (app.boardSynchronized) {
            xiangqi::DrawPieces(app.board);
        }
        xiangqi::DrawCursor(app.cursor);

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
        EndDrawing();
    }

    CloseWindow();
    return 0;
}



    