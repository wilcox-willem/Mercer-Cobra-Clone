
#include <vector>
#include <queue>
#include <iostream>
#include <cstdlib>
#include <cmath> // for pow and log10
using namespace std;
#include "Sort.h"

int maxElemLength(const vector<int>& v); // returns number of digits of max int in v
int GetDigit(int number, int k); // returns kth digit of number
vector<queue<int>> ItemstoQueue(const vector<int>& L, int k); // radix step 1
vector<int> QueuestoArray(vector<queue<int>>& QA, int numVals); // radix step 2
void radixSort (vector<int>& L, int numDigits); // ties functions together
void printVector(const vector<int>& L); // prints vector w/o modification

void FillUp (vector<int>& array, int SIZE);


// int main(int argc, char *argv[])
// {
//   int SIZE = atoi(argv[1]);
//   vector<int> array(SIZE);

//   FillUp (array, SIZE);	
//   radixSort(array);

//   return 0;
// }

int main() {
  vector<int> testArray = {380, 95, 345, 382, 260, 100, 492};
  // print presort
  cout << "-- PRESORT --" << endl;
  printVector(testArray);


  int digits = maxElemLength(testArray);
  radixSort(testArray, digits);
  cout << "-- POSTSORT --" << endl;
  printVector(testArray);


  return 0;
}

void FillUp (vector<int>& array, int SIZE) {
	int i = 0;

	while (i < SIZE)
		cin >> array[i++];
}

int maxElemLength(const vector<int>& v){
// returns number of digits of max int in v
  int maxElem = 0;
  
  // misinput catch
  if (v.empty()) return maxElem; 
  
  for (int i = 0; i < v.size(); i++) {
    if (v[i] > maxElem) {
      maxElem = v[i];
    }
  }       

  int numDigits = static_cast<int>(log10(maxElem)) + 1;

  return numDigits;
} 

int GetDigit(int number, int k) {
// returns kth digit of number
// Note:: k = 0 returns the digit in the ones place

  // misinput catch
  if (k < 0) return -1;

  // set divisor to 10^k to match desired digit place
  int divisor = static_cast<int>(pow(10, k));

  // divide by 10 to isolate upper digits
  // mod by 10 to isolate lower digits
  int digit = (number / divisor) % 10; 

  return digit;

}


vector<queue<int>> ItemstoQueue(const vector<int>& L, int k) {
// radix step 1
// distribute elements of L into buckets based on the k-th digit

  vector<queue<int>> QA(10); // 10 buckets for digits 0-9

  for (int i = 0; i < L.size(); i++) {
  	int num = L[i];
  	int digit = GetDigit(num, k);
  	QA[digit].push(num);
  }

  return QA;
}

vector<int> QueuestoArray(vector<queue<int>>& QA, int numVals) {
// radix step 2
    vector<int> result;

    for (int i = 0; i < QA.size(); i++) {
        while (!QA[i].empty()) {
            result.push_back(QA[i].front());
            QA[i].pop();
        }
    }

    return result;
}

void radixSort (vector<int>& L, int numDigits){
// ties functions together

  vector<queue<int>> QA(10); 

  for (int k = 0; k < numDigits; k++) {
  	QA = ItemstoQueue(L, k);
  	L = QueuestoArray(QA, L.size());

  	// view the vector each pass
  	cout << "-- PASS: " << k + 1 << endl;
  	printVector(L);
  }


}

void printVector(const vector<int>& L) {
// prints vector w/o modification
  
  for (int i = 0; i < L.size(); i++) {
  	cout << L[i] << endl;
  }

}