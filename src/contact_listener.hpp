//
// Created by piotr on 5/4/23.
//

#ifndef ANGRYBIRDS_CONTACT_LISTENER_HPP
#define ANGRYBIRDS_CONTACT_LISTENER_HPP

#include "../box2d/include/box2d/box2d.h"
#include "entities/entity.hpp"
#include "entities/birds/bird.hpp"
#include "entities/boxes/box.hpp"
#include "entities/boxes/wood/wood.hpp"
#include "entities/boxes/stone/stone.hpp"
#include "entities/boxes/glass/glass.hpp"
#include "entities/pigs/pig.hpp"
#include "entities/pigs/basic_pig/basic_pig.hpp"
#include <iostream>


class ContactListener: public b2ContactListener {
public:
    ContactListener();
    ~ContactListener();
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
};


#endif //ANGRYBIRDS_CONTACT_LISTENER_HPP
