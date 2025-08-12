#ifndef ARMORED_PIG_HPP
#define ARMORED_PIG_HPP

#include "include/entities/pigs/pig.hpp"

class ArmoredPig final: public Pig
{
    public:
        ArmoredPig()=default;
        ArmoredPig(b2WorldId world, const std::vector<std::shared_ptr<sf::Texture>>& textures, float coord_x, float coord_y);
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif