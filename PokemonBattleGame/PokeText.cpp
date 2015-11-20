#include "PokeText.h"
void PokeText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (hasShadow) 
	{
		target.draw(shadow, states);
	}
	target.draw(text, states);
}

PokeText::PokeText() {}
PokeText::PokeText(std::string text, sf::Vector2f position, bool hasShadow, sf::Font *font, int fontSize)
{
	this->words = text;
	this->pos = position;
	this->font = font;
	this->text.setString(words);
	this->text.setCharacterSize(fontSize);
	this->text.setFont(*font);
	this->text.setPosition(this->pos);
	this->text.setColor(sf::Color(72, 72, 72));
	this->hasShadow = hasShadow;
	this->shadow.setString(words);
	this->shadow.setCharacterSize(fontSize);
	this->shadow.setFont(*font);
	this->shadow.setPosition(this->pos + sf::Vector2f(1, 1));
	this->shadow.setColor(sf::Color(208, 208, 200));
}
void PokeText::setText(std::string text)
{
	this->text.setString(text);
	this->shadow.setString(text);
}
void PokeText::setPosition(sf::Vector2f position)
{
	this->pos = position;
}
void PokeText::move(sf::Vector2f delta)
{
	this->pos += delta;
}

void PokeText::setHasShadow(bool hasShadow)
{
	this->hasShadow = hasShadow;
}
