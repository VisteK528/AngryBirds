//
// Created by piotr on 5/13/23.
//

#ifndef ANGRYBIRDS_EDITOR_STATE_HPP
#define ANGRYBIRDS_EDITOR_STATE_HPP

#include "state.hpp"
#include "../gui_manager.hpp"
#include "../exceptions.hpp"
#include "../entities/entity.hpp"
#include "../textures.hpp"
#include <iostream>
#include <fstream>
#include "../../include/json.hpp"

using json = nlohmann::json;

typedef struct{
    TEXTURE_TYPE type;
    sf::Vector2f position;
    sf::Sprite sprite;
    bool rotated;
    bool moving;
} ENTITY;

class EditorState: public State {
private:
    std::unordered_map<BACKGROUNDS, sf::Texture> background_textures_table;
    std::unordered_map<TEXTURE_TYPE, std::vector<sf::Texture>> entities_textures;

    //Logic elements
    BACKGROUNDS selected_background;
    TEXTURE_TYPE selected_block_type = WOOD;
    TEXTURE_TYPE selected_pig_type = BASIC_PIG;
    unsigned int selected_background_index;
    unsigned int selected_block_index=0;
    unsigned int selected_pig_index=6;
    bool placingBlock = false;
    bool placingPig = false;
    bool movingEntity = false;
    bool intersecting = false;
    bool rotated = false;

    // GUI Elements
    std::shared_ptr<GuiManager> gui_manager;
    std::unique_ptr<ui::Text> title;
    std::unique_ptr<ui::Button> back_btn;
    std::unique_ptr<ui::Button> save_btn;
    std::unique_ptr<ui::Button> change_background_btn;
    std::unique_ptr<ui::TextureButton> change_selected_block_btn;
    std::unique_ptr<ui::TextureButton> change_selected_pig_btn;
    std::vector<ENTITY> added_entities;
    std::vector<sf::FloatRect> place_area;
    sf::Sprite background_sprite;
    sf::Sprite selected_sprite;

    void updateChangeSelectedBlockBtn(unsigned int block_index);
    void updateChangeSelectedPigBtn(unsigned int pig_index);
    void updateChangeSelectedSprite();
    void updateBackgroundTexture();
    void loadTextures();
    void initVariables();
    void saveToFile(std::string path);
public:
    EditorState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager);
    ~EditorState();
    void init() override;
    void update(const float& dt) override;
    void handleEvent(const sf::Event& e) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;

};


#endif //ANGRYBIRDS_EDITOR_STATE_HPP
