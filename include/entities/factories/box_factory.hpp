//
// Created by piotr on 5/6/23.
//

#ifndef ANGRYBIRDS_BOX_FACTORY_HPP
#define ANGRYBIRDS_BOX_FACTORY_HPP

#include <utility>

#include "include/entities/entity.hpp"

#include "include/entities/boxes/box.hpp"
#include "include/entities/boxes/wood/wood.hpp"
#include "include/entities/boxes/wood/wood3x1.hpp"
#include "include/entities/boxes/glass/glass.hpp"
#include "include/entities/boxes/glass/glass3x1.hpp"
#include "include/entities/boxes/stone/stone.hpp"
#include "include/entities/boxes/stone/stone3x1.hpp"

template<class T>
class BoxFactory{
private:
    std::shared_ptr<b2World> world;
    std::vector<std::shared_ptr<sf::Texture>> box_textures;
public:
    BoxFactory(std::shared_ptr<b2World> b2world, std::vector<std::shared_ptr<sf::Texture>> textures): world(std::move(b2world)), box_textures(std::move(textures)){};
    std::unique_ptr<T> createBox(float coord_x, float coord_y){
        return std::make_unique<T>(this->world, box_textures, coord_x, coord_y);
    }

    std::unique_ptr<T> createBoxRotated(float coord_x, float coord_y){
        return std::make_unique<T>(this->world, box_textures, coord_x, coord_y, true);
    }

};


#endif //ANGRYBIRDS_BOX_FACTORY_HPP
