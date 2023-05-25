#ifndef ANGRYBIRDS_TEXTURES_HPP
#define ANGRYBIRDS_TEXTURES_HPP

#include <SFML/Graphics.hpp>
#include <memory>

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



std::vector<std::shared_ptr<sf::Texture>> makeShared(std::vector<sf::Texture>& textures);

#endif //ANGRYBIRDS_TEXTURES_HPP
