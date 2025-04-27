#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <ncursesw/ncurses.h>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <string>
#include <unistd.h>

using namespace std;

const int row = 6;
const string filename = "Alphabet.txt";
const string facefile = "structure.txt";

//extern const int min_r = 40;
//extern const int min_c = 150;

//int scr_row = 40;
//int scr_col = 150;

class Display
{

    const int min_r = 40;
    const int min_c = 150;

    map<char, vector<string>> character;
    map<string, vector<string>> faces;
    string player;
    vector<string> faceNames;

    int scr_row = 40;
    int scr_col = 150;

    void merge(vector<string>& title, const char& ch)
    {
        vector<string> chnew = character[ch];

        for (int i = 0; i < row; i++)
        {
            title[i] += chnew[i];
        }
    }

    void print_line(vector<string> out, int row = 0, int column = 0)
    {
        for (const auto& line : out)
        {
            mvwprintw(stdscr, row++, column, "%s", line.c_str());
        }
        refresh();
    }

    Display()
    {

        getmaxyx(stdscr, scr_row, scr_col);
        //store all the characters in the map

        checkDisplaySize();

        ifstream file(filename);
        if (!file.is_open())
        {
            mvprintw(scr_row / 3, scr_col / 2, "Error opening file: %s", filename.c_str());
            refresh();

        }

        string line = "\n";
        for (char a = 'A'; a <= 'Z'; a++)
        {

            if (line.empty()) continue; // Skip empty lines

            for (int i = 0; i < row; i++)
            {
                getline(file, line);
                if (line.empty()) continue; // Skip empty lines
                character[a].push_back(line);

            }
        }
        for (int i = 0; i < row;i++)
            character[' '].push_back("      ");
        file.close();

        ifstream face(facefile);

        if (!face.is_open())
        {
            mvprintw(scr_row / 3, scr_col / 2, "Error opening file: %s", facefile.c_str());
            refresh();
            getch();

        }


        while (!face.eof())
        {
            string line, name;
            getline(face, name);
            faceNames.push_back(name);
            getline(face, line);

            while (!line.empty())
            {
                faces[name].push_back(line);
                getline(face, line);
            }
        }

    }


public:

    static Display* instance()
    {
        static Display instance;

        return &instance;

    }

    void print_line(string title, int r = 0, int c = 0)
    {

        if (r == 0 && c == 0)
        {
            r = scr_row / 3;
            c = scr_col / 2;
        }
        clear();
        mvprintw(r, c, "%s", title.c_str());
        refresh();

    }

    void print(string title, int r = 0, int c = 0)
    {
        checkDisplaySize();

        if (faces.find(title) != faces.end())
        {
            if (r == 0 && c == 0)
            {

                c = (scr_col - faces[title][0].length()) / 2;
                r = scr_row / 10;

            }
            for (const auto& line : faces[title])
            {
                mvprintw(r++, c, "%s", line.c_str());
                refresh();
            }

            return;
        }

        vector<string> out(row);

        for (const char& ch : title)
        {
            if (character.find(toupper(ch)) != character.end())

                merge(out, toupper(ch));
            else
                mvprintw(r++, c, "Error loading number %c", ch);

        }
        refresh();

        if (r == 0 && c == 0)
        {

            r = scr_row / 10;
            c = (scr_col - out[0].length()) / 2;
        }

        print_line(out, r, c);
        refresh();

    }

    void checkDisplaySize()
    {

        int r, c;

        getmaxyx(stdscr, r, c);
        while (r < min_r || c < min_c)
        {
            clear();
            mvprintw(r / 2, c / 4, "Make terminal size bigger");
            refresh();
            usleep(500000);
            getmaxyx(stdscr, r, c);
        }
    }

    void error(string title)
    {
        clear();
        print_line(title);
        sleep(1);
    }

    void selectCharacter()
    {
        int selection = 1;

        int inp;

        while (true)
        {
            clear();
            print("Select your one", 2, 5);
            //will have 6 characters with size 15 height and 23 width

            int row = 10, col = 25;
            for (auto face : faces)
            {
                if (face.first.substr(0, 4) != "Face")
                    continue;
                print(face.first, row, col);

                col += 40;
                if (col >= min_c - 40)
                {


                    col = 25;
                    row += 15;
                }

            }


            if (selection < 4)
            {
                print("arrow", 17, selection * 40 - 20);
            }
            else
            {
                print("arrow", 32, (selection - 3) * 40 - 20);
            }

            usleep(200000);

            inp = getch();

            if (inp == KEY_UP && selection > 3)
                selection -= 3;
            else if (inp == KEY_DOWN && selection < 4)
                selection += 3;
            else if (inp == KEY_LEFT && selection != 1 && selection != 4)
                selection -= 1;
            else if (inp == KEY_RIGHT && selection != 3 && selection != 6)
                selection += 1;

            else if (inp == KEY_ENTER || inp == 10)
                break;
            player = faceNames[selection];
        }
        endwin();

    }

};

#endif