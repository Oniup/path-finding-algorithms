#include "World.h"

#include "fmt/base.h"
#include <cstdio>
#include <string>

namespace path_finding {

World::World(CellTypeMap cell_type)
    : map_path_(), cell_types_(cell_type), cells_(m_width)
{
    for (CellInfo::Type &type : cells_) {
        type = CellInfo::CLEAR;
    }
}

bool World::loadFromMap(const std::string_view &path)
{
    std::FILE *stream = std::fopen(path.data(), "r");
    if (!stream) {
        fmt::println("Failed to open file {}", path);
        return false;
    }

    enum class Stage {
        GET_WORLD_SIZE,
        GET_START_AND_END,
        FILL_WORLD_CELLS,
    };

    int start, end, width, height;
    std::vector<char> map_data;

    constexpr int MAX_BUFFER_SIZE = 1024;
    char line_buffer[MAX_BUFFER_SIZE];
    Stage stage = Stage::GET_WORLD_SIZE;
    while (std::fgets(line_buffer, MAX_BUFFER_SIZE, stream) != NULL) {
        size_t length = strlen(line_buffer);
        // Skip if there is nothing at the line or if there is a comment
        if (length == 0 || line_buffer[0] == '#') {
            continue;
        }

        switch (stage) {
        case Stage::GET_WORLD_SIZE: {
            char num_str_buffer[MAX_BUFFER_SIZE];
            int j = 0;
            bool fill_width = true;
            for (size_t i = 0; i < length; i++) {
                if (line_buffer[i] == ' ') {
                    if (j == 0) {
                        continue;
                    }
                    num_str_buffer[j + 1] = '\0';
                    if (fill_width) {
                        width = std::atoi(num_str_buffer);
                        j = 0;
                        fill_width = false;
                        continue;
                    }
                    height = std::atoi(num_str_buffer);
                    stage = Stage::GET_START_AND_END;
                    break;
                }
                if (line_buffer[i] <= '9' && line_buffer[i] >= '0') {
                    num_str_buffer[j] = line_buffer[i];
                    j++;
                }
            }
            break;
        }
        case Stage::GET_START_AND_END:
            break;
        case Stage::FILL_WORLD_CELLS:
            break;
        }
    }

    std::fclose(stream);
    return true;
}

Cell World::getCell(int x, int y) const
{
    size_t index = y + x * m_width;
    CellInfo::Type type = cells_[index];
    const CellInfo *info = &cell_types_.at(type);
    return Cell{type, info, x, y};
}

void World::changeCellType(int x, int y, CellInfo::Type type)
{
    size_t index = y + x * m_width;
    cells_[index] = type;
}

void World::update() {}

void World::render() {}

void reset();

} // namespace path_finding
