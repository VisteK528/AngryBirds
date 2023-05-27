#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "include/entities/factories/bird_factory.hpp"
#include "include/entities/entity_manager.hpp"
#include "include/textures.hpp"


TEST_CASE("Test loading textures", "loading textures]"){
    SECTION("Loading vector of textures"){
        REQUIRE_NOTHROW(loadTexturesFromPaths(textures_paths.at(TEXTURE_TYPE::RED_BIRD)));
    }

    SECTION("Loading all game textures"){
        std::unordered_map<TEXTURE_TYPE, std::vector<sf::Texture>> entities_textures;
        std::unordered_map<BACKGROUNDS, sf::Texture> background_textures;

        REQUIRE(loadTextures(background_textures, entities_textures) == true);

        REQUIRE(background_textures.size() == 4);
        REQUIRE(entities_textures.size() == 12);
    }
}

TEST_CASE("Test entity manager", "[Entity Manager]"){
    std::shared_ptr<b2World> world = std::make_shared<b2World>(b2Vec2(0, 9.81f));
    EntityManager manager(world);

    std::vector<sf::Texture> textures = loadTexturesFromPaths(textures_paths.at(TEXTURE_TYPE::RED_BIRD));

    BirdFactory<Bird> birdFactory(world, makeShared(textures));

    SECTION("Check birds number"){
        manager.pushEntity(birdFactory.createBird());
        manager.pushEntity(birdFactory.createBird());
        manager.pushEntity(birdFactory.createBird());
        manager.pushEntity(birdFactory.createBird());

        REQUIRE(manager.CountBirds() == 4);
    }
}