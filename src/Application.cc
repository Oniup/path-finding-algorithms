#include "Application.h"
#include "fmt/base.h"
#include "raylib.h"

namespace path_finding {

Application::Application(
    const std::string_view &title, World::CellTypeMap &&cell_types,
    const std::string_view &map_path, int window_size
)
    : window_size_(window_size), world_(std::move(cell_types))
{
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(window_size_, window_size_, title.data());
    if (window_size_ == 1) {
        int monitor_width = GetMonitorWidth(0);
        int monitor_height = GetMonitorHeight(0);
        window_size_ = monitor_height - monitor_height / 4;
        SetWindowSize(window_size_, window_size_);
        SetWindowPosition(
            monitor_width / 2 - window_size_ / 2,
            monitor_height / 2 - window_size_ / 2
        );
    }
    SetTargetFPS(60);

    if (world_.loadMapFromSource(map_path)) {
        fmt::println("Failed to load map from path '{}'", map_path);
    }
}

Application::~Application()
{
    CloseWindow();
}

bool Application::isRunning()
{
    return !WindowShouldClose();
}

void Application::update() {}

void Application::render()
{
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
}

} // namespace path_finding
