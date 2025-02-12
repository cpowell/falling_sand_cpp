// Helps raylib not freak out about spdlog (and anything else that includes windows.h)
// Seems pertinent in VStud but not in Clion
// See https://github.com/raysan5/raylib/issues/1217#issuecomment-1219728255
#if defined(_WIN32)
#define NOGDI  // All GDI defines and routines  // NOLINT(clang-diagnostic-unused-macros)
#define NOUSER // All USER defines and routines  // NOLINT(clang-diagnostic-unused-macros)
#endif

#include "Grid.h"
#include <imgui.h>
#include <raylib.h>

constexpr int MAX_X = 800;
constexpr int MAX_Y = 600;
constexpr int CELL_WIDTH = 10;

int main() {
    // Raylib overall-window configuration
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(MAX_X, MAX_Y, "Sand");
    auto dpi = GetWindowScaleDPI();

    SetWindowMinSize(MAX_X, MAX_Y);

    int ROWS = MAX_Y / CELL_WIDTH;
    int COLS = MAX_X / CELL_WIDTH;
    Grid g{ COLS, ROWS };

    while (!WindowShouldClose()) {
        // auto frame_start = high_resolution_clock::now();

        // ===============================
        // Input
        // ===============================
        auto pos = GetMousePosition();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            int nearest_row = pos.y / CELL_WIDTH;
            int nearest_col = pos.x / CELL_WIDTH;
            g.setCell(nearest_row, nearest_col, Grid::Kind::Sand);
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            int nearest_row = pos.y / CELL_WIDTH;
            int nearest_col = pos.x / CELL_WIDTH;
            g.setCell(nearest_row, nearest_col, Grid::Kind::Rock);
        }

        // ===============================
        // Update
        // ===============================
        g.evolve();

        // ===============================
        // Render / UI input
        // ===============================

        BeginDrawing();
        // rlImGuiBegin();

        // auto& io = ImGui::GetIO();
        // bool mouse_captured = io.WantCaptureMouse;

        ClearBackground(BLACK);

        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLS; ++c) {
                if (g.getCell(r, c) == Grid::Kind::Sand) {
                    DrawRectangle(c * CELL_WIDTH, r * CELL_WIDTH, CELL_WIDTH, CELL_WIDTH, GOLD);
                }

                if (g.getCell(r, c) == Grid::Kind::Rock) {
                    DrawRectangle(c * CELL_WIDTH, r * CELL_WIDTH, CELL_WIDTH, CELL_WIDTH, GRAY);
                }
            }
        }

        DrawFPS(5, MAX_Y - 30);

        // immediate_ui(io);
        // rlImGuiEnd();
        EndDrawing();
    }
}
