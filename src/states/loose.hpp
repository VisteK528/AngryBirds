#ifndef ANGRYBIRDS_LOOSE_HPP
#define ANGRYBIRDS_LOOSE_HPP

#include "../widgets.hpp"
#include "../gui_manager.hpp"
#include "../sound_manager.hpp"
#include "state.hpp"
#include "game_state.hpp"
#include "menu.hpp"
#include "lobby.hpp"

class Loose: public State {
private:
    std::shared_ptr<GuiManager> gui_manager;
    std::shared_ptr<SoundManager> sound_manager;
    std::unique_ptr<ui::Text> title;
    std::unique_ptr<ui::Button> menu_btn;
    std::unique_ptr<ui::Button> exit_btn;

    sf::Texture background_texture;
    sf::Sprite background;

    void initVariables();

public:
    Loose(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager);
    ~Loose();
    void init() override;
    void update(const float& dt) override;
    void handleEvent(const sf::Event& e) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
};

#endif //ANGRYBIRDS_LOSE_HPP