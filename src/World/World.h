//
// Created by Vlad Puscaru on 01.12.2023.
//

#ifndef ALGORITHMS_WORLD_H
#define ALGORITHMS_WORLD_H

#include <SFML/Graphics.hpp>

#include "../Tile/Tile.h"
#include "../AssetsRepository/AssetsRepository.h"
#include <vector>

#include <iostream>
#include <chrono>

struct MapConfig {
    int mapWidth;
    int mapHeight;
    int tileWidth;
    int tileHeight;
};

class World : public sf::Drawable {
private:
    std::vector<std::vector<Tile>> mMap;
    std::vector<std::vector<Tile>> mMapOriginal;
    MapConfig mConfig;

public:
    World();

    void init(const MapConfig &config, const AssetsRepository& assetsRepository);

    const Tile &getTileAt(const sf::Vector2i &position) const;

    void setTileAt(const sf::Vector2i &position, TileType tileType);

    sf::Vector2i getTileCoordsFromPixelPos(int x, int y) const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void resetToOriginal();

    MapConfig getMapConfig() const;
};


#endif //ALGORITHMS_WORLD_H
