//
// Created by Vlad Puscaru on 02.12.2023.
//

#include "Graph.h"

Node *Graph::getNode(int x, int y) {
    Node *node = nullptr;
    for (int i = 0; i < mNodes.size(); i++) {
        if (mNodes[i].mY == y && mNodes[i].mX == x) {
            return &mNodes[i];
        }
    }
    return node;
}

Graph::Graph(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Node newNode;
            newNode.mValue = matrix[i][j];
            newNode.mX = j;
            newNode.mY = i;
            newNode.parent = nullptr;
            mNodes.emplace_back(newNode);
        }
    }

    for (int i = 0; i < mNodes.size(); i++) {
        Node *adjTop = getNode(mNodes[i].mX, mNodes[i].mY - 1);
        Node *adjRight = getNode(mNodes[i].mX + 1, mNodes[i].mY);
        Node *adjBot = getNode(mNodes[i].mX, mNodes[i].mY + 1);
        Node *adjLeft = getNode(mNodes[i].mX - 1, mNodes[i].mY);

        Node *adjTopRight = getNode(mNodes[i].mX + 1, mNodes[i].mY - 1);
        Node *adjBotRight = getNode(mNodes[i].mX + 1, mNodes[i].mY + 1);
        Node *adjBotLeft = getNode(mNodes[i].mX - 1, mNodes[i].mY + 1);
        Node *adjTopLeft = getNode(mNodes[i].mX - 1, mNodes[i].mY - 1);

        if (adjTop && adjTop->mValue == mNodes[i].mValue) mNodes[i].mAdjacents.push_back(adjTop);
        if (adjRight && adjRight->mValue == mNodes[i].mValue) mNodes[i].mAdjacents.push_back(adjRight);
        if (adjBot && adjBot->mValue == mNodes[i].mValue) mNodes[i].mAdjacents.push_back(adjBot);
        if (adjLeft && adjLeft->mValue == mNodes[i].mValue) mNodes[i].mAdjacents.push_back(adjLeft);

        if (adjTopRight && adjTopRight->mValue == mNodes[i].mValue) mNodes[i].mAdjacents.push_back(adjTopRight);
        if (adjBotRight && adjBotRight->mValue == mNodes[i].mValue) mNodes[i].mAdjacents.push_back(adjBotRight);
        if (adjBotLeft && adjBotLeft->mValue == mNodes[i].mValue) mNodes[i].mAdjacents.push_back(adjBotLeft);
        if (adjTopLeft && adjTopLeft->mValue == mNodes[i].mValue) mNodes[i].mAdjacents.push_back(adjTopLeft);
    }
}

void Graph::resetCosts() {
    for (auto & node : mNodes) {
        node.gCost = -1;
        node.hCost = -1;
        node.fCost = -1;
    }
}
