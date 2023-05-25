#ifndef ANGRYBIRDS_WIN_HPP
#define ANGRYBIRDS_WIN_HPP

#include "result_state.hpp"

class Win: public ResultState{
public:
    Win(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager, const sf::Image& background_image, int score);
    ~Win();
    void init() override;
};

#endif //ANGRYBIRDS_WIN_HPP