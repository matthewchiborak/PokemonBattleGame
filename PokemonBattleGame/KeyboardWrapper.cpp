#include "KeyboardWrapper.h"



KeyboardWrapper::KeyboardWrapper()
{
}

void KeyboardWrapper::addKeyWatch(sf::Keyboard::Key key)
{
	watchForPressed.push_back(key);
	pressed.push_back(false);
}

std::vector<sf::Keyboard::Key> KeyboardWrapper::getPressedKeys()
{
	std::vector<sf::Keyboard::Key> pressed;
	for (int i = 0; i < watchForPressed.size(); i++)
	{
		if (sf::Keyboard::isKeyPressed(watchForPressed[i]))
		{
			if (!this->pressed[i])//if the key was not pressed last check and is now pressed
			{
				pressed.push_back(watchForPressed[i]);
			}
		}
		this->pressed[i] = sf::Keyboard::isKeyPressed(watchForPressed[i]);//save the current state of the key
	}
	return pressed;
}


KeyboardWrapper::~KeyboardWrapper()
{
}
