#include "include/states/game_state.hpp"

GameState::GameState(Game& game,std::string level_path): AngryBirdsState(game), contact_listener(world) {

    this->score_text = nullptr;
    this->level_path = level_path;
    onEnter();
    initWorld();
    this->contact_listener.setWorld(world);
}

void GameState::onEnter() {
    game_.sound_manager->getBackgroundMusic().stop();
    game_.sound_manager->setBackgroundMusic("sounds/ingame_music.wav");
    game_.sound_manager->getBackgroundMusic().setLoop(true);
    game_.sound_manager->getBackgroundMusic().play();

    loadTextures(background_textures, entities_textures);

    this->score_text = game_.gui_manager->createText("Score: "+std::to_string(this->score), 15, sf::Vector2f(1100, 20), ui::ORIGIN::C);
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
    b2World_SetGravity(world, gravity);

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
    b2WorldDef def = b2DefaultWorldDef();
    this->world = b2CreateWorld(&def);
    b2World_SetGravity(world, gravity);
    this->entity_manager = std::make_shared<EntityManager>(this->world);

    // Create contact listener and add it to the world object
    // this->world->SetContactListener(&contact_listener);

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
    game_.sound_manager->updateVolume();
    if(running){
        score = entity_manager->getCurrentScore();
        b2World_Step(world, dt, 3);
        contact_listener.poll();

        entity_manager->update();
        entity_manager->setBirds(cannon->getBirdsCount());

        sf::Vector2f mouse_position = game_.window->mapPixelToCoords(sf::Mouse::getPosition(*game_.window), game_.window->getView());
        cannon->update(mouse_position);
        cannon_power_widget.update(cannon->getPower(), cannon->isActive());
    }
    else if(!running && !quit){
        quit = true;
        game_.window->display();
        sf::Texture t;
        t.create(game_.window->getSize().x, game_.window->getSize().y);
        std::cout<<game_.window->getSize().x<<" "<<game_.window->getSize().y<<std::endl;
        t.update(*game_.window);
        if(result == RESULT::WIN){
            game_.addState(std::make_unique<Win>(game_, t.copyToImage(), score), true);
        }
        else if(result == RESULT::LOOSE){
            game_.addState(std::make_unique<Loose>(game_, t.copyToImage(), score), true);
        }
    }

    if(entity_manager->CountPigs() == 0){
        score += cannon->getBirdsCount()*5000;
        std::cout<<"Birds left: "<<cannon->getBirdsCount()<<std::endl;
        running = false;
        result = RESULT::WIN;
    }
    else if(cannon->getBirdsCount() == 0 && entity_manager->CountBirds() == 0){
        running = false;
        result = RESULT::LOOSE;
    }
    this->score_text->setString("Score: "+std::to_string(score));
}

void GameState::handleEvent(const sf::Event &e) {
    cannon->handleInput(e);

    if(e.type == sf::Event::KeyReleased){
        if(e.key.code == sf::Keyboard::Escape){
            quit = true;
            game_.sound_manager->getBackgroundMusic().stop();
        }
    }
}

void GameState::onExit() {
    entity_manager->clearPhysicsAndEraseAll();
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

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.userData = reinterpret_cast<void*>(this);
    bodyDef.type = b2_staticBody;
    bodyDef.position = b2Vec2(x/SCALE, y/SCALE);;
    b2BodyId b_ground = b2CreateBody(world, &bodyDef);

    b2Polygon gr = b2MakeBox(w/SCALE, h/SCALE);

    b2ShapeDef fixtureDef = b2DefaultShapeDef();

    fixtureDef.density = 1000.0f;
    fixtureDef.material.friction = 0.5f;
    fixtureDef.material.restitution = 0.5f;
    fixtureDef.enableContactEvents = true;
    b2CreatePolygonShape(b_ground, &fixtureDef, &gr);
}
