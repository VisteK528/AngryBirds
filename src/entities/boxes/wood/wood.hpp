#ifndef WOOD_HPP
#define WOOD_HPP

#include "../box.hpp"

class Wood: public Box
{
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    Wood()=default;
    Wood(std::shared_ptr<b2World> world, std::vector<std::shared_ptr<sf::Texture>> textures, float coord_x, float coord_y);
};

#endif