#ifndef BASIC_PIG_HPP
#define BASIC_PIG_HPP

#include "../pig.hpp"

class BasicPig: public Pig
{
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    BasicPig()=default;
    BasicPig(std::shared_ptr<b2World> world, std::vector<std::shared_ptr<sf::Texture>> textures, float coord_x, float coord_y);
};

#endif