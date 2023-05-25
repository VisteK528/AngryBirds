#ifndef ANGRYBIRDS_RESULT_STATE_HPP
#define ANGRYBIRDS_RESULT_STATE_HPP

#include "../widgets.hpp"
#include "state.hpp"

class ResultState: public State {
protected:
    std::unique_ptr<ui::Text> title;
    std::unique_ptr<ui::Text> score_widget;
    std::unique_ptr<ui::Button> menu_btn;
    std::unique_ptr<ui::Button> exit_btn;

    sf::Image background_image;
    sf::Texture background_texture;
    sf::Sprite background;

    int player_score = 0;
    void initVariables();
public:
    ResultState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager, const sf::Image& background_image, int score);
    ~ResultState(){};
    void init() override;
    void update(const float& dt) override;
    void handleEvent(const sf::Event& e) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
};


#endif //ANGRYBIRDS_RESULT_STATE_HPP
