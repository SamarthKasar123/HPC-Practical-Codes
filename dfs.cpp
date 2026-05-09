#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

struct Node {
    int data;
    vector<Node*> neighbors;
};

void parallel_DFS(Node* node, vector<bool>& visited) {

    visited[node->data] = true;

    cout << node->data << " ";

    #pragma omp parallel for
    for(int i=0;i<node->neighbors.size();i++) {

        Node* neighbor = node->neighbors[i];

        if(!visited[neighbor->data]) {
            parallel_DFS(neighbor, visited);
        }
    }
}

int main() {

    vector<Node> graph(5);

    graph[0].data = 0;
    graph[1].data = 1;
    graph[2].data = 2;
    graph[3].data = 3;
    graph[4].data = 4;

    graph[0].neighbors = {&graph[1], &graph[2]};
    graph[1].neighbors = {&graph[0], &graph[3]};
    graph[2].neighbors = {&graph[0], &graph[4]};

    vector<bool> visited(5, false);

    parallel_DFS(&graph[0], visited);

    return 0;
}
