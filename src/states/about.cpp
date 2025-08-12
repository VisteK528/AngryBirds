#include "include/states/about.hpp"

About::About(Game& game): AngryBirdsState(game){
    title_ = nullptr;
    about_text_ = nullptr;
    back_btn_ = nullptr;
    initVariables();
}

void About::initVariables() {
    title_ = game_.gui_manager->createText("About", 70, sf::Vector2f(640, 125), ui::ORIGIN::C);


    about_text_ = game_.gui_manager->createText("This is Angry Birds remake, a game made Piotr Patek and Jakub Wroblewski.\n"
                                                "We are students of Automatics and Robotics at the Warsaw University of Technology.\n"
                                                "This game was made as a project for the subject 'Object Oriented Programming'.\n"
                                                "We hope you will enjoy it!\n\n"
                                                "There are two modes in this game: Adventure and Custom.\n"
                                                "In Adventure mode you can play 14 levels, each one is harder than the previous one.\n"
                                                "In Custom mode you can play levels created by other players or create your own levels.\n\n"
                                                "Controls:\n"
                                                "Left mouse button - shoot\n"
                                                "Right mouse button - special ability\n"
                                                "Scroll - change bird\n"
                                                "Mouse - aim\n"
                                                "Esc - return to menu\n\n"
                                                "Birds:\n"
                                                "Red bird - normal bird\n"
                                                "Yellow bird - speeds up\n"
                                                "Big red bird - heavy bird\n"
                                                "Grey bird - launches downwards\n",
                                                12, sf::Vector2f(640, 250), ui::ORIGIN::C);

    back_btn_ = game_.gui_manager->createButton("> Back", 20, sf::Vector2f(1180, 680), sf::Vector2f(160, 40), ui::ORIGIN::C);


    background_texture_.loadFromFile("textures/menu_background.jpeg");
    background_ = sf::Sprite(background_texture_);
    background_.setColor(sf::Color(255, 255, 255, 120));
    background_.setPosition(0,0);
}

void About::update(const float &) {
    game_.sound_manager->updateVolume();
    sf::Vector2f position = game_.window->mapPixelToCoords(sf::Mouse::getPosition(*game_.window), game_.window->getView());
    back_btn_->update(position);
}

void About::handleEvent(const sf::Event &e) {
    sf::Vector2f position = game_.window->mapPixelToCoords(sf::Mouse::getPosition(*game_.window), game_.window->getView());

    if (back_btn_->handleInput(position, e)) {
        quit = true;
    }
}

void About::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background_);
    target->draw(*title_);
    target->draw(*about_text_);
    target->draw(*back_btn_);
}
