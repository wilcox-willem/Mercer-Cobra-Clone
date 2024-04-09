#include "huffman.h"
#include <iostream>
using namespace std;

HuffmanTree:: HuffmanTree()
	: numChars(0), built(false) {}

void HuffmanTree:: insert(char ch, int weight) {
    HNode newNode = {ch, weight, -1, -1}; 
    built = false;
    nodes.push_back(newNode);
    numChars++;

}

bool HuffmanTree:: inTree(char ch) {


}

int HuffmanTree:: GetFrequency(char ch) {

}

int HuffmanTree:: GetFrequency(int i) {

}

int HuffmanTree:: lookUp(char ch) {

}

string HuffmanTree:: GetCode(char ch) {

}


string HuffmanTree:: GetCode(int i) {

}

void HuffmanTree:: PrintTable() {

}

int HuffmanTree:: numNodes() {

}

void HuffmanTree:: build() {

}
