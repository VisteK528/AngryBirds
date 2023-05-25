#include "cannon.hpp"

Cannon::Cannon(sf::Vector2f position, std::shared_ptr<EntityManager> manager) {
    this->manager = std::move(manager);
    this->loading = false;

    hull_texture.loadFromFile("textures/cannon/cannon_base.png");
    hull_texture.setSmooth(true);

    hull_sprite.setOrigin(hull_texture.getSize().x / 2, hull_texture.getSize().y / 2);
    hull_sprite.setPosition(position);
    hull_sprite.setTexture(hull_texture);

    cannon_texture.loadFromFile("textures/cannon/cannon.png");
    cannon_texture.setSmooth(true);

    cannon_sprite.setOrigin(cannon_texture.getSize().x / 2 - 20, cannon_texture.getSize().y / 2);
    cannon_position = {position.x + 40,
                       position.y - hull_texture.getSize().y / 2 - cannon_texture.getSize().y / 2 + 25};
    cannon_sprite.setPosition(cannon_position);
    cannon_sprite.setTexture(cannon_texture);
}

void Cannon::update(sf::Vector2f mouse_position){
    angle = std::atan2(mouse_position.y - cannon_sprite.getPosition().y, mouse_position.x - cannon_sprite.getPosition().x);
    cannon_sprite.setRotation(angle * 57.29577);

    if(!this->manager->isBirdActive()){
        active = true;
    }

    // Activity factor set depending on number of available birds
    if(this->birds.empty()){
        active = false;
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && active && loading){
        if(power < max_power){
            power += power_gain;
        }
    }
}

void Cannon::handleInput(const sf::Event e){
    if(e.type == sf::Event::MouseButtonPressed && active){
        if(e.mouseButton.button == sf::Mouse::Left){
            loading = true;
        }
    }

    if(e.type == sf::Event::MouseButtonReleased && active){
        if(e.mouseButton.button == sf::Mouse::Middle){
            if(bird_index < 3){
                bird_index++;
            }
            else{
                bird_index = 0;
            }
        }

        if(e.mouseButton.button == sf::Mouse::Left){
            loading = false;
            sf::Vector2f position = {cannon_sprite.getPosition().x-20 + (cannon_texture.getSize().x / 2 + 20) * std::cos(angle), cannon_sprite.getPosition().y-20 + (cannon_texture.getSize().x / 2 + 20) * std::sin(angle)};

            if(!birds.empty()){
                float SCALE = 10;
                std::unique_ptr<Bird> bird = std::move(birds[0]);
                bird->setPosition(b2Vec2(position.x/SCALE, position.y/SCALE));
                bird->setActive(true);
                if(bird->getType().sub_type == TYPE_DATA::FAT_RED_BIRD){
                    b2Vec2 velocity(0.5f*power*std::cos(angle), 0.5f*power*std::sin(angle));
                    bird->applyLinearVelocity(velocity);
                    this->manager->pushEntity( std::move(bird));
                }
                else{
                    b2Vec2 velocity(power*std::cos(angle), power*std::sin(angle));
                    bird->applyLinearVelocity(velocity);
                    this->manager->pushEntity(std::move(bird));
                }
                birds.erase(birds.begin());
                setBirdsVisualPosition();
            }
            power = 0;

            //active = false;
        }
    }
}

void Cannon::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(cannon_sprite, states);
    target.draw(hull_sprite, states);

    for(const auto& bird: birds){
        target.draw(*bird);
    }
}

void Cannon::setBirds(std::vector<std::unique_ptr<Bird>>& birds_vector) {
    this->birds = std::move(birds_vector);

    setBirdsVisualPosition();
}

void Cannon::setBirdsVisualPosition() {
    int i = 0;
    for(const auto& bird: birds){
        float radius = bird->getBody()->GetFixtureList()->GetShape()->m_radius;
        bird->setPosition(b2Vec2(20-i*7.f, 62-radius));
        bird->update();
        i++;
    }
}

float Cannon::getPower() const {
    return power;
}

float Cannon::getMaxPower() const {
    return max_power;
}

bool Cannon::isActive() const {
    return this->active;
}

CannonPowerWidget::CannonPowerWidget(float coord_x, float coord_y, float cannon_max_power) {
    this->outline_rectangle_widget = sf::RectangleShape({300, 30});
    this->outline_rectangle_widget.setPosition({coord_x, coord_y});
    this->outline_rectangle_widget.setFillColor(sf::Color::Transparent);
    this->outline_rectangle_widget.setOutlineThickness(2.f);
    this->outline_rectangle_widget.setOutlineColor(sf::Color::Black);

    this->fill_rectangle_widget = sf::RectangleShape({0, 30});
    this->fill_rectangle_widget.setPosition({coord_x, coord_y});
    this->fill_rectangle_widget.setFillColor(sf::Color::Yellow);

    this->cannon_max_power = cannon_max_power;
}

void CannonPowerWidget::update(float cannon_power, bool cannon_active) {
    if(cannon_active){
        this->fill_rectangle_widget.setSize({(cannon_power/this->cannon_max_power)*300, 30});
    }
    else{
        this->fill_rectangle_widget = sf::RectangleShape({0, 30});
    }
}

void CannonPowerWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const{
   target.draw(outline_rectangle_widget, states);
   target.draw(fill_rectangle_widget, states);
}

int Cannon::getBirdsCount() const {
    return birds.size();
}