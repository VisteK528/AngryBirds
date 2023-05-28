//
// Created by piotr on 5/4/23.
//

#ifndef ANGRYBIRDS_STATE_HPP
#define ANGRYBIRDS_STATE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <map>
#include <memory>
#include <utility>
#include "include/gui_manager.hpp"
#include "include/sound_manager.hpp"

class State {
protected:
    std::shared_ptr<std::stack<std::unique_ptr<State>>> states;
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<GuiManager> gui_manager;
    std::shared_ptr<SoundManager> sound_manager;

    inline static bool retry_level = false;
    inline static bool load_next_level = false;
    inline static unsigned int current_level_number = 0;

    bool quit = false;
    bool return_to_first = false;
    bool retry = false;
public:
    State(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager);
    virtual ~State();

    virtual void init() = 0;
    const bool& getQuit() const;
    const bool& returnToFirst() const;
    virtual void update(const float& dt) = 0;
    virtual void handleEvent(const sf::Event& e) = 0;
    virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr) = 0;
};


#endif //ANGRYBIRDS_STATE_HPP
