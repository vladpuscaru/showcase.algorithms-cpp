//
// Created by Vlad Puscaru on 03.12.2023.
//

#ifndef ALGORITHMS_STATEPATHFINDER_H
#define ALGORITHMS_STATEPATHFINDER_H

#include <unordered_map>
#include <vector>
#include "Graph/Graph.h"
#include <iostream>
#include <cmath>

struct AlgorithmState {
    std::unordered_map<Node*, bool> visited;
    std::vector<Node *> open;
    std::vector<Node *> path;
    bool finished;
};

class StatePathfinder {
private:
    Graph mMap;

    std::vector<int> mStart;
    std::vector<int> mGoal;

    AlgorithmState mBFS;
    AlgorithmState mDFS;
    AlgorithmState mAStar;

    void resetState();

    // TODO: More efficient to have a data structure for AStar state that
    // always keeps track of the min value
    Node* getMinCost(std::vector<Node*> vec, int* nodePos) const;
    float computeDistance(const Node *node, int x, int y) const;
public:

    StatePathfinder(int **mapMatrix, int rows, int cols);

    bool isRunning() const;

    void setStart(int x, int y);
    void setGoal(int x, int y);

    AlgorithmState getBFSState() const;
    AlgorithmState getDFSState() const;
    AlgorithmState getAStarState() const;

    void advanceDFS();
    void advanceBFS();
    void advanceAStar();
};


#endif //ALGORITHMS_STATEPATHFINDER_H
