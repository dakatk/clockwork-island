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

Level* Assets::LoadLevel(Robot* player, uint8_t levelNum)
{
#define LEVEL_FILE_REL_PATH "resources/levels/level"
#define LEVEL_FILE_EXT ".bin"

    stringstream stream;
    stream << LEVEL_FILE_REL_PATH << (int)levelNum << LEVEL_FILE_EXT;

#undef LEVEL_FILE_REL_PATH
#undef LEVEL_FILE_EXT

    ifstream lvlFile(stream.str(), ios::in | ios::binary);

    Background* background = Assets::LoadBackground(levelNum);
    Texture* tileSheet = Assets::LoadTileSheet(levelNum);

    auto* level = new Level(background, tileSheet);

    try
    {
        Assets::LoadPlayerData(player, &lvlFile);

        while (!lvlFile.eof())
        {
            Platform* platform = Assets::LoadPlatformData(tileSheet, &lvlFile);

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

#define IMAGE_FILE_REL_PATH "resources/images/level"

Background* Assets::LoadBackground(uint8_t levelNum)
{
#define BACKGROUND_LAYER_0_NAME "/background_layer_0.png"
#define BACKGROUND_LAYER_1_NAME "/background_layer_1.png"
#define BACKGROUND_LAYER_2_NAME "/background_layer_2.png"

    stringstream backgroundFile0;
    stringstream backgroundFile1;
    stringstream backgroundFile2;

    backgroundFile0 << IMAGE_FILE_REL_PATH << (int)levelNum << BACKGROUND_LAYER_0_NAME;
    backgroundFile1 << IMAGE_FILE_REL_PATH << (int)levelNum << BACKGROUND_LAYER_1_NAME;
    backgroundFile2 << IMAGE_FILE_REL_PATH << (int)levelNum << BACKGROUND_LAYER_2_NAME;

    string backgroundLayers[BACKGROUND_NUM_LAYERS] = {
            backgroundFile0.str(), backgroundFile1.str(), backgroundFile2.str()
    };
    return new Background(backgroundLayers);

#undef BACKGROUND_LAYER_0_NAME
#undef BACKGROUND_LAYER_1_NAME
#undef BACKGROUND_LAYER_2_NAME
}

Texture* Assets::LoadTileSheet(uint8_t levelNum)
{
#define TILE_SHEET_NAME "/tiles.png"
#define TILE_CLIP_SIZE 128

    stringstream tileSheet;
    tileSheet << IMAGE_FILE_REL_PATH << (int)levelNum << TILE_SHEET_NAME;

    return new Texture(tileSheet.str(), TILE_CLIP_SIZE, TILE_CLIP_SIZE);

#undef TILE_SHEET_NAME
#undef TILE_CLIP_SIZE
}

#undef IMAGE_FILE_REL_PATH

void Assets::LoadPlayerData(Robot* player, ifstream* file)
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

    player->MoveTo(px, py);
    player->SetAllowedFilters(u);
}

Platform* Assets::LoadPlatformData(Texture* tileSheet, ifstream* file)
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

    auto* platform = new Platform(tileSheet, f * 90, sx, sy, s, x, y, w, h);
    platform->SetBoundingBox(bw, bh);
    platform->SetVisibility(vi);

    return platform;
}

