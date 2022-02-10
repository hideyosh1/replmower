#include <ncurses.h>

int main() {
  initscr();
  cbreak();
	curs_set(1);

  endwin();
  return 0;
}