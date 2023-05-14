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

class EditorState: public State {
private:
    std::unordered_map<BACKGROUNDS, sf::Texture> background_textures_table;
    std::unordered_map<TEXTURE_TYPE, std::vector<sf::Texture>> entities_textures;

    //Logic elements
    BACKGROUNDS selected_background;
    TEXTURE_TYPE selected_texture_type = WOOD;
    unsigned int selected_background_index;
    unsigned int selected_entity_index=0;
    bool placingSprite = false;
    bool intersecting = false;
    bool rotated = false;

    // GUI Elements
    std::shared_ptr<GuiManager> gui_manager;
    std::unique_ptr<ui::Text> title;
    std::unique_ptr<ui::Button> back_btn;
    std::unique_ptr<ui::Button> save_btn;
    std::unique_ptr<ui::Button> change_background_btn;
    std::unique_ptr<ui::TextureButton> change_selected_sprite_btn;
    std::vector<std::pair<TEXTURE_TYPE, sf::Vector2f>> added_entities;
    std::vector<sf::Sprite> added_sprites_textures;
    sf::Sprite background_sprite;
    sf::Sprite selected_sprite;

    void addTransparentBarriers();
    void updateChangeSelectedSprite(unsigned int entity_index);
    void updateBackgroundTexture();
    void loadTextures();
    void initVariables();
public:
    EditorState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager);
    ~EditorState();
    void init() override;
    void update(const float& dt) override;
    void handleEvent(const sf::Event& e) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;

};


#endif //ANGRYBIRDS_EDITOR_STATE_HPP
