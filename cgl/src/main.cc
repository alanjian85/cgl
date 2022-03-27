#include <chrono>
#include <thread>

#include <ncurses.h>

#include "cell.h"
#include "world.h"
using namespace cgl;

int main() {
    using namespace std::literals;
    initscr();
    World world(COLS, LINES);
    world.setCell(2, 1, Cell(true));
    world.setCell(3, 2, Cell(true));
    world.setCell(1, 3, Cell(true));
    world.setCell(2, 3, Cell(true));
    world.setCell(3, 3, Cell(true));
    for (;;) {
        world.update();
        world.display();
        refresh();
        std::this_thread::sleep_for(250ms);
    }
    return 0;
}