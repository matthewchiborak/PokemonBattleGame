#ifndef POKESELECTBOXLARGE_H
#define POKESELECTBOXLARGE_H

#include <SFML\Graphics.hpp>
#include "Pokemon.h"
#include "HealthBar.h"
#include "PokeText.h"
#include "functions.h"
#include "TextureLoader.h"
class PokeSelectBoxLarge : public sf::Drawable
{
	TextureLoader loader;
	sf::Sprite box, icon;
	sf::Font font;
	HealthBar bar;
	PokeText name, level, health;
	Pokemon *pokemon;
	sf::Vector2f pos;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	

public:
	PokeSelectBoxLarge();
	PokeSelectBoxLarge(sf::Vector2f position);
	~PokeSelectBoxLarge();
	void setPosition(sf::Vector2f position);
	void setPokemon(Pokemon *pokemon);
	void setHealth(int hp, int maxHp);
};

#endif