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
    erase();
    display->print("Avengers", 15, 55);
    refresh();
    usleep(300000);

    while (true) {

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

        //the menu intro

        int choice = 1;

        while (true)
        {
            erase();

            display->print("Avengers", 1, 50);
            display->print("start", 14, 60);
            display->print("about", 23, 60);
            display->print("exit", 32, 60);

            //refresh();
            //usleep(300000);

            display->print("arrow", 5 + (9 * choice), 45);
            refresh();
            usleep(300000);

            inp = getch();
            if (inp == KEY_UP && choice != 1)
                choice -= 1;
            if (inp == KEY_DOWN && choice != 3)
                choice += 1;
            if (inp == KEY_ENTER || inp == 10)
                break;

        }
        if (choice == 3)
        {
            break;
        }
        else if (choice == 2)
        {
            //about
            erase();
            display->print("Storyline", 3, 15);

            inp = 0;
            while (inp != KEY_ENTER && inp != 10)
            {

                erase();
                display->print_line("Welcome to Avengers End Game, an engaging turn-based puzzle game that immerses you in the thrilling world of", 10, 15);
                display->print_line("the Avengers. In this game, you are Black Widow, a skilled fighter and strategist, battling against Hawkeye,", 11, 15);
                display->print_line("who is controlled by an advanced AI. Your mission is to outmaneuver the AI and ensure that it picks up the", 12, 15);
                display->print_line("last block in a game of strategy and cunning.", 13, 15);

                display->print("Game Overview", 15, 15);
                display->print_line("Avengers End Game is designed for single-player gameplay, allowing you to challenge yourself against a", 22, 15);
                display->print_line("computer-controlled opponent. The game is based on the classic Nim game, where two players take turns", 23, 15);
                display->print_line("removing blocks from pillars. However, this version adds unique elements related to the Avengers theme,", 24, 15);
                display->print_line("making it a fun and exciting experience.", 25, 15);

                display->print_line("Join Black Widow in this thrilling battle against Hawkeye. Use your strategic thinking and quick reflexes", 27, 15);
                display->print_line("to outsmart the AI and claim victory in Avengers End Game! Experience the excitement of the Avengers universe", 28, 15);
                display->print_line("while honing your skills in this captivating puzzle game. Good luck, and may the best strategist win!", 29, 15);
                refresh();
                usleep(300000);
                //inp = 0;
                //while (inp != KEY_ENTER && inp != 10)
                //{
                display->checkDisplaySize();
                inp = getch();

            }

            erase();
            display->print("How to Play", 3, 15);
            display->print_line("- Each player takes turns making their moves. You might start first or second randomly assigned, providing", 10, 15);
            display->print_line("competeition and uniquesituation to play the game.", 11, 15);
            display->print_line("- The game consists of a series of rounds where you and the AI alternate turns until all blocks are removed", 12, 15);
            display->print_line("from the pillars.", 13, 15);

            display->print_line("- The game features multiple pillars, each stacked with a varying number of blocks. The layout of these", 14, 15);
            display->print_line("pillars changes with different levels, adding to the challenge.", 15, 15);
            display->print_line("- Your goal is to manage these blocks wisely, anticipating the AI's moves while planning your own.", 16, 15);

            display->print("Making Move", 18, 15);
            display->print_line("- Selecting a Pillar: Use the left and right arrow keys to navigate through the available pillars. Each", 25, 15);
            display->print_line("pillar's height represents the number of blocks remaining in the pillar.", 26, 15);
            display->print_line("- Choosing the Number of Blocks: Once you have selected a pillar, use the up and down arrow keys to determine", 27, 15);
            display->print_line("how many blocks you wish to remove. The game will show the maximum number of blocks you can take in that turn,", 28, 15);
            display->print_line("ensuring you play within the rules.", 29, 15);
            display->print_line("- Confirming Your Decision: After making your selections, press 'Enter' to confirm your move. This will update", 30, 15);
            display->print_line("the game state and show the remaining blocks.", 31, 15);


            refresh();
            inp = 0;
            while (inp != 10 && inp != KEY_ENTER)   inp = getch();

            erase();

            display->print("AI Opponent", 3, 15);
            display->print_line("After your move, it’s Hawkeye’s turn. The AI has been designed using reinforcement learning, which means it", 10, 15);
            display->print_line("learns from previous games to improve its strategy. You will see a message indicating that the AI is thinking", 11, 15);
            display->print_line("about its next move. This adds an element of suspense as you wait to see what decision it makes.", 12, 15);

            display->print("Winning and Losing", 14, 15);
            display->print_line("The main objective of Avengers End Game is to force the AI to pick up the last block. If you manage to do this,", 21, 15);
            display->print_line("you win the game! However, if you are the one who removes the last block, you lose. This creates a tense", 22, 15);
            display->print_line("atmosphere as both players strive to outwit each other.", 23, 15);

            display->print("Level and Difficulty", 24, 15);
            display->print_line("Avengers End Game features three difficulty levels: Easy, Normal, Challenger. Each level presents distinct challenges", 31, 15);
            display->print_line("- Easy: The AI makes basic moves, allowing you to familiarize yourself with the game mechanics.", 32, 15);
            display->print_line("- Normal: The AI becomes more strategic, requiring you to think more critically about your moves.", 33, 15);
            display->print_line("- Challenger: The AI uses advanced tactics, making it a formidable opponent.", 34, 15);
            refresh();
            inp = 0;
            while (inp != KEY_ENTER && inp != 10)   inp = getch();



            erase();
            display->print("Contributors", 0, 27);
            display->print("Lohano Luv Kumar", 7, 11);
            display->print("Nalluri Parjany", 13, 12);
            display->print("Peng Zhenghui", 19, 27);
            display->print("Wang Aofei", 25, 37);
            display->print("Wang Lixiao", 31, 35);
            display->print("Mian Muneeb", 37, 34);
            inp = 0;
            while (inp != KEY_ENTER && inp != 10) {
                display->checkDisplaySize();
                inp = getch();
            }

            continue;
        }



        choice = 1;
        while (true) {
            erase();

            display->print("Choose a Level", 5, 15);
            display->print("easy", 14, 50);
            display->print("medium", 23, 50);
            display->print("hard", 32, 50);

            display->print("arrow", 5 + (9 * choice), 35);
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
            display->print("Choose your map", 2, 15);
            display->print("level1", 10, 15);
            display->print("level2", 16, 15);
            display->print("level3", 22, 15);
            display->print("level4", 28, 15);
            display->print("level5", 34, 15);
            display->print("level6", 10, 90);
            display->print("level7", 16, 90);
            display->print("level8", 22, 90);
            display->print("level9", 28, 90);
            display->print("level10", 34, 90);


            if (level < 6)
            {
                display->print("arrow", 4 + (level * 6), 0);
            }
            else
                display->print("arrow", 4 + ((level - 5) * 6), 75);

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

        erase();
        display->print("Game Ended", 15, 40);
        refresh();

    }

    endwin();
    return 0;
}
