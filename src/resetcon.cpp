#include <ncurses.h>

int main() {
  initscr();
  cbreak();

  endwin();
  return 0;
}