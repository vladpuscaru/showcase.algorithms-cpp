//
// Created by Vlad Puscaru on 02.12.2023.
//

#ifndef ALGORITHMS_GRAPH_H
#define ALGORITHMS_GRAPH_H

#include <stack>
#include <vector>

struct Node {
    int mValue;
    int mX;
    int mY;
    std::vector<Node*> mAdjacents;
    Node* parent;

    // Used for A Star
    float gCost = -1; // distance from start node
    float hCost = -1; // distance from goal node
    float fCost = -1; // gCost + hCost
};

class Graph {
private:
    std::vector<Node> mNodes;

public:
    Graph(int **matrix, int rows, int cols);
    Node* getNode(int x, int y);

    void resetCosts();
};


#endif //ALGORITHMS_GRAPH_H
