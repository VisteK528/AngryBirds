#ifndef WOOD3X1_HPP
#define WOOD3X1_HPP

#include "include/entities/boxes/box.hpp"

class Wood3x1: public Box
{
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    Wood3x1()=default;
    Wood3x1(std::shared_ptr<b2World> world, std::vector<std::shared_ptr<sf::Texture>> textures, float coord_x, float coord_y, bool rotated=false);
};

#endif