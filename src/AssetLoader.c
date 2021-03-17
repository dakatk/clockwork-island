#include "AssetLoader.h"
#include "engine/Texture.h"
#include "engine/Viewport.h"
#include "engine/Background.h"

#include <stdio.h>
#include <stdint.h>

#define NUM_VISIBLE_OPTIONS 43
#define NUM_TEXTURES 2

static struct Texture spritesheets[NUM_TEXTURES];

static const bool optionsVisible[NUM_VISIBLE_OPTIONS][NUM_PLATFORM_VISIBLE_OPTIONS] = {
		{true, false, false, false, false, false}, // only NONE					(0)
		{false, true, false, false, false, false}, // only RED					(1)
		{false, false, true, false, false, false}, // only GREEN				(2)
		{false, false, false, true, false, false}, // only BLUE					(3)
		{false, false, false, false, true, false}, // only ORANGE				(4)
		{false, false, false, false, false, true}, // only VIOLET				(5)

		{true, true, false, false, false, false}, // NONE and RED				(6)
		{true, false, true, false, false, false}, // NONE and GREEN				(7)
		{true, false, false, true, false, false}, // NONE and BLUE				(8)
		{true, false, false, false, true, false}, // NONE and ORANGE			(9)
		{true, false, false, false, false, true}, // NONE and VIOLET			(10)

		{false, true, true, false, false, false}, // RED and GREEN				(11)
		{false, true, false, true, false, false}, // RED and BLUE				(12)
		{false, true, false, false, true, false}, // RED and ORANGE				(13)
		{false, true, false, false, false, true}, // RED and VIOLET				(14)

		{false, false, true, true, false, false}, // GREEN and BLUE				(15)
		{false, false, true, false, true, false}, // GREEN and ORANGE			(16)
		{false, false, true, false, false, true}, // GREEN and VIOLET			(17)

		{false, false, false, true, true, false}, // BLUE and ORANGE			(18)
		{false, false, false, true, false, true}, // BLUE and VIOLET			(19)

		{false, false, false, false, true, true}, // ORANGE and VIOLET			(20)

		{true, true, true, true, true, true}, // ALL							(21)

		{false, true, true, true, true, true}, // not NONE						(22)
		{true, false, true, true, true, true}, // not RED						(23)
		{true, true, false, true, true, true}, // not GREEN						(24)
		{true, true, true, false, true, true}, // not BLUE						(25)
		{true, true, true, true, false, true}, // not ORANGE					(26)
		{true, true, true, true, true, false}, // not VIOLET					(27)

		{false, false, true, true, true, true}, // not NONE and not RED			(28)
		{false, true, false, true, true, true}, // not NONE and not GREEN		(29)
		{false, true, true, false, true, true}, // not NONE and not BLUE		(30)
		{false, true, true, true, false, true}, // not NONE and not ORANGE		(31)
		{false, true, true, true, true, false}, // not NONE and not VIOLET		(32)

		{true, false, false, true, true, true}, // not RED and not GREEN		(33)
		{true, false, true, false, true, true}, // not RED and not BLUE			(34)
		{true, false, true, true, false, true}, // not RED and not ORANGE		(35)
		{true, false, true, true, true, false}, // not RED and not VIOLET		(36)

		{true, true, false, false, true, true}, // not GREEN and not BLUE		(37)
		{true, true, false, true, false, true}, // not GREEN and not ORANGE		(38)
		{true, true, false, true, true, false}, // not GREEN and not VIOLET		(39)

		{true, true, true, false, false, true}, // not BLUE and not ORANGE		(40)
		{true, true, true, false, true, false}, // not BLUE and not VIOLET		(41)

		{true, true, true, true, false, false}, // not ORANGE and not VIOLET	(42)
};

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

	const int clipSizes[NUM_TEXTURES] = {
			PLAYER_SPRITE_CLIP_SIZE,
			PLATFORM_SPRITE_CLIP_SIZE
	};

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
    // REMEMBER: ordering is little-endian
    // (buffer[0] is LSBs of data[0], buffer[1] is MSBs)
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

    else if (u >= PLAYER_NUM_FILTERS)
        u = PLAYER_NUM_FILTERS - 1;

	Player_Init(player, &spritesheets[0], px, py, PLAYER_WIDTH, PLAYER_HEIGHT, u);

	return true;
}

static int LoadPlatformData(struct Platform* platform, FILE* lvlFile)
{
    union {
        uint8_t buffer[14];
        uint16_t data[7];
    } platformData;

    size_t result = fread(platformData.buffer, sizeof(platformData.buffer), 1, lvlFile);
    if (result != 1)
    {
        if (platformData.buffer[0] == 0xff) {
            return 0;
        }
        fprintf(stderr, "Corrupt or incomplete platform data.\n");
        return -1;
    }

    // t = visibility index
    // s = sprite sheet index
    // x = x-coordinate
    // y = y-coordinate
    // w = width
    // h = height
    // f = facing
    int t = (int)platformData.data[0];
    int s = (int)platformData.data[1];
    int x = (int)platformData.data[2];
    int y = (int)platformData.data[3];
    int w = (int)platformData.data[4];
    int h = (int)platformData.data[5];
    int f = (int)platformData.data[6];

    if (t < 0 || t >= NUM_VISIBLE_OPTIONS)
    {
        fprintf(stderr, "Error: Invalid visibility index found.\n");
        return -1;
    }
    double angle = (double)(f * 90);
    Platform_Init(platform, &spritesheets[1], angle, s, x, y, w, h);

    for (int j = 0; j < NUM_PLATFORM_VISIBLE_OPTIONS; j ++)
        platform->visible[j] = optionsVisible[t][j];

    return 1;
}

#undef NUM_VISIBLE_OPTIONS
#undef NUM_TEXTURES