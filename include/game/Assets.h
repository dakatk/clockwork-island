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
        static Background* background;

        static void LoadPlayerData(Robot** player, ifstream* file);
        static Platform* LoadPlatformData(ifstream* file);

    public:
        static void Load();
        static void Unload();

        static Background* GetBackground();
        static Level* LoadLevel(Robot** player, unsigned int levelNum);
    };

    class DataParsingException : public exception
    {
    private:
        string message;
    public:
        explicit DataParsingException(string message_) : message(move(message_)) {}
        const char* what() const noexcept override { return message.c_str(); }
    };
}

#endif /* CLOCKWORKISLAND_ASSETS_H__ */
