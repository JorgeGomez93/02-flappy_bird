#pragma once

#include <src/World.hpp>
#include <src/Bird.hpp>
#include <src/states/BaseState.hpp>

class PauseState : public BaseState
{
public:
    PauseState(StateMachine* sm) noexcept;

    void enter(std::shared_ptr<World> world, std::shared_ptr<Bird> bird, int score) noexcept override;
    void exit() noexcept override;
    void handle_inputs(const sf::Event& event) noexcept override;
    void render(sf::RenderTarget& target) const noexcept override;

private:
    std::shared_ptr<World> paused_world;
    std::shared_ptr<Bird> paused_bird;
    int paused_score;
};