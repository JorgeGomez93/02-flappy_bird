/*
    ISPPJ1 2023
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class PlayingBaseState.
*/

#include <Settings.hpp>
#include <src/text_utilities.hpp>
#include <src/states/StateMachine.hpp>
#include <src/states/PlayingState.hpp>

PlayingState::PlayingState(StateMachine* sm) noexcept
    : BaseState{sm}, worm_sprite{} 
{
    worm_sprite.setTexture(Settings::textures["worm"]);
}

void PlayingState::enter(std::shared_ptr<World> _world, std::shared_ptr<Bird> _bird, int _score, bool _hard_mode, bool invulnerable, float time_left) noexcept
{
    is_hard_mode = _hard_mode;
    is_invulnerable = invulnerable;
    invulnerability_timer = time_left;

    score = _score;
    world = _world;
    world->reset(true, is_hard_mode);
    
    if (_bird == nullptr)
    {
        bird = std::make_shared<Bird>(
            Settings::VIRTUAL_WIDTH / 2 - Settings::BIRD_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 2 - Settings::BIRD_HEIGHT / 2,
            Settings::BIRD_WIDTH, Settings::BIRD_HEIGHT
        );
    }
    else
    {
        bird = _bird;
    }

    worm_visible = false;
}

bool PlayingState::is_out_of_game(const sf::Sprite& sprite) noexcept
{
    return sprite.getPosition().x + sprite.getGlobalBounds().width < 0;
}

sf::FloatRect PlayingState::get_worm_collision_rect() const noexcept
{
    return worm_sprite.getGlobalBounds();
}

bool PlayingState::collides(const sf::FloatRect& rect) const noexcept
{
    return worm_visible && get_worm_collision_rect().intersects(rect);
}

void PlayingState::handle_inputs(const sf::Event& event) noexcept
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        bird->jump();
    }
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::P)
        {
            state_machine->change_state("pause", world, bird, score, is_hard_mode, is_invulnerable, invulnerability_timer);
        }

        if (is_hard_mode)  // Solo permitir movimiento lateral en modo difícil
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::A)
                {
                    bird->move_left(); // Movimiento hacia la izquierda al presionar "A"
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    bird->move_right(); // Movimiento hacia la derecha al presionar "D"
                }
            }
        }
    }
}

void PlayingState::update(float dt) noexcept
{
    bird->update(dt);
    world->update(dt);

    if (collides(bird->get_collision_rect()))
    {
        Settings::sounds["explosion"].play();
        worm_visible = false;
        //cambiar la textura del pajaro a la del fantasma
        bird->set_texture(Settings::textures["ghost"]);
        //Activar estado de invulnerabilidad y temporizador
        is_invulnerable = true;
        invulnerability_timer = 5.0f; //5 segundos de invulnerabilidad
    }
    //verificar el estado de invulnerabilidad
    if(is_invulnerable)
    {
        invulnerability_timer -=dt;
        Settings::music.setPitch(1.5f);
        if(invulnerability_timer <= 0)
        {
            is_invulnerable = false;
            invulnerability_timer = 0.0f;
            bird->set_texture(Settings::textures["bird"]);
            Settings::music.setPitch(1.0f);
        }
    }else if(!is_invulnerable && world->collides(bird->get_collision_rect()))
    {
        Settings::sounds["explosion"].play();
        Settings::sounds["hurt"].play();
        state_machine->change_state("count_down",nullptr,nullptr,0,is_hard_mode);
    }

    if (world->update_scored(bird->get_collision_rect()))
    {
        ++score;
        Settings::sounds["score"].play();
    }

    if (world->get_log_pair_counter() % 6 == 0 && world->get_log_pair_counter() != 0 && !worm_visible)
    {
        int visible_counter = world->get_visible_log_pair_counter();

        auto log_pair = world->get_log_pair(visible_counter-1);
        if (log_pair != nullptr)
        {
            float worm_x = log_pair->get_x() + (Settings::LOG_WIDTH / 2) - (Settings::WORM_WIDTH / 2);
            
            float top_log_y = log_pair->get_y() + Settings::LOG_HEIGHT;
            float bottom_log_y = top_log_y + Settings::LOGS_GAP;

            float worm_y = (Settings::VIRTUAL_HEIGHT - (top_log_y + bottom_log_y)) / 2 + top_log_y;

            worm_sprite.setPosition(worm_x, worm_y);
            worm_visible = true;
        }
    }
    // Actualizar la posición del worm
    if (is_hard_mode && worm_visible)
    {
        worm_sprite.move(-Settings::MAIN_SCROLL_SPEED * dt, 0);
        if (is_out_of_game(worm_sprite))
        {
            worm_visible = false;
        }
    }
}

void PlayingState::render(sf::RenderTarget& target) const noexcept
{
    world->render(target);
    bird->render(target);

    if(is_hard_mode && worm_visible)
    {
        target.draw(worm_sprite);  // Renderizar el sprite del worm
    }
    render_text(target, 20, 10, "Score: " + std::to_string(score), Settings::FLAPPY_TEXT_SIZE, "flappy", sf::Color::White);

    // Mostrar el tiempo restante de invulnerabilidad solo si está activo
    if (is_invulnerable)
    {
        sf::Vector2u window_size = target.getSize();
        std::string time_left_str = "Time left: " + std::to_string(static_cast<int>(invulnerability_timer + 0.9));
        render_text(target, window_size.x - 200, 10, time_left_str, Settings::FLAPPY_TEXT_SIZE, "flappy", sf::Color::White);
    }
}