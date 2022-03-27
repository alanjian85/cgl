#include <chrono>
#include <thread>

#include <ncurses.h>

#include "cell.h"
#include "world.h"
using namespace cgl;

int main() {
    using namespace std::literals;
    auto window = initscr();
    nodelay(window, TRUE);
    World world(COLS, LINES);
    world.setCell(2, 1, Cell(true));
    world.setCell(3, 2, Cell(true));
    world.setCell(1, 3, Cell(true));
    world.setCell(2, 3, Cell(true));
    world.setCell(3, 3, Cell(true));
    
    bool quit = false;
    bool paused = false;
    while (!quit) {
        switch (getch()) {
            case ' ':
                paused = !paused;
                break;
            case 'q':
                quit = true;
                continue;
                break;
        }

        if (!paused) {
            world.update();
        }
        world.display();
        refresh();
        std::this_thread::sleep_for(250ms);
    }

    endwin();
    return 0;
}