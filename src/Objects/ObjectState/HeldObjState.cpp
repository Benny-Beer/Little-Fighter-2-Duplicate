//#include "Objects/ObjectStates/HeldObjState.h"
//#include <cmath>
//
//void HeldObjState::enter(PickableObject& obj)
//{
//	std::cout << "Entering HeldObjState for object: " << obj.getName() << std::endl;
//	obj.setStateName("held");
//	m_clock.restart();
//}
//
//void HeldObjState::update(PickableObject& obj, float dt)
//{
//    if (!obj.getHolder()) return;
//
//    float time = m_clock.getElapsedTime().asSeconds();
//
//    // תנודות קלות למעלה ולמטה (כמו "נשימה" או תנועה טבעית של היד)
//    float yOffset = std::sin(time * 2.5f) * 3.f; // עדינות יותר
//
//    // סכין מוחזקת ביד ימין של השחקן שנמצא בעמידה
//    sf::Vector2f baseOffset(30.f, -95.f); // יד ימין למעלה יותר
//    sf::Vector2f finalOffset = baseOffset + sf::Vector2f(0.f, yOffset);
//
//    obj.setPosition(obj.getHolder()->getPosition() + finalOffset);
//}
