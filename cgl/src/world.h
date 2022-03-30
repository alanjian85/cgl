#ifndef CGL_WORLD_H_
#define CGL_WORLD_H_

#include <vector>

#include <ncurses.h>

#include "cell.h"

namespace cgl {
    class World {
    public:
        World(int width, int height);

        void resize(int width, int height);

        void clear();

        int getWidth() const {
            return width_;
        }

        int getHeight() const {
            return height_;
        }

        void setCell(int x, int y, bool alive) {
            (*front_buffer_)[y * width_ + x].setAlive(alive);
            (*back_buffer_)[y * width_ + x].setAlive(alive);
        }

        Cell& getCell(int x, int y) {
            x = (x % width_ + width_) % width_;
            y = (y % height_ + height_) % height_;
            return (*back_buffer_)[y * width_ + x];
        }

        Cell& getFrontCell(int x, int y) {
            x %= width_;
            y %= height_;
            return (*front_buffer_)[y * width_ + x];
        }

        void update();
    private:
        int width_;
        int height_;
        std::vector<Cell>* front_buffer_;
        std::vector<Cell>* back_buffer_;
        std::vector<Cell> cells_[2];
    };
}

#endif // CGL_WORLD_H_