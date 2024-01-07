//
// Created by Vlad Puscaru on 01.12.2023.
//

#ifndef ALGORITHMS_GAME_H
#define ALGORITHMS_GAME_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include "../World/World.h"
#include "../Pathfinder/StatePathfinder.h"
#include "../AssetsRepository/AssetsRepository.h"
#include <memory>

class Game {
private:
    sf::RenderWindow mWindow;
    sf::Event mEvent;

    AssetsRepository assetsRepository;

    World mWorld;

    sf::Vector2i mStart;
    TileType mStartPreviousType;

    sf::Vector2i mGoal;
    TileType mGoalPreviousType;

    std::unique_ptr<StatePathfinder> mStatePathfinder;
    int mActiveAlgState;

    void init();

    void input();
    void update(float deltaTime);
    void render();

    void resetTiles();

    void initStatePathfinding();
    void advanceStatePathfinding();
public:
    Game(int wWidth, int wHeight, const sf::String& title);
    void run();
};


#endif //ALGORITHMS_GAME_H
