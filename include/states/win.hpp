#ifndef ANGRYBIRDS_WIN_HPP
#define ANGRYBIRDS_WIN_HPP

#include "result_state.hpp"

class Win: public ResultState{

private:
    std::unique_ptr<ui::Button> next_lvl_btn;
public:
    Win(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager, const sf::Image& background_image, int score);
    ~Win();
    void init() override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
    void handleEvent(const sf::Event& e) override;
};

#endif //ANGRYBIRDS_WIN_HPP