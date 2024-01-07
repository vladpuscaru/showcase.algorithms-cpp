//
// Created by Vlad Puscaru on 01.12.2023.
//

#include "Tile.h"

Tile::Tile(sf::Vector2f size)
        : mType() {
    setType(TileType::EMPTY);
    setSize(size);
    setOutlineThickness(.5f);
    setOutlineColor(sf::Color::Black);
}

TileType Tile::getType() const {
    return mType;
}

void Tile::setType(TileType type) {
    mType = type;
    switch (mType) {
        case EMPTY:
            setFillColor(sf::Color::White);
            break;
        case OBSTACLE:
            setFillColor(sf::Color::Red);
            break;
        case START:
            setFillColor(sf::Color::Green);
            break;
        case GOAL:
            setFillColor(sf::Color::Magenta);
            break;
        case ALG_PATH:
            setFillColor(sf::Color::Yellow);
            break;
        case ALG_VISITED:
            setFillColor(sf::Color(0, 200, 255));
            break;
        case ALG_OPEN:
            setFillColor(sf::Color(0, 0, 255));
            break;
        default:
            setFillColor(sf::Color::Black);
    }
}

const sf::Text &Tile::getText() const {
    return mText;
}

void Tile::setText(const sf::Text &text) {
    mText = text;
}

