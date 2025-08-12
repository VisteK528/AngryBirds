#include "include/states/loose.hpp"

Loose::Loose(Game& game, const sf::Image& background_image, const int score): ResultState(
                     game, background_image, score){}

void Loose::onEnter() {
    ResultState::onEnter();

    game_.sound_manager->setBackgroundMusic("sounds/fail_sound.wav");
    game_.sound_manager->getBackgroundMusic().setLoop(false);
    game_.sound_manager->getBackgroundMusic().play();

    vignette_texture.loadFromFile("textures/red_vignette.png");
    vignette_sprite = sf::Sprite(vignette_texture);
    vignette_sprite.setColor(sf::Color(255, 255, 255, 90));
    vignette_sprite.setPosition(0,0);

    title_ = game_.gui_manager->createText("You lost!", 70, sf::Vector2f(640, 150), ui::ORIGIN::C);
    score_widget_ = game_.gui_manager->createText("Score: "+std::to_string(player_score_), 20, sf::Vector2f(640, 250), ui::ORIGIN::C);
    retry_btn_ = game_.gui_manager->createButton("> Retry",20, sf::Vector2f(640, 320), sf::Vector2f(250, 60), ui::ORIGIN::C);
    back_btn_ = game_.gui_manager->createButton("> Back", 20, sf::Vector2f(640, 400), sf::Vector2f(250, 60), ui::ORIGIN::C);
    menu_btn_ = game_.gui_manager->createButton("> Menu",20, sf::Vector2f(640, 480), sf::Vector2f(250, 60), ui::ORIGIN::C);
}

void Loose::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background_);
    target->draw(vignette_sprite);
    target->draw(*title_);
    target->draw(*back_btn_);
    target->draw(*menu_btn_);
    target->draw(*retry_btn_);
    target->draw(*score_widget_);
}