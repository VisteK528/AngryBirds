#include "game_state.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states): State(window, states) {
    init();
    initWorld();
}

GameState::~GameState() {

}

void GameState::init() {
    sf::Texture t1, t2, t3, t4, t5, t6, t7;
    t1.loadFromFile("textures/background.png");
    t2.loadFromFile("textures/birds/bird_red.png");
    t3.loadFromFile("textures/birds/bird_blue.png");
    t4.loadFromFile("textures/birds/bird_yellow.png");
    t5.loadFromFile("textures/boxes/wood/wood_1x1.png");
    t6.loadFromFile("textures/boxes/stone/stone_1x1.png");
    t7.loadFromFile("textures/boxes/glass/glass_1x1.png");

    textures = {t1, t2, t3, t4, t5, t6, t7};

    // Wygładzanie tekstur
    for(auto &t: textures){
        t.setSmooth(true);
    }
}

void GameState::initWorld() {
    this->gravity = b2Vec2(0.0f, 9.81f);
    this->world = std::make_shared<b2World>(this->gravity);
    this->contact_listener = ContactListener();

    this->world->SetContactListener(&contact_listener);

    this->entity_manager = std::make_unique<EntityManager>(this->world);
    // INFORMACJE O ŚWIECIE
    // 1 metr = 10 pikseli
    // 1 stopień = 57.29577 radiana
    // Świat ma wymiary 1280x720 pikseli
    // Świat ma wymiary 128x72 metry

    background = sf::Sprite(textures[0]);
    entity_manager->pushEntity(std::make_unique<Bird>(this->world, 0.2f, 5.f, 1.f, b2Vec2(-20,0), textures[1]));
    entity_manager->pushEntity(std::make_unique<Bird>(this->world, 0.2f, 20.f, 0.5f, b2Vec2(3, 5), textures[2]));
    entity_manager->pushEntity(std::make_unique<Bird>(this->world, 0.2f, 10.f, 0.5f, b2Vec2(0, 0), textures[3]));

    // Ustawienie boxów
    entity_manager->pushEntity(std::make_unique<Box>(this->world, 0.2f, 3.f, 60.f, textures[4]));
    entity_manager->pushEntity(std::make_unique<Box>(this->world, 0.2f, 7.f, 60.f, textures[4]));
    entity_manager->pushEntity(std::make_unique<Box>(this->world, 0.2f, 11.f, 60.f, textures[6]));
    entity_manager->pushEntity(std::make_unique<Box>(this->world, 0.2f, 7.f, 56.f, textures[6]));
    entity_manager->pushEntity(std::make_unique<Box>(this->world, 0.2f, 7.f, 52.f, textures[5]));
    entity_manager->pushEntity(std::make_unique<Box>(this->world, 0.2f, 7.f, 48.f, textures[5]));

    // Podłoże
    setWall(640, 630, 1280, 10);
    // Prawa ściana
    setWall(1280, 360, 10, 640);
    // Lewa ściana
    setWall(0, 360, 10, 640);
}

void GameState::update(const float &dt) {
    world->Step(dt, 8, 3);
    entity_manager->update();
}

void GameState::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background);
    entity_manager->render(target);
}

void GameState::setWall(int x, int y, int w, int h)
{
    b2PolygonShape gr;
    gr.SetAsBox(w/SCALE, h/SCALE);

    b2BodyDef bdef;
    bdef.position.Set(x/SCALE, y/SCALE);

    b2Body *b_ground = this->world->CreateBody(&bdef);
    b_ground->CreateFixture(&gr, 1);
}
