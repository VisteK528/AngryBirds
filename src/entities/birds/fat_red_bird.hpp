//
// Created by piotr on 5/9/23.
//

#ifndef ANGRYBIRDS_FAT_RED_BIRD_HPP
#define ANGRYBIRDS_FAT_RED_BIRD_HPP

#include "bird.hpp"

class FatRedBird: public Bird {
private:
    void loadTextures() override;
public:
    FatRedBird(const std::shared_ptr<b2World>& world, float coord_x, float coord_y);
};


#endif //ANGRYBIRDS_FAT_RED_BIRD_HPP
