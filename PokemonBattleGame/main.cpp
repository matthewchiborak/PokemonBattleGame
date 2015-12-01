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
#include "FileReader.h"
#include "Pokemon.h"
#include "PokeSelectScreen.h"


const sf::Vector2i WIN_SIZE(960, 640);//The size of the window.

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIN_SIZE.x,WIN_SIZE.y), "Pokemon Battlescreen Test");//create the window
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	FileReader fileReader;
	if (!fileReader.readPokemonFile("Resources/Pokemon_List.csv"))
	{
		std::cout << "Error could not read Pokemon List" << std::endl;
	}
	std::vector<Pokemon> pokemon;
	for (int i = 0; i < fileReader.numPkmnStats(); i++)
	{
		pokemon.push_back(Pokemon(fileReader.getPokemonStats(i)));
	}


	BattleScreen Screen(WIN_SIZE);//create the battlescreen

	PokeSelectScreen Screen2(WIN_SIZE);
	Screen2.setPokemonList(&pokemon);

	KeyboardWrapper keyboard;//create a keyboard wrapper to watch for key presses

	//tell the keyboardWrapper what keys to watch
	keyboard.addKeyWatch(sf::Keyboard::Up);
	keyboard.addKeyWatch(sf::Keyboard::Down);
	keyboard.addKeyWatch(sf::Keyboard::Left);
	keyboard.addKeyWatch(sf::Keyboard::Right);
	keyboard.addKeyWatch(sf::Keyboard::Z);
	keyboard.addKeyWatch(sf::Keyboard::X);

	//test variables to manipulating healthbars
	int health = 30;
	int health2 = 30;

	Screen2.refresh();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//insert code to run each frame after this

		//test statements for manipulating the healthbars
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
		std::vector<sf::Keyboard::Key> keys = keyboard.getPressedKeys();

		Screen.keysPressed(keys);//send the pressed keys to the battleScreen
		Screen2.keysPressed(keys);

		window.clear();//clear the window's frame buffer
		window.draw(Screen2);//draw the battlescreen to the frame buffer
		window.display();//display the frame buffer to the user.
	}

	return 0;
}