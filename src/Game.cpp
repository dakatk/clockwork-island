#include "engine/Window.h"
#include "engine/Input.h"
#include "engine/Viewport.h"
#include "Robot.h"
#include "Level.h"
#include "Assets.h"
#include <iostream>

#define BUFFER_WIDTH 800
#define BUFFER_HEIGHT 600

#define GRAVITY 0.2f
#define FRICTION 0.85f

#define PLAYER_MOVE_SPEED 3.5f
#define PLAYER_JUMP_SPEED 8.5f

#define PLAYER_MAX_MOVE_SPEED 4.1f
#define PLAYER_MAX_JUMP_SPEED 8.4f
#define PLAYER_MIN_MOVE_SPEED 0.45f

using namespace std;
using namespace engine;

Robot* player;
Level* level;

void Update();
void Render();
void Cleanup();

int main(__attribute__((unused)) int argc, char* argv[])
{
    cout << "Running from executable '" << argv[0] << "'" << endl;

    Window::Create("Clockwork Island (Alpha v0.0.1)", BUFFER_WIDTH, BUFFER_HEIGHT);

    if (!Assets::Load())
    {
        cerr << "Failed to load game assets" << endl;
        Cleanup();

        return 1;
    }

    level = Assets::LoadLevel(&player, 0);
    if (level == nullptr)
    {
        cerr << "Failed to load level data" << endl;
        Cleanup();

        return 1;
    }

    do {
        Input::Capture();

        if (Input::KeyPressed(KEY_QUIT))
            break;

        Update();
        Render();

    } while (true);

    Cleanup();

    return 0;
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

    float playerCenterX = player->GetBoundingBox()->GetCenterX();
    float playerCenterY = player->GetBoundingBox()->GetCenterY();

    Viewport::SnapTo(playerCenterX, playerCenterY);
    Viewport::Constrain();

    Assets::GetBackground()->Scroll();

    player->UpdateDirection();
    player->Animate();
}

void Render()
{
    Assets::GetBackground()->Render();
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
