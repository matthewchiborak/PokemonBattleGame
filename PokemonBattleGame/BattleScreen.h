#pragma once
#include <SFML\Graphics.hpp>
#include "PokeText.h"
#include "HealthBar.h"
#include "BattleBar.h"

class BattleScreen : public sf::Drawable
{
private:
	sf::Font font;

	PokeText SelfName;
	PokeText OpName;
	PokeText HealthText;

	HealthBar OpHealth;
	HealthBar SelfHealth;

	BattleBar battleBar;

	sf::RenderTexture ScreenTex;

	sf::Texture OpInfoTex;
	sf::Texture SelfInfoTex;
	sf::Texture SelfInfoFrameTex;
	sf::Texture BackgroundsTex;
	sf::Texture OpPokemonTex;
	sf::Texture SelfPokemonTex;


	sf::Sprite Screen;
	sf::Sprite OpInfo;
	sf::Sprite SelfInfo;
	sf::Sprite SelfInfoFrame;
	sf::Sprite BackGround;
	sf::Sprite OpPokemon;
	sf::Sprite SelfPokemon;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	BattleScreen(const sf::Vector2i WIN_SIZE);
	void refresh();
	void SetOPHealth(int health);
	void SetSelfHealth(int health);
	void keysPressed(std::vector<sf::Keyboard::Key> key);
};

