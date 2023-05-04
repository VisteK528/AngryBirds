//
// Created by piotr on 5/4/23.
//

#ifndef ANGRYBIRDS_CONTACT_LISTENER_HPP
#define ANGRYBIRDS_CONTACT_LISTENER_HPP

#include "../box2d/include/box2d/box2d.h"
#include "entities/entity.hpp"
#include "entities/bird.hpp"


class ContactListener: public b2ContactListener {
public:
    ContactListener();
    ~ContactListener();
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
};


#endif //ANGRYBIRDS_CONTACT_LISTENER_HPP
