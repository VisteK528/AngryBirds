//
// Created by piotr on 5/4/23.
//

#ifndef ANGRYBIRDS_MENU_HPP
#define ANGRYBIRDS_MENU_HPP

#include "../widgets.hpp"
#include "../gui_manager.hpp"
#include "state.hpp"
#include "game_state.hpp"
#include "editor_state.hpp"
#include "lobby.hpp"

class Menu: public State {
private:
    std::shared_ptr<GuiManager> gui_manager;
    std::unique_ptr<ui::Text> title;
    std::unique_ptr<ui::Button> start_btn;
    std::unique_ptr<ui::Button> editor_btn;
    std::unique_ptr<ui::Button> about_btn;
    std::unique_ptr<ui::Button> exit_btn;

    void initVariables();
public:
    Menu(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager);
    ~Menu();
    void init() override;
    void update(const float& dt) override;
    void handleEvent(const sf::Event& e) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
};


#endif //ANGRYBIRDS_MENU_HPP
