//
// Created by Piotr Patek on 19/05/2023.
//

#ifndef ANGRYBIRDS_SOUND_MANAGER_HPP
#define ANGRYBIRDS_SOUND_MANAGER_HPP

#include <SFML/Audio.hpp>


class SoundManager {
private:
    sf::Music background_music;
public:
    SoundManager()=default;
    void loadBackgroundMusic(std::string path);
    sf::Music& getBackgroundMusic();

};


#endif //ANGRYBIRDS_SOUND_MANAGER_HPP
