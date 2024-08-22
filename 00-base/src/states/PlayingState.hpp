/*
    ISPPJ1 2023
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the declaration of the class PlayingBaseState.
*/

#pragma once

#include <src/Bird.hpp>
#include <src/World.hpp>
#include <src/states/BaseState.hpp>

class PlayingState: public BaseState
{

public:
    PlayingState(StateMachine* sm) noexcept;

    void enter(std::shared_ptr<World> _world = nullptr, std::shared_ptr<Bird> _bird = nullptr, int _score = 0, bool _hard_mode = false) noexcept override;

    void handle_inputs(const sf::Event& event) noexcept override;

    void update(float dt) noexcept override;

    void render(sf::RenderTarget& target) const noexcept override;

    bool collides(const sf::FloatRect& rect) const noexcept;

    bool is_out_of_game(const sf::Sprite& sprite) noexcept;

private:
    std::shared_ptr<Bird> bird;
    std::shared_ptr<World> world;
    int score{0};
    bool is_hard_mode = false;
    
    bool worm_visible{false};
    sf::Sprite worm_sprite;
    sf::Text time_left_text;
    sf::FloatRect get_worm_collision_rect() const noexcept;
    bool is_invulnerable{false};
    float invulnerability_timer{0.f};
};
