#ifndef BASIC_PIG_HPP
#define BASIC_PIG_HPP

#include "include/entities/pigs/pig.hpp"

class BasicPig final: public Pig
{
    public:
        BasicPig()=default;
        BasicPig(b2WorldId world, const std::vector<std::shared_ptr<sf::Texture>>& textures, float coord_x, float coord_y);
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif