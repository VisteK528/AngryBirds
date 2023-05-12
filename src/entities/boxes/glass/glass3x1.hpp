#ifndef GLASS3X1_HPP
#define GLASS3X1_HPP

#include "../box.hpp"

class Glass3x1: public Box
{
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void setTexture() override;
public:
    Glass3x1(){};
    Glass3x1(std::shared_ptr<b2World> world, float coord_x, float coord_y, bool rotated=false);
};

#endif