#ifndef POKETEXT_H
#define POKETEXT_H
#include <SFML/Graphics.hpp>

class PokeText : public sf::Drawable
{
	//this class is used to render text in the 3rd gen pokemon game style
private:
	std::string words;
	sf::Text text, shadow;
	sf::Font *font;
	sf::Vector2f pos;
	bool hasShadow;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;//draw the text
public:
	PokeText();
	PokeText(std::string text, sf::Vector2f position, bool hasShadow, sf::Font *font, int fontSize);
	void setText(std::string text);//set the String
	void setPosition(sf::Vector2f position);//set the postition
	void move(sf::Vector2f delta);//move it from it's current position
	void setHasShadow(bool hasShadow);//should the text have a shadow
	void setLightText();
	void setDarkText();
};
#endif