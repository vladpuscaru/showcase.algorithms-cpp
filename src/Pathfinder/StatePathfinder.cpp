//
// Created by Vlad Puscaru on 03.12.2023.
//

#include "StatePathfinder.h"

StatePathfinder::StatePathfinder(int **mapMatrix, int rows, int cols) : mMap(mapMatrix, rows, cols) {
    resetState();
}

void StatePathfinder::setStart(int x, int y) {
    mStart.clear();
    mStart.push_back(x);
    mStart.push_back(y);

    resetState();
    Node *start = mMap.getNode(x, y);
    mBFS.open.emplace_back(start); // pushing at the back for queue
    mDFS.open.emplace_back(start); // pushing at the back for stack
    mAStar.open.emplace_back(start);
}

void StatePathfinder::setGoal(int x, int y) {
    mGoal.clear();
    mGoal.push_back(x);
    mGoal.push_back(y);
}

void StatePathfinder::resetState() {
    mDFS = AlgorithmState();
    mBFS = AlgorithmState();
    mAStar = AlgorithmState();

    mBFS.finished = false;
    mDFS.finished = false;
    mAStar.finished = false;

    mMap.resetCosts();
}

void StatePathfinder::advanceBFS() {
    if (!mBFS.finished && !mBFS.open.empty()) {
        // FIFO Queue
        Node *node = mBFS.open.front();
        mBFS.open.erase(mBFS.open.begin());

        if (node->mX == mGoal[0] && node->mY == mGoal[1]) {
            mBFS.finished = true;
            return;
        }


        mBFS.visited.insert(std::make_pair(node, true));
        for (int i = 0; i < node->mAdjacents.size(); i++) {
            if (mBFS.visited.find(node->mAdjacents[i]) == mBFS.visited.end()) {
                mBFS.open.push_back(node->mAdjacents[i]);
                node->mAdjacents[i]->parent = node;
            }
        }
    }

    // Compute path if exists
    if (mBFS.finished && mBFS.path.empty()) {
        Node *n = mMap.getNode(mGoal[0], mGoal[1]);

        while (n != nullptr) {
            mBFS.path.push_back(n);
            n = n->parent;
        }
    }
}

void StatePathfinder::advanceDFS() {
    if (!mDFS.finished && !mDFS.open.empty()) {
        // LIFO Queue
        Node *node = mDFS.open.back();
        mDFS.open.pop_back();

        if (node->mX == mGoal[0] && node->mY == mGoal[1]) {
            mDFS.finished = true;
            return;
        }

        mDFS.visited.insert(std::make_pair(node, true));
        for (int i = 0; i < node->mAdjacents.size(); i++) {
            if (mDFS.visited.find(node->mAdjacents[i]) == mDFS.visited.end()) {
                mDFS.open.push_back(node->mAdjacents[i]);
                node->mAdjacents[i]->parent = node;
            }
        }
    }

    // Compute path if exists
    if (mDFS.finished && mDFS.path.empty()) {
        Node *n = mMap.getNode(mGoal[0], mGoal[1]);

        while (n != nullptr) {
            mDFS.path.push_back(n);
            n = n->parent;
        }
    }
}

AlgorithmState StatePathfinder::getBFSState() const {
    return mBFS;
}

AlgorithmState StatePathfinder::getDFSState() const {
    return mDFS;
}

bool StatePathfinder::isRunning() const {
    return !mStart.empty() && !mGoal.empty();
}

AlgorithmState StatePathfinder::getAStarState() const {
    return mAStar;
}

void StatePathfinder::advanceAStar() {
    if (!mAStar.finished && !mAStar.open.empty()) {
        // FIFO Queue
        int nodePos;
        Node *node = getMinCost(mAStar.open, &nodePos);
        mAStar.open.erase(mAStar.open.begin() + nodePos);
        mAStar.visited.insert(std::make_pair(node, true));

        if (node->mX == mGoal[0] && node->mY == mGoal[1]) {
            mAStar.finished = true;
            return;
        }

        for (int i = 0; i < node->mAdjacents.size(); i++) {
            // Because when I make the graph I already account for obstacles,
            // the obstacles are not part of the graph
            // Usually, you check here if a neighbour is traversable or not
            // Because of that, I just check if I already visited that node
            if (mAStar.visited.find(node->mAdjacents[i]) != mAStar.visited.end()) {
                continue;
            }

            int newMovementCostToNeighbour = node->mAdjacents[i]->gCost + computeDistance(node, node->mAdjacents[i]->mX, node->mAdjacents[i]->mY);
            auto x = std::find(mAStar.open.begin(),mAStar.open.end(), node->mAdjacents[i]);
            if (newMovementCostToNeighbour < node->mAdjacents[i]->gCost || x == mAStar.open.end()) {
                node->mAdjacents[i]->gCost = newMovementCostToNeighbour;
                node->mAdjacents[i]->hCost = computeDistance(node->mAdjacents[i], mGoal[0], mGoal[1]);
                node->mAdjacents[i]->parent = node;

                if (x == mAStar.open.end()) {
                    mAStar.open.push_back(node->mAdjacents[i]);
                }
            }
        }
    }

    // Compute path if exists
    if (mAStar.finished && mAStar.path.empty()) {
        Node *n = mMap.getNode(mGoal[0], mGoal[1]);

        while (n != nullptr) {
            mAStar.path.push_back(n);
            n = n->parent;
        }
    }
}

Node *StatePathfinder::getMinCost(std::vector<Node *> vec, int *nodePos) const {
    Node *min = vec[0];
    *nodePos = 0;
    for (int i = 1; i < vec.size(); i++) {
        if (min->fCost > vec[i]->fCost || (min->fCost == vec[i]->fCost && min->hCost > vec[i]->hCost)) {
            min = vec[i];
            *nodePos = i;
        }
    }
    return min;
}

float StatePathfinder::computeDistance(const Node *node, int x, int y) const {
    int xDist = std::abs(x - node->mX);
    int yDist = std::abs(y - node->mY);

    if (xDist > yDist) {
        return 14 * yDist + 10 * (xDist - yDist);
    }
    return 14 * xDist + 10 * (yDist - xDist);
}

