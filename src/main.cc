#include "Application.h"
#include "World.h"

using namespace path_finding;

int main(int argc, char **argv)
{
    const char *target_file = nullptr;
    if (argc > 1) {
        target_file = argv[1];
    }
    else {
        target_file = ASSETS_PATH "maps/map1.txt";
    }

    Application app(
        "Learning Path Finding",
        World::CellTypeMap({
            {CellInfo::CLEAR, CellInfo(2, RAYWHITE, '.')},
            {CellInfo::PATH, CellInfo(1, GREEN, 'p')},
            {CellInfo::MUD, CellInfo(5, GREEN, 'm')},
            {CellInfo::WATER, CellInfo(10, GREEN, 'w')},
            {CellInfo::WALL_WOOD, CellInfo(CellInfo::kNoCost, GREEN, 'x')},
            {CellInfo::WALL_STONE, CellInfo(CellInfo::kNoCost, GREEN, 'X')},
        }),
        target_file
    );
    while (app.isRunning()) {
        app.update();
        app.render();
    }
    return 0;
}
