//
// Created by Vlad Puscaru on 01.12.2023.
//

#include "World.h"

World::World() = default;

void World::init(const MapConfig &config, const AssetsRepository &assetsRepository) {
    mMap.reserve(config.mapHeight);
    mMapOriginal.reserve(config.mapHeight);
    for (int i = 0; i < config.mapHeight; i++) {
        std::vector<Tile> row;
        row.reserve(config.mapWidth);
        for (int j = 0; j < config.mapWidth; j++) {
            Tile tile({(float) config.tileWidth, (float) config.tileHeight});
            tile.setPosition(j * config.tileWidth, i * config.tileHeight);

            if (i > config.mapHeight / 4 && i < config.mapHeight / 1.5 && j > config.mapWidth / 4 &&
                j < config.mapWidth / 1.5) {
                tile.setType(TileType::OBSTACLE);
            }

//            sf::Text text;
//            text.setFont(assetsRepository.getFont());
//            text.setString("2");
//            text.setFillColor(sf::Color::Green);
//            text.setCharacterSize(5);
//            text.setPosition({ (float)j * config.tileWidth, (float)i * config.tileHeight });
//
//            tile.setText(text);

            row.emplace_back(tile);
        }
        mMap.emplace_back(row);
        mMapOriginal.push_back(row);
    }

    mConfig = config;
}

void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &tileRow: mMap) {
        for (const auto &tile: tileRow) {
            target.draw(tile);
            target.draw(tile.getText());
        }
    }
}

void World::setTileAt(const sf::Vector2i &position, TileType tileType) {
    assert(position.x >= 0 && position.x <= mMap[0].size() && position.y >= 0 && position.y <= mMap.size());
    mMap[position.y][position.x].setType(tileType);
}

sf::Vector2i World::getTileCoordsFromPixelPos(int x, int y) const {
    int cX = x / mConfig.tileWidth;
    int cY = y / mConfig.tileHeight;

    if (cX >= mMap[0].size() || cY >= mMap.size()) {
        return {-1, -1};
    }

    return {cX, cY};
}

const Tile &World::getTileAt(const sf::Vector2i &position) const {
    assert(position.x >= 0 && position.x <= mMap[0].size() && position.y >= 0 && position.y <= mMap.size());
    return mMap[position.y][position.x];
}

MapConfig World::getMapConfig() const {
    return mConfig;
}

void World::resetToOriginal() {
    for (int i = 0; i < mMapOriginal.size(); i++) {
        for (int j = 0; j < mMapOriginal[i].size(); j++) {
            mMap[i][j] = mMapOriginal[i][j];
        }
    }
}
