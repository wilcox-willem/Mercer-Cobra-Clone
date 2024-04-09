#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct HNode {
    char ch;
    int weight;
    int parent;
    int childType;
};

// Custom comparison function for priority queue
struct CompareWeights {
    bool operator()(const HNode& node1, const HNode& node2) {
        // Compare weights in ascending order
        return node1.weight > node2.weight;
    }
};

int main() {
    // Example usage in main function
    priority_queue<HNode, vector<HNode>, CompareWeights> pq;

    // Sample nodes
    HNode node1 = {'A', 10, -1, -1};
    HNode node2 = {'B', 5, -1, -1};
    HNode node3 = {'C', 8, -1, -1};

    // Push nodes into the priority queue
    pq.push(node1);
    pq.push(node2);
    pq.push(node3);

    // Pop elements from the priority queue
    while (!pq.empty()) {
        HNode topNode = pq.top();
        cout << "Character: " << topNode.ch << " Weight: " << topNode.weight << endl;
        pq.pop();
    }

    return 0;
}