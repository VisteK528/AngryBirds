//
// Created by piotr on 5/4/23.
//

#ifndef ANGRYBIRDS_ENTITY_HPP
#define ANGRYBIRDS_ENTITY_HPP


#include <SFML/Graphics.hpp>
#include "../../box2d/include/box2d/box2d.h"
#include <memory>
#include <string>

typedef enum{BIRD, BOX, ENEMY} TYPE;

class Entity: public sf::Drawable {
protected:
    const float SCALE = 10.0f;
    const float DEG = 57.29577f;

    std::shared_ptr<b2World> world;
    b2Body* m_body;
    sf::Sprite sprite;
    std::unique_ptr<sf::Texture> texture;

    bool coliding;
    bool destroyed;
    TYPE type;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    b2Body* getBody();
    bool getDestroyed() const;
    virtual void startCollision()=0;
    virtual void endCollision()=0;
    virtual void update()=0;
    Entity();
    Entity(std::shared_ptr<b2World> world);
};


#endif //ANGRYBIRDS_ENTITY_HPP
