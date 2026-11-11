
#include "raylib.h"
#include "BoardView.h"


int main() {

    InitWindow(1000, 900, "Xiangqi - S2");

    SetTargetFPS(60);

    // 当前鼠标所在的棋盘坐标
    int hoverRow = -1;
    int hoverCol = -1;

    // 当前选中的棋盘坐标
    int selectedRow = -1;
    int selectedCol = -1;

    bool hasSelection = false;

    while (!WindowShouldClose()) {

        // ===== 输入处理 =====

        Vector2 mouse = GetMousePosition();

        bool hoverValid = Xiangqi::ScreenToBoard(
            mouse,
            hoverRow,
            hoverCol
        );

        // 鼠标左键点击有效交叉点
        if (hoverValid &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            selectedRow = hoverRow;
            selectedCol = hoverCol;

            hasSelection = true;
        }

        // ===== 绘制 =====

        BeginDrawing();

        ClearBackground(RAYWHITE);

        Xiangqi::DrawXiangqiBoard();

        // 显示鼠标当前所在坐标
        if (hoverValid) {

            DrawText(
                TextFormat("Hover: row=%d col=%d",
                           hoverRow, hoverCol),
                20, 20, 22, DARKGRAY
            );

            // 蓝色圆圈标记鼠标所在交叉点
            Vector2 hoverPoint = Xiangqi::BoardToScreen(
                hoverRow, hoverCol
            );

            DrawCircleLines(
                (int)hoverPoint.x,
                (int)hoverPoint.y,
                18,
                BLUE
            );

        } else {

            DrawText(
                "Move mouse near a board intersection",
                20, 20, 22, DARKGRAY
            );
        }

        // 显示选中坐标
        if (hasSelection) {

            Vector2 selectedPoint = Xiangqi::BoardToScreen(
                selectedRow, selectedCol
            );

            DrawCircleLines(
                (int)selectedPoint.x,
                (int)selectedPoint.y,
                11,
                RED
            );

            DrawText(
                TextFormat("Selected: row=%d col=%d",
                           selectedRow, selectedCol),
                20, 48, 22, RED
            );
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

    