#ifndef ANGRYBIRDS_ABOUT_HPP
#define ANGRYBIRDS_ABOUT_HPP

#include "include/widgets.hpp"
#include "state.hpp"

class About: public State {
private:
    std::unique_ptr<ui::Text> title;
    std::unique_ptr<ui::Text> about_text;
    std::unique_ptr<ui::Button> back_btn;

    sf::Texture background_texture;
    sf::Sprite background;

    void initVariables();

public:
    About(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager);
    ~About();
    void init() override;
    void update(const float& dt) override;
    void handleEvent(const sf::Event& e) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
};


#endif //ANGRYBIRDS_ABOUT_HPP