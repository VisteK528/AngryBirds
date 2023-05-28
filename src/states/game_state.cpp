#include "include/states/game_state.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states,
                     std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager,
                     std::string level_path): State(std::move(window), std::move(states),
                                                    std::move(gui_manager), std::move(sound_manager)) {

    this->score_text = nullptr;
    this->level_path = level_path;
    init();
    initWorld();
}

GameState::~GameState() {

}

void GameState::init() {
    this->sound_manager->getBackgroundMusic().stop();
    this->sound_manager->setBackgroundMusic("sounds/ingame_music.wav");
    this->sound_manager->getBackgroundMusic().setLoop(true);
    this->sound_manager->getBackgroundMusic().play();
    loadTextures(background_textures, entities_textures);

    this->score_text = gui_manager->createText("Score: "+std::to_string(this->score), 15, sf::Vector2f(1100, 20), ui::ORIGIN::C);
}

std::vector<std::unique_ptr<Bird>> GameState::loadWorld(const std::string& level_path) {
    std::ifstream file;
    file.open(level_path);

    std::vector<std::shared_ptr<sf::Texture>> red_bird_t = makeShared(entities_textures[RED_BIRD]);
    std::vector<std::shared_ptr<sf::Texture>> big_bird_t = makeShared(entities_textures[FAT_RED_BIRD]);
    std::vector<std::shared_ptr<sf::Texture>> yellow_bird_t = makeShared(entities_textures[YELLOW_BIRD]);
    std::vector<std::shared_ptr<sf::Texture>> grey_bird_t = makeShared(entities_textures[GREY_BIRD]);

    BirdFactory<Bird> red_factory(this->world, red_bird_t);
    BirdFactory<YellowBird> yellow_factory(this->world, yellow_bird_t);
    BirdFactory<FatRedBird> red_fat_factory(this->world, big_bird_t);
    BirdFactory<GreyBird> grey_factory(this->world, grey_bird_t);

    BoxFactory<Wood> wood_fact(world, makeShared(entities_textures[WOOD]));
    BoxFactory<Wood3x1> wood3x1_fact(world, makeShared(entities_textures[WOOD3x1]));
    BoxFactory<Glass> glass_fact(world, makeShared(entities_textures[GLASS]));
    BoxFactory<Glass3x1> glass3x1_fact(world, makeShared(entities_textures[GLASS3x1]));
    BoxFactory<Stone> stone_fact(world, makeShared(entities_textures[STONE]));
    BoxFactory<Stone3x1> stone3x1_fact(world, makeShared(entities_textures[STONE3x1]));

    PigFactory<BasicPig> basic_pig_fact(world, makeShared(entities_textures[BASIC_PIG]));
    PigFactory<ArmoredPig> armored_pig_fact(world, makeShared(entities_textures[ARMORED_PIG]));

    json j;
    file >> j;

    background = sf::Sprite(background_textures[j["background"]]);
    this->gravity = b2Vec2(0.f, j["gravity"]);
    this->world->SetGravity(gravity);

    std::vector<std::unique_ptr<Bird>> birds = {};
    for(const auto& bird: j["birds"].items()){
        switch (static_cast<int>(bird.value())) {
            case 8:
                birds.push_back(red_factory.createBird());
                break;
            case 9:
                birds.push_back(yellow_factory.createBird());
                break;
            case 10:
                birds.push_back(red_fat_factory.createBird());
                break;
            case 11:
                birds.push_back(grey_factory.createBird());
                break;
            default:
                break;
        }
    }

    for(const auto& entity_array: j["entities"].items()){
        json entity_array_json = entity_array.value();
        int type = entity_array_json[0];
        std::vector<float> unscaled_position = entity_array_json[1].get<std::vector<float>>();
        std::vector<float> position = {unscaled_position[0]/SCALE, unscaled_position[1]/SCALE};
        bool rotated = entity_array_json[2].get<bool>();

        switch (type) {
            case 0:
                entity_manager->pushEntity(wood_fact.createBox(position[0], position[1]));
                break;
            case 1:
                if(rotated){
                    entity_manager->pushEntity(wood3x1_fact.createBoxRotated(position[0], position[1]));
                }
                else{
                    entity_manager->pushEntity(wood3x1_fact.createBox(position[0], position[1]));
                }
                break;
            case 2:
                entity_manager->pushEntity(stone_fact.createBox(position[0], position[1]));
                break;
            case 3:
                if(rotated){
                    entity_manager->pushEntity(stone3x1_fact.createBoxRotated(position[0], position[1]));
                }
                else{
                    entity_manager->pushEntity(stone3x1_fact.createBox(position[0], position[1]));
                }
                break;
            case 4:
                entity_manager->pushEntity(glass_fact.createBox(position[0], position[1]));
                break;
            case 5:
                if(rotated){
                    entity_manager->pushEntity(glass3x1_fact.createBoxRotated(position[0], position[1]));
                }
                else{
                    entity_manager->pushEntity(glass3x1_fact.createBox(position[0], position[1]));
                }
                break;
            case 6:
                entity_manager->pushEntity(basic_pig_fact.createPig(position[0], position[1]));
                break;
            case 7:
                entity_manager->pushEntity(armored_pig_fact.createPig(position[0], position[1]));

            default:
                break;
        }
    }
    return birds;
}

void GameState::initWorld() {
    // Initialize the world
    this->gravity = b2Vec2(0.0f, 9.81f);
    this->world = std::make_shared<b2World>(this->gravity);
    this->entity_manager = std::make_shared<EntityManager>(this->world);

    // Create contact listener and add it to the world object
    this->contact_listener = ContactListener();
    this->world->SetContactListener(&contact_listener);

    // Load world data from file
    std::vector<std::unique_ptr<Bird>> birds = loadWorld(level_path);

    // Create cannon and initialize it with the deck of loaded birds
    this->cannon = std::make_unique<Cannon>(sf::Vector2f(100, 600), this->entity_manager);
    this->cannon->setBirds(birds);
    this->cannon_power_widget = CannonPowerWidget(10, 10, this->cannon->getMaxPower());

    // INFORMACJE O ŚWIECIE
    // 1 metr = 10 pikseli
    // 1 stopień = 57.29577 radiana
    // Świat ma wymiary 1280x720 pikseli
    // Świat ma wymiary 128x72 metry

    // Ground
    setWall(640, 630, 1280, 10);

    // Right wall
    setWall(1280, 360, 10, 640);

    // Left wall
    setWall(-30, 360, 10, 640);
    running = true;
}

void GameState::update(const float &dt) {
    this->sound_manager->updateVolume();
    if(running){
        score = entity_manager->getCurrentScore();
        world->Step(dt, 8, 3);
        entity_manager->update();
        entity_manager->setBirds(cannon->getBirdsCount());

        sf::Vector2f mouse_position = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), this->window->getView());
        cannon->update(mouse_position);
        cannon_power_widget.update(cannon->getPower(), cannon->isActive());
    }
    else if(!running && !quit){
        quit = true;
        window->display();
        sf::Texture t;
        t.create(window->getSize().x, window->getSize().y);
        std::cout<<window->getSize().x<<" "<<window->getSize().y<<std::endl;
        t.update(*window);
        if(result == WIN){
            this->states->push(std::make_unique<Win>(this->window, this->states, this->gui_manager, this->sound_manager, t.copyToImage(), score));
        }
        else if(result == LOOSE){
            this->states->push(std::make_unique<Loose>(this->window, this->states, this->gui_manager, this->sound_manager, t.copyToImage(), score));
        }
        this->states->top()->init();
    }

    if(entity_manager->CountPigs() == 0){
        score += cannon->getBirdsCount()*5000;
        std::cout<<"Birds left: "<<cannon->getBirdsCount()<<std::endl;
        running = false;
        result = WIN;
    }
    else if(cannon->getBirdsCount() == 0 && entity_manager->CountBirds() == 0){
        running = false;
        result = LOOSE;
    }
    this->score_text->setString("Score: "+std::to_string(score));
}

void GameState::handleEvent(const sf::Event &e) {
    cannon->handleInput(e);

    if(e.type == sf::Event::KeyReleased){
        if(e.key.code == sf::Keyboard::Escape){
            quit = true;
            this->sound_manager->getBackgroundMusic().stop();
        }
    }
}

void GameState::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background);
    target->draw(*cannon);
    entity_manager->render(target);
    target->draw(cannon_power_widget);
    target->draw(*score_text);
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
