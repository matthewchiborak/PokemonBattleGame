#pragma once
#include <SFML\System.hpp>
#include <SFML\Main.hpp>
#include <SFML\Window.hpp>
#include <vector>
class KeyboardWrapper
{
	std::vector<sf::Keyboard::Key> watchForPressed;
	std::vector<bool> pressed;
public:
	KeyboardWrapper();
	void addKeyWatch(sf::Keyboard::Key);
	std::vector<sf::Keyboard::Key> getPressedKeys();
	~KeyboardWrapper();
};

