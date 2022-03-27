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
    world.setCell(1, 1, Cell(true));
    world.setCell(2, 1, Cell(true));
    world.setCell(3, 1, Cell(true));
    for (;;) {
        world.update();
        world.display();
        refresh();
        std::this_thread::sleep_for(1s);
    }
    return 0;
}