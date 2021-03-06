#include "world.h"
using namespace cgl;

World::World(int width, int height) {
    width_ = width;
    height_ = height;
    front_buffer_ = &cells_[0];
    back_buffer_ = &cells_[1];
    cells_[0].resize(width * height);
    cells_[1].resize(width * height);
    clear();
}

void World::clear() {
    for (int x = 0; x < width_; ++x) {
        for (int y = 0; y < height_; ++y) {
            (*front_buffer_)[y * width_ + x] = Cell(false, x, y);
            (*back_buffer_)[y * width_ + x] = Cell(false, x, y);
        }
    }
}

void World::resize(int width, int height) {
    auto old_width = width_;
    auto old_height = height_;
    auto old_front_buffer = *front_buffer_;
    auto old_back_buffer = *back_buffer_;
    width_ = width;
    height_ = height;
    cells_[0].resize(width * height);
    cells_[1].resize(width * height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (x < old_width && y < old_height) {
                (*front_buffer_)[y * width_ + x] = old_front_buffer[y * old_width + x];
                (*back_buffer_)[y * width_ + x] = old_back_buffer[y * old_width + x];
            } else {
                (*front_buffer_)[y * width_ + x] = Cell(false, x, y);
                (*back_buffer_)[y * width_ + x] = Cell(false, x, y);
            }
        }
    }
}

void World::update() {
    for (int x = 0; x < width_; ++x) {
        for (int y = 0; y < height_; ++y) {
            (*front_buffer_)[y * width_ + x].update(*this);
        }
    }
    std::swap(front_buffer_, back_buffer_);
}