// Willem Wilcox, CSC245, Dr. Digh, MU. 10/22/23
//Lab 5, this is the client file "STLpq.cpp"
#include <iostream>
#include <queue>
#include <string>

using namespace std;

void insertTenNames(priority_queue<string> & pq){
    // pushes ten names into arg pq
    pq.push("Hareld");
    pq.push("Easy-Pete");
    pq.push("Elbertson");
    pq.push("Harold");
    pq.push("Billylyn");
    pq.push("Chocula");
    pq.push("Gary");
    pq.push("GhostFace");
    pq.push("Micheal");
    pq.push("Herald");
}

void printAllItems(priority_queue<string> pq){
    while(!pq.empty()){
        cout << pq.top() << endl;
        pq.pop();
    }
}


int main() {
    priority_queue<string> pq;
    insertTenNames(pq);
    printAllItems(pq);

    return 0;
}


