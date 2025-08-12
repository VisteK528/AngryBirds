#ifndef ANGRYBIRDS_LOBBY_HPP
#define ANGRYBIRDS_LOBBY_HPP

#include "aether/widgets.hpp"
#include "angry_birds_state.hpp"

class Lobby final: public AngryBirdsState {
public:
    Lobby(Game& game);
    ~Lobby() override = default;
    void onEnter() override {};
    void onExit() override {};
    void update(const float& dt) override;
    void handleEvent(const sf::Event& e) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
private:
    std::unique_ptr<ui::Text> title_;
    std::unique_ptr<ui::Button> adventure_mode_btn_;
    std::unique_ptr<ui::Button> custom_mode_btn_;
    std::unique_ptr<ui::Button> back_btn_;

    sf::Texture background_texture_;
    sf::Sprite background_;

    void initVariables();
};


#endif //ANGRYBIRDS_LOBBY_HPP