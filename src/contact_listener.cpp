//
// Created by piotr on 5/4/23.
//

#include "contact_listener.hpp"

ContactListener::ContactListener() {

}
ContactListener::~ContactListener(){

}

void ContactListener::BeginContact(b2Contact* contact){
    uintptr_t data = contact->GetFixtureA()->GetBody()->GetUserData().pointer;

    if(data != 0){
        auto *i = reinterpret_cast<Entity *>(data);
        i->startCollision();
    }

    b2Body* body2 = contact->GetFixtureB()->GetBody();
    uintptr_t data2 = body2->GetUserData().pointer;

    if(data2 != 0){
        auto *i2 = reinterpret_cast<Entity *>(data2);
        i2->startCollision();
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