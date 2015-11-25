#ifndef POKESELECTBOX_H
#define POKESELECTBOX_H
#include <SFML\Graphics.hpp>
#include "Pokemon.h"
#include "HealthBar.h"
#include "PokeText.h"
class PokeSelectBox : public sf::Drawable
{
	sf::Texture boxTex, boxSelectedTex, iconTex;
	sf::Sprite box, icon;
	sf::Font font;
	HealthBar bar;
	PokeText name, level, health;
	Pokemon *pokemon;
	sf::Vector2f pos;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
public:
	PokeSelectBox(Pokemon *pokemon, sf::Vector2f position);//not working yet
	PokeSelectBox(sf::Vector2f position);
	void setPosition(sf::Vector2f position);
	~PokeSelectBox();

	
};

#endif