#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include "nim.h"
#include <vector>
#include "display.h"
#include <ncursesw/ncurses.h>
#include <unistd.h>


using namespace std;
//
//const int min_c = 150;
//const int min_r = 40;


int main() {

    //intro
        //cout<<"yes"<<endl;
    setlocale(LC_ALL, "");
    initscr();              // Start curses
    cbreak();               //Line buffering disabled
    noecho();               // Don't echo keypresses
    curs_set(0);            // Hide cursor
    keypad(stdscr, TRUE);   // Enable special keys
    nodelay(stdscr, TRUE);  // Non-blocking input
    //curs_set(0);            // hide curser

    //cout<<"yes"<<endl;
    Display* display = Display::instance();

    display->print("Avengers", 15, 15);
    refresh();
    usleep(300000);
    int inp = 0;
    while (inp != 10 && inp != KEY_ENTER)
    {
        inp = getch();

    }

    //endwin();
    //return 0;


    vector<int> map1 = { 1, 3, 5 };
    vector<int> map2 = { 3, 5, 7 };
    vector<int> map3 = { 5, 7, 9 };
    vector<int> map4 = { 1, 3, 5, 7 };
    vector<int> map5 = { 3, 5, 7, 9 };
    vector<int> map6 = { 5, 7, 9, 11 };
    vector<int> map7 = { 1, 3, 5, 7, 9 };
    vector<int> map8 = { 3, 5, 7, 9, 11 };
    vector<int> map9 = { 5, 7, 9, 11, 13 };
    vector<int> map10(6);  // Change to vector for dynamic sizing
    map10[0] = 2; map10[1] = 1; map10[2] = 1; map10[3] = 3;

    srand(static_cast<unsigned>(time(NULL)));
    for (int i = 0; i < 2; i++) {
        map10[4 + i] = rand() % 10 + 1;
    }

    //cout << "Choose a level to challenge" << endl;
    //cout << "1. Easy level" << endl;
    //cout << "2. Medium level" << endl;
    //cout << "3. Hard level" << endl;

    int choice = 1;
    while (true) {
        erase();

        display->print("Choose a Level", 5, 5);
        display->print("easy", 14, 10);
        display->print("medium", 23, 10);
        display->print("hard", 32, 10);

        display->print("arrow", 5 + (9 * choice));
        refresh();

        //endwin();
        //return 0;
        usleep(300000);
        inp = getch();
        if (inp == KEY_UP)
            choice -= 1;
        else if (inp == KEY_DOWN)
            choice += 1;
        if (choice < 1)
            choice = 1;
        else if (choice > 3)
            choice = 3;
        if (inp == 10 || inp == KEY_ENTER)
            break;
    }
    //endwin();
    //return 0;

    int text = choice;

    int level = 1;
    //cout << "Please choose your map from 1 to 10 (10 is a surprise!!):" << endl;
    //cin >> level;

    while (true)
    {
        erase();
        display->print("Choose your map", 2, 10);
        display->print("level1", 10, 10);
        display->print("level2", 16, 10);
        display->print("level3", 22, 10);
        display->print("level4", 28, 10);
        display->print("level5", 34, 10);
        display->print("level6", 10, 70);
        display->print("level7", 16, 70);
        display->print("level8", 22, 70);
        display->print("level9", 28, 70);
        display->print("level1", 34, 70);


        if (level < 6)
        {
            display->print("arrow", 4 + (level * 6), 0);
        }
        else
            display->print("arrow", 4 + ((level - 5) * 6), 60);

        refresh();
        usleep(300000);
        inp = getch();

        if (inp == KEY_UP && level != 1 && level != 6)
            level -= 1;
        else if (inp == KEY_DOWN && level != 10 && level != 5)
            level += 1;
        else if (inp == KEY_RIGHT && level < 6)
            level += 5;
        else if (inp == KEY_LEFT && level > 5)
            level -= 5;
        else if (inp == 10 || inp == KEY_ENTER)
            break;
    }

    display->selectCharacter();

    //endwin();
   // return 0;


    if (text == 1) {
        if (level == 1) {
            NimAI ai = train(5000, map1);
            play(ai, map1);
        }
        else if (level == 2) {
            NimAI ai = train(5000, map2);
            play(ai, map2);
        }
        else if (level == 3) {
            NimAI ai = train(5000, map3);
            play(ai, map3);
        }
        else if (level == 4) {
            NimAI ai = train(5000, map4);
            play(ai, map4);
        }
        else if (level == 5) {
            NimAI ai = train(5000, map5);
            play(ai, map5);
        }
        else if (level == 6) {
            NimAI ai = train(5000, map6);
            play(ai, map6);
        }
        else if (level == 7) {
            NimAI ai = train(5000, map7);
            play(ai, map7);
        }
        else if (level == 8) {
            NimAI ai = train(5000, map8);
            play(ai, map8);
        }
        else if (level == 9) {
            NimAI ai = train(5000, map9);
            play(ai, map9);
        }
        else if (level == 10) {
            NimAI ai = train(5000, map10);
            play(ai, map10);
        }
        else {
            display->error("Invalid input!");
        }
    }
    else if (text == 2) {
        if (level == 1) {
            NimAI ai = train(20000, map1);
            play(ai, map1);
        }
        else if (level == 2) {
            NimAI ai = train(20000, map2);
            play(ai, map2);
        }
        else if (level == 3) {
            NimAI ai = train(20000, map3);
            play(ai, map3);
        }
        else if (level == 4) {
            NimAI ai = train(20000, map4);
            play(ai, map4);
        }
        else if (level == 5) {
            NimAI ai = train(20000, map5);
            play(ai, map5);
        }
        else if (level == 6) {
            NimAI ai = train(20000, map6);
            play(ai, map6);
        }
        else if (level == 7) {
            NimAI ai = train(20000, map7);
            play(ai, map7);
        }
        else if (level == 8) {
            NimAI ai = train(20000, map8);
            play(ai, map8);
        }
        else if (level == 9) {
            NimAI ai = train(20000, map9);
            play(ai, map9);
        }
        else if (level == 10) {
            NimAI ai = train(20000, map10);
            play(ai, map10);
        }
        else {
            display->error("Invalid input!");
        }
    }
    else if (text == 3) {
        if (level == 1) {
            NimAI ai = train(100000, map1);
            play(ai, map1);
        }
        else if (level == 2) {
            NimAI ai = train(100000, map2);
            play(ai, map2);
        }
        else if (level == 3) {
            NimAI ai = train(100000, map3);
            play(ai, map3);
        }
        else if (level == 4) {
            NimAI ai = train(100000, map4);
            play(ai, map4);
        }
        else if (level == 5) {
            NimAI ai = train(100000, map5);
            play(ai, map5);
        }
        else if (level == 6) {
            NimAI ai = train(100000, map6);
            play(ai, map6);
        }
        else if (level == 7) {
            NimAI ai = train(100000, map7);
            play(ai, map7);
        }
        else if (level == 8) {
            NimAI ai = train(100000, map8);
            play(ai, map8);
        }
        else if (level == 9) {
            NimAI ai = train(100000, map9);
            play(ai, map9);
        }
        else if (level == 10) {
            NimAI ai = train(100000, map10);
            play(ai, map10);
        }
        else {
            display->error("Invalid input!");
        }
    }
    else {
        display->error("Invalid input!");
    }

    endwin();
    return 0;
}