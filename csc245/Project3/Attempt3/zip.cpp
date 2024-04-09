#include <cctype>
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include "huffman.h"

using namespace std;

void Weight(ifstream& infile, int Letters[], int argc, char *argv[], int source, string& s);
void InsertChars(const int Letters[], HuffmanTree& t, int header);
void Zip(ifstream& infile, int argc, char *argv[], int Letters[256], HuffmanTree& t, int source, string& s, int header);

int main(int argc, char *argv[]) {
        string s;
        int source = 0;
        int header = 0;
        int Letters[256];
        string i;

	// check if a file was recived
        if(argc > 1)
                i = argv[1];
        
        HuffmanTree t;
        ifstream infile;

	// if no file recived throw error and exit program, else if check for 
	// additional command line arguments, else build tree and compress file
        if(argc <= 1) {
                cout << "Error!! No File Entered." << endl;
                exit(1);
        }
        else if(i.compare("--help") == 0) {
                infile.open("help");
                string in;
                
		// while file has input
		while(!infile.eof()) {
                        getline(infile, in);
                        cout << in << endl;
                }

                exit(1);
        }
        else {
                Weight(infile, Letters, argc, argv, source, s);
                InsertChars(Letters, t, header);
                t.build();
                Zip(infile, argc, argv, Letters, t, source, s, header);
        }

        return 0;
}

// function Weight, calculates the weight and counts the occurence of 
// different chars in a file so it determines the weight of a char
void Weight (ifstream& infile, int Letters[], int argc, char* argv[], int source, string& s) {
        string name;
        char ch;
        
        if(argc > 2)
                name = argv[2];
        else
                name = argv[1];
        
        infile.open(name.c_str());
        
        for (char ch = char(0);  ch <= char(126);  ch++)
                Letters[ch] = 0;

        infile.get(ch);
        
        while (infile) {
                Letters[ch]++;
                s += ch;
                infile.get(ch);
        }
        
        infile.close();
}

// function InsertChars, inserts the chars into huffman tree along with their
// respective weights
void InsertChars(const int Letters[], HuffmanTree& t, int header) {
        for (char ch = char(0);  ch <= char(126);  ch++)         {
                if ((Letters[ch] != 0) && (ch != '\n') && (ch != ' ')) {
                        t.insert(ch, Letters[ch]);
                        header++;
                }
                else if ((Letters[ch] != 0) && (ch == '\n')) {
                        t.insert('^', Letters[ch]);
                        header++;
                }
                else if ((Letters[ch] != 0) && (ch == ' ')) {
                        t.insert('$', Letters[ch]);
                        header++;
                }
        }
}

// function Zip, main compressions algorithm for the zip 
void Zip(ifstream& infile, int argc, char *argv[], int Letters[256], HuffmanTree& t,
	 int source, string& s, int header) {
        int zip = 0;
        float ratio;
        int i, j;
        string input = argv[1];
        string name;

	// checks for additional command line arguments, sets file name accordingly
	if(argc > 2)
                name = argv[2];
        else
                name = argv[1];
        
        infile.open(name.c_str());
        
	// if file entered does not exist exit program, else continue
	if(infile.fail()) {
                cout << "ZIP: Invalid input\nTry 'ZIP --help' for more information.\n" << endl;
                exit(1);
        }
        else {
                header = t.numNodes() - (t.numNodes() / 2);
                
                // appends '.zip' to the file name
                name += ".zip";
                ofstream outfile;
                outfile.open(name.c_str());
                outfile << header << endl;
                
	// for loop that compresses each char; multiple differnt cases handled
	for (char ch = char(0);  ch <= char(126);  ch++)
        {
            	if ( (Letters[ch] != 0) && (ch != '\n') && (ch != ' ') )
                {
                 	outfile << (int)ch << " " << t.GetCode(ch) << endl;
                        source++;
                }
                else if ( (Letters[ch] != 0) && (ch == '\n') )
                {
                        outfile << (int)ch << " "<< t.GetCode('^') << endl;
                        source++;
                }
                else if ( (Letters[ch] != 0) && (ch == ' ') )
                {
                        outfile << (int)ch << " " << t.GetCode('$') << endl;
                        source++;
                }
        }

	// if --t is entered print huffman encoding table
	if(input.compare("--t") == 0 && argc > 2) t.PrintTable();
                
                char currChar;
                
                for(int i = 0; i < s.length(); i++)
                {
                        currChar = s[i];
                        outfile << t.GetCode(currChar);

                        int bitsUsed = 
                        zip++;
                }
                
                outfile << endl;
                outfile.close();
                ratio = (1 - (float)(zip / ((float)source * 8))) * 100;
                
                cout << "File Successfully zip to " << zip << " Bits (" << ratio << "% Less)" << endl;
        }
}