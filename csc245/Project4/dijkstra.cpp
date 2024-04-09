// Will Wilcox, Dr. Digh, CSC245, MU
// 12/13/23
// Final / Prog4 / Dijkstra's Algorithm

#include <sstream>
#include <iomanip>
#include <stack>
#include <set>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include "graph.h"
#include "queue.h"

using namespace std;

// struct to track items in graph
struct stringVertex {
	string name;
	bool marked;
	int distance;
	string previous;
};

// function declarations
void insertionSort(vector<string> &currCities, int numVertexes);
void makeGraph(Graph<string> &inputGraph, string fileName, vector<string> &currCities,
								 		 int &numVertexes, int &numEdges, vector <stringVertex> currVertexes);
void printCities(vector<string> currCities);
string setStart(int numVertexes, vector<string> currCities);
void printRow(int currItem, vector <stringVertex> currVertexes);
int findMin(vector <stringVertex> currVertexes, int numVertexes);
void dijkstrasAlgorithm(Graph<string> &inputGraph, int numVertexes, vector <stringVertex> currVertexes,
																													 const vector<string> &currCities);
void updateTable(vector <stringVertex> &currVertexes, string s, int weight, string p);
void makeTable(vector <stringVertex> &currVertexes, vector<string> currCities, string firstCity); 
stringVertex getVertex(string name, vector <stringVertex> currVertexes);

//// MAIN ////
int main(int argc, char* argv[]) {
	// check if 2 args for fileName
	if (argc != 2) {
		cerr << "The command line inputs were not correct.\nPlease try again." << endl;
		return 1;
	}	

	// initialize data
	string fileName = argv[1];
	Graph<string> inputGraph;
	int numVertexes;
	int numEdges;
	vector <stringVertex> currVertexes;
	vector<string> currCities;

	// build graph and print currCities
	makeGraph(inputGraph, fileName, currCities, numVertexes, numEdges, currVertexes);	// Builds the Graph using the data from the external file.
	printCities(currCities);	// Prints Cities found in file

	// perform dijkstras algorithm
	dijkstrasAlgorithm(inputGraph, numVertexes, currVertexes, currCities);	// Computes Dijkstra's Algorithm:
	return(0);
}

//// END MAIN ////

// Function implementations/defs

////// dijkstrasAlgorithm
// performs dijkstra's algorithm on inputGraph
void dijkstrasAlgorithm(Graph<string> &inputGraph, int numVertexes, vector <stringVertex> currVertexes, const vector<string> &currCities) {
  //  in: ref graph inputGraph, numberOfVerts, strVert vec currVerts, ref str vec currCities
  // out: updates table/currVerts using D's ajlgorithm
  string startName = setStart(numVertexes, currCities);
  makeTable(currVertexes, currCities, startName);

  // marked items track visited items and loop control
  for (int numMarked = 0; numMarked < currVertexes.size(); numMarked++) {
    stringVertex currOriginal = currVertexes[numMarked];
    Queue<string> originalPaths;
    inputGraph.GetToVertices(currOriginal.name, originalPaths);

    while(!originalPaths.isEmpty()) {
      string currNeighbor = originalPaths.dequeue();
      if (currNeighbor != currOriginal.name) {
        stringVertex currNeighborVertex = getVertex(currNeighbor, currVertexes);
	    	if (!currNeighborVertex.marked) {
	        int weight = inputGraph.WeightIs(currOriginal.name, currNeighborVertex.name);
	    	  updateTable(currVertexes, currNeighborVertex.name, weight + currOriginal.distance, currOriginal.name);
	    	}
      }
    }
  }


  cout << "---------------------------------------------------------" << endl;
  cout << setw(14) << "Vertex" << setw(18) << "Distance" << setw(18) << "Previous\n" << endl;

  for (int i = 0; i < currVertexes.size(); i++) {
    printRow(i, currVertexes);
  }

  cout << "\n---------------------------------------------------------" << endl;
}

////// makeGraph
// fills inputGraph wiht file from user input fileName
void makeGraph(Graph<string> &inputGraph, string fileName, vector<string> &currCities, 
								 int &numVertexes, int &numEdges, vector <stringVertex> currVertexes) {
	//  in: ref graph inputGraph, fileName, ref vec currCities, numberOfVerts
	//			numberOfEdges, stringVertex vec currentVerts
	// out: fills currVerts using inputGraph and fileName
	ifstream infile;
	infile.open(fileName);
	char start[30];
	char dest[30];
	char num[6];
	int weight;

	while (infile) {
		infile.getline(start, 30,';');
		infile.getline(dest, 30,';');
		infile.getline(num, 6);
		weight = atoi(num);
		bool conStart = false;
		bool conDest= false;
		for (int i=0; i < currCities.size(); i++) {
	    if (currCities.at(i) == start) conStart = true;
			if (currCities.at(i) == dest) conDest = true;
	  }
		
		if (!conStart && start[0] != 0) {
			inputGraph.AddVertex(start);
			currCities.push_back(start);
			numVertexes++;
		} 
		if (!conDest) {
			inputGraph.AddVertex(dest);
			currCities.push_back(dest);
			numVertexes++;
		}
		
		inputGraph.AddEdge(start, dest, weight);
		numEdges++;
	}
}

////// printCities
// prints current cities
void printCities(vector<string> currCities) {
	//  in: string vec of currentCities
	// out: prints the vec of cities
	cout << "\n\n\n~~~~~~~~~~~~~~~~~~ DIJKSTRA'S ALGORITHM ~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\nA Weighted Graph Has Been Built For These " << currCities.size() << " Vectors:" << endl;
	for (int i=0; i < currCities.size(); i++) {
		if (i%3 == 0){
			cout << '\n';
		}
		cout << setw(14) << currCities.at(i);
	}
	cout << endl;
}

////// insertionSort
// insertion sort alphabetically
void insertionSort(vector<string> &currCities, int numVertexes) {
	//  in: ref string vec of currCities, numberOfVerts
	// out: sorted currCities alphabetically
	for( int p = 1; p < currCities.size( ); p++ ) {
		string tmp = currCities[p];
		int j;
		
		for( j = p; j > 0 && (tmp.compare(currCities[j - 1]) < 0); j-- ) {
			currCities[j] = currCities[j - 1];
		}
		
		currCities[j] = tmp;
	}
}

////// setStart
// starting newVertex/city for D's algorithm
string setStart(int numVertexes, vector<string> currCities) {
	//  in: numberOfVerts, string vec of currCities
	// out: users starting vert
	cout << "\n Please input your starting newVertex: ";
	string response;
	getline(cin,response);
	bool isThere = false;

	for (int i = 0;	i < currCities.size(); i++) {
		if (currCities[i].compare(response) == 0)	{
			return response;
		}
	}

	while (!isThere) {
		cout << " Starting currItem does not exist..." << endl;
		cout << " Please input your new newVertex: ";
   	string response;
   	cin >> response;
		for (int i = 0; i < currCities.size(); i++)	{
      if (currCities[i].compare(response) == 0) {
       	return response;
      }
   	}
	}

	return "";
}

////// findMin
// finds and returns min non-marked item
int findMin(vector <stringVertex> currVertexes, int numVertexes) {
	//  in: vec of currVerts, numberOfVerts
	// out: returns the current min item based on dist/weight
 	int minWeight = INT_MAX - 1;
  int minItem = -1;
	for (int i = 0; i < numVertexes; i++) {
    if (currVertexes[i].distance < minWeight && !currVertexes[i].marked) {
  	  minWeight = currVertexes[i].distance;
    	minItem = i;
    }	
    else if (currVertexes[i].distance == minWeight && !currVertexes[i].marked) {
        minWeight = currVertexes[i].distance;
        minItem = i;
    }
	}
		return minItem;
}

////// printRow
// prints given item/row of table
void printRow(int currItem, vector <stringVertex> currVertexes) {
	//  in: currItem, vec of currVerts
	// out:  prints the currItem of currVerts
	if (currVertexes[currItem].distance != INT_MAX && currVertexes[currItem].distance != INT_MIN) {
		cout << setw(14) << currVertexes[currItem].name << setw(18) << currVertexes[currItem].distance << setw(16) << currVertexes[currItem].previous << endl;
	}
	else {
	 cout << setw(14) << currVertexes[currItem].name << setw(18) << "Not On Path" << setw(16) << "N/A" << endl;
	}
}
////// updateTable
// adds new item to currVertexes, weight updated in D's algorithm
void updateTable(vector <stringVertex> &currVertexes, string newItem, int weight, string prevItem) {
	//  in: ref vec of currVerts, newItem, weight, prevItem
	// out: adds newItem/s to currVert or adds new connection w/ weight
  stringVertex newVertex;
	newVertex.name = newItem;
	newVertex.marked = false;
	newVertex.distance = weight;
	newVertex.previous = prevItem;

	stringVertex tmp;

	// check new vertex against current vertexes
	for (int i = 0; i < currVertexes.size(); i++) {
		if (currVertexes[i].name == newVertex.name) {
			if (newVertex.distance == INT_MIN) {
				newVertex.distance = INT_MAX;
				newVertex.previous = "";
				currVertexes[i] = newVertex;
			}
			else if (newVertex.distance <= currVertexes[i].distance) {
				currVertexes[i] = newVertex;
			}
			else {
				newVertex.distance = currVertexes[i].distance;
				newVertex.previous =  currVertexes[i].previous;
				currVertexes[i] = newVertex;
			}

			tmp = getVertex(prevItem, currVertexes);
			tmp.marked = true;
			
			for (int j = 0 ; j < currVertexes.size(); j++) {
				if (tmp.name == currVertexes[j].name) {
					currVertexes[j] = tmp;
				}
			}
		}
	}
 	

	for(int p = 1; p < currVertexes.size( ); p++ ) {
	  stringVertex tmp = currVertexes[p];
		int k;

		for(k = p; k > 0 && tmp.distance < currVertexes[k-1].distance; k--) {
			currVertexes[k] = currVertexes[k - 1];
		}

		currVertexes[k] = tmp;
	}
}

////// makeTable
// prepares a fresh table for D's algorithm
void makeTable(vector <stringVertex> &currVertexes, vector<string> currCities, string firstCity) {
	//  in:  ref vec of currentVerts, vec of currCities, and firstCity
	// out: makes table of distances between firstCity and other verts
  stringVertex newVertex;
	for (int i = 0; i < currCities.size(); i++) {
		if ((currCities[i] == firstCity) && (i == 0)) {
			newVertex.name = firstCity;
			newVertex.marked = false;
			newVertex.distance = 0;
			newVertex.previous = "N/A";
			currVertexes.push_back(newVertex);
		}
		else if (currCities[i] == firstCity && (i > 0)) {
			newVertex.name = firstCity;
			newVertex.marked = false;
			newVertex.distance = 0;
			newVertex.previous = "N/A";
		  stringVertex tmp;
			tmp = currVertexes[0];
			currVertexes[0] = newVertex;
			currVertexes.push_back(tmp);
		}
		else {
			newVertex.name = currCities[i];
			newVertex.marked = false;
			newVertex.distance = INT_MAX; // closest to infinity
			newVertex.previous = "";
			currVertexes.push_back(newVertex);
		}
	}
}


////// getVertex()
// returns stringVertex for name in currVertexes, or cV[0] if not found
stringVertex getVertex(string name, vector <stringVertex> currVertexes) {
	//  in: vertex name, vector of currVertexes
	// out: found vertex or cV[0] if not found
	for (int i = 0; i < currVertexes.size(); i++) {
		if (currVertexes[i].name == name) {
			return currVertexes[i];
		}ty
	}

	return currVertexes[0];
}

jj