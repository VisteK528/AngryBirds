//
// Created by piotr on 5/14/23.
//

#include "textures.hpp"

std::vector<std::shared_ptr<sf::Texture>> makeShared(std::vector<sf::Texture> &textures) {
    std::vector<std::shared_ptr<sf::Texture>> shared_vector;
    shared_vector.reserve(textures.size());
    for(const sf::Texture& texture: textures){
        shared_vector.push_back(std::make_shared<sf::Texture>(texture));
    }
    return shared_vector;
}
