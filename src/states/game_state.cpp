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

    this->entity_manager = std::make_shared<EntityManager>(this->world);

    std::unique_ptr<Bird> bird1 = std::make_unique<YellowBird>(this->entity_manager->getWorld(), 40, 50);
    std::unique_ptr<Bird> bird2 = std::make_unique<YellowBird>(this->entity_manager->getWorld(), 50, 50);
    std::unique_ptr<Bird> bird3 = std::make_unique<FatRedBird>(this->entity_manager->getWorld(), 60, 50);

    std::vector<std::unique_ptr<Bird>> birds = {};
    birds.push_back(std::move(bird1));
    birds.push_back(std::move(bird2));
    birds.push_back(std::move(bird3));

    this->cannon = std::make_unique<Cannon>(sf::Vector2f(100, 600), this->entity_manager);
    this->cannon->setBirds(birds);

    // INFORMACJE O ŚWIECIE
    // 1 metr = 10 pikseli
    // 1 stopień = 57.29577 radiana
    // Świat ma wymiary 1280x720 pikseli
    // Świat ma wymiary 128x72 metry

    background = sf::Sprite(textures[0]);

    // Ustawienie boxów
    /*entity_manager->pushEntity(std::make_unique<Wood>(this->world, 80.f, 10.f));

    entity_manager->pushEntity(std::make_unique<Wood>(this->world, 50.f, 60.f));
    entity_manager->pushEntity(std::make_unique<Wood>(this->world, 50.f, 56.f));
    entity_manager->pushEntity(std::make_unique<Wood>(this->world, 50.f, 52.f));
    entity_manager->pushEntity(std::make_unique<Wood>(this->world, 52.f, 60.f));
    entity_manager->pushEntity(std::make_unique<Wood>(this->world, 52.f, 56.f));
    entity_manager->pushEntity(std::make_unique<Wood>(this->world, 52.f, 52.f));
    entity_manager->pushEntity(std::make_unique<Wood>(this->world, 54.f, 60.f));
    entity_manager->pushEntity(std::make_unique<Wood>(this->world, 54.f, 56.f));
    entity_manager->pushEntity(std::make_unique<Wood>(this->world, 54.f, 52.f));*/


    entity_manager->pushEntity(std::make_unique<Wood>(this->world, 100.f, 60.f));
    entity_manager->pushEntity(std::make_unique<Wood>(this->world, 100.f, 56.f));
    entity_manager->pushEntity(std::make_unique<Wood>(this->world, 100.f, 52.f));
    entity_manager->pushEntity(std::make_unique<Stone>(this->world, 105.f, 60.f));
    entity_manager->pushEntity(std::make_unique<Stone>(this->world, 105.f, 56.f));
    entity_manager->pushEntity(std::make_unique<Stone>(this->world, 105.f, 52.f));
    entity_manager->pushEntity(std::make_unique<Glass>(this->world, 110.f, 60.f));
    entity_manager->pushEntity(std::make_unique<Glass>(this->world, 110.f, 56.f));
    entity_manager->pushEntity(std::make_unique<Glass>(this->world, 110.f, 52.f));

    // Ustawienie świń
    entity_manager->pushEntity(std::make_unique<BasicPig>(this->world, 105.f, 48.f));
    entity_manager->pushEntity(std::make_unique<BasicPig>(this->world, 105.f, 44.f));
    entity_manager->pushEntity(std::make_unique<BasicPig>(this->world, 105.f, 40.f));

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

    sf::Vector2f mouse_position = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), this->window->getView());
    cannon->update(mouse_position);
}

void GameState::handleEvent(const sf::Event &e) {
    cannon->handleInput(e);
}

void GameState::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background);
    target->draw(*cannon);
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
