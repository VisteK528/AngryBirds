#ifndef BIRD_HPP
#define BIRD_HPP

#include <SFML/Graphics.hpp>
#include "../box2d/include/box2d/box2d.h"
#include "../box2d/include/box2d/b2_settings.h"
#include <memory>
#include <string>

class Data
{
    public:
        std::string text;
        int test_number = 5;
        int number;
};

class Bird: public sf::Drawable
{
    private:
        Data data;
        b2Body* m_body;
        sf::Sprite sprite;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    public:
        void update();
        Bird(){};
        Bird(std::shared_ptr<b2World> world, float density, float coord_x, float coord_y, b2Vec2 velocity, std::string name, const sf::Texture& t);   //: my_body(NULL){};
};

#endif