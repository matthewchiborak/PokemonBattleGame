#include "PokeSelectBoxLarge.h"



PokeSelectBoxLarge::PokeSelectBoxLarge()
{
	font.loadFromFile("Resources/EmeraldPro.ttf");

	box.setTexture(*loader.tryLoadTexture("PokeSelectLarge","Resources/pokemonSelectBox.png"));
	icon.setTexture(*loader.tryLoadTexture("icon213", "Resources/PokemonSprites/MenuSprites/213.png"));
	icon.setOrigin(10, 10);
	
	name = PokeText("SHUCKLE!!!",sf::Vector2f(0,0),true,&font,16);
	level = PokeText("50", sf::Vector2f(0, 0), true, &font, 16);
	health = PokeText("100/100", sf::Vector2f(0, 0), true, &font, 16);

	setPosition(sf::Vector2f(0, 0));

}


PokeSelectBoxLarge::~PokeSelectBoxLarge()
{
}

void PokeSelectBoxLarge::setPosition(sf::Vector2f position)
{
	this->pos = position;
	box.setPosition(this->pos);
	icon.setPosition(this->pos);
	bar.setPosition(this->pos + sf::Vector2f(29, 38));
	name.setPosition(this->pos + sf::Vector2f(20, 30));
	level.setPosition(this->pos + sf::Vector2f(47, 27));
	health.setPosition(this->pos + sf::Vector2f(48, 44));
}
