#include "include/states/result_state.hpp"

ResultState::ResultState(Game& game, const sf::Image& background_image, const int score): AngryBirdsState(game){
    title_ = nullptr;
    back_btn_ = nullptr;
    menu_btn_ = nullptr;
    retry_btn_ = nullptr;
    score_widget_ = nullptr;
    player_score_ = score;
    background_image_ = background_image;
    initVariables();
}

void ResultState::initVariables() {
    onEnter();
}

void ResultState::onEnter() {
    background_texture_.loadFromImage(background_image_);
    background_ = sf::Sprite(background_texture_);
    background_.setColor(sf::Color(255, 255, 255, 180));
    background_.setScale(1280.f/(float)game_.window->getSize().x, 720.f/(float)game_.window->getSize().y);
    background_.setPosition(0,0);
}

void ResultState::update(const float &) {
    game_.sound_manager->updateVolume();
    sf::Vector2f position = game_.window->mapPixelToCoords(sf::Mouse::getPosition(*game_.window), game_.window->getView());
    if(back_btn_ != nullptr && menu_btn_ != nullptr && retry_btn_ != nullptr){
        back_btn_->update(position);
        menu_btn_->update(position);
        retry_btn_->update(position);
    }
}

void ResultState::handleEvent(const sf::Event &e) {
    sf::Vector2f position = game_.window->mapPixelToCoords(sf::Mouse::getPosition(*game_.window), game_.window->getView());
    if(back_btn_ != nullptr && menu_btn_ != nullptr && retry_btn_ != nullptr){
        if(back_btn_->handleInput(position, e)){
            quit = true;
        }

        if(menu_btn_->handleInput(position, e)){
            return_to_first = true;
            quit = true;
        }

        if(retry_btn_->handleInput(position, e)){
            retry_level = true;
            quit = true;
        }
    }

    if(quit || return_to_first){
        game_.sound_manager->getBackgroundMusic().stop();
    }
}

void ResultState::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background_);
    if(back_btn_ != nullptr && menu_btn_ != nullptr && title_ != nullptr && score_widget_ != nullptr && retry_btn_ != nullptr){
        target->draw(*title_);
        target->draw(*back_btn_);
        target->draw(*menu_btn_);
        target->draw(*score_widget_);
        target->draw(*retry_btn_);
    }
}
