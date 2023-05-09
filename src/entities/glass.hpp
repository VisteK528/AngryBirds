#ifndef GLASS_HPP
#define GLASS_HPP

#include "box.hpp"

class Glass: public Box
{
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void setTexture() override;
public:
    Glass(){};
    Glass(std::shared_ptr<b2World> world, float coord_x, float coord_y);
};

#endif