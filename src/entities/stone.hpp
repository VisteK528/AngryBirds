#ifndef STONE_HPP
#define STONE_HPP

#include "box.hpp"

class Stone: public Box
{
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void setTexture();
    void startCollision(b2Body* body_b) override;
    void endCollision(b2Body* body_b) override;
public:
    Stone(){};
    Stone(std::shared_ptr<b2World> world, float coord_x, float coord_y);
};

#endif