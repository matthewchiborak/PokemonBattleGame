#include "BattleScreen.h"

void BattleScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(Screen);
}

BattleScreen::BattleScreen(const sf::Vector2i WIN_SIZE)
{
	ScreenTex.create(240, 160);

	Screen.setScale(sf::Vector2f(WIN_SIZE.x / 240, WIN_SIZE.y / 160));

	font.loadFromFile("Resources/EmeraldPro.ttf");

	SelfName = PokeText("CHARIZARD", sf::Vector2f(155, 68), true, &font, 16);
	OpName = PokeText("BLAZIKEN", sf::Vector2f(20, 13), true, &font, 16);
	HealthText = PokeText("25/ 60", sf::Vector2f(197, 87), true, &font, 15);


	OpInfoTex.loadFromFile("Resources/OpponetInfo.png");
	OpInfo.setTexture(OpInfoTex);
	OpInfo.setPosition(13, 16);


	SelfInfoTex.loadFromFile("Resources/SelfInfo.png");
	SelfInfo.setTexture(SelfInfoTex);
	SelfInfo.setPosition(134, 70);


	SelfInfoFrameTex.loadFromFile("Resources/SelfInfoFrame.png");
	SelfInfoFrame.setTexture(SelfInfoFrameTex);
	SelfInfoFrame.setPosition(134, 70);


	BackgroundsTex.loadFromFile("Resources/battleBackgrounds.png");
	BackGround.setTexture(BackgroundsTex);
	BackGround.setTextureRect(sf::IntRect(1, 1, 240, 160));


	OpPokemonTex.loadFromFile("Resources/blaziken.png");
	OpPokemon.setTexture(OpPokemonTex);
	OpPokemon.setPosition(140, 10);


	SelfPokemonTex.loadFromFile("Resources/Charizard.png");
	SelfPokemon.setTexture(SelfPokemonTex);
	SelfPokemon.setPosition(40, 50);

	OpHealth = HealthBar(30, 30, sf::Vector2f(52, 33), sf::Vector2f(100, 36));
	SelfHealth = HealthBar(25, 60, sf::Vector2f(187, 88), sf::Vector2f(235, 91));

	refresh();
	//ScreenTex.getTexture().copyToImage().saveToFile("ScreenShot.png");
}

void BattleScreen::refresh()
{
	ScreenTex.clear();

	ScreenTex.draw(BackGround);
	ScreenTex.draw(battleBar);
	ScreenTex.draw(OpPokemon);
	ScreenTex.draw(SelfPokemon);
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
	OpHealth.setHealth(health);
	refresh();
}

void BattleScreen::SetSelfHealth(int health)
{
	SelfHealth.setHealth(health);
	HealthText.setText(std::to_string(health) + "/ 60");
	refresh();
}

void BattleScreen::keyPressed(sf::Keyboard::Key key)
{
	battleBar.keyPressed(key);
	refresh();
}
