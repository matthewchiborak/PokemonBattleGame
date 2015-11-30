#include "PokeSelectBoxLarge.h"

void PokeSelectBoxLarge::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(bar, states);
	target.draw(box,states);
	target.draw(icon, states);
	target.draw(name, states);
	target.draw(level , states);
	target.draw(health, states);
}

PokeSelectBoxLarge::PokeSelectBoxLarge()
{
	font.loadFromFile("Resources/EmeraldPro.ttf");

	box.setTexture(*loader.tryLoadTexture("PokeSelectLarge","Resources/pokemonSelectBox.png"));
	icon.setTexture(*loader.tryLoadTexture("icon213", "Resources/PokemonSprites/MenuSprites/213.png"));
	icon.setOrigin(10, 10);
	
	name = PokeText("SHUCKLE!!!",sf::Vector2f(0,0),true,&font,16);
	level = PokeText("50", sf::Vector2f(0, 0), true, &font, 16);
	health = PokeText("100/100", sf::Vector2f(0, 0), true, &font, 16);

	name.setLightText();
	level.setLightText();
	health.setLightText();

	bar = HealthBar(100, 100, sf::Vector2f(0, 0),sf::Vector2f(49,3));

	setPosition(sf::Vector2f(0, 0));
	setHealth(100, 100);
}

PokeSelectBoxLarge::PokeSelectBoxLarge(sf::Vector2f position)
{
	PokeSelectBoxLarge();
	setPosition(position);
}


PokeSelectBoxLarge::~PokeSelectBoxLarge()
{
}

void PokeSelectBoxLarge::setPosition(sf::Vector2f position)
{
	this->pos = position;
	box.setPosition(this->pos);
	icon.setPosition(this->pos);
	bar.setPosition(this->pos + sf::Vector2f(29, 39));
	name.setPosition(this->pos + sf::Vector2f(23, 7));
	level.setPosition(this->pos + sf::Vector2f(47, 19));
	health.setPosition(this->pos + sf::Vector2f(38, 37));
}

void PokeSelectBoxLarge::setPokemon(Pokemon * pokemon)
{
	this->pokemon = pokemon;
	icon.setTexture(*loader.tryLoadTexture("icon" + itos(pokemon->getID()), "Resources/PokemonSprites/MenuSprites/" + itos(pokemon->getID()) + ".png"));
	name.setText(pokemon->getName());
	setHealth(pokemon->getHP(), pokemon->getMaxHP());
}

void PokeSelectBoxLarge::setHealth(int hp, int maxHp)
{
	std::stringstream s;
	if (hp < 10)
	{
		s << "  " << hp;
	}
	else if (hp < 100)
	{
		s << " " << hp;
	}
	else
	{
		s << hp;
	}
	s << "/";
	if (maxHp < 10)
	{
		s << "  " << maxHp;
	}
	else if (maxHp < 100)
	{
		s << " " << maxHp;
	}
	else
	{
		s << maxHp;
	}
	health.setText(s.str());
	bar.reset(hp, maxHp);
}
