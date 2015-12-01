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
	HealthText = PokeText("25/ 60", sf::Vector2f(197, 87), true, &font, 15);


	OpInfo.setTexture(*loader.tryLoadTexture("OpInfo","Resources/OpponetInfo.png"));
	OpInfo.setPosition(13, 16);

	SelfInfo.setTexture(*loader.tryLoadTexture("SelfInfo", "Resources/SelfInfo.png"));
	SelfInfo.setPosition(134, 70);

	SelfInfoFrame.setTexture(*loader.tryLoadTexture("SelfInfoFrame", "Resources/SelfInfoFrame.png"));
	SelfInfoFrame.setPosition(134, 70);

	BackGround.setTexture(*loader.tryLoadTexture("BattleBackgrounds", "Resources/battleBackgrounds.png"));
	BackGround.setTextureRect(sf::IntRect(1, 1, 240, 160));

	OpPokemon.setTexture(*loader.tryLoadTexture("front257", "Resources/PokemonSprites/Front/257.png"));
	OpPokemon.setPosition(140, 10);

	SelfPokemon.setTexture(*loader.tryLoadTexture("back6", "Resources/PokemonSprites/Back/6.png"));
	SelfPokemon.setPosition(40, 54);

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

	ScreenTex.display();
	Screen.setTexture(ScreenTex.getTexture());
}

void BattleScreen::SetOPHealth(int health)
{
	//change the opponet's healthbar and refresh the screen
	OpHealth.setHealth(health);
	refresh();
}

void BattleScreen::SetSelfHealth(int health)
{
	//change the user's health bar and health text. refresh the screen
	SelfHealth.setHealth(health);
	HealthText.setText(std::to_string(health) + "/600");
	refresh();
}

void BattleScreen::keysPressed(std::vector<sf::Keyboard::Key> keys)//respond to key presses
{
	for (int i = 0; i < keys.size(); i++)
	{
		battleBar.keyPressed(keys[i]);
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
}

