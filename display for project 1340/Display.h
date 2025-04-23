#pragma once
#ifndef DISPLAY_Hs
#define DISPLAY_Hs

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

class display
{
	map<char, vector<string>> character;
	string filename = "structure.txt";

	void merge(vector<string>& title, const char& ch)
	{
		vector<string> chnew = character[ch];

		for (int i = 0; i < 8; i++)
		{
			title[i] += chnew[i];
		}
	}

	void print_line(vector<string> out)
	{
		for (const auto& line : out)
		{
			cout << line << endl;
		}
	}

public:
	display()
	{
		//store all the characters in the map

		ifstream file(filename);
		if (!file.is_open())
		{
			cerr << "Error opening file: " << filename << endl;
			return;
		}

		string line = "\n";
		for (char a = 'A'; a <= 'Z'; a++)
		{

			if (line.empty()) continue; // Skip empty lines
			
			for (int i = 0; i < 8; i++)
			{
				getline(file, line);
				if (line.empty()) continue; // Skip empty lines
				character[a].push_back(line);

			}
		}
		file.close();

	}

	void print(string title)
	{	
		vector<string> out(8);

		for (const char& ch: title)
		{
			merge(out, toupper(ch));
		}

		print_line(out);

	}
	

};

#endif