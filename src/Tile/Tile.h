//
// Created by Vlad Puscaru on 01.12.2023.
//

#ifndef ALGORITHMS_TILE_H
#define ALGORITHMS_TILE_H

#include <SFML/Graphics.hpp>

enum TileType {
    EMPTY,
    OBSTACLE,
    START,
    GOAL,
    ALG_PATH,
    ALG_VISITED,
    ALG_OPEN
};

class Tile : public sf::RectangleShape {
private:
    TileType mType;

    sf::Text mText;
public:
    explicit Tile(sf::Vector2f size);

    TileType getType() const;
    void setType(TileType type);

    const sf::Text& getText() const;
    void setText(const sf::Text& text);
};


#endif //ALGORITHMS_TILE_H
