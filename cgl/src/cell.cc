#include "cell.h"
using namespace cgl;

#include "world.h"

void Cell::update(World& world, int x, int y) {
    int count = 0;
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i >= 0 && i < world.getWidth() &&
                j >= 0 && j < world.getHeight() &&
                (i != x || j != y))
            {   
                count += world.getCell(i, j).isAlive();
            }
        }
    }

    if (count < 2)
        alive_ = false;
    else if (count == 2)
        alive_ = world.getCell(x, y).isAlive();
    else if (count == 3)
        alive_ = true;
    else if (count > 3)
        alive_ = false;
}