#include "include/states/loose.hpp"

Loose::Loose(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states,
             std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager,
             const sf::Image& background_image, int score): ResultState(
                     std::move(window), std::move(states), std::move(gui_manager),
                     std::move(sound_manager), background_image, score){}

Loose::~Loose()= default;

void Loose::init() {
    ResultState::init();

    this->sound_manager->setBackgroundMusic("sounds/fail_sound.wav");
    this->sound_manager->getBackgroundMusic().setLoop(false);
    this->sound_manager->getBackgroundMusic().play();

    this->vignette_texture.loadFromFile("textures/red_vignette.png");
    this->vignette_sprite = sf::Sprite(vignette_texture);
    this->vignette_sprite.setColor(sf::Color(255, 255, 255, 90));
    this->vignette_sprite.setPosition(0,0);

    this->title = gui_manager->createText("You lost!", 70, sf::Vector2f(640, 150), ui::ORIGIN::C);
    this->score_widget = gui_manager->createText("Score: "+std::to_string(player_score), 20, sf::Vector2f(640, 250), ui::ORIGIN::C);
    this->retry_btn = gui_manager->createButton("> Retry",20, sf::Vector2f(640, 320), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->back_btn = gui_manager->createButton("> Back", 20, sf::Vector2f(640, 400), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->menu_btn = gui_manager->createButton("> Menu",20, sf::Vector2f(640, 480), sf::Vector2f(250, 60), ui::ORIGIN::C);
}

void Loose::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(this->background);
    target->draw(this->vignette_sprite);
    target->draw(*this->title);
    target->draw(*this->back_btn);
    target->draw(*this->menu_btn);
    target->draw(*this->retry_btn);
    target->draw(*this->score_widget);
}