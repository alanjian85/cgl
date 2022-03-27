#include <algorithm>
#include <chrono>

#include <ncurses.h>

#include "cell.h"
#include "world.h"
using namespace cgl;

int main() {
    using namespace std::literals;
    auto window = initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(window, TRUE);
    start_color();

    init_pair(0, COLOR_GREEN, COLOR_GREEN);

    World world(COLS, LINES);
    constexpr auto tick = 100ms;
    auto last_time = std::chrono::system_clock::now();
    bool quit = false, pause = true;
    int x = 0, y = 0;
    while (!quit) {
        switch (getch()) {
            case '\n':
                last_time = std::chrono::system_clock::now();
                pause = !pause;
                break;
            case 'q':
                quit = true;
                break;
            case KEY_UP:
                y -= 1;
                break;
            case KEY_DOWN:
                y += 1;
                break;
            case KEY_LEFT:
                x -= 1;
                break;
            case KEY_RIGHT:
                x += 1;
                break;
            case ' ':
                world.setCell(x, y, Cell(!world.getFrontCell(x, y).isAlive()));
                break;
        }
        x = std::clamp(x, 0, COLS);
        y = std::clamp(y, 0, LINES);

        auto curr_time = std::chrono::system_clock::now();
        if (!pause) {
            for (int i = 0; i < (curr_time - last_time) / tick; ++i) {
                world.update();
                last_time += tick;
            }
        }
        
        world.display();

        attron(COLOR_PAIR(0));
        mvaddch(y, x, ' ');
        attroff(COLOR_PAIR(0));
        
        refresh();
    }

    endwin();
    return 0;
}