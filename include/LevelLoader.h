#ifndef GAME_LEVEL_LOADER_H__
#define GAME_LEVEL_LOADER_H__

#include <SDL2/SDL.h>

#include "Level.h"
#include "Player.h"

bool LevelLoader_LoadResources(struct Level* level, SDL_Renderer* renderer);
void LevelLoader_UnloadResources(struct Level* level);

bool LevelLoader_LoadLevelFile(struct Level* level, struct Player* player, const char* filename);

#endif /* GAME_LEVEL_LOADER_H__ */
