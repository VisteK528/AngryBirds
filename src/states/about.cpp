#include "include/states/about.hpp"

About::About(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states,
             std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager): State(
        std::move(window), std::move(states), std::move(gui_manager), std::move(sound_manager)){
    this->title = nullptr;
    this->about_text = nullptr;
    this->back_btn = nullptr;
    initVariables();
}

About::~About() {

}

void About::initVariables() {
    this->title = gui_manager->createText("About", 70, sf::Vector2f(640, 125), ui::ORIGIN::C);

    this->about_text = gui_manager->createText("This is Angry Birds remake, a game made Piotr Patek and Jakub Wroblewski.\n"
                                                "We are students of Automatics and Robotics at the Warsaw University of Technics.\n"
                                                "This game was made as a project for the subject 'Object Oriented Programming'.\n"
                                                "We hope you will enjoy it!\n\n"
                                                "There are two modes in this game: Adventure and Custom.\n"
                                                "In Adventure mode you can play 14 levels, each one is harder than the previous one.\n"
                                                "In Custom mode you can play levels created by other players or create your own levels.\n\n"
                                                "Controls:\n"
                                                "Left mouse button - shoot\n"
                                                "Right mouse button - special ability\n"
                                                "Mouse - aim\n\n"
                                                "Birds:\n"
                                                "Red bird - normal bird\n"
                                                "Yellow bird - speeds up\n"
                                                "Big red bird - heavy bird\n"
                                                "Grey bird - launches downwards\n",
                                                12, sf::Vector2f(640, 250), ui::ORIGIN::C);

    this->back_btn = gui_manager->createButton("> Back", 20, sf::Vector2f(1180, 680), sf::Vector2f(160, 40), ui::ORIGIN::C);

    this->background_texture.loadFromFile("textures/menu_background.jpeg");
    this->background = sf::Sprite(background_texture);
    this->background.setColor(sf::Color(255, 255, 255, 180));
    this->background.setPosition(0,0);
}

void About::update(const float &) {
    this->sound_manager->updateVolume();
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());
    this->back_btn->update(position);
}

void About::handleEvent(const sf::Event &e) {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());

    if (this->back_btn->handleInput(position, e)) {
        quit = true;
    }
}

void About::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background);
    target->draw(*this->title);
    target->draw(*this->about_text);
    target->draw(*this->back_btn);
}

void About::init() {

}
