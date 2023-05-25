#ifndef ANGRYBIRDS_LOOSE_HPP
#define ANGRYBIRDS_LOOSE_HPP

#include "result_state.hpp"

class Loose: public ResultState {
private:
    sf::Texture vignette_texture;
    sf::Sprite vignette_sprite;
public:
    Loose(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager, const sf::Image& background_image, int score);
    ~Loose();
    void init() override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
};

#endif //ANGRYBIRDS_LOSE_HPP