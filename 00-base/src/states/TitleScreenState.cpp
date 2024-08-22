/*
    ISPPJ1 2023
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the declaration of the class TitleScreenState.
*/

#include <Settings.hpp>
#include <src/text_utilities.hpp>
#include <src/states/StateMachine.hpp>
#include <src/states/TitleScreenState.hpp>

TitleScreenState::TitleScreenState(StateMachine* sm) noexcept
    : BaseState{sm}, world{}
{

}

void TitleScreenState::handle_inputs(const sf::Event& event) noexcept
{
    if (event.type == sf::Event::KeyPressed) {

        if (event.key.code == sf::Keyboard::Num1) {

            state_machine->change_state("count_down", nullptr,nullptr,0,false,false,0);

        } else if (event.key.code == sf::Keyboard::Num2) {

            state_machine->change_state("count_down",nullptr,nullptr,0,true,false,0);
        }
    }
}

void TitleScreenState::update(float dt) noexcept
{
    world.update(dt);
}

void TitleScreenState::render(sf::RenderTarget& target) const noexcept 
{
    world.render(target);
    render_text(target, Settings::VIRTUAL_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 3, "Flappy Bird", Settings::FLAPPY_TEXT_SIZE, "flappy", sf::Color::White, true);
	render_text(target, Settings::VIRTUAL_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 3 + Settings::MEDIUM_TEXT_SIZE + 30, "Select Mode", Settings::MEDIUM_TEXT_SIZE, "flappy", sf::Color::White, true);
    render_text(target, Settings::VIRTUAL_WIDTH / 2, 2 * Settings::VIRTUAL_HEIGHT / 3, "1 - EASY", Settings::MEDIUM_TEXT_SIZE, "font", sf::Color::White, true);
    render_text(target, Settings::VIRTUAL_WIDTH / 2, 2 * Settings::VIRTUAL_HEIGHT / 3 + Settings::MEDIUM_TEXT_SIZE + 10, "2 - HARD", Settings::MEDIUM_TEXT_SIZE, "font", sf::Color::White, true);
}