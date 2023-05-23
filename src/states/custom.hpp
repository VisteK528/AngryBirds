#ifndef ANGRYBIRDS_CUSTOM_HPP
#define ANGRYBIRDS_CUSTOM_HPP

#include "../widgets.hpp"
#include "../gui_manager.hpp"
#include "state.hpp"
#include "game_state.hpp"

class Custom: public State {
private:
    std::shared_ptr<SoundManager> sound_manager;
    std::shared_ptr<GuiManager> gui_manager;
    std::unique_ptr<ui::Text> title;
    std::unique_ptr<ui::Button> level1_btn;
    std::unique_ptr<ui::Button> level2_btn;
    std::unique_ptr<ui::Button> level3_btn;
    std::unique_ptr<ui::Button> level4_btn;
    std::unique_ptr<ui::Button> level5_btn;

    std::unique_ptr<ui::Button> back_btn;

    sf::Texture background_texture;
    sf::Sprite background;

    void initVariables();

public:
    Custom(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager);
    ~Custom();
    void init() override;
    void update(const float& dt) override;
    void handleEvent(const sf::Event& e) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
};


#endif //ANGRYBIRDS_CUSTOM_HPP