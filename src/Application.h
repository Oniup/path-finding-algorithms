#ifndef _PATH_FINDING_APPLICATION_H_
#define _PATH_FINDING_APPLICATION_H_

#include "World.h"

namespace path_finding {

class Application {
public:
    Application(
        const std::string_view &title, World::CellTypeMap &&cell_types,
        const std::string_view &map_path, int window_size = 1
    );
    ~Application();

public:
    bool isRunning();
    void update();
    void render();

    inline int getWindowSize() const { return window_size_; }
    const World &getWorld() const { return world_; }
    World &getWorld() { return world_; }

private:
    int window_size_;
    World world_;
};

} // namespace path_finding

#endif
