//
// Created by piotr on 5/4/23.
//

#include "contact_listener.hpp"

ContactListener::ContactListener() {

}
ContactListener::~ContactListener(){

}

void ContactListener::BeginContact(b2Contact* contact){
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    uintptr_t dataA = bodyA->GetUserData().pointer;

    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    uintptr_t dataB = bodyB->GetUserData().pointer;

    if(dataA != 0){
        auto *i = reinterpret_cast<Entity *>(dataA);
        i->startCollision(bodyB);
    }

    if(dataB != 0){
        auto *i2 = reinterpret_cast<Entity *>(dataB);
        i2->startCollision(bodyA);
    }
}
void ContactListener::EndContact(b2Contact* contact){
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    uintptr_t dataA = bodyA->GetUserData().pointer;

    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    uintptr_t dataB = bodyB->GetUserData().pointer;

    if(dataA != 0){
        auto *i = reinterpret_cast<Entity *>(dataA);
        i->endCollision(bodyB);
    }

    if(dataB != 0){
        auto *i2 = reinterpret_cast<Entity *>(dataB);
        i2->endCollision(bodyA);
    }
}