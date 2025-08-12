#include "include/states/win.hpp"

Win::Win(Game& game, const sf::Image& background_image, int score): ResultState(game, background_image, score){}

void Win::onEnter() {
    ResultState::onEnter();
    title_ = game_.gui_manager->createText("You won!", 70, sf::Vector2f(640, 150), ui::ORIGIN::C);
    score_widget_ = game_.gui_manager->createText("Score: "+std::to_string(player_score_), 20, sf::Vector2f(640, 250), ui::ORIGIN::C);

    next_lvl_btn = game_.gui_manager->createButton("> Next level",20, sf::Vector2f(640, 320), sf::Vector2f(250, 60), ui::ORIGIN::C);
    retry_btn_ = game_.gui_manager->createButton("> Retry",20, sf::Vector2f(640, 400), sf::Vector2f(250, 60), ui::ORIGIN::C);
    back_btn_ = game_.gui_manager->createButton("> Back", 20, sf::Vector2f(640, 480), sf::Vector2f(250, 60), ui::ORIGIN::C);
    menu_btn_ = game_.gui_manager->createButton("> Menu",20, sf::Vector2f(640, 560), sf::Vector2f(250, 60), ui::ORIGIN::C);

    game_.sound_manager->setBackgroundMusic("sounds/win_sound.wav");
    game_.sound_manager->getBackgroundMusic().setLoop(false);
    game_.sound_manager->getBackgroundMusic().play();
}

void Win::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background_);
    target->draw(*title_);
    target->draw(*back_btn_);
    target->draw(*menu_btn_);
    target->draw(*retry_btn_);
    target->draw(*next_lvl_btn);
    target->draw(*score_widget_);
}

void Win::handleEvent(const sf::Event &e) {
    sf::Vector2f position = game_.window->mapPixelToCoords(sf::Mouse::getPosition(*game_.window), game_.window->getView());
    if(back_btn_ != nullptr && menu_btn_ != nullptr &&  retry_btn_ != nullptr){
        if(back_btn_->handleInput(position, e)){
            quit = true;
        }

        if(menu_btn_->handleInput(position, e)){
            return_to_first = true;
        }

        if(retry_btn_->handleInput(position, e)){
            retry_level = true;
            quit = true;
        }

        if(next_lvl_btn->handleInput(position, e)){
            load_next_level = true;
            quit = true;
        }

        if(quit || return_to_first){
            game_.sound_manager->getBackgroundMusic().stop();
        }
    }
}