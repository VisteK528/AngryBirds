#include "include/states/menu.hpp"

Menu::Menu(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states,
           std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager): State(
                   std::move(window), std::move(states), std::move(gui_manager),
                   std::move(sound_manager)){
    this->title = nullptr;
    this->start_btn = nullptr;
    this->editor_btn = nullptr;
    this->about_btn = nullptr;
    this->exit_btn = nullptr;
    initVariables();
}

Menu::~Menu(){

}

void Menu::initVariables() {
    this->title = gui_manager->createText("Angry Birds", 70, sf::Vector2f(640, 250), ui::ORIGIN::C);
    this->start_btn = gui_manager->createButton("> Start", 20, sf::Vector2f(640, 400), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->editor_btn = gui_manager->createButton("> Editor",20, sf::Vector2f(640, 480), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->about_btn = gui_manager->createButton("> About", 20, sf::Vector2f(640, 560), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->exit_btn = gui_manager->createButton("> Exit",20, sf::Vector2f(640, 640), sf::Vector2f(250, 60), ui::ORIGIN::C);

    this->sound_manager->loadBackgroundMusic("sounds/Angry-Birds-Theme.wav");
    this->sound_manager->getBackgroundMusic().setLoop(true);
    this->sound_manager->getBackgroundMusic().play();

    this->background_texture.loadFromFile("textures/menu_background.jpeg");
    this->background = sf::Sprite(background_texture);
    this->background.setColor(sf::Color(255, 255, 255, 180));
    this->background.setPosition(0,0);
}

void Menu::update(const float &) {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());
    this->start_btn->update(position);
    this->editor_btn->update(position);
    this->about_btn->update(position);
    this->exit_btn->update(position);
}

void Menu::handleEvent(const sf::Event &e) {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());

    if(this->start_btn->handleInput(position, e)){
        // TODO Create Lobby state as a intermediate state between menu and game state
        /* Lobby state should provide user with two types of gameplay
         *      1. Adventure - previously created levels with increasing level of difficulty
         *      2. Custom    - levels created and saved to data directory by user
         * */
        this->states->push(std::make_unique<Lobby>(this->window, this->states, this->gui_manager, this->sound_manager));
    }

    if(this->editor_btn->handleInput(position, e)){
        this->states->push(std::make_unique<EditorState>(this->window, this->states, this->gui_manager, this->sound_manager));
    }

    if(this->about_btn->handleInput(position, e)){
        // TODO Add about state
    }

    if(this->exit_btn->handleInput(position, e)){
        quit = true;
    }
}

void Menu::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background);
    target->draw(*title);
    target->draw(*start_btn);
    target->draw(*editor_btn);
    target->draw(*about_btn);
    target->draw(*exit_btn);
}

void Menu::init() {

}
