#include "PauseState.hpp"
#include "StateMachine.hpp"
#include "Settings.hpp"
#include "src/text_utilities.hpp"

PauseState::PauseState(StateMachine* sm) noexcept
    : BaseState{sm}
{
}

void PauseState::enter(std::shared_ptr<World> world, std::shared_ptr<Bird> bird, int score, bool _hard_mode, bool invulnerable, float time_left) noexcept
{
    paused_world = world;
    paused_bird = bird;
    paused_score = score;
    paused_hard_mode = _hard_mode;
    paused_invulnerable = invulnerable;
    paused_time_left = time_left;
}

void PauseState::exit() noexcept
{
    paused_world.reset();
    paused_bird.reset();
    paused_score = 0;
}

void PauseState::handle_inputs(const sf::Event& event) noexcept
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
    {
        state_machine->change_state("playing", paused_world, paused_bird, paused_score, paused_hard_mode, paused_invulnerable, paused_time_left);
    }
}

void PauseState::render(sf::RenderTarget& target) const noexcept
{
    paused_world->render(target);
    render_text(target, Settings::VIRTUAL_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 3, "PAUSED", Settings::HUGE_TEXT_SIZE, "flappy", sf::Color::White, true);
}