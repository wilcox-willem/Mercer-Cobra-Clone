#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include <fstream>
#include "huffman.h"

using namespace std;

void CheckInput(ifstream& file, int argc, char* argv[]);
void Unzip(map<string, char>& M, ifstream& file, string line, string code, 
	   string answer, char *argv[]);

int main(int argc, char *argv[])
{
	// initialize files to be reas, a string that holds file input 
	ifstream file;
	string line;
	string code;	// char codes
	string answer;	

	// initializes map
	map<string, char> M;
	
	CheckInput(file, argc, argv);
	Unzip(M, file, line, code, answer, argv);
	
	// print message letting user know unzip was successful
	cout << "File Successfully Inflated Back to Original." << endl;

	return 0;
}

// function Unzip, using maps this fucntion does most of the actual unzipping of 
// the file
void Unzip(map<string, char>& M, ifstream& file, string line, string code,
	   string answer, char *argv[])
{
	int title;
	int ASCII;
	file >> title;

	// for loop that converts the ASCII codes back to chars
	for (int i = 0; i < title; i++)
	{
		file >> ASCII >> code;
		M[code] = (char) ASCII;
	}
	file >> answer;
	file.close();
	ofstream outfile;
	string name = argv[1];
	name = name.substr(0, name.find("."));
	string index;
	outfile.open(name.c_str());

	// initialize variables for manipulating the subtring positions
	int pos = 0;
	int end = 1;
	
	// for loop that traverses the binary and converts it back to its uncompressed
	// form
	for (int i = 0; i < answer.length(); i++)
	{
		// conditional that checks if a given index is the last index
		index = answer.substr(pos, end);
		if (!(M.find(index) == M.end()))
		{
			outfile << M.at(index);
			pos = i + 1;
			end = 1;
		}
		else
			end++;
	}
	outfile.close();
}

// function CheckInput, checks the command line input: 1) was there a file name
// entered after execution? 2) does the file have the .zip extention?
void CheckInput(ifstream& file, int argc, char* argv[])
{
	// (error handling) conditional that checks if there is file input to console
	if (argc == 1)
	{
		cout << "No file entered." << endl;
		exit(1);
	}

	// string for storing file name
	string name = argv[1];
	file.open(name.c_str());
	
	// string that holds the file's extension after the dot
	string extension = name.substr(name.find("."), 3);

	// (error handling) conditional that checks if file is zipped
	if (extension == "zip")
	{
		cout << "File not zipped!" << endl;
		exit(1);
	}
}