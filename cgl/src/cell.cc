#include "cell.h"
using namespace cgl;

#include "world.h"

void Cell::update(World& world, int x, int y) const {
    int count = 0;
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i >= 0 && i < world.getWidth() &&
                j >= 0 && j < world.getHeight())
            {
                count += world.getCell(i, j).isAlive();
            }
        }
    }

    if (count < 2)
        world.setCell(x, y, Cell(false));
    else if (count == 3)
        world.setCell(x, y, Cell(true));
    else if (count > 3)
        world.setCell(x, y, Cell(false));
}