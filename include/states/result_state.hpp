#ifndef ANGRYBIRDS_RESULT_STATE_HPP
#define ANGRYBIRDS_RESULT_STATE_HPP

#include "aether/widgets.hpp"
#include "angry_birds_state.hpp"

class ResultState: public AngryBirdsState {
    public:
        ResultState(Game& game, const sf::Image& background_image, int score);
        ~ResultState() override = default;
        void onEnter() override;
        void onExit() override {};
        void update(const float& dt) override;
        void handleEvent(const sf::Event& e) override;
        void render(std::shared_ptr<sf::RenderTarget> target) override;
    protected:
        std::unique_ptr<ui::Text> title_;
        std::unique_ptr<ui::Text> score_widget_;
        std::unique_ptr<ui::Button> back_btn_;
        std::unique_ptr<ui::Button> menu_btn_;
        std::unique_ptr<ui::Button> retry_btn_;

        sf::Image background_image_;
        sf::Texture background_texture_;
        sf::Sprite background_;

        int player_score_ = 0;
        void initVariables();
};


#endif //ANGRYBIRDS_RESULT_STATE_HPP
