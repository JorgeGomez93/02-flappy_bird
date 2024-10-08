/*
    ISPPJ1 2023
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the declaration of the class World.
*/

#pragma once

#include <list>
#include <memory>
#include <random>

#include <SFML/Graphics.hpp>

#include <src/Factory.hpp>
#include <src/LogPair.hpp>

class World
{
public:
    World(bool _generate_logs = false, bool _hard_mode = false) noexcept;

    World(const World& world) = delete;

    World& operator = (World) = delete;

    void reset(bool _generate_logs, bool _hard_mode) noexcept;

    bool collides(const sf::FloatRect& rect) const noexcept;

    bool update_scored(const sf::FloatRect& rect) noexcept;

    void update(float dt) noexcept;

    void render(sf::RenderTarget& target) const noexcept;
    
    // Método para obtener el contador de pares de troncos
    int get_log_pair_counter() const noexcept;

    // Nuevo método para obtener el contador de pares de troncos visibles
    int get_visible_log_pair_counter() const noexcept;

    // Método para obtener un par de troncos específico por índice
    std::shared_ptr<LogPair> get_log_pair(int index) const noexcept;
    
private:
    bool generate_logs;
    bool hard_mode;

    sf::Sprite background;
    sf::Sprite ground;

    float background_x{0.f};
    float ground_x{0.f};

    Factory<LogPair> log_factory;

    std::list<std::shared_ptr<LogPair>> logs;

    std::mt19937 rng;

    float logs_spawn_timer{0.f};
    float last_log_y{0.f};

    int log_pair_counter{0};
    int visible_log_pair_counter{0};
};
