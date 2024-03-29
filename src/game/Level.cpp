#include "game/Level.h"
#include "engine/Viewport.h"

using namespace game;
using namespace platforms;

Level::Level(Background* background)
{
    this->background = background;
    this->head = nullptr;
}

Level::~Level()
{
    delete this->background;

    struct PlatformNode* current = this->head;
    while (current != nullptr)
    {
        struct PlatformNode* next = current->next;

        delete current->platform;
        delete current;

        current = next;
    }
}

void Level::AddPlatform(Platform* platform)
{
    auto* node = new PlatformNode();

    node->platform = platform;
    node->next = this->head;

    this->head = node;
}

void Level::CheckPhysics(Robot& player)
{
    for (struct PlatformNode* current = this->head; current != nullptr; current = current->next) {

        Platform* platform = current->platform;

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

    for (struct PlatformNode* current = this->head; current != nullptr; current = current->next)
    {
        Platform* platform = current->platform;
        if (platform->IsOffscreen() || !platform->IsVisible(activeFilter))
            continue;

        platform->Render();
    }
}
