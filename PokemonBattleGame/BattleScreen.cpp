#include "BattleScreen.h"

void BattleScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(Screen);
}

BattleScreen::BattleScreen(const sf::Vector2i WIN_SIZE)
{
	ScreenTex.create(240, 160);

	Screen.setScale(sf::Vector2f(WIN_SIZE.x / 240, WIN_SIZE.y / 160));

	//load resources from external files

	font.loadFromFile("Resources/EmeraldPro.ttf");

	SelfName = PokeText("CHARIZARD", sf::Vector2f(155, 68), true, &font, 16);
	OpName = PokeText("BLAZIKEN", sf::Vector2f(20, 13), true, &font, 16);
	HealthText = PokeText("25/ 60", sf::Vector2f(193, 87), true, &font, 15);

	OpInfo.setTexture(*loader.tryLoadTexture("OpInfo","Resources/OpponetInfo.png"));
	OpInfo.setPosition(13, 16);

	SelfInfo.setTexture(*loader.tryLoadTexture("SelfInfo", "Resources/SelfInfo.png"));
	SelfInfo.setPosition(134, 70);

	SelfInfoFrame.setTexture(*loader.tryLoadTexture("SelfInfoFrame", "Resources/SelfInfoFrame.png"));
	SelfInfoFrame.setPosition(134, 70);

	BackGround.setTexture(*loader.tryLoadTexture("BattleBackground"+itos(1), "Resources/Backgrounds/"+itos(1)+".png"));

	OpPokemon.setTexture(*loader.tryLoadTexture("front257", "Resources/PokemonSprites/Front/257.png"));
	OpPokemon.setPosition(140, 10);

	SelfPokemon.setTexture(*loader.tryLoadTexture("back6", "Resources/PokemonSprites/Back/6.png"));
	SelfPokemon.setPosition(40, 46);

	//create the healthbars
	OpHealth = HealthBar(30, 30, sf::Vector2f(52, 33), sf::Vector2f(100, 36));
	SelfHealth = HealthBar(250, 600, sf::Vector2f(187, 88), sf::Vector2f(235, 91));

	refresh();//refresh the texture
	//save a screenshot of the battle screen
	//ScreenTex.getTexture().copyToImage().saveToFile("ScreenShot.png");
}

void BattleScreen::refresh()
{
	ScreenTex.clear();

	ScreenTex.draw(BackGround);
	ScreenTex.draw(OpPokemon);
	ScreenTex.draw(SelfPokemon);
	ScreenTex.draw(battleBar);
	ScreenTex.draw(OpHealth);
	ScreenTex.draw(OpInfo);
	ScreenTex.draw(SelfHealth);
	ScreenTex.draw(SelfInfo);
	ScreenTex.draw(SelfName);
	ScreenTex.draw(HealthText);
	ScreenTex.draw(SelfInfoFrame);
	ScreenTex.draw(OpName);
	ScreenTex.draw(opStatusEffect);
	ScreenTex.draw(selfStatusEffect);

	ScreenTex.display();
	Screen.setTexture(ScreenTex.getTexture());
}



void BattleScreen::SetOPHealth(int health)
{
	//change the opponet's healthbar and refresh the screen
	OpHealth.setHealth(health);
	//refresh();
}

void BattleScreen::SetSelfHealth(int health)
{
	//change the user's health bar and health text. refresh the screen
	SelfHealth.setHealth(health);
	HealthText.setText(std::to_string(health) + "/600");
	//refresh();
}

void BattleScreen::refreshHealth()
{
	SelfHealth.setHealth(selfPokemon->getHP());
	OpHealth.setHealth(oppPokemon->getHP());
	std::stringstream s;
	int hp = selfPokemon->getHP();
	int maxHp = selfPokemon->getMaxHP();
	if (hp > 100)
	{
		s << hp;
	}
	else if (hp > 10)
	{
		s << " " << hp;
	}
	else
	{
		s << "  " << hp;
	}
	s << "/";
	if (maxHp > 100) 
	{
		s << maxHp;
	}
	else if (maxHp > 10)
	{
		s << " " << maxHp;
	}
	else
	{
		s << "  " << maxHp;
	}
	HealthText.setText(s.str());

	// Set status effect for the pokemon
	
	std::cout << "Opponent current Pokemon status: " << oppPokemon->getCurrentStatis() << std::endl;
	// Set a status effect for opponent
	switch (oppPokemon->getCurrentStatis())
	{
		case 0:															// No Status Effect, set to blank texture
			opStatusEffect.setTexture(*loader.tryLoadTexture("NoStatus", "Resources/Status/NoStatusIcon.png"));
			opStatusEffect.setPosition(14, 29);
			break;
		case 1:															// Burn Status Effect
			opStatusEffect.setTexture(*loader.tryLoadTexture("BurnStatus", "Resources/Status/BurnIcon.png"));
			opStatusEffect.setPosition(14, 29);
			break;
		case 2:															// Frozen Status Effect
			opStatusEffect.setTexture(*loader.tryLoadTexture("FrozenStatus", "Resources/Status/FrozenIcon.png"));
			opStatusEffect.setPosition(14, 29);
			break;
		case 3:															// Paraylyzed Status Effect
			opStatusEffect.setTexture(*loader.tryLoadTexture("ParalyseStatus", "Resources/Status/ParalyzeIcon.png"));
			opStatusEffect.setPosition(14, 29);
			break;
		case 4:															// Poison Status Effect
			opStatusEffect.setTexture(*loader.tryLoadTexture("PoisonStatus", "Resources/Status/PoisonIcon.png"));
			opStatusEffect.setPosition(14, 29);
			break;
		case 5:															// Sleeping Status Effect
			opStatusEffect.setTexture(*loader.tryLoadTexture("SleepStatus", "Resources/Status/SleepIcon.png"));
			opStatusEffect.setPosition(14, 29);
			break;
		case 6:															// Sleepin Status Effect (can wake up)
			opStatusEffect.setTexture(*loader.tryLoadTexture("SleepStatus", "Resources/Status/SleepIcon.png"));
			opStatusEffect.setPosition(14, 29);
			break;
		case 7:															// Confusion Status Effect
			opStatusEffect.setTexture(*loader.tryLoadTexture("ConfusionStatus", "Resources/Status/ConfusionIcon.png"));
			opStatusEffect.setPosition(14, 29);
			break;
		case 8:															// Confusion Status Effect (can hit)
			opStatusEffect.setTexture(*loader.tryLoadTexture("ConfusionStatus", "Resources/Status/ConfusionIcon.png"));
			opStatusEffect.setPosition(14, 29);
			break;
		default:
			opStatusEffect.setTexture(*loader.tryLoadTexture("NoStatus", "Resources/Status/NoStatusIcon.png"));
			opStatusEffect.setPosition(14, 29);
			break;
	}

	// Set status effect for our pokemon
	std::cout << "Our current Pokemon status: " << selfPokemon->getCurrentStatis() << std::endl;
	switch (selfPokemon->getCurrentStatis())
	{
	case 0:															// No Status Effect, set to blank texture
		selfStatusEffect.setTexture(*loader.tryLoadTexture("NoStatus", "Resources/Status/NoStatusIcon.png"));
		selfStatusEffect.setPosition(149, 85);
		break;
	case 1:															// Burn Status Effect
		selfStatusEffect.setTexture(*loader.tryLoadTexture("BurnStatus", "Resources/Status/BurnIcon.png"));
		selfStatusEffect.setPosition(149, 85);
		break;
	case 2:															// Frozen Status Effect
		selfStatusEffect.setTexture(*loader.tryLoadTexture("FrozenStatus", "Resources/Status/FrozenIcon.png"));
		selfStatusEffect.setPosition(149, 85);
		break;
	case 3:															// Paraylyzed Status Effect
		selfStatusEffect.setTexture(*loader.tryLoadTexture("ParalyseStatus", "Resources/Status/ParalyzeIcon.png"));
		selfStatusEffect.setPosition(149, 85);
		break;
	case 4:															// Poison Status Effect
		selfStatusEffect.setTexture(*loader.tryLoadTexture("PoisonStatus", "Resources/Status/PoisonIcon.png"));
		selfStatusEffect.setPosition(149, 85);
		break;
	case 5:															// Sleeping Status Effect
		selfStatusEffect.setTexture(*loader.tryLoadTexture("SleepStatus", "Resources/Status/SleepIcon.png"));
		selfStatusEffect.setPosition(149, 85);
		break;
	case 6:															// Sleepin Status Effect (can wake up)
		selfStatusEffect.setTexture(*loader.tryLoadTexture("SleepStatus", "Resources/Status/SleepIcon.png"));
		selfStatusEffect.setPosition(149, 85);
		break;
	case 7:															// Confusion Status Effect
		selfStatusEffect.setTexture(*loader.tryLoadTexture("ConfusionStatus", "Resources/Status/ConfusionIcon.png"));
		selfStatusEffect.setPosition(149, 85);
		break;
	case 8:															// Confusion Status Effect (can hit)
		selfStatusEffect.setTexture(*loader.tryLoadTexture("ConfusionStatus", "Resources/Status/ConfusionIcon.png"));
		selfStatusEffect.setPosition(149, 85);
		break;
	default:
		selfStatusEffect.setTexture(*loader.tryLoadTexture("NoStatus", "Resources/Status/NoStatusIcon.png"));
		selfStatusEffect.setPosition(149, 85);
		break;
	}

	//refresh();
}

void BattleScreen::keysPressed(std::vector<sf::Keyboard::Key> keys)//respond to key presses
{
	for (int i = 0; i < keys.size(); i++)
	{
		battleBar.keyPressed(keys[i]);
		if (keys[i] == sf::Keyboard::Z)//check if the user selected a move
		{
			if (battleBar.getState() == BattleBar::MOVESELECTED)
			{
				userInput = battleBar.getSelection() + 1;
				battleBar.resetState();
				cv.notify_all();
			}
			if (battleBar.getState() == BattleBar::SELECTION)
			{
				userInput = 5;
				cv.notify_all();
			}
		}
	}
	refresh();
}

void BattleScreen::setOppPokemon(Pokemon * p)
{
	oppPokemon = p;
	OpHealth.reset(oppPokemon->getHP(), oppPokemon->getMaxHP());
	OpPokemon.setTexture(*loader.tryLoadTexture("front" + itos(oppPokemon->getID()), "Resources/PokemonSprites/Front/" + itos(oppPokemon->getID()) + ".png"));
	OpName.setText(oppPokemon->getName());
}

void BattleScreen::setSelfPokemon(Pokemon * p)
{
	selfPokemon = p;
	SelfHealth.reset(selfPokemon->getHP(), selfPokemon->getMaxHP());
	SelfPokemon.setTexture(*loader.tryLoadTexture("back" + itos(selfPokemon->getID()), "Resources/PokemonSprites/Back/" + itos(selfPokemon->getID()) + ".png"));
	SelfName.setText(selfPokemon->getName());
	SelfHealth.reset(selfPokemon->getHP(), selfPokemon->getMaxHP());
	battleBar.setMoves(selfPokemon);
	refreshHealth();
}

void BattleScreen::setRandomBackground()
{
	int a = 1+rand() % 5;
	BackGround.setTexture(*loader.tryLoadTexture("BattleBackground" + itos(a), "Resources/Backgrounds/" + itos(a) + ".png"));
}

void BattleScreen::resetBattleBarState()
{
	battleBar.resetState();
}

void BattleScreen::showMessage(std::string message)
{
	battleBar.showMessage(message);
}

int BattleScreen::getUserInput()
{
	std::mutex mtx;
	std::unique_lock<std::mutex> lock(mtx);
	
	userInput = 0;

	cv.wait(lock);
	return userInput;
}

BattleBar::states BattleScreen::getBattleBarState()
{
	return battleBar.getState();
}

