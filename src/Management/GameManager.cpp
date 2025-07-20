#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Management/GameManager.h"
#include "Management/Controller.h"
#include "Screens/IScreen.h"
#include "Screens/InGameScreen.h"
#include "Screens/WelcomeScreen.h"
#include "GamePlay/Level.h" 
#include<iostream>

GameManager::GameManager() : m_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Little Fighter 2")
{
    m_currScreen = std::make_unique<WelcomeScreen>(m_window, *this);
}

void GameManager::run()
{
    sf::Clock clock;
    while (m_window.isOpen())
    {
        sf::Event ev;
        while (m_window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
            {
                m_window.close();
            }
            else if (ev.type == sf::Event::KeyReleased && ev.key.code == sf::Keyboard::Escape)
            {
                m_window.close();
            }
            m_currScreen->handleEvents(ev);


            if (m_nextScreen)
            {
                m_currScreen = std::move(m_nextScreen);
            }

        }
        sf::Time deltaTime = clock.restart();

        m_currScreen->update(deltaTime);

        m_window.clear();

        m_currScreen->render();
        m_window.display();
    }
}

void GameManager::switchScreen(std::unique_ptr<IScreen> nextScreen)
{
    m_nextScreen = std::move(nextScreen);
}
/*
void GameManager::readLevels(std::string path)
{
    std::ifstream file(path);
    std::string line;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue; // remove empty lines from beggining

        Level level(line);

        while (std::getline(file, line)) {
            // objects
            if (line.rfind("Objects: ", 0) == 0) {
                level.addPickableObjects(line.substr(9));
                break; 
            }
            // squads
            if (!line.empty())
                level.addSquad(line);
        }

        m_levels.push_back(std::move(level));
    }
**/