#include "include/states/result_state.hpp"

ResultState::ResultState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states,
         std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager,
         const sf::Image& background_image, int score): State(std::move(window), std::move(states),
                                                              std::move(gui_manager), std::move(sound_manager)){
    this->title = nullptr;
    this->back_btn = nullptr;
    this->menu_btn = nullptr;
    this->retry_btn = nullptr;
    this->score_widget = nullptr;
    this->player_score = score;
    this->background_image = background_image;
    initVariables();
}

void ResultState::initVariables() {
    init();
}

void ResultState::init() {
    this->background_texture.loadFromImage(background_image);
    this->background = sf::Sprite(background_texture);
    this->background.setColor(sf::Color(255, 255, 255, 180));
    this->background.setScale(1280.f/(float)window->getSize().x, 720.f/(float)window->getSize().y);
    this->background.setPosition(0,0);
}

void ResultState::update(const float &) {
    this->sound_manager->updateVolume();
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());
    if(this->back_btn != nullptr && this->menu_btn != nullptr && this-> retry_btn != nullptr){
        this->back_btn->update(position);
        this->menu_btn->update(position);
        this->retry_btn->update(position);
    }
}

void ResultState::handleEvent(const sf::Event &e) {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());
    if(this->back_btn != nullptr && this->menu_btn != nullptr && this-> retry_btn != nullptr){
        if(this->back_btn->handleInput(position, e)){
            quit = true;
        }

        if(this->menu_btn->handleInput(position, e)){
            return_to_first = true;
            quit = true;
        }

        if(this->retry_btn->handleInput(position, e)){
            ResultState::State::retry_level = true;
            quit = true;
        }
    }

    if(quit || return_to_first){
        this->sound_manager->getBackgroundMusic().stop();
    }
}

void ResultState::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(this->background);
    if(this->back_btn != nullptr && this->menu_btn != nullptr && this->title != nullptr && this->score_widget != nullptr && this-> retry_btn != nullptr){
        target->draw(*this->title);
        target->draw(*this->back_btn);
        target->draw(*this->menu_btn);
        target->draw(*this->score_widget);
        target->draw(*this->retry_btn);
    }
}
