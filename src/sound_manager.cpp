//
// Created by Piotr Patek on 19/05/2023.
//

#include "sound_manager.hpp"

sf::Music& SoundManager::getBackgroundMusic() {
    return this->background_music;
}

void SoundManager::loadBackgroundMusic(std::string path) {
    this->background_music.openFromFile(path);
}