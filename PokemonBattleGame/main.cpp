#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Main.hpp>
#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

#include "PokeText.h"
#include "HealthBar.h"
#include "BattleScreen.h"
#include "KeyboardWrapper.h"

const sf::Vector2i WIN_SIZE(960, 640);//The size of the window.

/*
HealthBar Info
Green = Bottom(112,248,168) Top(88,208,128)
Yellow = Bottom(248,224,56) Top(200,168,8)
Red = Bottom(248,88,56) Top(168,64,72)
Black = Bottom(80,104,88) Top(72,64,88)

OpPosition = (52,33) to (99,35)
SelfPositon = (187,88) to (234,90)
*/


int main()
{
	sf::RenderWindow window(sf::VideoMode(WIN_SIZE.x,WIN_SIZE.y), "Pokemon Battlescreen Test");
	window.setFramerateLimit(60);

	BattleScreen Screen(WIN_SIZE);
	KeyboardWrapper keyboard;

	keyboard.addKeyWatch(sf::Keyboard::Up);
	keyboard.addKeyWatch(sf::Keyboard::Down);
	keyboard.addKeyWatch(sf::Keyboard::Left);
	keyboard.addKeyWatch(sf::Keyboard::Right);
	keyboard.addKeyWatch(sf::Keyboard::Return);

	int health = 30;
	int health2 = 30;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			health += 1;
			Screen.SetOPHealth(health);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			health -= 1;
			Screen.SetOPHealth(health);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			health2 += 1;
			Screen.SetSelfHealth(health2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			health2 -= 1;
			Screen.SetSelfHealth(health2);
		}

		Screen.keysPressed(keyboard.getPressedKeys());

		window.clear();
		window.draw(Screen);
		window.display();
	}

	return 0;
}