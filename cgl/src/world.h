#ifndef CGL_WORLD_H_
#define CGL_WORLD_H_

#include <vector>

#include <ncurses.h>

#include "cell.h"

namespace cgl {
    class World {
    public:
        World(int width, int height)
        {
            width_ = width;
            height_ = height;
            front_buffer_ = &cells_[0];
            back_buffer_ = &cells_[1];
            cells_[0].resize(width * height);
            cells_[1].resize(width * height);
            init_pair(1, COLOR_BLACK, COLOR_BLACK);
            init_pair(2, COLOR_WHITE, COLOR_WHITE);
        }

        int getWidth() const {
            return width_;
        }

        int getHeight() const {
            return height_;
        }

        void setCell(int x, int y, Cell cell) {
            (*front_buffer_)[y * width_ + x] = cell;
        }

        Cell getCell(int x, int y) {
            return (*back_buffer_)[y * width_ + x];
        }

        Cell& getFrontCell(int x, int y) {
            return (*front_buffer_)[y * width_ + x];
        }

        void update() {
            std::swap(front_buffer_, back_buffer_);
            for (int x = 0; x < width_; ++x) {
                for (int y = 0; y < height_; ++y) {
                    getFrontCell(x, y).update(*this, x, y);
                }
            }
        }

        void display() {
            for (int x = 0; x < width_; ++x) {
                for (int y = 0; y < height_; ++y) {
                    if (getFrontCell(x, y).isAlive()) {
                        attron(COLOR_PAIR(1));
                        mvaddch(y, x, ' ');
                        attroff(COLOR_PAIR(1));
                    } else {
                        attron(COLOR_PAIR(2));
                        mvaddch(y, x, ' ');
                        attroff(COLOR_PAIR(2));
                    }
                }
            }
        }
    private:
        int width_;
        int height_;
        std::vector<Cell>* front_buffer_;
        std::vector<Cell>* back_buffer_;
        std::vector<Cell> cells_[2];
    };
}

#endif // CGL_WORLD_H_