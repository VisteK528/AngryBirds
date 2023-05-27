#ifndef ANGRYBIRDS_SOUND_MANAGER_HPP
#define ANGRYBIRDS_SOUND_MANAGER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "exceptions.hpp"
#include <iostream>


class SoundManager {
private:
    sf::Music background_music;
    float background_music_volume = 50;
public:
    SoundManager()=default;
    void setBackgroundMusic(std::string path);
    void updateVolume();
    sf::Music& getBackgroundMusic();

};


#endif //ANGRYBIRDS_SOUND_MANAGER_HPP
