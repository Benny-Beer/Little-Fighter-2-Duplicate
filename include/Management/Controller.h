#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iostream>
#include "Gameplay/Level.h"
#include "Gameplay/Player.h"
#include "Gameplay/Ally.h"
#include "UI/HeadsUpDisplay.h"


class Controller
{
public:
    // Constructor: receives all game data needed to run the battle
    Controller(sf::RenderWindow& window,
        std::unique_ptr<Level> level,
        std::vector<std::shared_ptr<Player>> players,     // human-controlled
        std::vector<std::shared_ptr<Ally>> allies);       // AI-controlled allies

    // Called each frame from InGameState
    void updateAndRender(float deltaTime);

    // ========== Core logic ==========
    void handleInput(sf::Event ev);                  // Input for human-controlled players
    void updateWorld(float deltaTime);   // Updates players, allies, level, etc.
    void checkLevelEndConditions();      // Determines whether the match is over
    void render();

    // Returns whether the level has ended, and who won
    bool isLevelFinished() const;
    bool didWin() const;

private:
    sf::RenderWindow& m_window;
    std::unique_ptr<Level> m_level;
    std::vector<std::shared_ptr<Player>> m_players; // human-controlled
    std::vector<std::shared_ptr<Ally>> m_allies;  // computer-controlled
    std::vector<std::shared_ptr<Enemy>> m_enemies; // Non-owning pointers to current squad
    std::vector<std::shared_ptr<PickableObject>> m_pickables;
    std::vector<std::shared_ptr<PlayableObject>> m_deads;


    // ========== Internal state ==========
    HeadsUpDisplay m_stats;
    bool m_levelFinished = false;
    bool m_playerWon = false;
    void printHp(int hp, const sf::Vector2f& position, bool potential);
    //void handleDeath(std::shared_ptr<ComputerPlayer> deadOne, std::vector<std::shared_ptr<ComputerPlayer>> livePlayers);
    float distanceBetween(sf::Vector2f a, sf::Vector2f b);
    bool enemyExist() { return m_enemies.size(); }
    bool alliesExist() { return m_allies.size() + m_players.size(); }

    void updateComputerPlayerStats();
    void restoreKnockedAccess();
    //void updateSafeZone(std::shared_ptr<ComputerPlayer> self, std::vector<std::shared_ptr<ComputerPlayer>>& enemies);
    //void updateComputerPlayerTargetsTwo();

    template<typename Container>
    void checkClosest(const Container& container, const sf::Vector2f& enemyPos,
        float& closestDistance, std::shared_ptr<Object>& closest) {
        for (auto& obj : container) {
            if (auto pickable = std::dynamic_pointer_cast<PickableObject>(obj)) {
                if (!pickable->onEarth())
                    continue;
            }
            float dist = distanceBetween(enemyPos, obj->getPosition());
            if (dist < closestDistance) {
                closestDistance = dist;
                closest = obj;
            }
        }
    }

    // T1 - player's team
    // T2 - opponent team
    // T3 - another opponent team (optional)
    template<typename T1, typename T2, typename T3 = Object>
    void updateStats(std::vector<std::shared_ptr<T1>>& vec1, std::vector<std::shared_ptr<T2>>& vec2, std::vector<std::shared_ptr<T3>> vec3 = {}) {
        for (int i = 0; i < vec1.size(); i++) {
            std::shared_ptr<T1> player = vec1[i];
            if (!player)
                continue;

            std::shared_ptr<Object> closest = nullptr;
            float closestDistance = std::numeric_limits<float>::max();

            if (player->needItem()) {
                checkClosest(m_pickables, player->getPosition(), closestDistance, closest);
            }

            if (vec2.size() + vec3.size()) // there is at least 1 opponent
            {
                checkClosest(vec2, player->getPosition(), closestDistance, closest);
                if (!vec3.empty())
                    checkClosest(vec3, player->getPosition(), closestDistance, closest);

                player->setTarget(closest);

            }
            else {
                player->setTarget(nullptr);
            }

            if (!player->getState()->isAccessible()/*player->getHp() <= 0*/) {
                removeAccess(player, vec1);
            }
            else {
                updateSafeZone(player, vec2);
            }
        }
    }


    template<typename T>
    void updateSafeZone(std::shared_ptr<ComputerPlayer> self, std::vector<std::shared_ptr<T>>& enemies) {
        static_assert(std::is_base_of<ComputerPlayer, T>::value, "T must derive from ComputerPlayer");

        const float gridSize = 50.f;
        const sf::FloatRect searchBounds(50.f, 450.f, 900.f, 300.f);

        float bestScore = std::numeric_limits<float>::max();
        sf::Vector2f bestPoint;

        for (float x = searchBounds.left; x < searchBounds.left + searchBounds.width; x += gridSize) {
            for (float y = searchBounds.top; y < searchBounds.top+searchBounds.height; y += gridSize) {
                sf::Vector2f point(x, y);
                float dangerScore = 0.f;

                for (const auto& enemy : enemies) {
                    if (!enemy) continue;

                    float dist = distanceBetween(point, enemy->getPosition());
                    if (dist > 1.f)
                        dangerScore += 1.f / dist;
                    else
                        dangerScore += 1000.f; // very close - very dangerous
                }

                if (dangerScore < bestScore) {
                    bestScore = dangerScore;
                    bestPoint = point;
                }
            }
        }

        self->setSafeZone(bestPoint); 
    }

    template<typename T>
    void removeAccess(std::shared_ptr<T> deadOne, std::vector<std::shared_ptr<T>>& livePlayers) {

        auto it = std::find(livePlayers.begin(), livePlayers.end(), deadOne);
        if (it != livePlayers.end()) {
            m_deads.push_back(*it);
            std::cout << m_deads[0]->getName() << std::endl;

            livePlayers.erase(it);

            
        }

    }
};
