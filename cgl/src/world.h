#ifndef CGL_WORLD_H_
#define CGL_WORLD_H_

#include <vector>

#include "cell.h"

namespace cgl {
    class World {
    public:
        World(int width, int height)
            : cells_(width * height)
        {
            width_ = width;
        }

        void setCell(int x, int y, Cell cell) {
            cells_[y * width_ + x] = cell;
        }

        Cell getCell(int x, int y) const {
            return cells_[y * width_ + x];
        }
    private:
        int width_;
        std::vector<Cell> cells_;
    };
}

#endif // CGL_WORLD_H_