#ifndef STONE3X1_HPP
#define STONE3X1_HPP

#include "../box.hpp"

class Stone3x1: public Box
{
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    Stone3x1()=default;
    Stone3x1(std::shared_ptr<b2World> world, std::vector<std::shared_ptr<sf::Texture>> textures, float coord_x, float coord_y, bool rotated=false);
};

#endif