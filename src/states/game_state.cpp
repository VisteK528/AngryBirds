#include "game_state.hpp"

std::vector<std::shared_ptr<sf::Texture>> makeShared(std::vector<sf::Texture> &textures) {
    std::vector<std::shared_ptr<sf::Texture>> shared_vector;
    shared_vector.reserve(textures.size());
    for(const sf::Texture& texture: textures){
        shared_vector.push_back(std::make_shared<sf::Texture>(texture));
    }
    return shared_vector;
}

GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states): State(window, states) {
    init();
    initWorld();
}

GameState::~GameState() {

}

void GameState::init() {
    loadTextures();
}

// std::unordered_map<TEXTURE_TYPE, std::vector<sf::Texture>> table
void GameState::loadTextures() {
    // Paths for all textures
    std::vector<std::string> other_textures_paths = {
            "textures/background.png",
    };

    for(const std::string& path: other_textures_paths){
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

    // Paths for entities' textures to be loaded
    std::unordered_map<TEXTURE_TYPE, std::vector<std::string>> textures_paths = {
            {WOOD, {"textures/boxes/wood/wood_1x1.png", "textures/boxes/wood/wood_1x1_damaged.png", "textures/boxes/wood/wood_1x1_destroyed.png"}},
            {WOOD3x1, {"textures/boxes/wood/wood_3x1.png", "textures/boxes/wood/wood_3x1_damaged.png", "textures/boxes/wood/wood_3x1_damaged.png"}},
            {GLASS, {"textures/boxes/glass/glass_1x1.png", "textures/boxes/glass/glass_1x1_damaged.png", "textures/boxes/glass/glass_1x1_destroyed.png"}},
            {GLASS3x1, {"textures/boxes/glass/glass_3x1.png", "textures/boxes/glass/glass_3x1_damaged.png", "textures/boxes/glass/glass_3x1_damaged.png"}},
            {STONE, {"textures/boxes/stone/stone_1x1.png", "textures/boxes/stone/stone_1x1_damaged.png", "textures/boxes/stone/stone_1x1_destroyed.png"}},
            {STONE3x1, {"textures/boxes/stone/stone_3x1.png", "textures/boxes/stone/stone_3x1_damaged.png", "textures/boxes/stone/stone_3x1_damaged.png"}},
            {PIG, {"textures/pigs/basic/basic_pig.png", "textures/pigs/basic/basic_pig_damaged.png", "textures/pigs/basic/basic_pig_destroyed.png"}},
            {RED_BIRD, {"textures/birds/bird_red.png"}},
            {YELLOW_BIRD, {"textures/birds/bird_yellow.png"}},
            {GREY_BIRD, {"textures/birds/bird_blue.png"}},
            {FAT_RED_BIRD, {"textures/birds/bird_red.png"}},
            };
    
    for(const auto& pair: textures_paths){
        TEXTURE_TYPE type = pair.first;
        std::vector<sf::Texture> loaded_textures;
        for(const std::string& path: pair.second){
            sf::Texture t;
            if(!t.loadFromFile(path)){
                throw exceptions::TexturesLoadingError("Program couldn't load all graphics properly!");
            }
            loaded_textures.push_back(t);
        }
        // Smoothing the textures
        for(auto &t: loaded_textures){
            t.setSmooth(true);
        }
        entities_textures[type] = loaded_textures;
    }
}

void GameState::initWorld() {
    this->gravity = b2Vec2(0.0f, 9.81f);
    this->world = std::make_shared<b2World>(this->gravity);
    this->contact_listener = ContactListener();
    this->world->SetContactListener(&contact_listener);

    this->entity_manager = std::make_shared<EntityManager>(this->world);

    std::vector<std::shared_ptr<sf::Texture>> red_bird_t = makeShared(entities_textures[RED_BIRD]);
    std::vector<std::shared_ptr<sf::Texture>> yellow_bird_t = makeShared(entities_textures[YELLOW_BIRD]);
    std::vector<std::shared_ptr<sf::Texture>> grey_bird_t = makeShared(entities_textures[GREY_BIRD]);

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

    BoxFactory<Wood> wood_fact(world, makeShared(entities_textures[WOOD]));
    BoxFactory<Wood3x1> wood3x1_fact(world, makeShared(entities_textures[WOOD3x1]));
    BoxFactory<Glass> glass_fact(world, makeShared(entities_textures[GLASS]));
    BoxFactory<Glass3x1> glass3x1_fact(world, makeShared(entities_textures[GLASS3x1]));
    BoxFactory<Stone> stone_fact(world, makeShared(entities_textures[STONE]));
    BoxFactory<Stone3x1> stone3x1_fact(world, makeShared(entities_textures[STONE3x1]));

    // Ustawienie boxów
    entity_manager->pushEntity(wood3x1_fact.createBoxRotated(90.f, 50.f));
    entity_manager->pushEntity(wood3x1_fact.createBox(80.f, 50.f));

    entity_manager->pushEntity(glass3x1_fact.createBoxRotated(50.f, 56.f));
    entity_manager->pushEntity(glass_fact.createBox(52.f, 60.f));
    entity_manager->pushEntity(glass_fact.createBox(52.f, 56.f));
    entity_manager->pushEntity(glass_fact.createBox(52.f, 52.f));
    entity_manager->pushEntity(glass_fact.createBox(54.f, 60.f));
    entity_manager->pushEntity(glass_fact.createBox(54.f, 56.f));
    entity_manager->pushEntity(glass_fact.createBox(54.f, 52.f));
    entity_manager->pushEntity(glass3x1_fact.createBox(52.f, 48.f));

    entity_manager->pushEntity(stone3x1_fact.createBoxRotated(95.f, 60.f));
    entity_manager->pushEntity(wood_fact.createBox(100.f, 60.f));
    entity_manager->pushEntity(wood_fact.createBox(100.f, 56.f));
    entity_manager->pushEntity(wood_fact.createBox(100.f, 52.f));
    entity_manager->pushEntity(stone_fact.createBox(105.f, 60.f));
    entity_manager->pushEntity(stone_fact.createBox(105.f, 56.f));
    entity_manager->pushEntity(stone_fact.createBox(105.f, 52.f));
    entity_manager->pushEntity(glass_fact.createBox(110.f, 60.f));
    entity_manager->pushEntity(glass_fact.createBox(110.f, 56.f));
    entity_manager->pushEntity(glass_fact.createBox(110.f, 52.f));

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
