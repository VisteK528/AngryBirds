//
// Created by piotr on 5/4/23.
//

#ifndef ANGRYBIRDS_ENTITY_HPP
#define ANGRYBIRDS_ENTITY_HPP


#include <SFML/Graphics.hpp>
#include "box2d/include/box2d/box2d.h"
#include <memory>
#include <string>

struct TYPE_DATA{
    typedef enum{BIRD, BOX, PIG} TYPE;
    typedef enum{
        RED_BIRD,
        YELLOW_BIRD,
        FAT_RED_BIRD,
        GREY_BIRD,
        BLACK_BIRD,
        WOOD,
        STONE,
        GLASS,
        BASIC_PIG,
        ARMORED_PIG
    } SUBTYPE;

    TYPE main_type;
    SUBTYPE sub_type;
};

class Entity: public sf::Drawable {
protected:
    const float SCALE = 10.0f;
    const float DEG = 57.29577f;

    std::shared_ptr<b2World> world;
    b2Body* m_body;
    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture;
    double health=0;
    int score=0;

    bool coliding;
    bool destroyed;
    TYPE_DATA type;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    b2Body* getBody();
    const TYPE_DATA &getType() const;
    bool getDestroyed() const;
    virtual double getHealth() const;
    virtual void startCollision(b2Body* body_b)=0;
    virtual void endCollision(b2Body* body_b)=0;
    virtual void update()=0;
    void setDestroyed();

    int getScore();

    Entity();
    Entity(std::shared_ptr<b2World> world);
};


#endif //ANGRYBIRDS_ENTITY_HPP
