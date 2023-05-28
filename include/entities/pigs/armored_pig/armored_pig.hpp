#ifndef ARMORED_PIG_HPP
#define ARMORED_PIG_HPP

#include "include/entities/pigs/pig.hpp"

class ArmoredPig: public Pig
{
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    ArmoredPig()=default;
    ArmoredPig(std::shared_ptr<b2World> world, std::vector<std::shared_ptr<sf::Texture>> textures, float coord_x, float coord_y);
};

#endif