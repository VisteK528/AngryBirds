#include "game_state.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states): State(window, states) {
    init();
    initWorld();
}

GameState::~GameState() {

}

void GameState::init() {
    loadTextures();
}

void GameState::loadTextures() {
    std::vector<std::string> textures_paths = {
            "textures/background.png",
            "textures/birds/bird_red.png",
            "textures/birds/bird_blue.png",
            "textures/birds/bird_yellow.png",
            "textures/boxes/wood/wood_1x1.png",
            "textures/boxes/stone/stone_1x1.png",
            "textures/boxes/glass/glass_1x1.png",
    };

    for(const std::string& path: textures_paths){
        sf::Texture t;
        if(!t.loadFromFile(path)){
            throw exceptions::TexturesLoadingError("Program couldn't load all graphics properly!");
        }
        textures.push_back(t);
    }

    // Smoothing the textures
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

    std::vector<std::shared_ptr<sf::Texture>> red_bird_t = {std::make_shared<sf::Texture>(textures[1])};
    std::vector<std::shared_ptr<sf::Texture>> yellow_bird_t = {std::make_shared<sf::Texture>(textures[3])};
    std::vector<std::shared_ptr<sf::Texture>> grey_bird_t = {std::make_shared<sf::Texture>(textures[2])};

    // Bird Factories
    BirdFactory<Bird> red_factory(this->world, red_bird_t);
    BirdFactory<YellowBird> yellow_factory(this->world, yellow_bird_t);
    BirdFactory<FatRedBird> red_fat_factory(this->world, red_bird_t);
    BirdFactory<GreyBird> grey_factory(this->world, grey_bird_t);

    std::vector<std::unique_ptr<Bird>> birds = {};
    birds.push_back(red_factory.createBird());
    birds.push_back(yellow_factory.createBird());
    birds.push_back(red_fat_factory.createBird());
    birds.push_back(grey_factory.createBird());

    this->cannon = std::make_unique<Cannon>(sf::Vector2f(100, 600), this->entity_manager);
    this->cannon->setBirds(birds);

    this->cannon_power_widget = CannonPowerWidget(10, 10, this->cannon->getMaxPower());

    // INFORMACJE O ŚWIECIE
    // 1 metr = 10 pikseli
    // 1 stopień = 57.29577 radiana
    // Świat ma wymiary 1280x720 pikseli
    // Świat ma wymiary 128x72 metry

    background = sf::Sprite(textures[0]);

    // Ustawienie boxów
    entity_manager->pushEntity(std::make_unique<Wood3x1>(this->world, 90.f, 50.f, true));
    entity_manager->pushEntity(std::make_unique<Wood3x1>(this->world, 80.f, 50.f));

    entity_manager->pushEntity(std::make_unique<Glass3x1>(this->world, 50.f, 56.f, true));
    entity_manager->pushEntity(std::make_unique<Glass>(this->world, 52.f, 60.f));
    entity_manager->pushEntity(std::make_unique<Glass>(this->world, 52.f, 56.f));
    entity_manager->pushEntity(std::make_unique<Glass>(this->world, 52.f, 52.f));
    entity_manager->pushEntity(std::make_unique<Glass>(this->world, 54.f, 60.f));
    entity_manager->pushEntity(std::make_unique<Glass>(this->world, 54.f, 56.f));
    entity_manager->pushEntity(std::make_unique<Glass>(this->world, 54.f, 52.f));
    entity_manager->pushEntity(std::make_unique<Glass3x1>(this->world, 52.f, 48.f));

    entity_manager->pushEntity(std::make_unique<Stone3x1>(this->world, 95.f, 60.f, true));
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
    setWall(-30, 360, 10, 640);
}

void GameState::update(const float &dt) {
    world->Step(dt, 8, 3);
    entity_manager->update();

    sf::Vector2f mouse_position = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), this->window->getView());
    cannon->update(mouse_position);
    cannon_power_widget.update(cannon->getPower(), cannon->isActive());
}

void GameState::handleEvent(const sf::Event &e) {
    cannon->handleInput(e);
}

void GameState::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background);
    target->draw(*cannon);
    entity_manager->render(target);
    target->draw(cannon_power_widget);
}

void GameState::setWall(int x, int y, int w, int h)
{
    b2PolygonShape gr;
    gr.SetAsBox(w/SCALE, h/SCALE);

    b2BodyDef bdef;
    bdef.position.Set(x/SCALE, y/SCALE);
    bdef.type=b2_staticBody;
    b2Body *b_ground = this->world->CreateBody(&bdef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &gr;
    fixtureDef.density = 1000;
    fixtureDef.friction = 0.5;
    fixtureDef.restitution = 0.5;
    b_ground->CreateFixture(&fixtureDef);
}
