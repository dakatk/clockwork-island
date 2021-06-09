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

#define GRAVITY 0.2f
#define FRICTION 0.88f

#define PLAYER_MOVE_SPEED 3.5f
#define PLAYER_JUMP_SPEED 8.5f

#define PLAYER_MAX_MOVE_SPEED 4.1f
#define PLAYER_MAX_JUMP_SPEED 8.5f
#define PLAYER_MIN_MOVE_SPEED 0.2f

using namespace engine;
using namespace std;
using namespace game;

Robot* player;
Level* level;

void Loop();
void Update();
void Render();
void Cleanup();

int main(__attribute__((unused)) int argc, char* argv[])
{
    cout << "Running from executable '" << argv[0] << "'" << endl;

    Window::Create("Clockwork Island (Alpha v0.0.1)", BUFFER_WIDTH, BUFFER_HEIGHT);

    try
    {
        Assets::Load();
        level = Assets::LoadLevel(&player, 0);
    }
    catch(std::exception& e)
    {
        cerr << e.what() << endl;
        Cleanup();

        return 1;
    }
    Loop();
    Cleanup();

    return 0;
}

void Loop()
{
    Timer capTimer;

    do {
        capTimer.Start();

        Input::Capture();
        if (Input::KeyPressed(KEY_QUIT))
            break;

        Update();
        Render();

        uint32_t frameTicks = capTimer.Ticks();
        if (frameTicks < CAPPED_TICKS_PER_FRAME)
            SDL_Delay(CAPPED_TICKS_PER_FRAME - frameTicks);

    } while (true);
}

static inline void UpdatePlayerFilter()
{
    if (Input::KeyTyped(KEY_A))
        player->DecFilter();

    else if (Input::KeyTyped(KEY_S))
        player->IncFilter();

    else if (Input::KeyTyped(KEY_0 | KEY_1 | KEY_2 | KEY_3 | KEY_4 | KEY_5))
    {
        uint16_t buffer = Input::KeysBuffer();
        for (int i = player->GetAllowedFilters(); i >= 0; i --)
        {
            if (buffer & (1 << i))
            {
                player->SetFilter(i);
                break;
            }
        }
    }
}

void Update()
{
    if (Input::KeyTyped(KEY_F1))
        Window::ToggleFullscreen();

    UpdatePlayerFilter();

    if (Input::KeyPressed(KEY_LEFT))
        player->ChangeVX(-PLAYER_MOVE_SPEED);

    else if (Input::KeyPressed(KEY_RIGHT))
        player->ChangeVX(PLAYER_MOVE_SPEED);

    if (Input::KeyPressed(KEY_Z) && !player->IsJumping())
    {
        player->SetJumping();
        player->ChangeVY(PLAYER_JUMP_SPEED);
    }

    player->Move(GRAVITY, FRICTION, PLAYER_MAX_JUMP_SPEED, PLAYER_MAX_MOVE_SPEED, PLAYER_MIN_MOVE_SPEED);

    level->CheckPhysics(player);
    level->ScrollBackground(player);

    player->UpdateDirection();
    player->Animate();
}

void Render()
{
    level->Render(player->GetActiveFilter());
    player->Render();

    Window::PresentBuffer();
}

void Cleanup()
{
    delete player;
    delete level;

    Assets::Unload();
    Window::Destroy();
}
