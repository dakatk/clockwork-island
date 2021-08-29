#include "engine/Window.h"
#include "engine/Input.h"
#include "engine/Timer.h"
#include "game/Robot.h"
#include "game/Level.h"
#include "game/Assets.h"
#include <iostream>

#define CAPPED_FPS 60
#define CAPPED_TICKS_PER_FRAME (1000 / CAPPED_FPS)

#define BUFFER_WIDTH 800
#define BUFFER_HEIGHT 600

#define GRAVITY 0.25f
#define FRICTION 0.88f

#define PLAYER_MOVE_SPEED 3.5f
#define PLAYER_JUMP_SPEED 8.3f

#define PLAYER_MAX_MOVE_SPEED 4.1f
#define PLAYER_MAX_JUMP_SPEED 8.5f
#define PLAYER_MIN_MOVE_SPEED 0.2f

using namespace engine;
using namespace std;
using namespace game;

void Loop(Robot& player, Level& level);
void Update(Robot& player, Level& level);
void Render(Robot& player, Level& level);
void Cleanup();

int main(__attribute__((unused)) int argc, char* argv[])
{
    cout << "Running from executable '" << argv[0] << "'" << endl;
    Window::Create("Clockwork Island (Alpha v0.0.1)", BUFFER_WIDTH, BUFFER_HEIGHT);

    try
    {
        Texture* playerSpritesheet = Assets::LoadPlayerSpritesheet();
        Texture* levelTilesheet = Assets::LoadLevelTileSheet(0);

        Robot player = Robot(playerSpritesheet);
        Level level = Assets::LoadLevel(player, levelTilesheet, 0);

        Loop(player, level);

        delete playerSpritesheet;
        delete levelTilesheet;

        Cleanup();
    }
    catch(std::exception& e)
    {
        cerr << e.what() << endl;
        Cleanup();

        return 1;
    }
    return 0;
}

void Loop(Robot& player, Level& level)
{
    Timer capTimer;

    do {
        capTimer.Start();

        Input::Capture();
        if (Input::KeyPressed(KEY_QUIT))
            break;

        Update(player, level);
        Render(player, level);

        uint32_t frameTicks = capTimer.Ticks();
        if (frameTicks < CAPPED_TICKS_PER_FRAME)
            SDL_Delay(CAPPED_TICKS_PER_FRAME - frameTicks);

    } while (true);
}

static inline void UpdatePlayerFilter(Robot& player)
{
    int activeFilter = -1;

    if (Input::KeyTyped(KEY_Q | KEY_P)) {
        activeFilter = 1;
    }
    else if (Input::KeyTyped(KEY_W | KEY_L_BRACKET)) {
        activeFilter = 0;
    }
    else if (Input::KeyTyped(KEY_E | KEY_R_BRACKET)) {
        activeFilter = 2;
    }

    if (activeFilter >= 0 && activeFilter <= player.GetAllowedFilters()) {
        player.SetActiveFilter(activeFilter);
    }
}

void Update(Robot& player, Level& level)
{
    if (Input::KeyTyped(KEY_F1))
        Window::ToggleFullscreen();

    UpdatePlayerFilter(player);

    if (Input::KeyPressed(KEY_LEFT | KEY_A))
        player.ChangeVX(-PLAYER_MOVE_SPEED);

    else if (Input::KeyPressed(KEY_RIGHT | KEY_D))
        player.ChangeVX(PLAYER_MOVE_SPEED);

    if (Input::KeyPressed(KEY_Z | KEY_SPACE) && !player.IsJumping())
    {
        player.SetJumping(true);
        player.ChangeVY(PLAYER_JUMP_SPEED);
    }
    player.Move(GRAVITY, FRICTION, PLAYER_MAX_JUMP_SPEED, PLAYER_MAX_MOVE_SPEED, PLAYER_MIN_MOVE_SPEED);

    level.CheckPhysics(player);
    level.ScrollBackground(player);

    player.UpdateDirection();
    player.Animate();
}

void Render(Robot& player, Level& level)
{
    level.Render(player.GetActiveFilter());
    player.Render();

    Window::PresentBuffer();
}

void Cleanup()
{
    Window::Destroy();
}
