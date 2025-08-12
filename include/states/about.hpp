#ifndef ANGRYBIRDS_ABOUT_HPP
#define ANGRYBIRDS_ABOUT_HPP

#include "aether/widgets.hpp"
#include "angry_birds_state.hpp"

class About final: public AngryBirdsState {
    public:
        explicit About(Game& game);
        ~About() override = default;
        void onEnter() override {};
        void onExit() override {};
        void update(const float& dt) override;
        void handleEvent(const sf::Event& e) override;
        void render(std::shared_ptr<sf::RenderTarget> target) override;
    private:
        std::unique_ptr<ui::Text> title_;
        std::unique_ptr<ui::Text> about_text_;
        std::unique_ptr<ui::Button> back_btn_;

        sf::Texture background_texture_;
        sf::Sprite background_;

        void initVariables();
};


#endif //ANGRYBIRDS_ABOUT_HPP