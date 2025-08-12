#ifndef ANGRYBIRDS_ADVENTURE_HPP
#define ANGRYBIRDS_ADVENTURE_HPP

#include "angry_birds_state.hpp"
#include "aether/widgets.hpp"

class Adventure final: public AngryBirdsState {
public:
    explicit Adventure(Game& game);
    ~Adventure() override = default;
    void onEnter() override;
    void onExit() override {};

    void update(const float& dt) override;
    void handleEvent(const sf::Event& e) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;

private:
    std::unique_ptr<ui::Text> title;
    std::unique_ptr<ui::Button> level1_btn;
    std::unique_ptr<ui::Button> level2_btn;
    std::unique_ptr<ui::Button> level3_btn;
    std::unique_ptr<ui::Button> level4_btn;
    std::unique_ptr<ui::Button> level5_btn;
    std::unique_ptr<ui::Button> level6_btn;
    std::unique_ptr<ui::Button> level7_btn;
    std::unique_ptr<ui::Button> level8_btn;
    std::unique_ptr<ui::Button> level9_btn;
    std::unique_ptr<ui::Button> level10_btn;
    std::unique_ptr<ui::Button> level11_btn;
    std::unique_ptr<ui::Button> level12_btn;
    std::unique_ptr<ui::Button> level13_btn;
    std::unique_ptr<ui::Button> level14_btn;

    std::unique_ptr<ui::Button> back_btn;

    sf::Texture background_texture;
    sf::Sprite background;

    void initVariables();

};


#endif //ANGRYBIRDS_ADVENTURE_HPP