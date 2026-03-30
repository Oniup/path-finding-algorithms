#ifndef _PATH_FINDING_WORLD_H_
#define _PATH_FINDING_WORLD_H_

#include <limits>
#include <raylib.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace path_finding {

struct CellInfo {
    enum Type : size_t {
        CLEAR,
        PATH,
        MUD,
        WATER,
        WALL_WOOD,
        WALL_STONE,
    };

    static constexpr int kNoCost = std::numeric_limits<int>::max();

    int cost;
    Color color;
    char serialized;
};

struct Cell {
    CellInfo::Type type;
    const CellInfo *info;
    int x;
    int y;
};

// This is a comment and is ignored
// First specify the width x height values
// 5
// Second specify the start and target box indexes
// 17
// Now specify each row of column values
// . . . . .
// ~ X . . .
// ~ X ~ . .
// . X . . .
// m m m . .
// Note the number of rows and column values match
class World {
public:
    using CellTypeMap = std::unordered_map<CellInfo::Type, CellInfo>;

public:
    World(CellTypeMap cell_type);

public:
    bool loadFromMap(const std::string_view &path);

    Cell getCell(int x, int y) const;
    void changeCellType(int x, int y, CellInfo::Type type);

    void update();
    void render();
    void reset();

private:
    std::string map_path_;
    CellTypeMap cell_types_;

    int m_width = 5;
    std::vector<CellInfo::Type> cells_;
};

} // namespace path_finding

#endif
