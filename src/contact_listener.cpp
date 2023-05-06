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
        if(dataB != 0){
            i->startCollision(bodyB);
        }
    }

    if(dataB != 0){
        auto *i2 = reinterpret_cast<Entity *>(dataB);
        if(dataA != 0){
            i2->startCollision(bodyA);
        }
    }
}
void ContactListener::EndContact(b2Contact* contact){
    /*uintptr_t data = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    if(data != 0){
        reinterpret_cast<Entity*>(data)->endCollision();
    }

    uintptr_t data2 = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    if(data2 != 0){
        reinterpret_cast<Entity*>(data2)->endCollision();
    }*/
}