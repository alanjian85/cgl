#include <ncurses.h>

#include "cell.h"

int main() {
    initscr();
    printw("Hello world!");
    refresh();
    return 0;
}