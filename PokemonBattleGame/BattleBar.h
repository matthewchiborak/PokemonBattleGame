#ifndef BATTLEBAR_H
#define BATTLEBAR_H
#include "SFML\Graphics.hpp"
#include "PokeText.h"
#include "TextureLoader.h"
#include "Move.h"
#include "Pokemon.h"
#include "functions.h"
#include <condition_variable>
class BattleBar : public sf::Drawable
{
public: 
	enum states { ACTION, MOVE, TEXT, SELECTION, MOVESELECTED }; // the states
	/*
	ACTION = selecting from Fight, Pokemon, "Bag" or "Run"
	MOVE = selecting from the pokemon's move list
	TEXT = waiting for the user to confirm a message
	SELECTION = waiting for the user to select a pokemon
	MOVESELECTED = the user has selected a move to use
	*/
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

	Pokemon *pokemon;
	Move *moves[4];

	std::condition_variable cv;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;//draw the object
	void updateArrowPosition();//update the positon of the arrow

	
	states state;
	int selected;//what is being selected (Fight,Bag, Pokemon, or Run) or (Move1, Move2, Move3,or Move4)
	/*
	+------+
	| 0  1 |
	| 2  3 |
	+------+
	*/
	sf::Vector2f selectPositions[4];//coordinates for the arrow in the option select screen
	sf::Vector2f movePositions[4];//coordinates for the arrow on the move select screen
public:
	BattleBar();
	void keyPressed(sf::Keyboard::Key key);//respond of the keys pressed
	void clicked(sf::Vector2i location);//respond to the position of the mouse click
	void setMoves(Pokemon *p);//load the moves from the given Pokemon class
	void resetState();//sets the state to ACTION, and selected to 0 (top left)
	BattleBar::states getState();//returns the current state
	int getSelection();//returns the selection (1 - 4)
	void showMessage(std::string message);//display a message that the user must confirm( will block untill the user confirms)
	~BattleBar();
};

#endif