//
// Created by Vlad Puscaru on 04.12.2023.
//

#ifndef ALGORITHMS_ASSETSREPOSITORY_H
#define ALGORITHMS_ASSETSREPOSITORY_H

#include <iostream>
#include <SFML/Graphics.hpp>

class AssetsRepository {
private:
    sf::Font mFont;
public:
    AssetsRepository();

    const sf::Font& getFont() const;
};


#endif //ALGORITHMS_ASSETSREPOSITORY_H
