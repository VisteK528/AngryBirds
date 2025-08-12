#ifndef ANGRYBIRDS_MENU_HPP
#define ANGRYBIRDS_MENU_HPP

#include "aether/widgets.hpp"
#include "angry_birds_state.hpp"

class Menu final: public AngryBirdsState {
    public:
        explicit Menu(Game& game);
        ~Menu() override = default;
        void onEnter() override;
        void onExit() override {};
        void update(const float& dt) override;
        void handleEvent(const sf::Event& e) override;
        void render(std::shared_ptr<sf::RenderTarget> target) override;
    private:
        std::unique_ptr<ui::Text> title_;
        std::unique_ptr<ui::Button> start_btn_;
        std::unique_ptr<ui::Button> editor_btn_;
        std::unique_ptr<ui::Button> about_btn_;
        std::unique_ptr<ui::Button> exit_btn_;

        sf::Texture background_texture_;
        sf::Sprite background_;

        void initVariables();
};


#endif //ANGRYBIRDS_MENU_HPP
