//
// Created by piotr on 5/4/23.
//

#include "state.hpp"

State::State(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states){
    this->window = window;
    this->states = states;
    this->quit = false;
}

State::~State(){}

const bool& State::getQuit() const{
    return this->quit;
}