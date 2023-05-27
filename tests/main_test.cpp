#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../include/entities/entity_manager.hpp"
#include "../include/entities/factories/bird_factory.hpp"
#include "../include/entities/factories/pig_factory.hpp"

TEST_CASE("Test entity manager"){
    std::shared_ptr<b2World> world = std::make_shared<b2World>(b2Vec2(0, 9.81f));
    EntityManager manager(world);

    BirdFactory<Bird> birdFactory();

    manager.pushEntity()

}