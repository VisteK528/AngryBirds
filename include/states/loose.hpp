#ifndef ANGRYBIRDS_LOOSE_HPP
#define ANGRYBIRDS_LOOSE_HPP

#include "result_state.hpp"

class Loose final: public ResultState {
public:
    Loose(Game& game, const sf::Image& background_image, int score);
    ~Loose() override = default;
    void onEnter() override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
private:
    sf::Texture vignette_texture;
    sf::Sprite vignette_sprite;
};

#endif //ANGRYBIRDS_LOSE_HPP