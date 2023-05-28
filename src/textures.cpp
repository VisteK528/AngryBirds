#include "include/textures.hpp"

std::vector<std::shared_ptr<sf::Texture>> makeShared(std::vector<sf::Texture> &textures) {
    std::vector<std::shared_ptr<sf::Texture>> shared_vector;
    shared_vector.reserve(textures.size());
    for(const sf::Texture& texture: textures){
        shared_vector.push_back(std::make_shared<sf::Texture>(texture));
    }
    return shared_vector;
}

std::vector<sf::Texture> loadTexturesFromPaths(const std::vector<std::string>& paths) {
    std::vector<sf::Texture> loaded_textures;
    loaded_textures.reserve(paths.size());

    for(const std::string& path: paths){
        sf::Texture t;
        if(!t.loadFromFile(path)){
            throw exceptions::TexturesLoadingError("Program couldn't load all graphics properly!");
        }
        loaded_textures.push_back(t);
    }

    // Smoothing the textures
    for(auto &t: loaded_textures){
        t.setSmooth(true);
    }
    return loaded_textures;
}

bool loadTextures(std::unordered_map<BACKGROUNDS, sf::Texture>& background_textures, std::unordered_map<TEXTURE_TYPE, std::vector<sf::Texture>>& entities_textures){
    try {
        for(const auto& pair: background_paths){
            BACKGROUNDS type = pair.first;
            background_textures[type] = loadTexturesFromPaths({pair.second})[0];
        }

        for(const auto& pair: textures_paths){
            TEXTURE_TYPE type = pair.first;
            entities_textures[type] = loadTexturesFromPaths(pair.second);
        }
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

