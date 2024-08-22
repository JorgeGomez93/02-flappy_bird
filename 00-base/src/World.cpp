/*
    ISPPJ1 2023
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class World.
*/

#include <Settings.hpp>
#include <src/World.hpp>

// Función para generar tiempos aleatorios en un rango dado
inline float random_time(float min, float max) {
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (max - min);
}

World::World(bool _generate_logs, bool _hard_mode) noexcept
    : generate_logs{_generate_logs}, hard_mode{_hard_mode}, background{Settings::textures["background"]}, ground{Settings::textures["ground"]},
      logs{}, rng{std::default_random_engine{}()}
{
    ground.setPosition(0, Settings::VIRTUAL_HEIGHT - Settings::GROUND_HEIGHT);
    std::uniform_int_distribution<int> dist(0, 80);
    last_log_y = -Settings::LOG_HEIGHT + dist(rng) + 20;
    
    std::srand(static_cast<unsigned>(std::time(nullptr)));  // Inicializar el generador de números aleatorios
    // Inicializar logs_spawn_timer con un tiempo aleatorio
    logs_spawn_timer = random_time(Settings::MIN_LOG_SPAWN_TIME, Settings::MAX_LOG_SPAWN_TIME);
}

void World::reset(bool _generate_logs, bool _hard_mode) noexcept
{
    generate_logs = _generate_logs;
    hard_mode = _hard_mode;
    log_pair_counter = 0;
    visible_log_pair_counter = 0;
}

bool World::collides(const sf::FloatRect& rect) const noexcept
{
    if (rect.top + rect.height >= Settings::VIRTUAL_HEIGHT)
    {
        return true;
    }
    
    for (auto log_pair: logs)
    {
        if (log_pair->collides(rect))
        {
            return true;
        }
    }

    return false;
}

bool World::update_scored(const sf::FloatRect& rect) noexcept
{
    for (auto log_pair: logs)
    {
        if (log_pair->update_scored(rect))
        {
            return true;
        }
    }

    return false;
}

void World::update(float dt) noexcept
{
    if (generate_logs)
    {
        if(!hard_mode){

            logs_spawn_timer += dt;

            if (logs_spawn_timer >= Settings::TIME_TO_SPAWN_LOGS)
            {
                logs_spawn_timer = 0.f;

                std::uniform_int_distribution<int> dist{-20, 20};
                float y = std::max(-Settings::LOG_HEIGHT + 10, std::min(last_log_y + dist(rng), Settings::VIRTUAL_HEIGHT + 90 - Settings::LOG_HEIGHT));

                last_log_y = y;

                logs.push_back(log_factory.create(Settings::VIRTUAL_WIDTH, y));
            }
        }else
        {
            logs_spawn_timer -= dt;

            if (logs_spawn_timer <= 0.f)
            {
                int new_x_position = Settings::VIRTUAL_WIDTH;
                std::uniform_int_distribution<int> dist{-50, 50};
                float y = std::max(-Settings::LOG_HEIGHT + 10, std::min(last_log_y + dist(rng), Settings::VIRTUAL_HEIGHT + 90 - Settings::LOG_HEIGHT));
                last_log_y = y;

                logs.push_back(log_factory.create(new_x_position, y));

                log_pair_counter++;

                visible_log_pair_counter++;
                
                logs_spawn_timer = random_time(Settings::MIN_LOG_SPAWN_TIME, Settings::MAX_LOG_SPAWN_TIME);
            }
        }
    }

    background_x += -Settings::BACK_SCROLL_SPEED * dt;

    if (background_x <= -Settings::BACKGROUND_LOOPING_POINT)
    {
        background_x = 0;
    }

    background.setPosition(background_x, 0);

    ground_x += -Settings::MAIN_SCROLL_SPEED * dt;

    if (ground_x <= -Settings::VIRTUAL_WIDTH)
    {
        ground_x = 0;
    }

    ground.setPosition(ground_x, Settings::VIRTUAL_HEIGHT - Settings::GROUND_HEIGHT);

    for (auto it = logs.begin(); it != logs.end(); )
    {
        if ((*it)->is_out_of_game())
        {
            auto log_pair = *it;
            log_factory.remove(log_pair);
            it = logs.erase(it);
            if(hard_mode)
            {
                visible_log_pair_counter--;//solo si esta en modo dificil
            }
        }
        else
        {
            (*it)->update(dt);
            ++it;
        }
    }
}

void World::render(sf::RenderTarget& target) const noexcept
{
    target.draw(background);

    for (const auto& log_pair: logs)
    {
        log_pair->render(target);
    }

    target.draw(ground);
}

int World::get_log_pair_counter() const noexcept
{
    return log_pair_counter;
}


int World::get_visible_log_pair_counter() const noexcept
{
    return visible_log_pair_counter;
}

std::shared_ptr<LogPair> World::get_log_pair(int index) const noexcept
{
    if (index < 0 || index >= logs.size())
    {
        return nullptr;
    }

    auto it = logs.begin();
    std::advance(it, index);
    return *it;
}