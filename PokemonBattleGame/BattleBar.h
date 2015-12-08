#ifndef BATTLEBAR_H
#define BATTLEBAR_H
#include "SFML\Graphics.hpp"
#include "PokeText.h"
#include "TextureLoader.h"
#include "Move.h"
#include "Pokemon.h"
#include "functions.h"
class BattleBar : public sf::Drawable
{
public: 
	enum states { ACTION, MOVE, TEXT, SELECTION };
	//This class is contains the selection at the bottom of the battle screen
private:
	//initialize variables for the required textures
	TextureLoader loader;

	sf::Sprite bar;
	sf::Sprite select;
	sf::Sprite moveSelect;
	sf::Sprite arrow;
	sf::Sprite moveSelectFrame;

	sf::Font font;
	PokeText displayText;
	PokeText moveText[4];
	PokeText PP;
	PokeText moveType;

	sf::Vector2i WIN_SIZE;

	Pokemon *pokemon;
	Move *moves[4];

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;//draw the object
	void updateArrowPosition();//update the positon of the arrow

	
	states state;
	int selected;//what is being selected (Fight,Bag, Pokemon, or Run) or (Move1, Move2, Move3,or Move4)
	sf::Vector2f selectPositions[4];//coordinates for the arrow in the option select screen
	sf::Vector2f movePositions[4];//coordinates for the arrow on the move select screen
public:
	BattleBar();
	void keyPressed(sf::Keyboard::Key key);//respond of the keys pressed
	void clicked(sf::Vector2i location);//respond to the position of the mouse click
	void setMoves(Pokemon *p);//load the moves from the given Pokemon class
	void setWinSize(sf::Vector2i size);
	void resetState();
	BattleBar::states getState();
	int getSelection();
	~BattleBar();
};

#endif