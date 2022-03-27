#include "world.h"
using namespace cgl;

World::World(int width, int height) {
    width_ = width;
    height_ = height;
    front_buffer_ = &cells_[0];
    back_buffer_ = &cells_[1];
    cells_[0].resize(width * height);
    cells_[1].resize(width * height);
    for (int x = 0; x < width_; ++x) {
        for (int y = 0; y < height_; ++y) {
            (*front_buffer_)[y * width_ + x] = Cell(false, x, y);
            (*back_buffer_)[y * width_ + x] = Cell(false, x, y);
        }
    }
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
}

void World::update() {
    for (int x = 0; x < width_; ++x) {
        for (int y = 0; y < height_; ++y) {
            (*front_buffer_)[y * width_ + x].update(*this);
        }
    }
    std::swap(front_buffer_, back_buffer_);
}

void World::display() {
    for (int x = 0; x < width_; ++x) {
        for (int y = 0; y < height_; ++y) {
            if ((*front_buffer_)[y * width_ + x].isAlive()) {
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