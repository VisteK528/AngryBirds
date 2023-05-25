#include "include/states/win.hpp"

Win::Win(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states,
         std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager,
         const sf::Image& background_image, int score): ResultState(
                 std::move(window), std::move(states), std::move(gui_manager),
                 std::move(sound_manager), background_image, score){}

Win::~Win()= default;

void Win::init() {
    ResultState::init();
    this->title = gui_manager->createText("You won!", 70, sf::Vector2f(640, 250), ui::ORIGIN::C);
    this->menu_btn = gui_manager->createButton("> Menu", 20, sf::Vector2f(640, 420), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->exit_btn = gui_manager->createButton("> Exit",20, sf::Vector2f(640, 500), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->score_widget = gui_manager->createText("Score: "+std::to_string(player_score), 20, sf::Vector2f(640, 350), ui::ORIGIN::C);

    this->sound_manager->loadBackgroundMusic("sounds/Angry-Birds-Theme.wav");
    this->sound_manager->getBackgroundMusic().setLoop(true);
    this->sound_manager->getBackgroundMusic().play();
}