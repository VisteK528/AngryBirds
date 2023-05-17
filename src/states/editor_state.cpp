//
// Created by piotr on 5/13/23.
//

#include "editor_state.hpp"

EditorState::EditorState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager): State(window, states){
    this->gui_manager = gui_manager;
    this->title = nullptr;
    this->back_btn = nullptr;
    this->save_btn = nullptr;
    this->change_background_btn = nullptr;
    this->change_selected_block_btn = nullptr;
    this->change_selected_pig_btn = nullptr;
    loadTextures();
    initVariables();
}

EditorState::~EditorState() noexcept {

}

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

    // Paths for entities' textures to be loaded
    std::unordered_map<TEXTURE_TYPE , std::vector<std::string>> textures_paths = {
            {WOOD, {"textures/boxes/wood/wood_1x1.png", "textures/boxes/wood/wood_1x1_damaged.png", "textures/boxes/wood/wood_1x1_destroyed.png"}},
            {WOOD3x1, {"textures/boxes/wood/wood_3x1.png", "textures/boxes/wood/wood_3x1_damaged.png", "textures/boxes/wood/wood_3x1_damaged.png"}},
            {GLASS, {"textures/boxes/glass/glass_1x1.png", "textures/boxes/glass/glass_1x1_damaged.png", "textures/boxes/glass/glass_1x1_destroyed.png"}},
            {GLASS3x1, {"textures/boxes/glass/glass_3x1.png", "textures/boxes/glass/glass_3x1_damaged.png", "textures/boxes/glass/glass_3x1_damaged.png"}},
            {STONE, {"textures/boxes/stone/stone_1x1.png", "textures/boxes/stone/stone_1x1_damaged.png", "textures/boxes/stone/stone_1x1_destroyed.png"}},
            {STONE3x1, {"textures/boxes/stone/stone_3x1.png", "textures/boxes/stone/stone_3x1_damaged.png", "textures/boxes/stone/stone_3x1_damaged.png"}},
            {BASIC_PIG, {"textures/pigs/basic/basic_pig.png", "textures/pigs/basic/basic_pig_damaged.png", "textures/pigs/basic/basic_pig_destroyed.png"}},
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

void EditorState::updateBackgroundTexture() {
    this->background_sprite = sf::Sprite(background_textures_table[selected_background]);
    this->background_sprite.setPosition(0, 0);
}

void EditorState::initVariables() {
    this->title = this->gui_manager->createText("Editor", 35, sf::Vector2f(20, 20), ui::ORIGIN::NW);
    this->back_btn = gui_manager->createButton("Back",15, sf::Vector2f(1190, 650), sf::Vector2f(150, 30), ui::ORIGIN::C);
    this->save_btn = gui_manager->createButton("Save", 15, sf::Vector2f(1190, 690), sf::Vector2f(150, 30), ui::ORIGIN::C);
    this->change_background_btn = gui_manager->createButton("Change background", 15, sf::Vector2f(400, 40), sf::Vector2f(300, 30), ui::ORIGIN::C);
    this->change_selected_block_btn = std::make_unique<ui::TextureButton>(entities_textures[WOOD][0], sf::Vector2f(700, 40), ui::ORIGIN::C);
    this->change_selected_pig_btn = std::make_unique<ui::TextureButton>(entities_textures[BASIC_PIG][0], sf::Vector2f(900, 40), ui::ORIGIN::C);

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
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());
    save_btn->update(position);
    back_btn->update(position);
    change_background_btn->update(position);
    change_selected_block_btn->update(position);
    change_selected_pig_btn->update(position);

    selected_sprite.setPosition(position);

    for(const auto& barrier: place_area){
        if(selected_sprite.getGlobalBounds().intersects(barrier)){
            selected_sprite.setColor(sf::Color(255, 0,0, 255));
            intersecting = true;
            break;
        }
        else{
            selected_sprite.setColor(sf::Color(255, 255,255, 255));
            intersecting = false;
        }
    }

    if((placingBlock || placingPig ) && !intersecting){
        if(!added_entities.empty()){
            for(const auto& added_sprite: added_entities){
                if(selected_sprite.getGlobalBounds().intersects(added_sprite.sprite.getGlobalBounds())){
                    selected_sprite.setColor(sf::Color(255, 0,0, 255));
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

    for(auto& added_sprite: added_entities){
        if(added_sprite.sprite.getGlobalBounds().contains(position.x, position.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            added_sprite.position = position;
            added_sprite.sprite.setPosition(position);
        }
    }
}

void EditorState::handleEvent(const sf::Event &e) {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());

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
        saveToFile("data/save1.json");
    }

    if(back_btn->handleInput(position, e)){
        quit = true;
    }

    if(e.type == sf::Event::MouseButtonReleased && (placingBlock || placingPig)){
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
            if(rotated && placingBlock){
                entity.sprite.setRotation(90);
            }
            added_entities.push_back(entity);
        }
        else if(e.mouseButton.button == sf::Mouse::Middle && placingBlock){
            selected_sprite.rotate(90);
            if(rotated){
                rotated = false;
            } else {
                rotated = true;
            }
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
        case ui::MIDDLE:
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
        case ui::MIDDLE:
            break;
        case ui::RIGHT:
            selected_pig_index = 6;
            updateChangeSelectedPigBtn(selected_pig_index);
            break;
        default:
            break;
    }
    if(placingBlock || placingPig){
        updateChangeSelectedSprite();
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
    for(const auto& sprite: added_entities){
        target->draw(sprite.sprite);
    }

    if(placingBlock || placingPig){
        target->draw(selected_sprite);
    }
}

void EditorState::saveToFile(std::string path){
    // TODO Saving strings mapped to enums instead of enums values
    json j;
    j["background"] = selected_background;
    j["birds"] = {RED_BIRD, YELLOW_BIRD, FAT_RED_BIRD};
    for(const auto& entity_block: added_entities){
        j["entities"].push_back(json::array({entity_block.type, json::array({entity_block.position.x, entity_block.position.y}), entity_block.rotated}));
    }
    std::ofstream file;
    file.open(path);
    file<<j.dump();
    file.close();
}

void EditorState::updateChangeSelectedBlockBtn(unsigned int block_index) {
    switch (block_index) {
        case 0:
            this->change_selected_block_btn->updateTexture(entities_textures[WOOD][0]);
            this->selected_block_type = WOOD;
            break;
        case 1:
            this->change_selected_block_btn->updateTexture(entities_textures[WOOD3x1][0]);
            this->selected_block_type = WOOD3x1;
            break;
        case 2:
            this->change_selected_block_btn->updateTexture(entities_textures[STONE][0]);
            this->selected_block_type = STONE;
            break;
        case 3:
            this->change_selected_block_btn->updateTexture(entities_textures[STONE3x1][0]);
            this->selected_block_type = STONE3x1;
            break;
        case 4:
            this->change_selected_block_btn->updateTexture(entities_textures[GLASS][0]);
            this->selected_block_type = GLASS;
            break;
        case 5:
            this->change_selected_block_btn->updateTexture(entities_textures[GLASS3x1][0]);
            this->selected_block_type = GLASS3x1;
            break;
        default:
            break;
    }
}

void EditorState::updateChangeSelectedPigBtn(unsigned int pig_index) {
    switch(pig_index) {
        case 6:
            this->change_selected_pig_btn->updateTexture(entities_textures[BASIC_PIG][0]);
            this->selected_pig_type = BASIC_PIG;
            break;
        default:
            break;
    }
}

void EditorState::updateChangeSelectedSprite() {
    if(placingBlock){
        placingPig = false;
        this->selected_sprite.setTexture(entities_textures[selected_block_type][0], true);
    }
    else{
        placingBlock = false;
        rotated = false;
        this->selected_sprite.setRotation(0);
        this->selected_sprite.setTexture(entities_textures[selected_pig_type][0], true);
    }
    this->selected_sprite.setOrigin(selected_sprite.getTexture()->getSize().x/2., selected_sprite.getTexture()->getSize().y/2);
}
