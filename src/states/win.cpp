#include "win.hpp"

Win::Win(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager, sf::Image background_image, int score): State(window, states){
    this->gui_manager = std::move(gui_manager);
    this->sound_manager = std::move(sound_manager);
    this->title = nullptr;
    this->menu_btn = nullptr;
    this->exit_btn = nullptr;
    this->score_widget = nullptr;
    this->player_score = score;
    this->background_image = background_image;
    initVariables();
}

Win::~Win(){

}

void Win::initVariables() {
    this->title = gui_manager->createText("You won!", 70, sf::Vector2f(640, 250), ui::ORIGIN::C);
    this->menu_btn = gui_manager->createButton("> Menu", 20, sf::Vector2f(640, 400), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->exit_btn = gui_manager->createButton("> Exit",20, sf::Vector2f(640, 480), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->score_widget = gui_manager->createText("Score: "+std::to_string(player_score), 20, sf::Vector2f(640, 350), ui::ORIGIN::C);

    this->sound_manager->loadBackgroundMusic("sounds/Angry-Birds-Theme.wav");
    this->sound_manager->getBackgroundMusic().setLoop(true);
    this->sound_manager->getBackgroundMusic().play();

    this->background_texture.loadFromImage(background_image);
    this->background = sf::Sprite(background_texture);
    this->background.setColor(sf::Color(255, 255, 255, 180));
    this->background.setPosition(0,0);
}

void Win::update(const float &) {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());
    this->menu_btn->update(position);
    this->exit_btn->update(position);
}

void Win::handleEvent(const sf::Event &e) {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());

    if(this->menu_btn->handleInput(position, e)){
        quit = true;
    }

    if(this->exit_btn->handleInput(position, e)){
        return_to_first = true;
    }
}

void Win::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(this->background);
    target->draw(*this->title);
    target->draw(*this->menu_btn);
    target->draw(*this->exit_btn);
    target->draw(*this->score_widget);
}

void Win::init() {

}