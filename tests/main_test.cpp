#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "include/entities/factories/bird_factory.hpp"
#include "include/entities/factories/pig_factory.hpp"
#include "include/entities/factories/box_factory.hpp"
#include "include/entities/entity_manager.hpp"
#include "include/textures.hpp"
#include "include/game.hpp"
#include "include/states/game_state.hpp"


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
    std::vector<sf::Texture> textures2 = loadTexturesFromPaths(textures_paths.at(TEXTURE_TYPE::BASIC_PIG));
    std::vector<sf::Texture> textures3 = loadTexturesFromPaths(textures_paths.at(TEXTURE_TYPE::WOOD));

    BirdFactory<Bird> birdFactory(world, makeShared(textures));
    PigFactory<BasicPig> pigFactory(world, makeShared(textures2));
    BoxFactory<Wood> boxFactory(world, makeShared(textures3));

    SECTION("Check birds number"){
        manager.pushEntity(birdFactory.createBird());
        manager.pushEntity(birdFactory.createBird());
        manager.pushEntity(birdFactory.createBird());
        manager.pushEntity(birdFactory.createBird());

        REQUIRE(manager.CountBirds() == 4);
    }

    SECTION("Check pigs number"){
        manager.pushEntity(pigFactory.createPig(0,0));
        manager.pushEntity(pigFactory.createPig(1,1));
        manager.pushEntity(pigFactory.createPig(2,2));

        REQUIRE(manager.CountPigs() == 3);
    }

    SECTION("Check blocks number"){
        manager.pushEntity(boxFactory.createBox(1,1));
        manager.pushEntity(boxFactory.createBox(2,2));

        REQUIRE(manager.CountBlocks() == 2);
    }

    SECTION("Check score"){
        manager.pushEntity(pigFactory.createPig(0,0));

        REQUIRE(manager.getCurrentScore() == 0);

        manager.updateScore(100);
        REQUIRE(manager.getCurrentScore() == 100);

        manager.updateScore(100);
        REQUIRE(manager.getCurrentScore() == 200);
    }

    SECTION("Check win"){
        REQUIRE(manager.CheckForWin() == false);
        manager.setBirds(1);
        manager.pushEntity(boxFactory.createBox(0,0));
        manager.getEntities().at(0)->setDestroyed();
        manager.update();
        REQUIRE(manager.CountPigs() == 0);
        REQUIRE(manager.CheckForWin() == true);
    }

    SECTION("Check lose"){
        REQUIRE(manager.CheckForLose() == false);
        manager.pushEntity(pigFactory.createPig(0,0));
        manager.setBirds(0);
        REQUIRE(manager.CheckForLose() == true);
    }

    SECTION("Check quantity of entities"){
        REQUIRE(manager.getEntities().size() == 0);
        manager.pushEntity(birdFactory.createBird());
        REQUIRE(manager.getEntities().size() == 1);
        manager.pushEntity(pigFactory.createPig(0,0));
        REQUIRE(manager.getEntities().size() == 2);
        manager.pushEntity(boxFactory.createBox(0,0));
        REQUIRE(manager.getEntities().size() == 3);
    }
}

TEST_CASE("Test bird factory", "[Bird Factory]"){
    std::shared_ptr<b2World> world = std::make_shared<b2World>(b2Vec2(0, 9.81f));
    std::vector<sf::Texture> textures = loadTexturesFromPaths(textures_paths.at(TEXTURE_TYPE::RED_BIRD));

    BirdFactory<Bird> birdFactory(world, makeShared(textures));

    SECTION("Check bird creation"){
        REQUIRE_NOTHROW(birdFactory.createBird());
    }

    SECTION("Check bird type"){
        REQUIRE(birdFactory.createBird()->getType().main_type == TYPE_DATA::BIRD);
    }
}

TEST_CASE("Test pig factory", "[Pig Factory]"){
    std::shared_ptr<b2World> world = std::make_shared<b2World>(b2Vec2(0, 9.81f));
    std::vector<sf::Texture> textures = loadTexturesFromPaths(textures_paths.at(TEXTURE_TYPE::BASIC_PIG));

    PigFactory<BasicPig> pigFactory(world, makeShared(textures));

    SECTION("Check pig creation"){
        REQUIRE_NOTHROW(pigFactory.createPig(0,0));
    }

    SECTION("Check pig type"){
        REQUIRE(pigFactory.createPig(0,0)->getType().main_type == TYPE_DATA::PIG);
    }
}

TEST_CASE("Test box factory", "[Box Factory]"){
    std::shared_ptr<b2World> world = std::make_shared<b2World>(b2Vec2(0, 9.81f));
    std::vector<sf::Texture> textures = loadTexturesFromPaths(textures_paths.at(TEXTURE_TYPE::WOOD));

    BoxFactory<Wood> boxFactory(world, makeShared(textures));

    SECTION("Check box creation"){
        REQUIRE_NOTHROW(boxFactory.createBox(0,0));
    }

    SECTION("Check box type"){
        REQUIRE(boxFactory.createBox(0,0)->getType().main_type == TYPE_DATA::BOX);
    }
}

TEST_CASE("Test entity", "[Entity]"){
    std::shared_ptr<b2World> world = std::make_shared<b2World>(b2Vec2(0, 9.81f));
    std::vector<sf::Texture> textures = loadTexturesFromPaths(textures_paths.at(TEXTURE_TYPE::RED_BIRD));
    std::vector<sf::Texture> textures2 = loadTexturesFromPaths(textures_paths.at(TEXTURE_TYPE::BASIC_PIG));
    std::vector<sf::Texture> textures3 = loadTexturesFromPaths(textures_paths.at(TEXTURE_TYPE::WOOD));

    BirdFactory<Bird> birdFactory(world, makeShared(textures));
    PigFactory<BasicPig> pigFactory(world, makeShared(textures2));
    BoxFactory<Wood> boxFactory(world, makeShared(textures3));

    EntityManager manager(world);

    SECTION("Check entity type"){
        manager.pushEntity(birdFactory.createBird());
        manager.pushEntity(pigFactory.createPig(0,0));
        manager.pushEntity(boxFactory.createBox(0,0));

        REQUIRE(manager.getEntities().at(0)->getType().main_type == TYPE_DATA::BIRD);
        REQUIRE(manager.getEntities().at(1)->getType().main_type == TYPE_DATA::PIG);
        REQUIRE(manager.getEntities().at(2)->getType().main_type == TYPE_DATA::BOX);
    }

    SECTION("Check entity position"){
        manager.pushEntity(birdFactory.createBird());
        manager.pushEntity(pigFactory.createPig(0,0));
        manager.pushEntity(boxFactory.createBox(0,0));

        REQUIRE(manager.getEntities().at(0)->getBody()->GetFixtureList()->GetBody()->GetPosition().x == 0);
        REQUIRE(manager.getEntities().at(0)->getBody()->GetFixtureList()->GetBody()->GetPosition().y == 0);

        REQUIRE(manager.getEntities().at(1)->getBody()->GetFixtureList()->GetBody()->GetPosition().x == 0);
        REQUIRE(manager.getEntities().at(1)->getBody()->GetFixtureList()->GetBody()->GetPosition().y == 0);

        REQUIRE(manager.getEntities().at(2)->getBody()->GetFixtureList()->GetBody()->GetPosition().x == 0);
        REQUIRE(manager.getEntities().at(2)->getBody()->GetFixtureList()->GetBody()->GetPosition().y == 0);
    }
}

TEST_CASE("Test bird", "[Bird]"){
    std::shared_ptr<b2World> world = std::make_shared<b2World>(b2Vec2(0, 9.81f));
    std::vector<sf::Texture> textures = loadTexturesFromPaths(textures_paths.at(TEXTURE_TYPE::RED_BIRD));

    BirdFactory<Bird> birdFactory(world, makeShared(textures));

    SECTION("Check bird type"){
        REQUIRE(birdFactory.createBird()->getType().main_type == TYPE_DATA::BIRD);
    }

    SECTION("Check bird position"){
        std::unique_ptr<Bird> bird = birdFactory.createBird();
        REQUIRE(bird->getBody()->GetFixtureList()->GetBody()->GetPosition().x == 0);
        REQUIRE(bird->getBody()->GetFixtureList()->GetBody()->GetPosition().y == 0);
    }
}

TEST_CASE("Test pig", "[Pig]"){
    std::shared_ptr<b2World> world = std::make_shared<b2World>(b2Vec2(0, 9.81f));
    std::vector<sf::Texture> textures = loadTexturesFromPaths(textures_paths.at(TEXTURE_TYPE::BASIC_PIG));

    PigFactory<BasicPig> pigFactory(world, makeShared(textures));

    SECTION("Check pig type"){
        REQUIRE(pigFactory.createPig(0,0)->getType().main_type == TYPE_DATA::PIG);
    }

    SECTION("Check pig position"){
        REQUIRE(pigFactory.createPig(0,0)->getBody()->GetFixtureList()->GetBody()->GetPosition().x == 0);
        REQUIRE(pigFactory.createPig(0,0)->getBody()->GetFixtureList()->GetBody()->GetPosition().y == 0);
    }

    SECTION("Check pig health"){
        std::unique_ptr<BasicPig> pig = pigFactory.createPig(0, 0);
        REQUIRE(pig->getHealth() == 800);
    }
}

TEST_CASE("Test box", "[Box]"){
    std::shared_ptr<b2World> world = std::make_shared<b2World>(b2Vec2(0, 9.81f));
    std::vector<sf::Texture> textures = loadTexturesFromPaths(textures_paths.at(TEXTURE_TYPE::WOOD));

    BoxFactory<Wood> boxFactory(world, makeShared(textures));

    SECTION("Check box type"){
        REQUIRE(boxFactory.createBox(0,0)->getType().main_type == TYPE_DATA::BOX);
    }

    SECTION("Check box position"){
        std::unique_ptr<Wood> wood = boxFactory.createBox(0, 0);
        REQUIRE(wood->getBody()->GetFixtureList()->GetBody()->GetPosition().x == 0);
        REQUIRE(wood->getBody()->GetFixtureList()->GetBody()->GetPosition().y == 0);
    }
}
