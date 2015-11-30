#ifndef POKESELECTBOX_H
#define POKESELECTBOX_H
#include <SFML\Graphics.hpp>
#include "Pokemon.h"
#include "HealthBar.h"
#include "PokeText.h"
#include "functions.h"
#include "TextureLoader.h"
class PokeSelectBox : public sf::Drawable
{
	TextureLoader loader;
	sf::Sprite box, boxSelected, icon;
	sf::Font font;
	HealthBar bar;
	PokeText name, level, health;
	Pokemon *pokemon;
	sf::Vector2f pos;
	bool selected;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void setHealth(int hp, int maxHp);
public:
	PokeSelectBox(Pokemon *pokemon, sf::Vector2f position);
	PokeSelectBox(sf::Vector2f position);
	PokeSelectBox();
	void setPosition(sf::Vector2f position);
	void select();
	void deselect();
	void setPokemon(Pokemon *pokemon);
	~PokeSelectBox();
};

#endif