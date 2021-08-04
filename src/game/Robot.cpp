#include "engine/Window.h"
#include "game/Robot.h"
#include "game/Filter.h"

#define PLAYER_WIDTH 100
#define PLAYER_HEIGHT 100

#define PLAYER_BB_WIDTH 70
#define PLAYER_BB_HEIGHT 94

using namespace engine;
using namespace game;

static const struct Filter* FILTERS[NUM_FILTERS] = {
        nullptr, &filters::RED, &filters::GREEN, &filters::BLUE, &filters::ORANGE, &filters::VIOLET
};

Robot::Robot(Texture *spritesheet) : Player(spritesheet, 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT)
{
    if (allowedFilters >= NUM_FILTERS)
        allowedFilters = NUM_FILTERS - 1;

    this->direction = &directions::STAND_RIGHT;

    this->allowedFilters = 0;
    this->activeFilter = 0;
    this->ticks = 0;

    this->SetBoundingBox(PLAYER_BB_WIDTH, PLAYER_BB_HEIGHT);
}

uint8_t Robot::GetAllowedFilters() const
{
    return this->allowedFilters;
}

void Robot::SetAllowedFilters(uint8_t allowedFilters_)
{
    this->allowedFilters = allowedFilters_;
}

uint8_t Robot::GetActiveFilter() const
{
    return this->activeFilter;
}

void Robot::SetActiveFilter(uint8_t activeFilter_)
{
    this->activeFilter = activeFilter_;
}

void Robot::IncFilter()
{
    this->activeFilter ++;

    if (this->activeFilter > this->allowedFilters)
        this->activeFilter = 0;
}

void Robot::DecFilter()
{
    if (this->activeFilter == 0)
        this->activeFilter = this->allowedFilters;
    else
        this->activeFilter --;
}

void Robot::UpdateDirection()
{
    // Right
    if (this->GetVX() > 0.0f)
    {
        if (this->GetVY() != 0.0f)
            this->direction = &directions::JUMP_RIGHT;
        else
            this->direction = &directions::WALK_RIGHT;
    }
    // Left
    else if (this->GetVX() < 0.0f)
    {
        if (this->GetVY() != 0.0f)
            this->direction = &directions::JUMP_LEFT;
        else
            this->direction = &directions::WALK_LEFT;
    }
    // Neither
    else
    {
        // Jumping/Falling
        if (this->GetVY() != 0.0f)
        {
            bool prevLeft = this->direction == &directions::WALK_LEFT || this->direction == &directions::STAND_LEFT;
            bool prevRight = this->direction == &directions::WALK_RIGHT || this->direction == &directions::STAND_RIGHT;

            if (prevLeft)
                this->direction = &directions::JUMP_LEFT;

            else if (prevRight)
                this->direction = &directions::JUMP_RIGHT;
        }
        // Standing
        else
        {
            bool prevLeft = this->direction == &directions::WALK_LEFT || this->direction == &directions::JUMP_LEFT;
            bool prevRight = this->direction == &directions::WALK_RIGHT || this->direction == &directions::JUMP_RIGHT;

            if (prevLeft)
                this->direction = &directions::STAND_LEFT;

            else if (prevRight)
                this->direction = &directions::STAND_RIGHT;
        }
    }
}

void Robot::Animate()
{
    this->spriteClipY = this->direction->value;

    if (this->ticks >= this->direction->sleep)
    {
        this->spriteClipX ++;
        if (this->spriteClipX >= this->direction->frames)
            this->spriteClipX = 0;

        this->ticks = 0;
    }
    else this->ticks ++;
}
void Robot::Render()
{
    const struct Filter* drawFilter = FILTERS[this->activeFilter];

    if (drawFilter != nullptr)
        Window::RenderFullScreenRect(drawFilter->r, drawFilter->g, drawFilter->b, FILTER_ALPHA);

    Player::Render();
}

