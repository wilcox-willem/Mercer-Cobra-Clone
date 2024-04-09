#include "huffman.h"
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

// HNode Code for reference!
// struct HNode {
//     char ch;
//     int weight;
//     int parent;
//     int childType;
// };

// Private (Priv)
// vector<HNode> nodes;
// int numChars;
// bool built; 
// 
// int lookUp(char ch);
// int GetFrequency(int i);
// string GetCode(int i);  

HuffmanTree:: HuffmanTree()
	: numChars(0), built(false) {}

void HuffmanTree:: insert(char ch, int weight) {
    HNode newNode = {ch, weight, -1, -1}; 
    built = false;
    nodes.push_back(newNode);
    numChars++;
}

void HuffmanTree:: insert(char ch) {
    if (!inTree(ch)){
        HNode newNode = {ch, 1, -1, -1}; 
        nodes.push_back(newNode);
        numChars++;
    } else {
        int thisCharIndex = lookUp(ch);
        if (thisCharIndex > -1) {
            nodes[thisCharIndex].weight += 1;
        }
    }

    built = false;
}


bool HuffmanTree:: inTree(char ch) {
    for (const HNode &node : nodes) {
        if (node.ch == ch) {
            return true;
        }
    }
    return false;
}

int HuffmanTree:: GetFrequency(char ch) {
    if (inTree(ch)) {
        return GetFrequency(lookUp(ch));
    }
    return 0; // Return 0 if character not found
}

// Priv
int HuffmanTree:: GetFrequency(int i) {
    if (i >= 0 && i < nodes.size()) {
        return nodes[i].weight;
    }
    return 0; // Return 0 if index is out of range
}

// Priv
int HuffmanTree:: lookUp(char ch) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].ch == ch) {
            return i;
        }
    }
    return -1; // Return -1 if character not found
}

string HuffmanTree::GetCode(char ch) {
    if (!built) {
        build();
    }
    int index = lookUp(ch);
    if (index != -1) {
        return GetCode(index);
    }
    return ""; // Return empty string if character not found
}

// Priv
string HuffmanTree::GetCode(int i) {
    if (nodes[i].parent == 0) {
        return "";
    }
    else {
        return (GetCode(nodes[i].parent) +
        (char)(nodes[i].childType+'0'));
    }
}

// NEEDS WORK
void HuffmanTree:: PrintTable() {
    // to be used later for counting non-leaf nodes
    int noncharNodeCount = 1;

    cout << "     ++++    ENCODING TABLE    +++++" << endl << endl;
    printf("%-8s%-8s%-8s%-8s%-8s \n", "Index", "Char", "Weight", "Parent", "ChildType");

    for (int i = 0; i < nodes.size(); i++){
        int pIndex = i;
        string pChar = "";
        int pWeight = nodes[i].weight;
        int pParent = nodes[i].parent;
        int childType = nodes[i].childType;

        // adjust pChar incase non A-z char
        if (isalpha(nodes[i].ch)) {
            pChar = nodes[i].ch;
        } else if (nodes[i].ch == '\n') {
            pChar = "nl";
        } else if (nodes[i].ch == ' ') {
            pChar = "sp";
        } else {
            pChar = "T" + to_string(noncharNodeCount++); // Non-leaf nodes labeled as "T#"
        }

       printf("%-8d%-8s%-8d%-8d%-8d \n", pIndex, pChar.c_str(), pWeight, pParent, childType);

    }


}

// NEEDS WORK
// Not sure if numNodes is just chars or chars and totals?
int HuffmanTree::numNodes() {
    return numChars;
}



// NEEDS WORK
void HuffmanTree::build() {
    // Create a priority queue (min-heap) for the nodes
     // Create a priority queue (min-heap) for the nodes
    priority_queue<HNode, vector<HNode>, CompareNodes> pq(nodes.begin(), nodes.end());

    // Build the Huffman tree
    while (pq.size() > 1) {
      // Extract two nodes with the lowest weights
      HNode left = pq.top();
      pq.pop();
      HNode right = pq.top();
      pq.pop();

      // Create a new node with the sum of weights
      HNode newNode;
      newNode.weight = left.weight + right.weight;
      newNode.childType = -1; // Indicate that it's an internal node

      // Set left and right children
      left.parent = nodes.size(); // Update parent index for left node
      right.parent = nodes.size(); // Update parent index for right node
      newNode.childType = -1; // Indicate internal node

      // Insert the new node back into the priority queue
      pq.push(newNode);

      // Add the new node to the vector
      nodes.push_back(newNode);

      built = true;
    }
    built = true;
}






///////////////////////////////////

    // cout << "     ++++    ENCODING TABLE   +++++" << endl;
    // cout << endl;
    // cout << "Index   Char    Weight  Parent  ChildType" << endl;
    // printf("%-8s%-8s%-8s%-8s%-8s", "Index", "Char", "Weight", "Parent", "ChildType");
    // cout << endl;
    // printf("%-8d%-8d%-8d%-8d%-8d", 1, 23, 234, 74, 3);

