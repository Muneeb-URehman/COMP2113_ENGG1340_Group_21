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

class Display
{
	
	const int row = 6;// to represent the number of rows for the characters used
	const string filename = "Alphabet.txt";// file storing characters
	const string facefile = "structure.txt";// file storing faces, and titles
	//minimun screen size for the game to run
	const int min_r = 40;
	const int min_c = 150;

	//data from the files are stored in these maps
 	map<char, vector<string>> character;
	map<string, vector<string>> faces;
	string player;
	vector<string> faceNames;// vector for the names of data collected from facefile for easy access
	
	int scr_row = 40;
	int scr_col = 150;

	void merge(vector<string>& title, const char& ch)//merges two characters from the character map
	{//input: takes a vector of already compiled characters, and character to add to the vector
		vector<string> chnew = character[ch];

		for (int i = 0; i < row; i++) // for each and every line of the title, it integrated the characters
		{
			title[i] += chnew[i];
		}
	}

	void print_line(vector<string> out, int row = 0, int column = 0) // the print statement on line with the title characters to be used by print(string, int, int)
	{// input: vector storing the statements to print, and the cordinates to print at
		for (const auto& line : out)
		{	
			mvwprintw(stdscr,row++, column, "%s", line.c_str());
		}
		
	}

	Display()	// initialization of the class
	{
		
		getmaxyx(stdscr, scr_row, scr_col);
		//store all the characters in the map

		checkDisplaySize();

		ifstream file(filename); // reads and stores data from filename
		if (!file.is_open()) // error handling for wrong file
		{
			mvprintw(scr_row / 3, scr_col / 2, "Error opening file: %s", filename.c_str());
			refresh();
			
			int inp = 0;
			while (inp != 10 || inp != KEY_ENTER)
				inp = getch();
			
		}

		string line = "\n";// adds the data
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
		for(int i = 0; i < row;i++)//adds empty space for " "
			character[' '].push_back("      ");
		file.close();

		ifstream face(facefile); // read and store data from facefile

		if (!face.is_open())//error handling for wrong file
		{
			mvprintw(scr_row / 2, scr_col / 3, "Error opening file: %s", facefile.c_str());
			refresh();
			int inp = 0;
			while (inp != KEY_ENTER)
				inp = getch();
			
		}


		while (!face.eof())//stores data to the map
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
	
	static Display* instance()//singleton for the Display class
	{//output: instance of the display class
		static Display* instance = new Display();
		
		return instance;

	}

	void print_line(string title, int r = 0, int c = 0) // to print normal text statement at (r, c)
	{// input: string title to print as line and coordinated to print at

		if (r == 0 && c == 0)
		{
			r = scr_row/3;
			c = scr_col/2;
		}
		//clear();
		mvprintw(r, c, "%s", title.c_str());
		

	}

	void print(string title, int r = 0, int c = 0) // to print title or face from character map
	{//input string title to print as title and coordinates
		checkDisplaySize();

		if (faces.find(title) != faces.end())// to find if the title is available in face map for example AI, faces, Level titles
		{
			if (r == 0 && c == 0)
		{
				
				c = (scr_col - faces[title][0].length())/2;
				r = scr_row/10;

			}
			for (const auto& line : faces[title])
			{
				mvprintw(r++,c,"%s",line.c_str());
			}
			refresh();

			return;
		}

		vector<string> out(row);

		for (const char& ch: title) // print title using the character map
		{
			if (character.find(toupper(ch)) != character.end())

				merge(out, toupper(ch));
			else
			{
				mvprintw(r++, c, "Error loading number %c",ch);
				refresh();
				int inp = 0;
				while (inp != KEY_ENTER)
					inp = getch();
			}
		}
		

		if (r == 0 && c == 0)//printing the statement using print_line()
		{

			r = scr_row/10;
			c = (scr_col - out[0].length())/2;
		}

		print_line(out, r, c);
	}

	void checkDisplaySize()// to check if the terminal is bigger than the minimum size 
	{

		int r, c;

		getmaxyx(stdscr, r, c);	
		while (r < min_r || c < min_c)
		{
			erase();
			mvprintw(r/2, c/4, "Make terminal size bigger");
			for (int i = 0; i < min_c; i++)
			{
				mvprintw(0, i, "*");
				mvprintw(min_r, i, "*");
			}
			for (int i = 1; i < min_r - 1; i++)
			{
				mvprintw(i, 0,"*");
				mvprintw(i, min_c, "*");
			}
			refresh();
			usleep(200000);
			getmaxyx(stdscr, r, c);
		}
	}
	
	void error(string title)//to print error on the screen if some is found
	{//string to display as error
		erase();
		print_line(title);
		int inp = 0;
		while (inp != KEY_ENTER)
			inp = getch();
	}

	void selectCharacter()// select characters from the user and stores it accordingly. 
	{
		int selection = 1;//represents the character selected by the user
		
		int inp;

		while (true)
		{
			erase();
			print("Select your one", 2, 10);
			//will have 6 characters with size 15 height and 23 width
		
			int row = 10, col = 20;
			for ( auto face:faces)// to print the characters on the screen
			{
				if (face.first.substr(0,4) != "Face")
				continue;
				print(face.first, row, col);
			
				col += 45;
				if (col > min_c - 30)
				{
					col = 20;
					row += 15;
				}
			}

		if (selection < 4)//print arrow on screen according to the position
		{
			print("arrow", 17, selection * 45 - 40);
		}
		else
		{
			print("arrow", 32, (selection - 3) * 45 - 40);
		}
		refresh();

		usleep(200000);

		inp = getch();

		if (inp == KEY_UP && selection > 3) // detect movement from user to control the arrow
			selection -= 3;
		else if (inp == KEY_DOWN && selection < 4)
			selection += 3;
		else if (inp == KEY_LEFT && selection != 1 && selection != 4)
			selection -= 1;
		else if (inp == KEY_RIGHT && selection != 3 && selection != 6)
			selection += 1;

		else if (inp == KEY_ENTER || inp == 10) // enter to make the selection
			break;
		player = faceNames[selection + 1];
		}
	//endwin();
	}

	void pile(int cur, int total, int height)//print the piles on the screen based on the height we have
	{//input: the current pile to print, the total number of piles available, and the height
		checkDisplaySize();
		// the pile will be between pixel between 20 on left to 120 on right
		//total height of pile will be about 30 with a number representing the size

		int posr = 30 - height;//initializing the positions and sizes of the pile
		int posc = (cur * 80 ) / total + 30;
		int endc = posc + 10;
		int endr = 30;

		for (int i = posr; i < endr;i++) //printing the pile on the screen
		{
			for (int j = posc; j < endc;j++)
			{
				if (i == posr)
					print_line("O", i, j);
				else
					print_line("U", i, j);
			}
		}
	}

	void arrow(int pile, int count, int total) // to print the arrow to represent the pile and height selected
	{//input: the pile the arrow is on, the height of the arrow, and the total number of piles
		checkDisplaySize();

		int posr = 30 - count;
		int posc = (pile * 80) / total + 26;

		print_line("-->", posr -1, posc+1);
	}

	void printcharacters() // print AI character and user selected character face on the screen during the game
	{
		int posr = 20;
		int posc = 0;

		print(player, posr, posc);

		print("AI", posr, 120);
		
	}

};

#endif
