#ifndef ANGRYBIRDS_LOBBY_HPP
#define ANGRYBIRDS_LOBBY_HPP

#include "../widgets.hpp"
#include "state.hpp"
#include "game_state.hpp"
#include "adventure.hpp"
#include "custom.hpp"

class Lobby: public State {
private:
    std::unique_ptr<ui::Text> title;
    std::unique_ptr<ui::Button> adventure_mode_btn;
    std::unique_ptr<ui::Button> custom_mode_btn;
    std::unique_ptr<ui::Button> back_btn;

    sf::Texture background_texture;
    sf::Sprite background;

    void initVariables();
public:
    Lobby(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager);
    ~Lobby();
    void init() override;
    void update(const float& dt) override;
    void handleEvent(const sf::Event& e) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
};


#endif //ANGRYBIRDS_LOBBY_HPP