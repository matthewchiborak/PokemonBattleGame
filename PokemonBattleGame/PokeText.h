#ifndef POKETEXT_H
#define POKETEXT_H
#include <SFML/Graphics.hpp>

class PokeText : public sf::Drawable
{
private:
	std::string words;
	sf::Text text, shadow;
	sf::Font *font;
	sf::Vector2f pos;
	bool hasShadow;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	PokeText();
	PokeText(std::string text, sf::Vector2f position, bool hasShadow, sf::Font *font, int fontSize);
	void setText(std::string text);
	void setPosition(sf::Vector2f position);
	void move(sf::Vector2f delta);
	void setHasShadow(bool hasShadow);
};
#endif