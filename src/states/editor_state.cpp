#include "include/states/editor_state.hpp"

EditorState::EditorState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states,
                         std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager): State(
                                 std::move(window), std::move(states), std::move(gui_manager),
                                 std::move(sound_manager)){
    this->title = nullptr;
    this->back_btn = nullptr;
    this->save_btn = nullptr;
    this->change_background_btn = nullptr;
    this->change_selected_block_btn = nullptr;
    this->change_selected_pig_btn = nullptr;
    this->change_bird_btn = nullptr;
    this->level_number_txt = nullptr;
    this->load_btn = nullptr;
    loadTextures();
    initVariables();
}

EditorState::~EditorState() noexcept = default;

void EditorState::loadTextures() {
    // TODO Move load textures function into separate function because of the usage in multiple files
    std::unordered_map<BACKGROUNDS, std::string> background_paths = {
            {DEFAULT, "textures/background.png"},
            {MOUNTAINS, "textures/background2.png"},
            {OCEAN, "textures/background3.png"},
            {SPACE, "textures/background4.png"},
    };

    for(const auto& pair: background_paths){
        BACKGROUNDS type = pair.first;
        sf::Texture t;
        if(!t.loadFromFile(pair.second)){
            throw exceptions::TexturesLoadingError("Program couldn't load all graphics properly!");
        }
        t.setSmooth(true);
        background_textures_table[type] = t;
    }

    environment_gravity = {
            {DEFAULT, 9.81f},
            {MOUNTAINS, 7.f},
            {OCEAN, 1.f},
            {SPACE, 9.81f/6.f}};

    // Paths for entities' textures to be loaded
    std::unordered_map<TEXTURE_TYPE , std::vector<std::string>> textures_paths = {
            {WOOD, {"textures/boxes/wood/wood_1x1.png", "textures/boxes/wood/wood_1x1_damaged.png", "textures/boxes/wood/wood_1x1_destroyed.png"}},
            {WOOD3x1, {"textures/boxes/wood/wood_3x1.png", "textures/boxes/wood/wood_3x1_damaged.png", "textures/boxes/wood/wood_3x1_damaged.png"}},
            {GLASS, {"textures/boxes/glass/glass_1x1.png", "textures/boxes/glass/glass_1x1_damaged.png", "textures/boxes/glass/glass_1x1_destroyed.png"}},
            {GLASS3x1, {"textures/boxes/glass/glass_3x1.png", "textures/boxes/glass/glass_3x1_damaged.png", "textures/boxes/glass/glass_3x1_damaged.png"}},
            {STONE, {"textures/boxes/stone/stone_1x1.png", "textures/boxes/stone/stone_1x1_damaged.png", "textures/boxes/stone/stone_1x1_destroyed.png"}},
            {STONE3x1, {"textures/boxes/stone/stone_3x1.png", "textures/boxes/stone/stone_3x1_damaged.png", "textures/boxes/stone/stone_3x1_damaged.png"}},
            {BASIC_PIG, {"textures/pigs/basic/basic_pig.png", "textures/pigs/basic/basic_pig_damaged.png", "textures/pigs/basic/basic_pig_destroyed.png"}},
            {ARMORED_PIG, {"textures/pigs/armored/armored_pig.png", "textures/pigs/armored/armored_pig_damaged.png", "textures/pigs/armored/armored_pig_destroyed.png"}},
            {RED_BIRD, {"textures/birds/bird_red.png"}},
            {YELLOW_BIRD, {"textures/birds/bird_yellow.png"}},
            {GREY_BIRD, {"textures/birds/grey_bird.png"}},
            {FAT_RED_BIRD, {"textures/birds/big_bird.png"}},
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

void EditorState::updateBackgroundTexture() {
    this->background_sprite = sf::Sprite(background_textures_table[selected_background]);
    this->background_sprite.setPosition(0, 0);
}

void EditorState::initVariables() {
    this->title = this->gui_manager->createText("Editor", 35, sf::Vector2f(20, 20), ui::ORIGIN::NW);
    this->back_btn = gui_manager->createButton("Back",15, sf::Vector2f(1195, 650), sf::Vector2f(160, 30), ui::ORIGIN::C);
    this->save_btn = gui_manager->createButton("Save", 15, sf::Vector2f(1237.5, 690), sf::Vector2f(75, 30), ui::ORIGIN::C);
    this->load_btn = gui_manager->createButton("Load", 15, sf::Vector2f(1152.5, 690), sf::Vector2f(75, 30), ui::ORIGIN::C);
    this->change_background_btn = gui_manager->createButton("Change background", 15, sf::Vector2f(400, 40), sf::Vector2f(300, 30), ui::ORIGIN::C);
    this->change_selected_block_btn = std::make_unique<ui::TextureButton>(entities_textures[WOOD][0], sf::Vector2f(700, 50), ui::ORIGIN::C);
    this->change_selected_pig_btn = std::make_unique<ui::TextureButton>(entities_textures[BASIC_PIG][0], sf::Vector2f(900, 50), ui::ORIGIN::C);
    this->change_bird_btn = std::make_unique<ui::TextureButton>(entities_textures[RED_BIRD][0], sf::Vector2f(1100, 50), ui::ORIGIN::C);
    this->level_number_txt = gui_manager->createText("Selected level: 0", 10, sf::Vector2f(1190, 620), ui::ORIGIN::C);

    this->place_area = {
            sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(1280, 120)),
            sf::FloatRect(sf::Vector2f(-10, 0), sf::Vector2f(10, 720)),
            sf::FloatRect(sf::Vector2f(0, 630), sf::Vector2f(1280, 400)),
            sf::FloatRect(sf::Vector2f(1280, 0), sf::Vector2f(10, 720)),
                        };

    this->selected_background = DEFAULT;
    this->selected_background_index = 1;
    updateChangeSelectedBlockBtn(selected_block_index);
    updateChangeSelectedPigBtn(selected_pig_index);
    updateBackgroundTexture();
}

void EditorState::init() {

}

void EditorState::update(const float &dt) {
    this->sound_manager->updateVolume();
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());
    save_btn->update(position);
    back_btn->update(position);
    change_background_btn->update(position);
    change_selected_block_btn->update(position);
    change_selected_pig_btn->update(position);
    change_bird_btn->update(position);
    load_btn->update(position);

    selected_sprite.setPosition(position);

    for(const auto& barrier: place_area){
        if(selected_sprite.getGlobalBounds().intersects(barrier)){
            selected_sprite.setColor(sf::Color(255, 0,0, 175));
            intersecting = true;
            break;
        }
        else{
            selected_sprite.setColor(sf::Color(255, 255,255, 255));
            intersecting = false;
        }
    }

    if((placingBlock || placingPig || movingEntity) && !intersecting){
        if(!added_entities.empty()){
            for(const auto& added_sprite: added_entities){
                if(selected_sprite.getGlobalBounds().intersects(added_sprite.sprite.getGlobalBounds())){
                    selected_sprite.setColor(sf::Color(255, 0,0, 175));
                    intersecting = true;
                    break;
                }
                else{
                    selected_sprite.setColor(sf::Color(255, 255,255, 255));
                    intersecting = false;
                }
            }
        }
    }
}

void EditorState::handleEvent(const sf::Event &e) {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());

    if(back_btn->handleInput(position, e)){
        quit = true;
    }

    // Changing level number, based on user input from keyboard
    if(e.type == e.KeyReleased){
        if(e.key.code == sf::Keyboard::Up && level_number < 4){
            level_number++;
        }

        if(e.key.code == sf::Keyboard::Down && level_number > 0){
            level_number--;
        }
        level_number_txt->setString("Selected level: "+std::to_string(level_number));
    }

    if(change_background_btn->handleInput(position, e)){
        selected_background_index ++;
        switch (selected_background_index) {
            case 0:
                selected_background = DEFAULT;
                break;
            case 1:
                selected_background = MOUNTAINS;
                break;
            case 2:
                selected_background = OCEAN;
                break;
            case 3:
                selected_background = SPACE;
                break;
            default:
                selected_background_index = 0;
                selected_background = DEFAULT;
                break;
        }
        updateBackgroundTexture();
    }

    if(save_btn->handleInput(position, e)){
        std::cout<<"Saving..."<<std::endl;
        saveToFile("data/custom/custom_level_"+std::to_string(level_number)+".json");
    }

    if(!placingBlock && !placingPig){
        added_entities.erase(std::remove_if(added_entities.begin(), added_entities.end(), [&](ENTITY& entity){return checkIfToDelete(entity, position, e);}), added_entities.end());
    }

    added_birds.erase(std::remove_if(added_birds.begin(), added_birds.end(), [&](BIRD & bird){return checkIfToDelete(bird, position, e);}), added_birds.end());

    for(auto& added_sprite: added_entities){
        if(added_sprite.sprite.getGlobalBounds().contains(position.x, position.y) && e.type == sf::Event::MouseButtonReleased && !movingEntity){
            if(e.mouseButton.button == sf::Mouse::Left){
                added_sprite.position = position;
                added_sprite.moving = true;
                selected_sprite = added_sprite.sprite;
                //added_sprite.sprite = sf::Sprite();
                if(added_sprite.type == BASIC_PIG || added_sprite.type == ARMORED_PIG){
                    placingPig = true;
                }
                movingEntity = true;
                break;
            }
        }
        else if(added_sprite.moving && e.type == sf::Event::MouseButtonReleased && movingEntity){
            if(e.mouseButton.button == sf::Mouse::Left && !intersecting){
                added_sprite.position = position;
                added_sprite.sprite = selected_sprite;
                added_sprite.moving = false;
                added_sprite.rotated = rotated;
                movingEntity = false;
                placingPig = false;
            }
        }
    }

    if((e.type == sf::Event::MouseButtonReleased || e.type == sf::Event::KeyReleased) && (placingBlock || movingEntity)){
        if((e.mouseButton.button == sf::Mouse::Middle || e.key.code == sf::Keyboard::R) && !placingPig){
            if(selected_sprite.getRotation() == 0){
                rotated = true;
                selected_sprite.setRotation(90);
            }
            else{
                rotated = false;
                selected_sprite.setRotation(0);
            }
        }
    }

    if(e.type == sf::Event::MouseButtonReleased && (placingBlock || placingPig) && !movingEntity){
        if(e.mouseButton.button == sf::Mouse::Left && !intersecting){
            ENTITY entity;
            if(placingBlock){
                entity.type = selected_block_type;
                entity.sprite = sf::Sprite(entities_textures[selected_block_type][0]);
            }
            else if(placingPig){
                entity.type = selected_pig_type;
                entity.sprite = sf::Sprite(entities_textures[selected_pig_type][0]);
            }
            entity.sprite.setOrigin(entity.sprite.getTexture()->getSize().x/2., entity.sprite.getTexture()->getSize().y/2.);
            entity.position = position;
            entity.rotated = rotated;
            entity.sprite.setPosition(position);
            entity.moving = false;
            if(rotated && placingBlock){
                entity.sprite.setRotation(90);
            }
            added_entities.push_back(entity);
        }
        else if(e.mouseButton.button == sf::Mouse::Right){
            placingBlock = false;
            placingPig = false;
        }
    }

    switch (change_selected_block_btn->handleInput(position, e)) {
        case ui::LEFT:
            placingBlock = true;
            break;
        case ui::RIGHT:
            if(selected_block_index < 5){
                selected_block_index++;
            }
            else{
                selected_block_index = 0;
            }
            updateChangeSelectedBlockBtn(selected_block_index);
            break;
        default:
            break;
    }

    switch(change_selected_pig_btn->handleInput(position, e)){
        case ui::LEFT:
            placingPig = true;
            break;
        case ui::RIGHT:
            if(selected_pig_index < 7){
                selected_pig_index++;
            }
            else{
                selected_pig_index = 6;
            }
            updateChangeSelectedPigBtn(selected_pig_index);
            break;
        default:
            break;
    }

    switch(change_bird_btn->handleInput(position, e)){
        case ui::LEFT: {
            if(added_birds.size() <= 7){
                BIRD bird;
                bird.type = selected_bird_type;
                bird.sprite = sf::Sprite(entities_textures[selected_bird_type][0]);
                bird.sprite.setOrigin(bird.sprite.getTexture()->getSize().x/2.f, bird.sprite.getTexture()->getSize().y/2.f);
                added_birds.push_back(bird);
            }
            break;
        }
        case ui::RIGHT:
            if(selected_bird_index < 11){
                selected_bird_index++;
            }
            else{
                selected_bird_index=8;
            }
            updateChangeSelectedBirdBtn(selected_bird_index);
            break;
        default:
            break;
    }
    if(placingBlock || placingPig){
        updateChangeSelectedSprite();
    }
    updateSelectedBirdsPosition();

    if(load_btn->handleInput(position, e)){
        loadFromFile("data/custom/custom_level_"+std::to_string(level_number)+".json");
    }
}

void EditorState::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background_sprite);
    target->draw(*title);
    target->draw((*back_btn));
    target->draw((*save_btn));
    target->draw(*change_background_btn);
    target->draw(*change_selected_block_btn);
    target->draw(*change_selected_pig_btn);
    target->draw(*change_bird_btn);
    target->draw(*level_number_txt);
    target->draw(*load_btn);
    for(const auto& sprite: added_entities){
        target->draw(sprite.sprite);
    }

    for(const auto& bird: added_birds){
        target->draw(bird.sprite);
    }

    if(placingBlock || placingPig || movingEntity){
        target->draw(selected_sprite);
    }
}

void EditorState::saveToFile(const std::string& path){
    json level_json;

    // Store environment information
    level_json["background"] = selected_background;
    level_json["gravity"] = environment_gravity[selected_background];

    // Store birds deck
    std::vector<TEXTURE_TYPE> selected_birds;
    selected_birds.reserve(added_birds.size());
    for(const BIRD& bird: added_birds){
        selected_birds.push_back(bird.type);
    }
    level_json["birds"] = selected_birds;

    // Store entities information including blocks and pigs
    for(const auto& entity_block: added_entities){
        level_json["entities"].push_back(json::array({entity_block.type, json::array({entity_block.position.x, entity_block.position.y}), entity_block.rotated}));
    }

    // Open file and save the string to the json file
    std::ofstream file;
    file.open(path);
    file<<level_json.dump();
    file.close();
}

void EditorState::loadFromFile(const std::string &path) {
    std::ifstream file;
    file.open(path);

    json level_json;
    file >> level_json;

    background_sprite = sf::Sprite(background_textures_table[backgrounds_dict[level_json["background"]]]);
    selected_background = backgrounds_dict[level_json["background"]];

    added_birds.clear();
    for(const auto& bird: level_json["birds"].items()){
        BIRD bird_struct;
        bird_struct.type = birds_dict[static_cast<int>(bird.value())];
        bird_struct.sprite = sf::Sprite(entities_textures[bird_struct.type][0]);
        bird_struct.sprite.setOrigin(bird_struct.sprite.getTexture()->getSize().x/2.f, bird_struct.sprite.getTexture()->getSize().y/2.f);
        added_birds.push_back(bird_struct);
    }
    updateSelectedBirdsPosition();


    added_entities.clear();
    for(const auto& entity_array: level_json["entities"].items()){
        json entity_array_json = entity_array.value();
        ENTITY loaded_entity;
        loaded_entity.type = entities_dict[entity_array_json[0]];
        std::vector<float> unscaled_position = entity_array_json[1].get<std::vector<float>>();
        loaded_entity.position = {unscaled_position[0], unscaled_position[1]};
        loaded_entity.rotated = entity_array_json[2].get<bool>();
        loaded_entity.sprite = sf::Sprite(entities_textures[loaded_entity.type][0]);
        loaded_entity.sprite.setOrigin(loaded_entity.sprite.getTexture()->getSize().x/2.f, loaded_entity.sprite.getTexture()->getSize().y/2.f);
        loaded_entity.sprite.setPosition(loaded_entity.position);
        if(loaded_entity.rotated){
            loaded_entity.sprite.setRotation(90);
        }
        added_entities.push_back(loaded_entity);
    }
}

void EditorState::updateChangeSelectedBlockBtn(unsigned int block_index) {
    this->change_selected_block_btn->updateTexture(entities_textures[entities_dict[block_index]][0]);
    this->selected_block_type = entities_dict[block_index];
}

void EditorState::updateChangeSelectedPigBtn(unsigned int pig_index) {
    this->change_selected_pig_btn->updateTexture(entities_textures[entities_dict[pig_index]][0]);
    this->selected_pig_type = entities_dict[pig_index];
}

void EditorState::updateChangeSelectedBirdBtn(unsigned int bird_index) {
    this->change_bird_btn->updateTexture(entities_textures[birds_dict[bird_index]][0]);
    this->selected_bird_type = birds_dict[bird_index];
}

void EditorState::updateChangeSelectedSprite() {
    if(placingBlock){
        placingPig = false;
        this->selected_sprite.setTexture(entities_textures[selected_block_type][0], true);
    }
    else{
        placingBlock = false;
        this->selected_sprite.setTexture(entities_textures[selected_pig_type][0], true);
    }
    this->selected_sprite.setOrigin(selected_sprite.getTexture()->getSize().x/2.f, selected_sprite.getTexture()->getSize().y/2.f);
}

void EditorState::updateSelectedBirdsPosition() {
    for(int i = 0; i < added_birds.size(); i++){
        added_birds[added_birds.size()-1-i].sprite.setPosition(50+i*100, 100);
    }
}
