#ifndef KEYBOARDWRAPPER_H
#define KEYBOARDWRAPPER_H
#include <SFML\System.hpp>
#include <SFML\Main.hpp>
#include <SFML\Window.hpp>
#include <vector>
class KeyboardWrapper
{
	//This class watches keys given to it for when they are pressed (not held)
	std::vector<sf::Keyboard::Key> watchForPressed;//what keys to watch
	std::vector<bool> pressed;//if the key was pressed last time it checked
public:
	KeyboardWrapper();
	void addKeyWatch(sf::Keyboard::Key);//add a key to watch.
	std::vector<sf::Keyboard::Key> getPressedKeys();//check for pressed keys and return the ones that were pressed.
	~KeyboardWrapper();
};
#endif