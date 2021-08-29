#ifndef CLOCKWORKISLAND_ASSETS_H__
#define CLOCKWORKISLAND_ASSETS_H__

#include <engine/Background.h>

#include <utility>
#include "Level.h"

using namespace engine;
using namespace std;

namespace game
{
    class Assets
    {
    private:
        static Background* LoadBackground(uint8_t levelNum);

        static void LoadPlayerData(Robot& player, ifstream* file);
        static Platform* LoadPlatformData(Texture* tileSheet, ifstream* file);

    public:
        static Texture* LoadPlayerSpritesheet();
        static Texture* LoadLevelTileSheet(uint8_t levelNum);
        static Level LoadLevel(Robot& player, Texture* tileSheet, uint8_t levelNum);
    };

    class AssetException : public exception
    {
    private:
        string message;
    public:
        explicit AssetException(string message_) : message(move(message_)) {}
        const char* what() const noexcept override { return message.c_str(); }
    };
}

#endif /* CLOCKWORKISLAND_ASSETS_H__ */
