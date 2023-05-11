#ifndef WOOD_HPP
#define WOOD_HPP

#include "../box.hpp"

class Wood: public Box
{
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void setTexture() override;
public:
    Wood(){};
    Wood(std::shared_ptr<b2World> world, float coord_x, float coord_y);
};

#endif