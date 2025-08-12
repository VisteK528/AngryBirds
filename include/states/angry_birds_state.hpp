#ifndef ANGRY_BIRDS_STATE_HPP
#define ANGRY_BIRDS_STATE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "aether/gui_manager.hpp"
#include "aether/game.hpp"

class AngryBirdsState: public IGameState {
    protected:
        Game& game_;

        inline static bool retry_level = false;
        inline static bool load_next_level = false;
        inline static unsigned int current_level_number = 0;

        bool retry = false;
    public:
        explicit AngryBirdsState(Game& game): game_(game){}
        virtual ~AngryBirdsState(){}

        virtual void update(const float& dt) = 0;
        virtual void handleEvent(const sf::Event& e) = 0;
        virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr) = 0;
};

#endif //ANGRY_BIRDS_STATE_HPP
