
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <cstdlib>
#include <cmath> // for pow and log10
using namespace std;
#include "Sort.h"

int maxElemLength(const vector<string>& words); // returns number of digits of max int in v
char GetChar(string word, int k); // returns kth char of word
vector<queue<string>> ItemstoQueue(const vector<string>& L, int k); // radix step 1
vector<string> QueuestoArray(vector<queue<string>>& QA); // radix step 2
void radixSort (vector<string>& words, int numLetters); // ties functions together
void printVector(const vector<string>& words); // prints vector w/o modification
void padWordsToRight(vector<string>& words, int targetLength);
void removeRightPadding(vector<string>& words);

int main() {
  vector<string> testArray = {"zebra", "apple", "orange", "can", "candy",
  			      "a", "top", "pumpkin", "today", "parade"};
  // print presort
  cout << "-- PRESORT --" << endl;
  printVector(testArray);

  int digits = maxElemLength(testArray);
  radixSort(testArray, digits);
  

  // print postsort
  cout << "-- POSTSORT --" << endl;
  printVector(testArray);

  


  return 0;
}


int maxElemLength(const vector<string>& words) {
// returns number of chars in longest string in v
  int maxElem = 0;
  
  for (int i = 0; i < words.size(); i++) {
    if (words[i].length() > maxElem) {
      maxElem = words[i].length();
    }
  }       

  return maxElem;
} 

char GetChar(string word, int k) {
// returns kth char of word
// Note:: k = 0 returns the first char

  char thisChar = word.at(k);
  return thisChar;

}


vector<queue<string>> ItemstoQueue(const vector<string>& L, int k) {
// radix step 1
// distribute elements of L into buckets based on the k-th digit

  vector<queue<string>> QA(128); // 128 buckets for each char

  for (int i = 0; i < L.size(); i++) {
  	string word = L[i];
  	char thisChar = GetChar(word, k);
  	QA[thisChar].push(word);
  }

  return QA;
}

vector<string> QueuestoArray(vector<queue<string>>& QA) {
// radix step 2
    vector<string> result;

    for (int i = 0; i < QA.size(); i++) {
        while (!QA[i].empty()) {
            string currWord = QA[i].front();
            //cout << currWord << endl;
            result.push_back(currWord);
            QA[i].pop();
        }
    }

    return result;
}

void radixSort (vector<string>& words, int numLetters) {
// ties functions together

  padWordsToRight(words, numLetters);

  vector<queue<string>> QA(128); 

  for (int k = numLetters - 1; k >= 0; k--) {
  	QA = ItemstoQueue(words, k);
  	words = QueuestoArray(QA);

  	// view the vector each pass
   	cout << "-- PASS: " << k + 1 << endl;
   	printVector(words);
   }

   removeRightPadding(words);
}

void printVector(const vector<string>& words) {
// prints vector w/o modification
  
  for (int i = 0; i < words.size(); i++) {
  	cout << words[i] << endl;
  }

}


// word padding functions

void padWordsToRight(vector<string>& words, int targetLength) {
  for (string& word : words) {
    int currentLength = word.length();
    if (currentLength < targetLength) {
        // pad to the left until targetLength
        word = word + string(targetLength - currentLength, ' ');
    }
  }
}

void removeRightPadding(vector<string>& words) {
    for (string& word : words) {
      // Find the last non-space character in the word
      size_t lastNonSpace = word.find_last_not_of(' ');

      // If the word is padded, remove the right padding
      if (lastNonSpace != string::npos) {
          word.resize(lastNonSpace + 1);
      }
    }
}