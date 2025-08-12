#ifndef ANGRYBIRDS_CUSTOM_HPP
#define ANGRYBIRDS_CUSTOM_HPP

#include "aether/widgets.hpp"
#include "angry_birds_state.hpp"

class Custom final: public AngryBirdsState {
    public:
        Custom(Game& game);
        ~Custom() override = default;
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

        std::unique_ptr<ui::Button> back_btn;

        sf::Texture background_texture;
        sf::Sprite background;

        void initVariables();
};


#endif //ANGRYBIRDS_CUSTOM_HPP