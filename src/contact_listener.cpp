//
// Created by piotr on 5/4/23.
//

#include "contact_listener.hpp"

ContactListener::ContactListener() {

}
ContactListener::~ContactListener(){

}

void ContactListener::BeginContact(b2Contact* contact){
    b2BodyUserData& data = contact->GetFixtureA()->GetBody()->GetUserData();
    if(data.pointer != 0){
        Entity *entity = reinterpret_cast<Entity *>(data.pointer);
        entity->startCollision();
    }

    uintptr_t data2 = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    if(data2 != 0){
        reinterpret_cast<Entity*>(data2)->startCollision();
    }
}
void ContactListener::EndContact(b2Contact* contact){
    uintptr_t data = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    if(data != 0){
        reinterpret_cast<Entity*>(data)->endCollision();
    }

    uintptr_t data2 = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    if(data2 != 0){
        reinterpret_cast<Entity*>(data2)->endCollision();
    }
}