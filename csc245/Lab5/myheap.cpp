// Willem Wilcox, CSC245, Dr. Digh, MU. 10/22/23
//Lab 5, this is the client file "myheap.cpp"
#include <iostream>
#include <string>
#include "BinaryHeap.h"

using namespace std;

int main() {
 	BinaryHeap<char> PQ(50);
	char currentChar = 'A';

  // Insert A->J into BinHeap "PQ"
	for (int i = 0; i < 10; i++){
 		PQ.insert(currentChar++);	
	}

  PQ.deleteMin();
  
  // Print demonstration
  cout << "Printing Left Subtree of the Root of Heap: ";
  PQ.printLtSubtree();
  cout << endl;
  cout << "The Height of Heap Is: " << PQ.Height() << endl;
  cout << "The Maximum Value of Heap Is: " << PQ.findMax() << endl;

  return 0;
}