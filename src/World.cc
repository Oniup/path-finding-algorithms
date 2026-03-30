#include "World.h"

#include "fmt/base.h"
#include <cstdio>
#include <string>

#define MAX_BUFFER_SIZE 1024

namespace path_finding {

bool readTwoNumbersFromLine(
    const char *line, size_t length, int &first, int &second
)
{
    char num_str_buffer[MAX_BUFFER_SIZE];
    int j = 0;
    bool fill_width = true;
    for (size_t i = 0; i < length; i++) {
        if (line[i] <= '9' && line[i] >= '0') {
            num_str_buffer[j] = line[i];
            j++;
        }
        else {
            if (j == 0) {
                continue;
            }
            num_str_buffer[j] = '\0';
            if (fill_width) {
                first = std::atoi(num_str_buffer);
                j = 0;
                fill_width = false;
                continue;
            }
            second = std::atoi(num_str_buffer);
            return true;
        }
    }
    return false;
}

World::World(CellTypeMap cell_type)
    : map_path_(), cell_types_(cell_type), cells_(m_width)
{
    for (CellInfo::Type &type : cells_) {
        type = CellInfo::CLEAR;
    }
}

bool World::loadMapFromSource(const std::string_view &path)
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

    char line_buffer[MAX_BUFFER_SIZE];
    Stage stage = Stage::GET_WORLD_SIZE;
    while (std::fgets(line_buffer, MAX_BUFFER_SIZE, stream) != NULL) {
        size_t length = strlen(line_buffer);
        // Skip if there is nothing at the line or if there is a comment
        if (length == 0 || line_buffer[0] == '#') {
            continue;
        }

        switch (stage) {
        case Stage::GET_WORLD_SIZE:
            if (readTwoNumbersFromLine(line_buffer, length, width, height)) {
                stage = Stage::GET_START_AND_END;
                map_data.reserve(width * height);
            }
            break;
        case Stage::GET_START_AND_END:
            if (readTwoNumbersFromLine(line_buffer, length, start, end)) {
                size_t map_size = width * height;
                if (start < map_size && start >= 0 && end < map_size &&
                    end >= 0)
                {
                    stage = Stage::FILL_WORLD_CELLS;
                }
            }
            break;
        case Stage::FILL_WORLD_CELLS:
            break;
        }
    }

    fmt::println(
        "World Size: {},{}\nStart: {}, End: {}", width, height, start, end
    );

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

void World::reset() {}

} // namespace path_finding
