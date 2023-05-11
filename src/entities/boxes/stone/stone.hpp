#ifndef STONE_HPP
#define STONE_HPP

#include "../box.hpp"

class Stone: public Box
{
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    Stone()=default;
    Stone(std::shared_ptr<b2World> world, std::vector<std::shared_ptr<sf::Texture>> textures, float coord_x, float coord_y);
};

#endif