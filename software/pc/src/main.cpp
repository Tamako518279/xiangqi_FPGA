
#include "raylib.h"

int main() {

    // 1. 初始化窗口
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Xiangqi - S1");
    SetTargetFPS(60);

    // 2. 定义变量
    Vector2 mouse_position = {400, 300};

    bool is_green = false;

    // 3. 游戏主循环
    while (!WindowShouldClose()) {

        // ===== 输入与状态更新 =====

        // 获取鼠标位置
        mouse_position = GetMousePosition();

        // 检测鼠标左键
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            is_green = !is_green;
        }

        // ===== 绘制画面 =====

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // 绘制横向网格
        for (int y = 0; y <= screenHeight; y += 50) {
            DrawLine(0, y, screenWidth, y, LIGHTGRAY);
        }

        // 绘制纵向网格
        for (int x = 0; x <= screenWidth; x += 50) {
            DrawLine(x, 0, x, screenHeight, LIGHTGRAY);
        }

        // 根据状态选择颜色
        Color color = is_green ? GREEN : DARKGRAY;

        // 绘制跟随鼠标的圆形
        DrawCircleV(mouse_position, 25, color);

        // 绘制文字
        DrawText("Move your mouse!", 20, 20, 20, BLACK);
        DrawText("Click LEFT button to change color",
                 20, 50, 20, BLACK);

        EndDrawing();
    }

    // 4. 关闭窗口
    CloseWindow();

    return 0;
}
