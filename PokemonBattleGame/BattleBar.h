#ifndef BATTLEBAR_H
#define BATTLEBAR_H
#include "SFML\Graphics.hpp"
#include "PokeText.h"
#include "TextureLoader.h"
class BattleBar : public sf::Drawable
{
	//This class is contains the selection at the bottom of the battle screen
private:
	//initialize variables for the required textures
	TextureLoader loader;

	sf::Sprite bar;
	sf::Sprite select;
	sf::Sprite moveSelect;
	sf::Sprite arrow;

	sf::Font font;
	PokeText displayText;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;//draw the object
	void updateArrowPosition();//update the positon of the arrow

	enum states {ACTION,MOVE,TEXT};
	states state;
	int selected;//what is being selected (Fight,Bag, Pokemon, or Run) or (Move1, Move2, Move3,or Move4)
	sf::Vector2f selectPositions[4];//coordinates for the arrow in the option select screen
	sf::Vector2f movePositions[4];//coordinates for the arrow on the move select screen
public:
	BattleBar();
	void keyPressed(sf::Keyboard::Key key);//respond of the keys pressed
	void clicked(sf::Vector2i location);//respond to the position of the mouse click
	~BattleBar();
};

#endif