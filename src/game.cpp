//
// Created by piotr on 5/4/23.
//

#include "game.hpp"

Game::Game() {
    this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(window_dimensions.x, window_dimensions.y), "AngryBirds");
    this->window->setFramerateLimit(120);
    this->view = std::make_unique<sf::View>(this->window->getDefaultView());

    loadTextures();
    setIcon();

    this->states = std::make_shared<std::stack<std::unique_ptr<State>>>();
    states->push(std::make_unique<GameState>(this->window, this->states));
}

Game::~Game() {
    while(!this->states->empty()){
        states->pop();
    }
}

void Game::render() {
    this->window->clear();
    if(!this->states->empty()){
        this->states->top()->render(this->window);
    }
    this->window->display();
}

void Game::updateDt() {
    this->dt = dt_clock.getElapsedTime().asSeconds();
}

void Game::updateEvents() {
    while(this->window->pollEvent(e)){
        if(this->e.type == sf::Event::Closed){
            this->window->close();
        }
        else if(this->e.type == sf::Event::Resized) {
            sf::Vector2f view_size = {static_cast<float>(this->e.size.width), static_cast<float>(this->e.size.height)};
            view->setSize(view_size);
            window->setView(*view);
        }
    }
}

void Game::run() {
    while(this->window->isOpen()){
        updateDt();
        update();
        render();
    }
}

void Game::loadTextures() {

}

void Game::setIcon() {

}

void Game::update() {
    updateEvents();
    if(!this->states->empty()){
        this->states->top()->update(dt);
        if(this->states->top()->getQuit()){
            this->states->pop();
            if(!this->states->empty()){
                this->states->top()->init();
            }
        }
    }
    else{
        window->close();
    }
}
