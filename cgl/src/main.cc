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

    constexpr auto tick = 100ms;
    auto last_time = std::chrono::system_clock::now();
    bool quit = false, pause = true;
    while (!quit) {
        switch (getch()) {
            case ' ':
                last_time = std::chrono::system_clock::now();
                pause = !pause;
                break;
            case 'q':
                quit = true;
                break;
        }

        auto curr_time = std::chrono::system_clock::now();
        if (!pause) {
            for (int i = 0; i < (curr_time - last_time) / tick; ++i) {
                world.update();
                last_time += tick;
            }
        }
        world.display();
        refresh();
    }

    endwin();
    return 0;
}