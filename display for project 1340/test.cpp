#include "Display.h"
#include <iostream>

using namespace std;

int main()
{
	display d;

	d.print("thanos");
	d.print("vs");
	d.print("cap america");
	d.print("Face1");
	d.print("Avengers");


	return 0;
}

#include <ncursesw/ncurses.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unistd.h> // for usleep
#include "display.h"
struct Object {
    int x, y;
};

int main() {

    setlocale(LC_ALL, "");
    initscr();              // Start curses
    cbreak();               //Line buffering disabled
    noecho();               // Don't echo keypresses
    curs_set(0);            // Hide cursor
    keypad(stdscr, TRUE);   // Enable special keys
    //nodelay(stdscr, TRUE);  // Non-blocking input
    curs_set(0);            // hide curser

    Display display;

    display.print("card", 5, 5);
    display.print("Avengers", 15, 7);
    display.print("level1", 25, 10);
    getch();
    endwin();

    return 0;
}