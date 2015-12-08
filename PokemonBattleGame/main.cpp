#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Main.hpp>
#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <thread>

#include "PokeText.h"
#include "HealthBar.h"
#include "BattleScreen.h"
#include "KeyboardWrapper.h"
#include "FileReader.h"
#include "Pokemon.h"
#include "PokeSelectScreen.h"
#include "client.h"


const sf::Vector2i WIN_SIZE(960, 640);//The size of the window.

void threadFucntion(BattleScreen *battle, PokeSelectScreen *select, FileReader *fileReader, int *whatToDraw, bool *active)
{
	std::vector<Pokemon*> party, selected;
	*whatToDraw = 1;
	select->getParty(&party , 3);
	*whatToDraw = 0;
	selected.push_back(party[0]);
	party.erase(party.begin());
	battle->setSelfPokemon(selected[0]);
	while (active)
	{
		if (battle->getBattleBarState() == BattleBar::SELECTION)
		{
			party.push_back(selected[0]);
			selected.clear();
			*whatToDraw = 1;
			select->getParty(&party, &selected, 1);
			//select->getParty(&selected, 1);
			battle->resetBattleBarState();
			*whatToDraw = 0;
			battle->setSelfPokemon(selected[0]);
		}
	}

	for (int i = 0; i < party.size(); i++)
	{
		delete party[i];
	}

}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIN_SIZE.x,WIN_SIZE.y), "Pokemon Battlescreen Test");	// Create the window
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	int whatToDraw;
	bool active = true;

	// Create a client object and set the socket ip and port
	//Client myClient;
	//// Attempt to set the socket
	//if (myClient.setSocket("99.248.220.4", 2000))						//	On Success with connecting to the server
	//{
	//	
	//}
	//else																// On failure with the connection
	//{

	//}

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

	whatToDraw = 0;

	std::thread  thread(threadFucntion, &Screen, &Screen2, &fileReader,&whatToDraw,&active);

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

		window.clear();//clear the window's frame buffer
		switch (whatToDraw)
		{
		case 0:
			Screen.keysPressed(keys);//send the pressed keys to the battleScreen
			window.draw(Screen);//draw the battlescreen to the frame buffer
			break;
		case 1:
			Screen2.keysPressed(keys);
			window.draw(Screen2);//draw the battlescreen to the frame buffer
			break;
		default:
			window.clear();
			break;
		}
		
		window.display();//display the frame buffer to the user.
	}

	active = false;
	for (int i = 0; i < pokemon.size(); i++)
	{
		delete pokemon[i];
	}

	thread.join();
	return 0;
}