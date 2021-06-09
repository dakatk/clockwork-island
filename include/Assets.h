#ifndef CLOCKWORKISLAND_ASSETS_H__
#define CLOCKWORKISLAND_ASSETS_H__

#include <engine/Background.h>

#include <utility>
#include "Level.h"

using namespace engine;

class Assets {
private:
    static Background* background;

    static void LoadPlayerData(Robot** player, std::ifstream* file);
    static Platform* LoadPlatformData(std::ifstream* file);

public:
    static bool Load();
    static void Unload();

    static Background* GetBackground();

    static Level* LoadLevel(Robot** player, unsigned int levelNum);
};

class DataParsingException : public std::exception {
private:
    std::string message;
public:
    explicit DataParsingException(std::string message_) : message(std::move(message_)) {}
    const char* what() const noexcept override { return message.c_str(); }
};

#endif /* CLOCKWORKISLAND_ASSETS_H__ */
