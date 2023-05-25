//
// Created by piotr on 5/11/23.
//

#ifndef ANGRYBIRDS_BIRD_FACTORY_HPP
#define ANGRYBIRDS_BIRD_FACTORY_HPP

#include <utility>

#include "include/entities/birds/bird.hpp"
#include "include/entities/birds/yellow_bird.hpp"
#include "include/entities/birds/grey_bird.hpp"
#include "include/entities/birds/fat_red_bird.hpp"

template<class T>
class BirdFactory {
private:
    std::shared_ptr<b2World> world;
    std::vector<std::shared_ptr<sf::Texture>> bird_textures;
public:
    BirdFactory(std::shared_ptr<b2World> b2world, std::vector<std::shared_ptr<sf::Texture>> textures): world(std::move(b2world)), bird_textures(std::move(textures)){};
    std::unique_ptr<T> createBird(){
        return std::make_unique<T>(world, bird_textures);
    }
    std::unique_ptr<T> createBird(float coord_x, float coord_y){
        return std::make_unique<T>(world, coord_x, coord_y, bird_textures);
    }

};


#endif //ANGRYBIRDS_BIRD_FACTORY_HPP
