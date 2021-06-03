#include "AssetLoader.h"
#include "engine/Filter.h"
#include "engine/Texture.h"
#include "engine/Viewport.h"
#include "engine/Background.h"

#include <stdio.h>
#include <stdint.h>

#define NUM_TEXTURES 2

static struct Texture spritesheets[NUM_TEXTURES];

bool AssetLoader_LoadResources(SDL_Renderer* renderer)
{
#define PLAYER_IMAGE "resources/images/player_character.png"
#define TILES_IMAGE "resources/images/tiles.png"

	const char* filenames[NUM_TEXTURES] = {
			PLAYER_IMAGE,
			TILES_IMAGE
	};
#undef PLAYER_IMAGE
#undef TILES_IMAGE

#define PLAYER_SPRITE_CLIP_SIZE 100
#define PLATFORM_SPRITE_CLIP_SIZE 128

	const int clipSizes[NUM_TEXTURES] = {
			PLAYER_SPRITE_CLIP_SIZE,
			PLATFORM_SPRITE_CLIP_SIZE
	};

#undef PLAYER_SPRITE_CLIP_SIZE
#undef PLATFORM_SPRITE_CLIP_SIZE

	for (int i = 0; i < NUM_TEXTURES; i ++)
	{
		if (!Texture_Init(&spritesheets[i], renderer, filenames[i], clipSizes[i]))
		{
			fprintf(stderr, "Error: Sprite sheet '%s' is missing.\n", filenames[i]);
			return false;
		}
	}
#define BACKGROUND_LAYER_1 "resources/images/background_layer_1.png"
#define BACKGROUND_LAYER_2 "resources/images/background_layer_2.png"

	if (!Background_Init(renderer, BACKGROUND_LAYER_1, BACKGROUND_LAYER_2))
	{
		fprintf(stderr, "Error: Failed to load background images.\n");
		return false;
	}
#undef BACKGROUND_LAYER_1
#undef BACKGROUND_LAYER_2

	return true;
}

void AssetLoader_UnloadResources()
{
	for(int i = 0; i < NUM_TEXTURES; i ++)
		Texture_Destroy(&spritesheets[i]);

	Background_Destroy();
}

static bool LoadPlayerData(struct Player* player, FILE* lvlFile);
static int LoadPlatformData(struct Platform* platform, FILE* lvlFile);

bool AssetLoader_LoadLevelFile(struct Level* level, struct Player* player, const char* filename)
{
	FILE* lvlFile = fopen(filename, "rb");
	if (lvlFile == NULL)
	{
		fprintf(stderr, "File not found '%s'\n", filename);
		return false;
	}
	fseek(lvlFile, 0, SEEK_SET);

	if (!LoadPlayerData(player, lvlFile))
	{
	    fclose(lvlFile);
        return false;
    }
	
	Level_Init(level);

	while(!feof(lvlFile))
    {
		struct Platform platform;

		int result = LoadPlatformData(&platform, lvlFile);
		if (result != 1)
		{
		    fclose(lvlFile);

		    if (result == -1)
                return false;

		    else break;
        }
		Level_AddPlatform(level, &platform);
	}
	return true;
}

static bool LoadPlayerData(struct Player* player, FILE* lvlFile)
{
    // REMEMBER: Ordering is little-endian
    // ('buffer[0]' is LSBs of 'data[0]', 'buffer[1]' is MSBs)
	union {
	    uint8_t buffer[6];
	    uint16_t data[3];
	} playerData;

    size_t result = fread(playerData.buffer, sizeof(playerData.buffer), 1, lvlFile);
    if (result != 1)
    {
        fprintf(stderr, "Corrupt or incomplete player data.\n");
        return false;
    }

    // px = player x-coordinate
    // py = player y-coordinate
    // u = player upgrades
    int px = (int)playerData.data[0];
    int py = (int)playerData.data[1];
    int u = (int)playerData.data[2];

    if (u < 0) u = 0;

    else if (u >= NUM_FILTERS)
        u = NUM_FILTERS - 1;

#define PLAYER_WIDTH 100
#define PLAYER_HEIGHT 100

	Player_Init(player, &spritesheets[0], px, py, PLAYER_WIDTH, PLAYER_HEIGHT, u);

#undef PLAYER_WIDTH
#undef PLAYER_HEIGHT

	return true;
}

static int LoadPlatformData(struct Platform* platform, FILE* lvlFile)
{
    union {
        uint8_t buffer[16];
        uint16_t data[8];
    } platformData;

    size_t result = fread(platformData.buffer, sizeof(platformData.buffer), 1, lvlFile);
    if (result != 1)
    {
        if (platformData.buffer[0] == 0xFF) {
            return 0;
        }
        fprintf(stderr, "Corrupt or incomplete platform data.\n");
        return -1;
    }

    // t = visibility index
    // s = sides
    // i = sprite sheet index
    // x = x-coordinate
    // y = y-coordinate
    // w = width
    // h = height
    // f = facing
    uint8_t t = (uint8_t)platformData.data[0];
    uint8_t s = (uint8_t)platformData.data[1];
    int i = (int)platformData.data[2];
    int x = (int)platformData.data[3];
    int y = (int)platformData.data[4];
    int w = (int)platformData.data[5];
    int h = (int)platformData.data[6];
    int f = (int)platformData.data[7];

    double angle = (double)(f * 90);
    Platform_Init(platform, &spritesheets[1], angle, i, t, s, x, y, w, h);

    return 1;
}

#undef NUM_VISIBLE_OPTIONS
#undef NUM_TEXTURES