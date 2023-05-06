#include "bird.hpp"



Bird::Bird(const std::shared_ptr<b2World>& world, float density, float coord_x, float coord_y, b2Vec2 velocity, const sf::Texture& t): Entity(world){
    //General information
    this->health = 3000;
    this->type.main_type = TYPE_DATA::BIRD;

    this->sprite = sf::Sprite(t);
    this->sprite.setOrigin((float)t.getSize().x/2, (float)t.getSize().y/2);

    b2BodyDef bdef;
    bdef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    float ptr = 10;
    b2PolygonShape shape;
    shape.SetAsBox(20/ptr, 20/ptr);

    bdef.type=b2_dynamicBody;
    ////ball///
    bdef.position.Set(coord_x,coord_y);
    b2CircleShape circle;
    circle.m_radius=20/ptr;

    this->m_body = world->CreateBody(&bdef);
    b2FixtureDef fdef;
    fdef.shape = &circle;
    fdef.restitution = 0.5f;
    fdef.density = density;
    fdef.friction=1;
    m_body->CreateFixture(&fdef);
    m_body->SetLinearVelocity(velocity);

    t2.loadFromFile("textures/boxes/wood/wood_1x1.png");
}

void Bird::update() {
    float angle = m_body->GetAngle();
    b2Vec2 pos = m_body->GetPosition();

    sprite.setRotation(angle*DEG);
    sprite.setPosition(pos.x*SCALE+20, pos.y*SCALE+20);
}

void Bird::startCollision(){
    //sprite.setTexture(t2);
    double linear_velocity = sqrt(pow(this->m_body->GetLinearVelocity().x, 2)+pow(this->m_body->GetLinearVelocity().y, 2));
    double mass = this->m_body->GetMass();
    this->health -= (mass*pow(linear_velocity, 2))/2;
    std::cout<<this->health<<std::endl;
    if(this->health <= 0){
        destroyed = true;
    }
}

void Bird::endCollision(){

}

void Bird::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(this->sprite, states);
}