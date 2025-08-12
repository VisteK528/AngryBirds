//
// Created by piotr on 5/11/23.
//

#ifndef ANGRYBIRDS_PIG_FACTORY_HPP
#define ANGRYBIRDS_PIG_FACTORY_HPP

#include "include/entities/pigs/pig.hpp"
#include "include/entities/pigs/basic_pig/basic_pig.hpp"

template<class T>
class PigFactory{
private:
    b2WorldId world;
    std::vector<std::shared_ptr<sf::Texture>> pig_textures;
public:
    PigFactory(b2WorldId b2world, std::vector<std::shared_ptr<sf::Texture>> textures): world(b2world), pig_textures(std::move(textures)){};
    std::unique_ptr<T> createPig(float coord_x, float coord_y){
        return std::make_unique<T>(this->world, pig_textures, coord_x, coord_y);
    }
};

#endif //ANGRYBIRDS_PIG_FACTORY_HPP
