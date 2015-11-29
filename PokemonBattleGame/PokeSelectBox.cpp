#include "PokeSelectBox.h"

PokeSelectBox::PokeSelectBox(Pokemon *pokemon, sf::Vector2f position)
{
	this->pokemon = pokemon;
	font.loadFromFile("Resources/EmeraldPro.ttf");
	iconTex.loadFromFile("Resources/PokemonSprites/MenuSprites/"+itos(pokemon->getID())+".png");
	boxTex.loadFromFile("Resources/pokemonSelection.png");
	boxSelectedTex.loadFromFile("Resources/pokemonSelection2.png");

	bar = HealthBar(pokemon->getHP(), pokemon->getMaxHP(), sf::Vector2f(0, 0), sf::Vector2f(48, 3));
	level = PokeText("50", sf::Vector2f(48, 14), true, &font, 15);
	level.setLightText();
	name = PokeText(pokemon->getName(), sf::Vector2f(0, 0), true, &font, 15);
	name.setLightText();
	health = PokeText("", sf::Vector2f(0, 0), true, &font, 15);
	setHealth(pokemon->getHP(), pokemon->getMaxHP());
	health.setHasShadow(true);
	health.setLightText();

	box.setTexture(boxTex);
	boxSelected.setTexture(boxSelectedTex);
	icon.setTexture(iconTex);
	icon.setOrigin(10, 10);

	setPosition(position);
	
}

PokeSelectBox::PokeSelectBox(sf::Vector2f position)
{
	font.loadFromFile("Resources/EmeraldPro.ttf");
	iconTex.loadFromFile("Resources/PokemonSprites/MenuSprites/213.png");
	boxTex.loadFromFile("Resources/pokemonSelection.png");
	boxSelectedTex.loadFromFile("Resources/pokemonSelection2.png");

	
	level = PokeText("50", sf::Vector2f(48, 14), true, &font, 15);
	level.setLightText();
	name = PokeText("SHUCKLE",sf::Vector2f(0,0),true,&font, 15);
	name.setLightText();

	health = PokeText("100/100", sf::Vector2f(0, 0), true, &font, 15);
	bar = HealthBar(100, 100, sf::Vector2f(0, 0), sf::Vector2f(48, 3));
	setHealth(100, 100);
	health.setHasShadow(true);
	health.setLightText();

	box.setTexture(boxTex);
	boxSelected.setTexture(boxSelectedTex);
	icon.setTexture(iconTex);
	icon.setOrigin(10, 10);

	setPosition(position);
}

PokeSelectBox::PokeSelectBox()
{
	font.loadFromFile("Resources/EmeraldPro.ttf");
	boxTex.loadFromFile("Resources/pokemonSelection.png");
	boxSelectedTex.loadFromFile("Resources/pokemonSelection2.png");

	bar = HealthBar(1, 1, sf::Vector2f(0, 0), sf::Vector2f(48, 3));
	level = PokeText("50", sf::Vector2f(48, 14), true, &font, 15);
	level.setLightText();
	name = PokeText("SHUCKLE!!!", sf::Vector2f(0, 0), true, &font, 15);
	name.setLightText();
	health = PokeText("100/100", sf::Vector2f(0, 0), true, &font, 15);
	health.setLightText();
	icon.setOrigin(10, 10);
	box.setTexture(boxTex);
	boxSelected.setTexture(boxSelectedTex);
}

void PokeSelectBox::setPosition(sf::Vector2f position)
{
	this->pos = position;
	box.setPosition(position);
	boxSelected.setPosition(position);
	icon.setPosition(position);
	bar.setPosition(pos + sf::Vector2f(96, 8));
	level.setPosition(pos + sf::Vector2f(48, 6));
	name.setPosition(pos + sf::Vector2f(30, -5));
	health.setPosition(pos + sf::Vector2f(100,6));

}

void PokeSelectBox::select()
{
	this->selected = true;
}

void PokeSelectBox::deselect()
{
	this->selected = false;
}

void PokeSelectBox::setPokemon(Pokemon *pokemon)
{
	this->pokemon = pokemon;
	iconTex.loadFromFile("Resources/PokemonSprites/MenuSprites/" + itos(pokemon->getID()) + ".png");
	icon.setTexture(iconTex);
	setHealth(pokemon->getHP(), pokemon->getMaxHP());
	name.setText(pokemon->getName());
}


PokeSelectBox::~PokeSelectBox()
{
}

void PokeSelectBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(bar,states);
	if (selected)
	{
		target.draw(boxSelected, states);
	}
	else
	{
		target.draw(box, states);
	}
	target.draw(icon, states);
	target.draw(name, states);
	target.draw(level, states);
	target.draw(health, states);
}

void PokeSelectBox::setHealth(int hp, int maxHp)
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
