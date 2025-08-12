#include "aether/game.hpp"
#include "include/states/menu.hpp"

int main()
{
    Game game("Angry Birds", {1280, 720});
    std::unique_ptr<Menu> menu_state = std::make_unique<Menu>(game);
    game.addState(std::move(menu_state));
    game.run();
    return 0;
}