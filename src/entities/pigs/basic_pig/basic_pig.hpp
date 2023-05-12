#ifndef BASIC_PIG_HPP
#define BASIC_PIG_HPP

#include "../pig.hpp"

class BasicPig: public Pig
{
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void setTexture();
public:
    BasicPig(){};
    BasicPig(std::shared_ptr<b2World> world, float coord_x, float coord_y);
};

#endif