//
// Created by piotr on 5/9/23.
//

#ifndef ANGRYBIRDS_YELLOW_BIRD_HPP
#define ANGRYBIRDS_YELLOW_BIRD_HPP

#include "bird.hpp"

class YellowBird: public Bird {
private:
    sf::Clock action_clock;
    bool dash_started = false;
    bool dash_ended = false;

    void makeAction() override;
public:
    YellowBird()=default;
    YellowBird(const std::shared_ptr<b2World>& world, std::vector<std::shared_ptr<sf::Texture>> bird_textures, float coord_x=0, float coord_y=0);
};


#endif //ANGRYBIRDS_YELLOW_BIRD_HPP
