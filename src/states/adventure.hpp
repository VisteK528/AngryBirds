#ifndef ANGRYBIRDS_ADVENTURE_HPP
#define ANGRYBIRDS_ADVENTURE_HPP

#include "../widgets.hpp"
#include "state.hpp"
#include "game_state.hpp"

class Adventure: public State {
private:
    std::unique_ptr<ui::Text> title;
    std::unique_ptr<ui::Button> level1_btn;
    std::unique_ptr<ui::Button> level2_btn;
    std::unique_ptr<ui::Button> level3_btn;
    std::unique_ptr<ui::Button> level4_btn;
    std::unique_ptr<ui::Button> level5_btn;
    std::unique_ptr<ui::Button> level6_btn;
    std::unique_ptr<ui::Button> level7_btn;
    std::unique_ptr<ui::Button> level8_btn;
    std::unique_ptr<ui::Button> level9_btn;
    std::unique_ptr<ui::Button> level10_btn;
    std::unique_ptr<ui::Button> level11_btn;
    std::unique_ptr<ui::Button> level12_btn;
    std::unique_ptr<ui::Button> level13_btn;
    std::unique_ptr<ui::Button> level14_btn;

    std::unique_ptr<ui::Button> back_btn;

    sf::Texture background_texture;
    sf::Sprite background;

    void initVariables();

public:
    Adventure(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager);
    ~Adventure();
    void init() override;
    void update(const float& dt) override;
    void handleEvent(const sf::Event& e) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
};


#endif //ANGRYBIRDS_ADVENTURE_HPP