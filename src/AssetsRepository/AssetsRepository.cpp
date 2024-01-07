//
// Created by Vlad Puscaru on 04.12.2023.
//

#include "AssetsRepository.h"

AssetsRepository::AssetsRepository() {
    if (!mFont.loadFromFile("./resources/fonts/Montserrat-VariableFont_wght.ttf")) {
        std::cerr << "Cannot load font" << std::endl;
        exit(-1);
    }
}

const sf::Font &AssetsRepository::getFont() const {
    return mFont;
}
