#ifndef CLOCKWORKISLAND_ASSET_LOADER_H__
#define CLOCKWORKISLAND_ASSET_LOADER_H__

#include "engine/Level.h"
#include "engine/Player.h"

#include <SDL.h>

bool AssetLoader_LoadResources(SDL_Renderer* renderer);
void AssetLoader_UnloadResources();

bool AssetLoader_LoadLevelFile(struct Level* level, struct Player* player, const char* filename);

#endif /* CLOCKWORKISLAND_ASSET_LOADER_H__ */
