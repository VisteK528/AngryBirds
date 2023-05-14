//
// Created by piotr on 5/14/23.
//

#ifndef ANGRYBIRDS_TEXTURES_HPP
#define ANGRYBIRDS_TEXTURES_HPP

#include <SFML/Graphics.hpp>
#include <memory>

typedef enum{DEFAULT, MOUNTAINS, OCEAN, SPACE} BACKGROUNDS;

typedef enum{
    WOOD,
    WOOD3x1,
    STONE,
    STONE3x1,
    GLASS,
    GLASS3x1,
    BASIC_PIG,
    RED_BIRD,
    YELLOW_BIRD,
    FAT_RED_BIRD,
    GREY_BIRD
} TEXTURE_TYPE;

std::vector<std::shared_ptr<sf::Texture>> makeShared(std::vector<sf::Texture>& textures);

#endif //ANGRYBIRDS_TEXTURES_HPP
