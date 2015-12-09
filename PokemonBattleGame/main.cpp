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
#include "AttackCalculator.h"
#include "StoredStats.h"
#include "Pokemon.h"
#include "PokeSelectScreen.h"
#include "client.h"


const sf::Vector2i WIN_SIZE(960, 640);//The size of the window.

void threadFucntion(BattleScreen *battle, PokeSelectScreen *select, FileReader *fileReader, int *whatToDraw, bool *active)
{
	std::vector<Pokemon*> party, pokemon, selected;
	for (int i = 0; i < fileReader->numPkmnStats(); i++)
	{
		//pokemon.push_back(new Pokemon(fileReader->getPokemonStats(i), fileReader->getMoveInfo()));
	}
	*whatToDraw = 1;
	select->getParty(&party , 3);
	*whatToDraw = 0;
	selected.push_back(party[0]);
	party.erase(party.begin());
	battle->setSelfPokemon(selected[0]);
	while (active)													// This will run continuously
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
	for (int i = 0; i < pokemon.size(); i++)
	{
		delete pokemon[i];
	}

	for (int i = 0; i < party.size(); i++)
	{
		delete party[i];
	}

}

void turnFunction(Client *client)										// All the game logic will go in here
{
	AttackCalculator testCalc;
	FileReader testReader;
	//if (testReader.readPokemonFile("/Users/Matt/Desktop/PokemonStats.txt"))		// Change location of the PokemonStats file
	//{
	//	std::cout << "Pkmn read success\n";
	//}
	//if (testReader.readMoveFile("/Users/Matt/Desktop/MoveStats.txt"))			// Change location of the MoveStats file
	//{
	//	std::cout << "Move read success\n";
	//}

	//Connect

	//Pick Pokemon
	//Select pokemon gives index ->
	int selectedPokemon1 = 0;
	int selectedPokemon2 = 1;
	int selectedPokemon3 = 2;
	Pokemon* myPokemon[3];
	Pokemon* yourPokemon[3];
	Pokemon testPokemon1(testReader.getPokemonStats(selectedPokemon1), testReader.getMoveInfo());
	Pokemon testPokemon2(testReader.getPokemonStats(selectedPokemon2), testReader.getMoveInfo());
	Pokemon testPokemon3(testReader.getPokemonStats(selectedPokemon3), testReader.getMoveInfo());
	Pokemon oppoPokemon1(testReader.getPokemonStats(selectedPokemon1), testReader.getMoveInfo());
	Pokemon oppoPokemon2(testReader.getPokemonStats(selectedPokemon2), testReader.getMoveInfo());
	Pokemon oppoPokemon3(testReader.getPokemonStats(selectedPokemon3), testReader.getMoveInfo());

	myPokemon[0] = &testPokemon1;
	myPokemon[1] = &testPokemon2;
	myPokemon[2] = &testPokemon3;
	yourPokemon[0] = &oppoPokemon1;
	yourPokemon[1] = &oppoPokemon2;
	yourPokemon[2] = &oppoPokemon3;

	std::string creationString = testPokemon1.sendCreationStats() + "-" + testPokemon2.sendCreationStats() + "-" + testPokemon3.sendCreationStats() + "~";

	//!!!Send pokemon stats through server and recieve other players!!!
	client->sendMessage(creationString);
	std::string recievedCreationString = client->recieveMessage();
	//std::string recievedCreationString = oppoPokemon1.sendCreationStats() + "-" + oppoPokemon2.sendCreationStats() + "-" + oppoPokemon3.sendCreationStats();

	//Oppenents pokemon made from recieved data

	//std::string testExtractingCS = "655,Delphox2,Fire,Psychic,135,135,100,50,50,50,50,1,3,2,1-Ifyouseethissomethingbroke";
	std::string recievedStats = testCalc.extractCreationStats(recievedCreationString, 1);
	Pokemon localOppoPokemon1(testReader.getMoveInfo(), recievedStats);
	recievedStats = testCalc.extractCreationStats(recievedCreationString, 2);
	Pokemon localOppoPokemon2(testReader.getMoveInfo(), recievedStats);
	recievedStats = testCalc.extractCreationStats(recievedCreationString, 3);
	Pokemon localOppoPokemon3(testReader.getMoveInfo(), recievedStats);

	Pokemon* activePokemon = &testPokemon1;
	Pokemon* activeOppoPokemon = &localOppoPokemon1;

	std::string endOfTurnMessage = "0";

	do {

		//Turn starts

		//Either pick a move, swap or run
		bool successSelection = false;
		int userInput = 0;
		while (!successSelection)
		{
			//User Picks an option. 1,2,3,4 Are the attacks, 5, 6, 7 are swap and 8 is run
			if (userInput == 1 || userInput == 2 || userInput == 3 || userInput == 4)
			{

				if (activePokemon->tryStruggling()) {
					userInput = 1;
				}
				else
				{
					//Player picks attack
					//selectedAttack=3;

					if (activePokemon->useMove(userInput))
					{
						std::cout << "Out of pp" << std::endl;
						//Pick a new attack
					}
					else
					{
						successSelection = true;
					}
				}

			}
			else if (userInput == 5 || userInput == 6 || userInput == 7)
			{

				if (myPokemon[userInput - 5]->getHP() != 0)
				{
					activePokemon = myPokemon[userInput - 5];
					successSelection = true;
				}

			}
			else if (userInput == 8)
			{
				//WORRY ABOUT THIS LATER THIS IS RUN BY THE WAY
			}

		}

		//SPEED TIME
		int tempSpeed = activePokemon->getSpeed();
		if (userInput == 5 || userInput == 6 || userInput == 7)
		{
			tempSpeed += 1000;
		}
		std::string speedToBeSent = std::to_string(tempSpeed);
		//SEND THIS STRING AND RECIEVE PLACE
		client->sendMessage(speedToBeSent);
		std::string recievedPlacing = client->recieveMessage();
		//std::string recievedPlacing = "1";
		std::string responseString = "";

		if (recievedPlacing == "1")
		{
			//User Picks an option. 1,2,3,4 Are the attacks, 5, 6, 7 are swap and 8 is run
			if (userInput == 1 || userInput == 2 || userInput == 3 || userInput == 4)
			{

				responseString = testCalc.applyDamage(activePokemon, activeOppoPokemon, userInput);

				std::string attackersNewStats = activePokemon->getNewStats();
				std::string defendersNewStats = activeOppoPokemon->getNewStats();

				std::string stringToBeSent = responseString + "-" + attackersNewStats + "-" + defendersNewStats + "~";
				//SEND THIS TO SERVER
				client->sendMessage(stringToBeSent);

			}
			else if (userInput == 5 || userInput == 6 || userInput == 7)
			{
				activePokemon = myPokemon[userInput - 5];

				std::string stringToBeSent = "swap" + std::to_string(userInput - 5) + "~";
				//SEND THIS TO YOUR FOE!!!!!!!
				client->sendMessage(stringToBeSent);
			}
			else if (userInput == 8)
			{
				//WORRY ABOUT THIS LATER THIS IS RUN BY THE WAY
			}

		}
		else
		{
			std::string syncString = "Not my turn~";
			//SENT TO SERVER
			client->sendMessage(syncString);
		}


		//Block here to read
		//Result-oppo-yours
		std::string testRecievedString = client->recieveMessage();
		//std::string testRecievedString = "unb21324-10,20,30,40,50,60,70,80,0,0,10,10,10,10-100,200,300,400,500,600,700,800,1,0,8,8,8,8";

		//THESE ARE ALSO FOR THE UI
		std::string swapString = "";
		int checkedSwap = testCalc.checkIfSwap(testRecievedString);
		std::vector<std::string> responsePhraseHolder;
		int usedMoveIndex;
		int numberOfPhrases;

		if (recievedPlacing == "2")
		{
			if (checkedSwap != 0)
			{
				swapString = testCalc.resultSwapTranslator(checkedSwap, yourPokemon[checkedSwap]);
				activeOppoPokemon = yourPokemon[checkedSwap];

			}
			else //ITS AN ATTACK
			{
				std::string translatedResult = testCalc.extractAttackString(testRecievedString);
				std::string translatedYourStats = testCalc.extractAttackStats(testRecievedString);
				std::string translatedOppoStats = testCalc.extractDefenceString(testRecievedString);

				numberOfPhrases = testCalc.attackResultTranslator(&responsePhraseHolder, translatedResult, activeOppoPokemon, activePokemon, &usedMoveIndex);
				activePokemon->updateStats(translatedYourStats);
				activeOppoPokemon->updateStats(translatedOppoStats);

			}
		}
		else
		{
			if (userInput == 1 || userInput == 2 || userInput == 3 || userInput == 4)
			{
				numberOfPhrases = testCalc.attackResultTranslator(&responsePhraseHolder, responseString, activeOppoPokemon, activePokemon, &usedMoveIndex);
			}

		}



		//Update UI
		if (checkedSwap != 0)
		{
			//CHANGE POKEMON ICON TO CURRENT POKEMON AND PRINT OUT  THE SWAP STRING
		}
		else
		{
			//OUTPUT ALL THE STRING FROM THE STRING HOLDER NOTE THAT THE USED MOVE INDEX IS WHERE THE HEALTH SHOULD PROBABLY DECREASE
		}

		//OTHER TURN

		if (recievedPlacing == "2")
		{
			if (activePokemon->getHP() == 0)
			{
				std::string faintedString = "Faint~";
				//SEND THIS TO THE OTHER PLAYER BECAUSE YOU CANT ATTACK
				client->sendMessage(faintedString);
			}
			//User Picks an option. 1,2,3,4 Are the attacks, 5, 6, 7 are swap and 8 is run
			else if (userInput == 1 || userInput == 2 || userInput == 3 || userInput == 4)
			{

				responseString = testCalc.applyDamage(activePokemon, activeOppoPokemon, userInput);

				std::string attackersNewStats = activePokemon->getNewStats();
				std::string defendersNewStats = activeOppoPokemon->getNewStats();

				std::string stringToBeSent = responseString + "-" + attackersNewStats + "-" + defendersNewStats + "~";
				//SEND THIS TO SERVER
				client->sendMessage(stringToBeSent);

			}
			else if (userInput == 5 || userInput == 6 || userInput == 7)
			{
				activePokemon = myPokemon[userInput - 5];

				std::string stringToBeSent = "swap" + std::to_string(userInput - 5) + "~";
				//SEND THIS TO YOUR FOE!!!!!!!
				client->sendMessage(stringToBeSent);
			}
			else if (userInput == 8)
			{
				//WORRY ABOUT THIS LATER THIS IS RUN BY THE WAY
			}

		}
		else
		{
			std::string syncString = "Not my turn~";
			client->sendMessage(syncString);
			//SENT TO SERVER
		}


		//Block here to read

		//Result-oppo-yours
		std::string testRecievedString2 = client->recieveMessage();
		//std::string testRecievedString2 = "unb21324-10,20,30,40,50,60,70,80,0,0,10,10,10,10-100,200,300,400,500,600,700,800,1,0,8,8,8,8";

		//THESE ARE ALSO FOR THE UI
		swapString = "";
		checkedSwap = testCalc.checkIfSwap(testRecievedString);


		if (recievedPlacing == "1")
		{
			if (checkedSwap != 0)
			{
				swapString = testCalc.resultSwapTranslator(checkedSwap, yourPokemon[checkedSwap]);
				activeOppoPokemon = yourPokemon[checkedSwap];

			}
			else //ITS AN ATTACK
			{
				std::string translatedResult = testCalc.extractAttackString(testRecievedString);
				std::string translatedYourStats = testCalc.extractAttackStats(testRecievedString);
				std::string translatedOppoStats = testCalc.extractDefenceString(testRecievedString);

				numberOfPhrases = testCalc.attackResultTranslator(&responsePhraseHolder, translatedResult, activeOppoPokemon, activePokemon, &usedMoveIndex);
				activePokemon->updateStats(translatedYourStats);
				activeOppoPokemon->updateStats(translatedOppoStats);

			}
		}
		else
		{
			if (userInput == 1 || userInput == 2 || userInput == 3 || userInput == 4)
			{
				numberOfPhrases = testCalc.attackResultTranslator(&responsePhraseHolder, responseString, activeOppoPokemon, activePokemon, &usedMoveIndex);
			}



			//Update UI
			if (checkedSwap != 0)
			{
				//CHANGE POKEMON ICON TO CURRENT POKEMON AND PRINT OUT  THE SWAP STRING
			}
			else
			{
				//OUTPUT ALL THE STRING FROM THE STRING HOLDER NOTE THAT THE USED MOVE INDEX IS WHERE THE HEALTH SHOULD PROBABLY DECREASE
			}
		}

		std::string endMessageToSend = "0";

		//END OF MESSAGE TRANSACTION
		if (activePokemon->getHP() != 0)
		{
			endMessageToSend = "0";
			//SEND THIS
			client->sendMessage(endMessageToSend);
		}
		else
		{
			//User selects new pokemon 1,2, or 3
			int selection = 2;
			activePokemon = myPokemon[1];
			endMessageToSend = "2"; //Or 2 or 3 Whatever they picked and send it
			//SEND THIS
			client->sendMessage(endMessageToSend);
		}

		//RECIEVE THE OTHER PLAYERS MESSAGE
		std::string recievedMessage = client->recieveMessage();
		//std::string recievedMessage = "0";

		if (recievedMessage != "0" || recievedMessage != "4")
		{
			int newPoke = std::stoi(recievedMessage);
			activeOppoPokemon = yourPokemon[newPoke];
		}

	} while (endOfTurnMessage != "4");
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIN_SIZE.x,WIN_SIZE.y), "Pokemon Battlescreen Test");	// Create the window
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	int whatToDraw;
	bool active = true;

	// Create a client object and set the socket ip and port
	Client myClient;
	// Attempt to set the socket
	if (myClient.setSocket("99.248.220.4", 2000))						//	On Success with connecting to the server
	{
		// Start the turn thread
	}
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