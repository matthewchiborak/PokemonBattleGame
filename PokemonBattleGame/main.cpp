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
#include "client.h"


const sf::Vector2i WIN_SIZE(960, 640);//The size of the window.

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIN_SIZE.x,WIN_SIZE.y), "Pokemon Battlescreen Test");//create the window
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	// Create a client object and set the socket ip and port
	Client myClient;
	if (myClient.setSocket("99.248.220.4", 2000))				// Attempt to set the socket
	{
		//
	}

	FileReader fileReader;
	if (!fileReader.readPokemonFile("Resources/Pokemon_List.csv"))
	{
		std::cout << "Error could not read Pokemon List" << std::endl;
	}
	if (!fileReader.readMoveFile("Resources/Moves.csv"))
	{
		std::cout << "Error could not read Move List" << std::endl;
	}
	std::vector<Pokemon*> pokemon;
	for (int i = 0; i < fileReader.numPkmnStats(); i++)
	{
		pokemon.push_back(new Pokemon(fileReader.getPokemonStats(i),fileReader.getMoveInfo()));
	}


	BattleScreen Screen(WIN_SIZE);//create the battlescreen
	int j = rand() % pokemon.size();
	Screen.setOppPokemon(pokemon[j]);
	j = rand() % pokemon.size();
	Screen.setSelfPokemon(pokemon[j]);

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
	keyboard.addKeyWatch(sf::Keyboard::R);

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
		std::vector<sf::Keyboard::Key> keys = keyboard.getPressedKeys();

		for (int i = 0; i < keys.size(); i++)
		{
			if (keys[i] == sf::Keyboard::R)
			{
				int j = rand() % pokemon.size();
				Screen.setOppPokemon(pokemon[j]);
				j = rand() % pokemon.size();
				Screen.setSelfPokemon(pokemon[j]);
				Screen.setRandomBackground();
			}
		}

		Screen.keysPressed(keys);//send the pressed keys to the battleScreen
		Screen2.keysPressed(keys);

		window.clear();//clear the window's frame buffer
		window.draw(Screen);//draw the battlescreen to the frame buffer
		window.display();//display the frame buffer to the user.
	}

	for (int i = 0; i < pokemon.size(); i++)
	{
		delete pokemon[i];
	}

	return 0;
}