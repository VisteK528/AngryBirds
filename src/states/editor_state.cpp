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
    this->change_selected_sprite_btn = nullptr;
    loadTextures();
    initVariables();
}

EditorState::~EditorState() noexcept {

}

void EditorState::loadTextures() {
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
    //this->background_sprite.setOrigin(background_textures_table[DEFAULT].getSize().x, background_textures_table[DEFAULT].getSize().y);
    this->background_sprite.setPosition(0, 0);
}

void EditorState::initVariables() {
    this->title = this->gui_manager->createText("Editor", 35, sf::Vector2f(20, 20), ui::ORIGIN::NW);
    this->back_btn = gui_manager->createButton("Back",15, sf::Vector2f(1190, 650), sf::Vector2f(150, 30), ui::ORIGIN::C);
    this->save_btn = gui_manager->createButton("Save", 15, sf::Vector2f(1190, 690), sf::Vector2f(150, 30), ui::ORIGIN::C);
    this->change_background_btn = gui_manager->createButton("Change background", 15, sf::Vector2f(400, 40), sf::Vector2f(300, 30), ui::ORIGIN::C);
    this->change_selected_sprite_btn = std::make_unique<ui::TextureButton>(entities_textures[WOOD][0], sf::Vector2f(700, 40), ui::ORIGIN::C);

    this->selected_background = DEFAULT;
    updateBackgroundTexture();
}

void EditorState::init() {

}

void EditorState::update(const float &dt) {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());
    save_btn->update(position);
    back_btn->update(position);
    change_background_btn->update(position);
    change_selected_sprite_btn->update(position);
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

    switch (change_selected_sprite_btn->handleInput(position, e)) {
        case ui::LEFT:
            break;
        case ui::MIDDLE:
            break;
        case ui::RIGHT:
            if(selected_entity_index < 5){
                selected_entity_index++;
            }
            else{
                selected_entity_index = 0;
            }
            updateChangeSelectedSpriteBtn(selected_entity_index);
            break;
        default:
            break;
    }

    if(save_btn->handleInput(position, e)){

    }


    if(back_btn->handleInput(position, e)){
        quit = true;
    }
}

void EditorState::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background_sprite);
    target->draw(*title);
    target->draw((*back_btn));
    target->draw((*save_btn));
    target->draw(*change_background_btn);
    target->draw(*change_selected_sprite_btn);
    for(const auto& sprite: added_sprites_textures){
        target->draw(sprite);
    }
}

void EditorState::updateChangeSelectedSpriteBtn(unsigned int entity_index) {
    switch (entity_index) {
        case 0:
            this->change_selected_sprite_btn->updateTexture(entities_textures[WOOD][0]);
            break;
        case 1:
            this->change_selected_sprite_btn->updateTexture(entities_textures[WOOD3x1][0]);
            break;
        case 2:
            this->change_selected_sprite_btn->updateTexture(entities_textures[STONE][0]);
            break;
        case 3:
            this->change_selected_sprite_btn->updateTexture(entities_textures[STONE3x1][0]);
            break;
        case 4:
            this->change_selected_sprite_btn->updateTexture(entities_textures[GLASS][0]);
            break;
        case 5:
            this->change_selected_sprite_btn->updateTexture(entities_textures[GLASS3x1][0]);
            break;
        default:
            break;
    }
}
