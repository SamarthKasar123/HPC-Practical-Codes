#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

struct Node {
    int data;
    vector<Node*> children;
};

void parallel_BFS(Node* root) {

    vector<bool> visited(100, false);

    queue<Node*> q;
    q.push(root);

    visited[root->data] = true;

    while(!q.empty()) {

        Node* current = q.front();
        q.pop();

        cout << current->data << " ";

        #pragma omp parallel for
        for(int i=0;i<current->children.size();i++) {

            Node* child = current->children[i];

            if(!visited[child->data]) {

                #pragma omp critical
                {
                    visited[child->data] = true;
                    q.push(child);
                }
            }
        }
    }
}

int main() {

    Node* root = new Node{1};

    Node* n2 = new Node{2};
    Node* n3 = new Node{3};
    Node* n4 = new Node{4};

    root->children.push_back(n2);
    root->children.push_back(n3);

    n3->children.push_back(n4);

    parallel_BFS(root);

    return 0;
}
