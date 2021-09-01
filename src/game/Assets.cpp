#include "game/Assets.h"
#include "game/platforms/Spring.h"
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

Level Assets::LoadLevel(Robot& player, Texture* tileSheet, uint8_t levelNum)
{
#define LEVEL_FILE_REL_PATH "resources/levels/level"
#define LEVEL_FILE_EXT ".bin"

    stringstream levelFile;
    levelFile << LEVEL_FILE_REL_PATH << (int)levelNum << LEVEL_FILE_EXT;

#undef LEVEL_FILE_REL_PATH
#undef LEVEL_FILE_EXT

    ifstream lvlFile(levelFile.str(), ios::in | ios::binary);

    if (!lvlFile.good())
        throw AssetException("Failed to load level file: " + levelFile.str());

    Background* background = Assets::LoadBackground(levelNum);
    auto level = Level(background);

    try
    {
        Assets::LoadPlayerData(player, &lvlFile);

        while (!lvlFile.eof())
        {
            Platform* platform = Assets::LoadPlatformData(tileSheet, &lvlFile);
            level.AddPlatform(platform);
        }
    }
    catch (exception& e)
    {
        lvlFile.close();
        throw AssetException(e.what());
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

Texture* Assets::LoadLevelTileSheet(uint8_t levelNum)
{
#define TILE_SHEET_NAME "/tiles.png"
#define TILE_CLIP_SIZE 64

    stringstream tileSheet;
    tileSheet << IMAGE_FILE_REL_PATH << (int)levelNum << TILE_SHEET_NAME;

    return new Texture(tileSheet.str(), TILE_CLIP_SIZE, TILE_CLIP_SIZE);

#undef TILE_SHEET_NAME
#undef TILE_CLIP_SIZE
}

#undef IMAGE_FILE_REL_PATH

void Assets::LoadPlayerData(Robot& player, ifstream* file)
{
    // REMEMBER: Ordering is little-endian
    // ('buffer[0]' is LSBs of 'data[0]', 'buffer[1]' is MSBs)
    union {
        char buffer[6];
        uint16_t data[3];
    } playerData {};

    file->read(playerData.buffer, sizeof(playerData.buffer));

    if (file->fail())
        throw AssetException("Corrupt or incomplete player data");

    // Player x-coordinate
    auto px = (int)playerData.data[0];
    // Player y-coordinate
    auto py = (int)playerData.data[1];
    // Upgrades
    auto u = (uint8_t)playerData.data[2];

    player.MoveTo(px, py);
    player.SetAllowedFilters(u);
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
            throw AssetException("Corrupt or incomplete platform data");
    }

    // Visibility index
    auto vi = (uint8_t)platformData.data[0];
    // Sides
    auto s = (uint8_t)platformData.data[1];
    // Spritesheet x-index
    auto sx = (int)platformData.data[2];
    // Spritesheet y-index
    auto sy = (int)platformData.data[3];
    // X-coordinate
    auto x = (int)platformData.data[4];
    // Y-coordinate
    auto y = (int)platformData.data[5];
    // Width
    auto w = (int)platformData.data[6];
    // Height
    auto h = (int)platformData.data[7];
    // Bounds width
    auto bw = (float)platformData.data[8];
    // Bounds height
    auto bh = (float)platformData.data[9];
    // Facing
    auto f = (int)platformData.data[10];

    auto rotation = f * 90;

    Platform* platform;
    if (sx == 3 && sy == 3)
        platform = new Spring(tileSheet, rotation, sx, sy, s, x, y, w, h);
    else
        platform = new Platform(tileSheet, rotation, sx, sy, s, x, y, w, h);

    platform->SetBoundingBox(bw, bh);
    platform->SetVisibility(vi);

    return platform;
}

