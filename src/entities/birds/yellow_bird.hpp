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
    void loadTextures() override;
public:
    YellowBird(const std::shared_ptr<b2World>& world, float coord_x, float coord_y);
};


#endif //ANGRYBIRDS_YELLOW_BIRD_HPP
