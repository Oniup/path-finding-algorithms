#include "Application.h"
#include "World.h"

using namespace path_finding;

int main(int argc, char **argv)
{
    Application app(
        "Learning Path Finding",
        World::CellTypeMap({
            {CellInfo::CLEAR, CellInfo(2, RAYWHITE, '.')},
            {CellInfo::PATH, CellInfo(1, GREEN, 'p')},
            {CellInfo::MUD, CellInfo(5, GREEN, 'm')},
            {CellInfo::WATER, CellInfo(10, GREEN, 'w')},
            {CellInfo::WALL_WOOD, CellInfo(CellInfo::kNoCost, GREEN, 'x')},
            {CellInfo::WALL_STONE, CellInfo(CellInfo::kNoCost, GREEN, 'X')},
        })
    );
    while (app.isOPen()) {
        app.updateLoop();
        app.render();
    }
    return 0;
}
