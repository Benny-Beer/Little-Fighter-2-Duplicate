#pragma once
#include "Objects/PlayableObject.h"
#include <SFML/Graphics.hpp>
#include <memory>

#include <string>
#include "PlayableObjectStates/PlayerStates/PlayerBaseState.h"

#include "Objects/PickableObject.h"
#include "Attacks/AttackBehavior.h"

struct PlayerData {
    std::string m_name;
    std::string m_description;
    std::shared_ptr<sf::Texture> m_profilePic;
    std::shared_ptr<sf::Texture> m_chracterIcon;
    std::shared_ptr<sf::Texture> m_animationSheet;
    std::string toString() {
        return "name: " + m_name + " desc: " + m_description;
    }
};

class Player : public PlayableObject
{
public:
    explicit Player(const sf::Vector2f pos, const std::string& name, float speed = 200.f);

    void handleInput(sf::Event event);                 // Reads arrow-key state (?) m_direction
    void update(float dt);
    //void move(float dt);                                // Moves position by m_direction * speed * dt
    //void setDiraction(Input input);
               
    //void draw(sf::RenderWindow& window) override;/* Draws the sprite at current position */
    void handleCollision() override;    // Stub for future collision handling

    void setSpeed(float speed);
    //float getSpeed() const;

    bool isAlive() const;

    /* Keep the player inside the window bounds */
    void clampToWindow(const sf::Vector2u& windowSize);

    /*void setAnimation(const Animation& anim);*/
    //void setState(std::unique_ptr<PlayerBaseState> state);
    void setAttack(std::unique_ptr<AttackBehavior> attack);
    //void pickUpObject(std::shared_ptr<PickableObject> obj);

    void setAniName(const std::string& name);
    //void setStrategyName(const std::string& name); 
    //void attack();
	

	//int getDirection() const { return static_cast<int>(m_dir); } 
    const PlayableObjectState* getState() const { return m_state.get(); }
private:
    bool m_alive = true;
};
