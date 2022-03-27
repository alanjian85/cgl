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

    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);

    World world(COLS, LINES);
    auto tick = 100ms;
    auto last_time = std::chrono::system_clock::now();
    bool quit = false, pause = true;
    int cursor_x = 0, cursor_y = 0;
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
                cursor_y -= 1;
                break;
            case KEY_DOWN:
                cursor_y += 1;
                break;
            case KEY_LEFT:
                cursor_x -= 1;
                break;
            case KEY_RIGHT:
                cursor_x += 1;
                break;
            case ' ':
                world.setCell(cursor_x, cursor_y, !world.getFrontCell(cursor_x, cursor_y).isAlive());
                break;
            case KEY_F(1):
                tick += 50ms;
                break;
            case KEY_F(2):
                if (tick > 50ms)
                    tick -= 50ms;
                break;
            case KEY_RESIZE:
                world.resize(COLS, LINES);
                break;
        }
        cursor_x = std::clamp(cursor_x, 0, world.getWidth() - 1);
        cursor_y = std::clamp(cursor_y, 0, world.getHeight() - 1);

        auto curr_time = std::chrono::system_clock::now();
        if (!pause) {
            for (int i = 0; i < (curr_time - last_time) / tick; ++i) {
                world.update();
                last_time += tick;
            }
        }
        
        for (int x = 0; x < world.getWidth(); ++x) {
            for (int y = 0; y < world.getHeight(); ++y) {
                if (x != cursor_x || y != cursor_y) {
                    if (world.getFrontCell(x, y).isAlive()) {
                        attron(COLOR_PAIR(0));
                        mvaddch(y, x, ' ');
                        attroff(COLOR_PAIR(0));
                    } else {
                        attron(COLOR_PAIR(1));
                        mvaddch(y, x, ' ');
                        attroff(COLOR_PAIR(1));
                    }
                }
            }
        }

        attron(COLOR_PAIR(2));
        mvaddch(cursor_y, cursor_x, ' ');
        attroff(COLOR_PAIR(2));
        
        refresh();
    }

    endwin();
    return 0;
}