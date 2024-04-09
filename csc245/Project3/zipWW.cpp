#include <iostream>
#include <fstream>
#include <string>
#include "huffman.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 3) {
    cerr << "Error: Try using \"--help\"" << endl;
    return 0;
  }

  const char* commandArg1 = argv[1];
  const char* commandArg2 = argv[2];

  // Read the input file contents
  ifstream input_file(commandArg1, ios::in);
  if (!input_file.is_open()) {
    cerr << "ZIP: file sample: " << commandArg1 << endl;
    return 1;
  }

  string input_text;
  while (input_file) {
    string line;
    getline(input_file, line);
    input_text += line;
  }
  input_file.close();

  // Build the Huffman tree based on input text
  HuffmanTree huffmanTree;
  for (char ch : input_text) {
    huffmanTree.insert(ch); // Using overloaded insert, self-weighs
  }
  huffmanTree.build();

  // Encode the input text using Huffman codes
  string encoded_text;
  for (char ch : input_text) {
    encoded_text += huffmanTree.GetCode(ch);
  }

  // Write encoded text to the output file
  ofstream output_file(commandArg2, ios::out | ios::binary);
  if (!output_file.is_open()) {
    cerr << "Error opening output file: " << commandArg2 << endl;
    return 1;
  }

  // Write the Huffman tree information (character-code mappings)
  huffmanTree.PrintTable();

  // Write the encoded data to the output file
  output_file << encoded_text;

  output_file.close();

  cout << "File compressed successfully!" << endl;

  return 0;
}