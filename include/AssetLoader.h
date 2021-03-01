#ifndef CLOCKWORKISLAND_ASSET_LOADER_H__
#define CLOCKWORKISLAND_ASSET_LOADER_H__

#include <SDL2/SDL.h>

#include "engine/Level.h"
#include "engine/Player.h"

bool AssetLoader_LoadResources(struct Level* level, SDL_Renderer* renderer);
void AssetLoader_UnloadResources(struct Level* level);

bool AssetLoader_LoadLevelFile(struct Level* level, struct Player* player, const char* filename);

#endif /* CLOCKWORKISLAND_ASSET_LOADER_H__ */
