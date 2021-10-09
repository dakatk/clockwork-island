#include "game/Level.h"
#include "engine/Viewport.h"

using namespace game;
using namespace platforms;
using namespace util;

Level::Level(Background* background)
{
    this->background = background;
}

Level::~Level()
{
    delete this->background;
}

void Level::AddPlatform(Platform* platform)
{
    this->platforms.Push(platform);
}

void Level::AddHazard(Hazard* hazard)
{
    this->hazards.Push(hazard);
}

void Level::CheckPhysics(Robot& player)
{
    this->hazards.Reset();
    while (!this->hazards.Done())
    {
        Hazard* hazard = this->hazards.Next();

        if (!hazard->IsApplicable(player.GetActiveFilter()))
            continue;

        hazard->Effect(&player);
    }

    this->platforms.Reset();
    while (!this->platforms.Done())
    {
        Platform* platform = this->platforms.Next();

        if (platform->IsOffscreen() || !platform->IsVisible(player.GetActiveFilter()))
            continue;

        if (player.GetBoundingBox()->Intersects(platform->GetBoundingBox()))
            player.Collide(platform);

        platform->Animate();
    }
}

void Level::ScrollBackground(Robot& player)
{
    float playerCenterX = player.GetBoundingBox()->GetCenterX();
    float playerCenterY = player.GetBoundingBox()->GetCenterY();

    Viewport::SnapTo(playerCenterX, playerCenterY);
    Viewport::Constrain();

    this->background->Scroll();
}

void Level::Render(uint8_t activeFilter)
{
    this->background->Render();

    this->platforms.Reset();
    while (!this->platforms.Done())
    {
        Platform* platform = this->platforms.Next();
        if (platform->IsOffscreen() || !platform->IsVisible(activeFilter))
            continue;

        platform->Render();
    }
}
