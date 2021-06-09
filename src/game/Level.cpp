#include "game/Level.h"

using namespace game;

Level::Level()
{
    this->head = nullptr;
}

Level::~Level()
{
    struct PlatformNode* current = this->head;

    while (current != nullptr)
    {
        struct PlatformNode* next = current->next;

        free(current->platform);
        free(current);

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

void Level::CheckPhysics(Robot* player)
{
    for (struct PlatformNode* current = this->head; current != nullptr; current = current->next) {

        Platform* platform = current->platform;

        if (platform->IsOffscreen() || !platform->IsVisible(player->GetActiveFilter()))
            continue;

        if (player->GetBoundingBox()->Intersects(platform->GetBoundingBox()))
            player->Collide(platform);
    }
}

void Level::Render(uint8_t activeFilter)
{
    for (struct PlatformNode* current = this->head; current != nullptr; current = current->next)
    {
        Platform* platform = current->platform;

        if (platform->IsOffscreen() || !platform->IsVisible(activeFilter))
            continue;

        platform->Render();
    }
}