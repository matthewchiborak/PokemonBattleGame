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

struct ObjectStorage
{
public:
	BattleScreen *bScreen;
	PokeSelectScreen *sScreen;
	FileReader *fileReader;
	int *whatToDraw; // 0 = battle screen, 1 = selectscreen;
	std::vector<Pokemon*> userParty;
	Pokemon* currentPokemon;
	Pokemon *uP1, *uP2, *uP3;//user's pokemon
	Pokemon *oP1, *oP2, *oP3;//opponets's pokemon
	Client *client;
};

void turnFunction(ObjectStorage *objStr)										// All the game logic will go in here
{
	AttackCalculator testCalc;
	FileReader testReader = *objStr->fileReader;
	//if (testReader.readPokemonFile("/Users/Matt/Desktop/PokemonStats.txt"))		// Change location of the PokemonStats file
	//{
	//	std::cout << "Pkmn read success\n";
	//}
	//if (testReader.readMoveFile("/Users/Matt/Desktop/MoveStats.txt"))			// Change location of the MoveStats file
	//{
	//	std::cout << "Move read success\n";
	//}

	//Connect

	Client *client = objStr->client;
	int userInput = objStr->bScreen->getUserInput();
	
	if (userInput != 0)
	{
		if (userInput == 5)
		{
			std::vector<Pokemon*> selected;
			*objStr->whatToDraw = 1;
			objStr->sScreen->getParty(&objStr->userParty, &selected, 1);
			objStr->currentPokemon = selected[0];
			objStr->userParty.push_back(objStr->currentPokemon);
			objStr->bScreen->resetBattleBarState();
			*objStr->whatToDraw = 0;
			objStr->bScreen->setSelfPokemon(selected[0]);
			if (selected[0] == objStr->uP1)
			{
				userInput = 5;
			}
			else if (selected[0] == objStr->uP2)
			{
				userInput = 6;
			}
			else if (selected[0] == objStr->uP3)
			{
				userInput = 7;
			}
		}
		std::cout << userInput << std::endl;
	}
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

	myPokemon[0] = objStr->uP1;
	myPokemon[1] = objStr->uP2;
	myPokemon[2] = objStr->uP3;
	yourPokemon[0] = &oppoPokemon1;
	yourPokemon[1] = &oppoPokemon2;
	yourPokemon[2] = &oppoPokemon3;

	// Create three send and recieve statements for to send your three pokemon and recieve the opponents 3 pokemon
	std::string ourPokemonStats = testPokemon1.sendCreationStats() + "~";			// Send first pokemon stats to server
	std::string oppoPokemonStats = client->recieveMessage();						// Receive first opponent pokemon
	objStr->oP1 = new Pokemon(testReader.getMoveInfo(), oppoPokemonStats);

	ourPokemonStats = testPokemon2.sendCreationStats() + "~";			// Send second pokemon stats to server
	oppoPokemonStats = client->recieveMessage();						// Receive second opponent pokemon
	objStr->oP2 = new Pokemon(testReader.getMoveInfo(), oppoPokemonStats);

	ourPokemonStats = testPokemon3.sendCreationStats() + "~";			// Send third pokemon stats to server
	oppoPokemonStats = client->recieveMessage();						// Receive third opponent pokemon
	objStr->oP3 = new Pokemon(testReader.getMoveInfo(), oppoPokemonStats);


	//std::string creationString = testPokemon1.sendCreationStats() + "-" + testPokemon2.sendCreationStats() + "-" + testPokemon3.sendCreationStats() + "~";

	//!!!Send pokemon stats through server and recieve other players!!!
	//client->sendMessage(creationString);
	//std::string recievedCreationString = client->recieveMessage();
	//std::string recievedCreationString = oppoPokemon1.sendCreationStats() + "-" + oppoPokemon2.sendCreationStats() + "-" + oppoPokemon3.sendCreationStats();

	//Oppenents pokemon made from recieved data

	//std::string testExtractingCS = "655,Delphox2,Fire,Psychic,135,135,100,50,50,50,50,1,3,2,1-Ifyouseethissomethingbroke";
	/*std::string recievedStats = testCalc.extractCreationStats(recievedCreationString, 1);
	objStr->oP1 = new Pokemon(testReader.getMoveInfo(), recievedStats);
	recievedStats = testCalc.extractCreationStats(recievedCreationString, 2);
	objStr->oP2 = new Pokemon(testReader.getMoveInfo(), recievedStats);
	recievedStats = testCalc.extractCreationStats(recievedCreationString, 3);
	objStr->oP3 = new Pokemon(testReader.getMoveInfo(), recievedStats);*/


	Pokemon* activePokemon = &testPokemon1;
	Pokemon* activeOppoPokemon = objStr->oP1;

	std::string endOfTurnMessage = "0";

	do {

		//Turn starts

		//Either pick a move, swap or run
		bool successSelection = false;
		int userInput = objStr->bScreen->getUserInput();
		std::cout << userInput << std::endl;
		if (userInput != 0)
		{
			if (userInput == 5)
			{
					std::vector<Pokemon*> selected;
					*objStr->whatToDraw = 1;
					objStr->sScreen->getParty(&objStr->userParty, &selected, 1);
					objStr->currentPokemon = selected[0];
					objStr->userParty.push_back(objStr->currentPokemon);
					objStr->bScreen->resetBattleBarState();
					*objStr->whatToDraw = 0;
					objStr->bScreen->setSelfPokemon(selected[0]);
					if (objStr->currentPokemon = objStr->uP1)
					{
						userInput == 5;
					}
					else if (objStr->currentPokemon == objStr->uP2)
					{
						userInput = 6;
					}
					else if (objStr->currentPokemon == objStr->uP3)
					{
						userInput = 7;
					}
			}
		}
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

void threadFunction(ObjectStorage *objectStorage, bool *active)
{
	std::vector<Pokemon*> selected;

	// Create a client object and set the socket ip and port
	Client myClient;

	std::ifstream portFileReader("Resources/ServerIP.txt");
	std::string line;
	std::string IPString;
	std::string portString;

	if (portFileReader.is_open())
	{
		getline(portFileReader, line);
		IPString = line;
		getline(portFileReader, line);
		portString = line;
		portFileReader.close();
	}
	else
	{
		std::cout << "Could not read port\n";
	}

	int myPort = std::stoi(portString);

	// Attempt to set the socket
	if (myClient.setSocket(IPString, myPort))						//	On Success with connecting to the server
	{
		objectStorage->client = &myClient;

		*objectStorage->whatToDraw = 1;
		objectStorage->sScreen->getParty(&objectStorage->userParty, 3);
		*objectStorage->whatToDraw = 0;
		objectStorage->uP1 = objectStorage->userParty[0];
		objectStorage->uP2 = objectStorage->userParty[1];
		objectStorage->uP3 = objectStorage->userParty[2];
		objectStorage->currentPokemon = objectStorage->uP1;
		objectStorage->bScreen->setSelfPokemon(objectStorage->currentPokemon);

		turnFunction(objectStorage);

		//while (active)													// This will run continuously
		//{
		//	if (objectStorage->bScreen->getBattleBarState() == BattleBar::SELECTION)
		//	{
		//		selected.clear();
		//		*objectStorage->whatToDraw = 1;
		//		objectStorage->sScreen->getParty(&objectStorage->userParty, &selected, 1);
		//		objectStorage->currentPokemon = selected[0];
		//		objectStorage->userParty.push_back(objectStorage->currentPokemon);
		//		objectStorage->bScreen->resetBattleBarState();
		//		*objectStorage->whatToDraw = 0;
		//		objectStorage->bScreen->setSelfPokemon(selected[0]);
		//	}

		//}
		
	}
	else
	{
		std::cout << "Error Connecting to server \n";
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIN_SIZE.x,WIN_SIZE.y), "Pokemon Battlescreen Test");	// Create the window
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	int whatToDraw;
	bool active = true;



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

	ObjectStorage objectStorage;
	objectStorage.bScreen = &Screen;
	objectStorage.sScreen = &Screen2;
	objectStorage.fileReader = &fileReader;
	objectStorage.whatToDraw = &whatToDraw;

	std::thread  thread(threadFunction,&objectStorage,&active);

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
		std::vector<sf::Keyboard::Key> keys = keyboard.getPressedKeys();

		//for (int i = 0; i < keys.size(); i++)
		//{
		//	if (keys[i] == sf::Keyboard::R)
		//	{
		//		int j = rand() % pokemon.size();
		//		Screen.setOppPokemon(pokemon[j]);
		//		j = rand() % pokemon.size();
		//		Screen.setSelfPokemon(pokemon[j]);
		//		Screen.setRandomBackground();
		//	}
		//}

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