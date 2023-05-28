#include "include/states/win.hpp"

Win::Win(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states,
         std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager,
         const sf::Image& background_image, int score): ResultState(
                 std::move(window), std::move(states), std::move(gui_manager),
                 std::move(sound_manager), background_image, score){}

Win::~Win()= default;

void Win::init() {
    ResultState::init();
    this->title = gui_manager->createText("You won!", 70, sf::Vector2f(640, 150), ui::ORIGIN::C);
    this->score_widget = gui_manager->createText("Score: "+std::to_string(player_score), 20, sf::Vector2f(640, 250), ui::ORIGIN::C);

    this->next_lvl_btn = gui_manager->createButton("> Next level",20, sf::Vector2f(640, 320), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->retry_btn = gui_manager->createButton("> Retry",20, sf::Vector2f(640, 400), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->back_btn = gui_manager->createButton("> Back", 20, sf::Vector2f(640, 480), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->menu_btn = gui_manager->createButton("> Menu",20, sf::Vector2f(640, 560), sf::Vector2f(250, 60), ui::ORIGIN::C);

    this->sound_manager->setBackgroundMusic("sounds/win_sound.wav");
    this->sound_manager->getBackgroundMusic().setLoop(false);
    this->sound_manager->getBackgroundMusic().play();
}

void Win::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(this->background);
    target->draw(*this->title);
    target->draw(*this->back_btn);
    target->draw(*this->menu_btn);
    target->draw(*this->retry_btn);
    target->draw(*this->next_lvl_btn);
    target->draw(*this->score_widget);
}

void Win::handleEvent(const sf::Event &e) {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());
    if(this->back_btn != nullptr && this->menu_btn != nullptr && this-> retry_btn != nullptr){
        if(this->back_btn->handleInput(position, e)){
            quit = true;
        }

        if(this->menu_btn->handleInput(position, e)){
            return_to_first = true;
        }

        if(this->retry_btn->handleInput(position, e)){
            ResultState::State::retry_level = true;
            quit = true;
        }

        if(this->next_lvl_btn->handleInput(position, e)){
            ResultState::State::load_next_level = true;
            quit = true;
        }

        if(quit){
            this->sound_manager->getBackgroundMusic().stop();
        }
    }
}