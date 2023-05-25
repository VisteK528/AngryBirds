#include "state.hpp"

State::State(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states,
             std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager){
    this->window = std::move(window);
    this->states = std::move(states);
    this->gui_manager = std::move(gui_manager);
    this->sound_manager = std::move(sound_manager);
    this->quit = false;
}

State::~State(){}

const bool& State::getQuit() const{
    return this->quit;
}

const bool& State::returnToFirst() const{
    return this->return_to_first;
}