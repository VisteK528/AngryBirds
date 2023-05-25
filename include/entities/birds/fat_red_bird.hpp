//
// Created by piotr on 5/9/23.
//

#ifndef ANGRYBIRDS_FAT_RED_BIRD_HPP
#define ANGRYBIRDS_FAT_RED_BIRD_HPP

#include "bird.hpp"

class FatRedBird: public Bird {
public:
    FatRedBird()=default;
    FatRedBird(const std::shared_ptr<b2World>& world, std::vector<std::shared_ptr<sf::Texture>> bird_textures, float coord_x=0, float coord_y=0);
};


#endif //ANGRYBIRDS_FAT_RED_BIRD_HPP
