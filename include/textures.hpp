#ifndef ANGRYBIRDS_TEXTURES_HPP
#define ANGRYBIRDS_TEXTURES_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "../include/exceptions.hpp"

typedef enum{DEFAULT, MOUNTAINS, OCEAN, SPACE} BACKGROUNDS;
typedef enum{
    WOOD,
    WOOD3x1,
    STONE,
    STONE3x1,
    GLASS,
    GLASS3x1,
    BASIC_PIG,
    ARMORED_PIG,
    RED_BIRD,
    YELLOW_BIRD,
    FAT_RED_BIRD,
    GREY_BIRD
} TEXTURE_TYPE;

static std::unordered_map<int, BACKGROUNDS> backgrounds_dict ={
        {0, DEFAULT},
        {1, MOUNTAINS},
        {2, OCEAN},
        {3, SPACE}
};

struct EnumHash {
    template <typename T>
    std::size_t operator()(T t) const {
        return static_cast<std::size_t>(t);
    }
};

static std::unordered_map<int, TEXTURE_TYPE, EnumHash> birds_dict = {
        {8, RED_BIRD},
        {9, YELLOW_BIRD},
        {10, FAT_RED_BIRD},
        {11, GREY_BIRD}
};

static std::unordered_map<int, TEXTURE_TYPE, EnumHash> entities_dict = {
        {0, WOOD},
        {1, WOOD3x1},
        {2, STONE},
        {3, STONE3x1},
        {4, GLASS},
        {5, GLASS3x1},
        {6, BASIC_PIG},
        {7, ARMORED_PIG}
};

static const std::unordered_map<TEXTURE_TYPE, std::vector<std::string>> textures_paths = {
        {WOOD, {"textures/boxes/wood/wood_1x1.png", "textures/boxes/wood/wood_1x1_damaged.png", "textures/boxes/wood/wood_1x1_destroyed.png"}},
        {WOOD3x1, {"textures/boxes/wood/wood_3x1.png", "textures/boxes/wood/wood_3x1_damaged.png", "textures/boxes/wood/wood_3x1_damaged.png"}},
        {GLASS, {"textures/boxes/glass/glass_1x1.png", "textures/boxes/glass/glass_1x1_damaged.png", "textures/boxes/glass/glass_1x1_destroyed.png"}},
        {GLASS3x1, {"textures/boxes/glass/glass_3x1.png", "textures/boxes/glass/glass_3x1_damaged.png", "textures/boxes/glass/glass_3x1_damaged.png"}},
        {STONE, {"textures/boxes/stone/stone_1x1.png", "textures/boxes/stone/stone_1x1_damaged.png", "textures/boxes/stone/stone_1x1_destroyed.png"}},
        {STONE3x1, {"textures/boxes/stone/stone_3x1.png", "textures/boxes/stone/stone_3x1_damaged.png", "textures/boxes/stone/stone_3x1_damaged.png"}},
        {BASIC_PIG, {"textures/pigs/basic/basic_pig.png", "textures/pigs/basic/basic_pig_damaged.png", "textures/pigs/basic/basic_pig_destroyed.png"}},
        {ARMORED_PIG, {"textures/pigs/armored/armored_pig.png", "textures/pigs/armored/armored_pig_damaged.png", "textures/pigs/armored/armored_pig_destroyed.png"}},
        {RED_BIRD, {"textures/birds/bird_red.png"}},
        {YELLOW_BIRD, {"textures/birds/bird_yellow.png"}},
        {GREY_BIRD, {"textures/birds/grey_bird.png"}},
        {FAT_RED_BIRD, {"textures/birds/big_bird.png"}},
};

static std::unordered_map<BACKGROUNDS, std::string> background_paths = {
        {DEFAULT, "textures/background.png"},
        {MOUNTAINS, "textures/background2.png"},
        {OCEAN, "textures/background3.png"},
        {SPACE, "textures/background4.png"},
};

std::vector<std::shared_ptr<sf::Texture>> makeShared(std::vector<sf::Texture>& textures);
std::vector<sf::Texture> loadTexturesFromPaths(const std::vector<std::string>& paths);
bool loadTextures(std::unordered_map<BACKGROUNDS, sf::Texture>& background_textures, std::unordered_map<TEXTURE_TYPE, std::vector<sf::Texture>>& entities_textures);

#endif //ANGRYBIRDS_TEXTURES_HPP
