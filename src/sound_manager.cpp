#include "include/sound_manager.hpp"

sf::Music& SoundManager::getBackgroundMusic() {
    return this->background_music;
}

void SoundManager::setBackgroundMusic(std::string path) {
    if(!this->background_music.openFromFile(path)){
        throw exceptions::MusicLoadingError("Program couldn't load the music properly!");
    }
    setBackgroundMusicVolume(background_music_volume);
}

void SoundManager::setBackgroundMusicVolume(float volume){
    this->background_music_volume = volume;
    this->background_music.setVolume(volume);
}

void SoundManager::updateVolume() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && background_music_volume > 0){
        background_music_volume -= 0.5;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && background_music_volume < 100){
        background_music_volume += 0.5;
    }
    this->background_music.setVolume((float)background_music_volume);
    this->background_sound.setVolume(background_music_volume);
}

void SoundManager::playBackgroundSound(std::string path) {
    if(!this->background_sound.openFromFile(path)){
        throw exceptions::MusicLoadingError("Program couldn't load the sound properly!");
    }
    this->background_sound.setVolume(background_music_volume);
}
