#ifndef BIRD_HPP
#define BIRD_HPP

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

class Bird
{
    private:
        Data data;
        b2Body* my_body;
    public:
        Bird(b2World *world, float density, float coord_x, float coord_y, b2Vec2 velocity, std::string name);   //: my_body(NULL){};
};

#endif