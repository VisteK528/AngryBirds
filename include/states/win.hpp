#ifndef ANGRYBIRDS_WIN_HPP
#define ANGRYBIRDS_WIN_HPP

#include "result_state.hpp"

class Win final: public ResultState{
public:
    Win(Game& game, const sf::Image& background_image, int score);
    ~Win() override = default;
    void onEnter() override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
    void handleEvent(const sf::Event& e) override;
private:
    std::unique_ptr<ui::Button> next_lvl_btn;
};

#endif //ANGRYBIRDS_WIN_HPP