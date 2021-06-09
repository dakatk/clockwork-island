#include "game/Assets.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>

using namespace engine;
using namespace std;
using namespace game;

Texture* Assets::LoadPlayerSpritesheet()
{
#define PLAYER_IMAGE "resources/images/player_character.png"
#define PLAYER_SPRITE_CLIP_SIZE 100

    return new Texture(PLAYER_IMAGE, PLAYER_SPRITE_CLIP_SIZE, PLAYER_SPRITE_CLIP_SIZE);

#undef PLAYER_IMAGE
#undef PLAYER_SPRITE_CLIP_SIZE
}

Level* Assets::LoadLevel(Robot** player, unsigned int levelNum)
{
#define LEVEL_FILE_REL_PATH "resources/levels/level"
#define LEVEL_FILE_EXT ".bin"

    stringstream stream;
    stream << LEVEL_FILE_REL_PATH << levelNum << LEVEL_FILE_EXT;

#undef LEVEL_FILE_REL_PATH
#undef LEVEL_FILE_EXT

    ifstream lvlFile(stream.str(), ios::in | ios::binary);

#define BACKGROUND_LAYER_1 "resources/images/level0/background_layer_1.png"
#define BACKGROUND_LAYER_2 "resources/images/level0/background_layer_2.png"

    string backgroundLayers[BACKGROUND_NUM_LAYERS] = {
            "", BACKGROUND_LAYER_1, BACKGROUND_LAYER_2
    };

#undef BACKGROUND_LAYER_1
#undef BACKGROUND_LAYER_2

    auto* background = new Background(backgroundLayers);
    auto* level = new Level(background);

    try
    {
        Assets::LoadPlayerData(player, &lvlFile);

        while (!lvlFile.eof())
        {
            Platform* platform = Assets::LoadPlatformData(&lvlFile);

            if (platform == nullptr)
                break;

            level->AddPlatform(platform);
        }
    }
    catch (exception& e)
    {
        lvlFile.close();
        throw e;
    }
    return level;
}

void Assets::LoadPlayerData(Robot** player, ifstream* file)
{
    // REMEMBER: Ordering is little-endian
    // ('buffer[0]' is LSBs of 'data[0]', 'buffer[1]' is MSBs)
    union {
        char buffer[6];
        uint16_t data[3];
    } playerData {};

    file->read(playerData.buffer, sizeof(playerData.buffer));

    if (file->fail())
        throw DataParsingException("Corrupt or incomplete player data");

    // px = player x-coordinate
    // py = player y-coordinate
    // u = player upgrades
    auto px = (int)playerData.data[0];
    auto py = (int)playerData.data[1];
    auto u = (uint8_t)playerData.data[2];

    delete *player;
    *player = new Robot(spritesheets[0], px, py, u);
}

Platform* Assets::LoadPlatformData(ifstream* file)
{
    union {
        char buffer[22];
        uint16_t data[11];
    } platformData {};

    file->read(platformData.buffer, sizeof(platformData.buffer));

    if (file->fail())
    {
        if (file->gcount() != 1 || platformData.buffer[0] != (char)0xFF)
            throw DataParsingException("Corrupt or incomplete platform data");

        return nullptr;
    }

    // vi = visibility index
    // s = sides
    // sx = sprite sheet index x
    // sy = sprite sheet index y
    // x = x-coordinate
    // y = y-coordinate
    // w = width
    // h = height
    // bw = bounds width
    // bh = bounds height
    // f = facing
    auto vi = (uint8_t)platformData.data[0];
    auto s = (uint8_t)platformData.data[1];
    auto sx = (int)platformData.data[2];
    auto sy = (int)platformData.data[3];
    auto x = (int)platformData.data[4];
    auto y = (int)platformData.data[5];
    auto w = (int)platformData.data[6];
    auto h = (int)platformData.data[7];
    auto bw = (float)platformData.data[8];
    auto bh = (float)platformData.data[9];
    auto f = (int)platformData.data[10];

    auto* platform = new Platform(spritesheets[1], f * 90, sx, sy, s, x, y, w, h);
    platform->SetBoundingBox(bw, bh);
    platform->SetVisibility(vi);

    return platform;
}

