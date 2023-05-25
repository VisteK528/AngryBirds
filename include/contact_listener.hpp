#ifndef ANGRYBIRDS_CONTACT_LISTENER_HPP
#define ANGRYBIRDS_CONTACT_LISTENER_HPP

#include "box2d/include/box2d/box2d.h"
#include "include/entities/entity.hpp"
#include "include/entities/birds/bird.hpp"
#include "include/entities/boxes/box.hpp"
#include "include/entities/boxes/wood/wood.hpp"
#include "include/entities/boxes/stone/stone.hpp"
#include "include/entities/boxes/glass/glass.hpp"
#include "src/entities/pigs/pig.hpp"
#include "src/entities/pigs/basic_pig/basic_pig.hpp"
#include <iostream>


class ContactListener: public b2ContactListener {
public:
    ContactListener();
    ~ContactListener();
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
};


#endif //ANGRYBIRDS_CONTACT_LISTENER_HPP
