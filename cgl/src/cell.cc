#include "cell.h"
using namespace cgl;

#include "world.h"

void Cell::update(World& world) {
    int count = 0;
    for (int i = x_ - 1; i <= x_ + 1; ++i) {
        for (int j = y_ - 1; j <= y_ + 1; ++j) {
            if (i != x_ || j != y_) {
                count += world.getCell(i, j).isAlive();
            }
        }
    }

    if (count < 2)
        alive_ = false;
    else if (count == 2)
        alive_ = world.getCell(x_, y_).isAlive();
    else if (count == 3)
        alive_ = true;
    else if (count > 3)
        alive_ = false;
}