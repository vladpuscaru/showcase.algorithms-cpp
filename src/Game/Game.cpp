//
// Created by Vlad Puscaru on 01.12.2023.
//

#include "Game.h"

/**
 * Escape to Close
 *
 * A to start State AStar
 * D to start State DFS
 * B to start State BFS
 *
 * R to reset
 */
void Game::input() {
    while (mWindow.pollEvent(mEvent)) {
        if (mEvent.type == sf::Event::Closed) {
            mWindow.close();
        }

        if (mEvent.type == sf::Event::KeyPressed) {
            switch (mEvent.key.code) {
                case sf::Keyboard::D:
                    if (mStart.x != -1 && mStart.y != -1 && mGoal.x != -1 && mGoal.y != -1) {
                        mActiveAlgState = 0;
                    }
                    break;
                case sf::Keyboard::B:
                    if (mStart.x != -1 && mStart.y != -1 && mGoal.x != -1 && mGoal.y != -1) {
                        mActiveAlgState = 1;
                    }
                    break;
                case sf::Keyboard::A:
                    if (mStart.x != -1 && mStart.y != -1 && mGoal.x != -1 && mGoal.y != -1) {
                        mActiveAlgState = 2;
                    }
                    break;
                case sf::Keyboard::Escape:
                    mWindow.close();
                    break;
                case sf::Keyboard::R:
                    resetTiles();
                    break;
            }
        }

        if (mEvent.type == sf::Event::MouseButtonPressed) {
            int mouseX = mEvent.mouseButton.x;
            int mouseY = mEvent.mouseButton.y;
            sf::Vector2i tileCoords = mWorld.getTileCoordsFromPixelPos(mouseX, mouseY);
            if (tileCoords.x == -1 || tileCoords.y == -1) {
                continue;
            }

            if (mEvent.mouseButton.button == sf::Mouse::Button::Left) {
                if (mStart.x != -1 && mStart.y != -1) {
                    mWorld.setTileAt(mStart, mStartPreviousType);
                }
                mStartPreviousType = mWorld.getTileAt(tileCoords).getType();
                mWorld.setTileAt(tileCoords, TileType::START);
                mStart = tileCoords;
            } else if (mEvent.mouseButton.button == sf::Mouse::Button::Right) {
                if (mGoal.x != -1 && mGoal.y != -1) {
                    mWorld.setTileAt(mGoal, mGoalPreviousType);
                }
                mGoalPreviousType = mWorld.getTileAt(tileCoords).getType();
                mWorld.setTileAt(tileCoords, TileType::GOAL);
                mGoal = tileCoords;
            }
        }
    }
}

void Game::update(float deltaTime) {
    if (mActiveAlgState != -1) {
        advanceStatePathfinding();

        AlgorithmState state;
        switch (mActiveAlgState) {
            case 0: // DFS
                state = mStatePathfinder->getDFSState();
                break;
            case 1: // BFS
                state = mStatePathfinder->getBFSState();
                break;
            case 2: // A Star
                state = mStatePathfinder->getAStarState();
                break;
        }

        for (int i = 0; i < state.open.size(); i++) {
            int x = state.open[i]->mX;
            int y = state.open[i]->mY;

            if ((x == mStart.x && y == mStart.y) || (x == mGoal.x && y == mGoal.y)) {
                continue;
            }

            if (mWorld.getTileAt({x, y}).getType() != TileType::ALG_OPEN) {
                mWorld.setTileAt({x, y}, TileType::ALG_OPEN);
            }
        }

        for (auto it = state.visited.begin(); it != state.visited.end(); it++) {
            int x = it->first->mX;
            int y = it->first->mY;

            if ((x == mStart.x && y == mStart.y) || (x == mGoal.x && y == mGoal.y)) {
                continue;
            }

            if (mWorld.getTileAt({x, y}).getType() != TileType::ALG_VISITED) {
                mWorld.setTileAt({x, y}, TileType::ALG_VISITED);
            }
        }

        if (state.finished) {
            for (int i = 0; i < state.path.size(); i++) {
                mWorld.setTileAt({state.path[i]->mX, state.path[i]->mY}, TileType::ALG_PATH);
            }
        }

        mWorld.setTileAt({mStart.x, mStart.y}, TileType::START);
        mWorld.setTileAt({mGoal.x, mGoal.y}, TileType::GOAL);
    }
}

void Game::render() {
    mWindow.clear(sf::Color::Blue);
    mWindow.draw(mWorld);
    mWindow.display();
}

void Game::run() {

    sf::Clock clock;
    while (mWindow.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        input();
        update(deltaTime);
        render();
    }
}

Game::Game(int wWidth, int wHeight, const sf::String &title)
        : mWindow(sf::VideoMode(wWidth, wHeight), title), mEvent(sf::Event()) {
    init();
}

void Game::init() {
    mWindow.setVerticalSyncEnabled(true);
    mWindow.setFramerateLimit(60);

    int tileWidth = 10;
    int tileHeight = 10;
    int mapWidth = (int) mWindow.getSize().x / tileWidth;
    int mapHeight = (int) mWindow.getSize().y / tileHeight;
    MapConfig mapConfig{mapWidth, mapHeight, tileWidth, tileHeight};
    mStart.x = -1;
    mStart.y = -1;
    mGoal.x = -1;
    mGoal.y = -1;
    mWorld.init(mapConfig, assetsRepository);

    mActiveAlgState = -1;
    initStatePathfinding();
}

void Game::resetTiles() {
    mWorld.resetToOriginal();
    mStart.x = -1;
    mStart.y = -1;
    mGoal.x = -1;
    mGoal.y = -1;

    mActiveAlgState = -1;
    initStatePathfinding();
}

void Game::advanceStatePathfinding() {
    if (mStart.x != -1 && mStart.y != -1 && mGoal.x != -1 && mGoal.y != -1) {
        if (!mStatePathfinder->isRunning()) {
            mStatePathfinder->setStart(mStart.x, mStart.y);
            mStatePathfinder->setGoal(mGoal.x, mGoal.y);
        }


        switch (mActiveAlgState) {
            case 0:
                mStatePathfinder->advanceDFS();
                break;
            case 1:
                mStatePathfinder->advanceBFS();
                break;
            case 2:
                mStatePathfinder->advanceAStar();
                break;
        }
    }
}

void Game::initStatePathfinding() {
    int **matrix;
    int rows = mWorld.getMapConfig().mapHeight;
    int cols = mWorld.getMapConfig().mapWidth;
    matrix = (int **) malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *) malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = mWorld.getTileAt({j, i}).getType();
        }
    }

    mStatePathfinder.reset(new StatePathfinder(matrix, rows, cols));

    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
