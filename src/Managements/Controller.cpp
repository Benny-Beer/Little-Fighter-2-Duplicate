#include "Management/Controller.h"
#include "Gameplay/Level.h"
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <utility>
#include <iostream>

Controller::Controller(sf::RenderWindow& window,
    std::unique_ptr<Level> level,
    std::vector<std::shared_ptr<Player>> players,
    std::vector<std::shared_ptr<Ally>> allies)
    : m_window(window),
    m_level(std::move(level)),
    m_players(std::move(players)),
    m_allies(std::move(allies))
{   
    AnimationManager::loadAnimations();
    //=============================================================
    // === this section is hard coded. need to be done in Level ===
    // add pickable (rock)
    std::string objectLine = "";
    m_level->addPickableObjects(objectLine);
    // add enemies (one bandit)
    std::string sq = "b1";
    m_level->addSquad(sq);
    // ============================================================

    //========================================================================
    // === this section is hard coded. need to be done in InGameScreem (?) === 
    // (The vectors will NOT be empty at first place) ========================
    // creating user's player
    m_players.push_back(std::make_shared<Player>(sf::Vector2f(1000, 800), "davis_ani", 320.f));
    // creating ally
    auto ally = std::make_shared<Ally>(sf::Vector2f(800, 40), "davis_ani",60.f);
    auto allyTwo = std::make_shared<Ally>(sf::Vector2f(900, 700), "davis_ani", 60.f);
    //auto allyThree = std::make_shared<Ally>(sf::Vector2f(380, 580), "davis_ani", 60.f);

    m_allies.push_back(ally);
    m_allies.push_back(allyTwo);
    //m_allies.push_back(allyThree);
    //========================================================================

    m_enemies = m_level->getAllEnemies();
    m_pickables = m_level->getAllObjects();
    updateComputerPlayerStats();

    // TODO: initialize HUD (m_stats)
}

void Controller::handleInput(sf::Event ev)
{
    for (auto& player : m_players)
    {
        player->handleInput(ev);
    }
}

void Controller::updateWorld(float deltaTime)
{
    for (auto& player : m_players)
    {
        player->update(deltaTime);
    }

    for (auto& ally : m_allies)
    {
       ally->update(deltaTime);     
    }
    for (auto& enemy : m_enemies)
    {
        enemy->update(deltaTime);
    }
    for (auto& obj : m_pickables)
    {
        obj->update(deltaTime);
    }
    for (auto& dead : m_deads)
    {
        dead->update(deltaTime);
    }
    updateComputerPlayerStats();

    for (int i = 0; i < m_players.size(); i++) {
        std::shared_ptr<Player> player = m_players[i];
        if (!player)
            continue;
        if (player->getHp() == 0) {
            handleDeath(player, m_players);
            i--;
        }
    }

    // Update the level itself (enemies, objects, etc.)
     //m_level->update(deltaTime);
    //      TODO: create uptade() in Level - needs to update m_enemies!

    // Update HUD/stats with current data
    //m_stats.update(m_players, m_allies, *m_level);
    //      TODO: create uptade() in HUD
    if(m_players.size())
        m_level->handleCollisionsWithPlayer(*m_players.back()); // currently through level, need to transfer into controller

}



void Controller::checkLevelEndConditions()
{
    if (m_level->areAllEnemiesDefeated())
    {
        m_levelFinished = true;
        m_playerWon = true;
        return;
    }

    bool allPlayersDefeated = true;
    for (const auto& player : m_players)
    {
        if (player->isAlive())  
        {
            allPlayersDefeated = false;
            break;
        }
    }
    for (const auto& ally : m_allies)
    {
        if (ally->isAlive())
        {
            allPlayersDefeated = false;
            break;
        }
    }

    if (allPlayersDefeated)
    {
        m_levelFinished = true;
        m_playerWon = false;
    }
}

void Controller::render()
{
   
    // Draw background, enemies, pickable objects, etc.
    m_level->render(m_window);

    for (const auto& player : m_players)
    {
        player->draw(m_window);
    }

    float i = 0.f;
    for (const auto& ally : m_allies)
    {

        ally->draw(m_window);
        // until we'll have HUD
        printHp(ally->getHp(), { 10.f, 10.f + i}, false);
        printHp(ally->getPotentialHp(), { 10.f, 30.f+i }, true);
        i += 40.f;
    }

    i = 0.f;
    for (const auto& enemy : m_enemies)
    {
        enemy->draw(m_window);
        // until we'll have HUD
        printHp(enemy->getHp(), { 930.f, 10.f + i}, false);
        printHp(enemy->getPotentialHp(), { 930.f, 30.f + i}, true);
        i += 40.f;
    }

    // Draw HUD
    //m_window.draw(m_stats);        TODO: draw() in HUD

    for (const auto& dead : m_deads)
    {
        dead->draw(m_window);
    }
            
}

//void Controller::updateAndRender(float deltaTime)
//{
//    if (m_levelFinished)
//        return;
//
//    handleInput(deltaTime);
//    updateWorld(deltaTime);
//    checkLevelEndConditions();
//    render();
//}


// Responsibile for target & safe zone assignment, death handling. 
// (for each of the computer players)
void Controller::updateComputerPlayerStats() {
    for (int i = 0; i < m_allies.size(); i++) {
        std::shared_ptr<Ally> ally = m_allies[i];
        if (!ally)
            continue;

        std::shared_ptr<Object> closest = nullptr;
        float closestDistance = std::numeric_limits<float>::max();

        if (ally->needItem()) {
            checkClosest(m_pickables, ally->getPosition(), closestDistance, closest);
        }

        if (enemyExist()) 
        {
            checkClosest(m_enemies, ally->getPosition(), closestDistance, closest);
            ally->setTarget(closest);

        } else {
            ally->setTarget(nullptr);
        }

        if (ally->getHp() == 0) {
            handleDeath(ally, m_allies);
        }
        else {
            updateSafeZone(ally, m_enemies);
        }
    }

    for (int i = 0; i < m_enemies.size(); i++) {
        std::shared_ptr<Enemy> enemy = m_enemies[i];
        if (!enemy)
            continue;

        std::shared_ptr<Object> closest = nullptr;
        float closestDistance = std::numeric_limits<float>::max();


        if (enemy->needItem()) {
            checkClosest(m_pickables, enemy->getPosition(), closestDistance, closest);
        }

        if (alliesExist())
        {
            checkClosest(m_allies, enemy->getPosition(), closestDistance, closest);
            checkClosest(m_players, enemy->getPosition(), closestDistance, closest);
            enemy->setTarget(closest);

        } else {
            enemy->setTarget(nullptr);
        }

        if (enemy->getHp() == 0) {
            handleDeath(enemy, m_enemies);
        }
        else {
            updateSafeZone(enemy, m_allies);

        }
    }
}

//======================================
//======= NOT SURE IF NEEDED ===========
bool Controller::isLevelFinished() const
{
    return m_levelFinished;
}

bool Controller::didWin() const
{
    return m_playerWon;
}
//======================================


// Calculates the Euclidean distance between two 2D points
float Controller::distanceBetween(sf::Vector2f a, sf::Vector2f b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}


// until we'll have HUD
void Controller::printHp(int hp, const sf::Vector2f& position, bool potential)
{
    static sf::Font font;
    static bool loaded = false;
    if (!loaded) {
        if (!font.loadFromFile("resources/Fonts/lesterbold.ttf")) 
            return;
        loaded = true;
    }

    sf::Text text;
    text.setFont(font);
    if(potential)
        text.setString("P-HP: " + std::to_string(hp));
    else
        text.setString("HP: " + std::to_string(hp));
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Red);
    text.setPosition(position);

    m_window.draw(text);
}

