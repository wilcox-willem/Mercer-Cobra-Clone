#include "huffman.h"
#include <iostream>
using namespace std;

HuffmanTree:: HuffmanTree()
	: numChars(0), built(false) {}

// inserts a character and its associated weight into a node of the Huffman tree
void HuffmanTree:: insert(char ch, int weight) {
    HNode newNode = {ch, weight, -1, -1}; 
    built = false;
    nodes.push_back(newNode);
    numChars++;

}

// returns a boolean value indicating whether a given character is stored in the tree
bool HuffmanTree:: inTree(char ch) {
	return (lookUp(ch) != -1);
}

// returns the weight of a given character
int HuffmanTree:: GetFrequency(char ch) {
	return GetFrequency(lookUp(ch));
}

// returns the weight at a given index 
int HuffmanTree:: GetFrequency(int i) {
	return nodes[i].weight;
}

// returns the index of a given character in tree
int HuffmanTree:: lookUp(char ch) {
	int index = -1;
	
	for (int i = 0; i <= nodes.size(); i++)
	{
		if (nodes[i].ch == ch)
			index = i;
	}
	return index;
}

// returns the compressed code of a given character in the tree using recursion
string HuffmanTree:: GetCode(char ch) {
	return GetCode(lookUp(ch));
}

// returns the compressed code of the character at a given index
string HuffmanTree:: GetCode(int i) {
	if (!built) {
        build();
    }

    if (nodes[i].parent == 0) {
        return "";
    }
    else {
        return (GetCode(nodes[i].parent) +
        (char)(nodes[i].childType+'0'));
    }
}

// displays the Huffman encoding table used in the compression process
void HuffmanTree:: PrintTable() {
	cout << "\t\t++++  ENCODING TABLE  ++++\n";
    printf("%-8s%-8s%-8s%-8s%-8s \n", "Index", "Char", "Weight", "Parent", "ChildType");	

	for (int i = 0; i < numChars * 2 - 1; i++)
	{
		int TNodes = 0;
		if ((nodes[i].ch != '\n') && (nodes[i].ch != ' ') && nodes[i].ch)
		{
			cout << "\t" << i << "\t" << nodes[i].ch << "\t";
			cout << nodes[i].weight << "\t" << nodes[i].parent;
			cout << "\t" << nodes[i].childType << "\n";
		}
		else if (nodes[i].ch == '\n')
		{
			cout << "\t" << i << "\tnl\t" << nodes[i].weight << "\t";
			cout << nodes[i].parent << "\t" << nodes[i].childType << "\n";
		}
		else if (nodes[i].ch == ' ')
		{
			cout << "\t" << i << "\tsp\t" << nodes[i].weight << "\t";
			cout << nodes[i].parent << "\t" << nodes[i].childType << "\n";
		}
		else if (i = (numChars * 2 - 2))
		{
			cout << "\t" << i << "\tT" << TNodes << "\t";
			cout << nodes[i].weight << "\t" << nodes[i].parent << "\t";
			cout << nodes[i].childType << "\n";
			TNodes++;
		}
		else
		{
			cout << "\t" << i << "\tT" << TNodes << "\t";
			cout << nodes[i].weight << "\t0\tN/A\n";
		}
	}
}

// returns the # of nodes currently in Huffman tree 
int HuffmanTree:: numNodes() {
	return nodes.size();
}

// builds the Huffman tree
void HuffmanTree:: build() {
	for (int i = 0; i < nodes.size(); i++)
	{
		if (compareWeight(i) != -1 && ((nodes[i].parent == -1 ||
		    nodes[compareWeight(i)].parent == -1)))
		{
			HNode newNode = {'\0', nodes[i].weight + 
					 nodes[compareWeight(i)].weight, -1, -1};
			nodes.push_back(newNode);
			nodes[i].parent = nodes.size() - 1;
			nodes[compareWeight(i)].parent =  nodes.size() - 1;
			i++;
			
			if (compareWeight(i) != -1)
			{
				nodes[i].parent = nodes.size() - 1;
				nodes[compareWeight(i)].parent = nodes.size() - 1;
			}
		}
	}
	
	// assigns left and right child for whole tree
	for (int i = 0; i <= nodes.size(); i++)
	{
		nodes[i].childType = 0;
		i++;
		nodes[i].childType = 1;
	}
	nodes[nodes.size() - 1].parent = 0;
	nodes[nodes.size() - 1].childType = -1;
}

// returns lesser or equal index
int HuffmanTree:: compareWeight(int i) {
	int index = -1;  // base case

	for (int j = 0; j <= nodes.size(); i++)
		if ((nodes[j].weight <= nodes[i].weight) && j != i)
			index = j;
	return index;
}

// returns the char at a given index
char HuffmanTree:: GetChar(int i) {
	return nodes[i].ch;
}

// returns the # of chars currently in Huffman Tree
int HuffmanTree:: GetNumChars() {
	return numChars;
}