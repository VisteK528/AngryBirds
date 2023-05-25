#ifndef GLASS_HPP
#define GLASS_HPP

#include "include/entities/boxes/box.hpp"

class Glass: public Box
{
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    Glass()=default;
    Glass(std::shared_ptr<b2World> world, std::vector<std::shared_ptr<sf::Texture>> textures, float coord_x, float coord_y);
};

#endif