#pragma once
#include "SFML\Graphics.hpp"
class BattleBar : public sf::Drawable
{
private:
	sf::Texture barTex;
	sf::Texture selectTex;
	sf::Texture moveSelectTex;
	sf::Texture arrowTex;

	sf::Sprite bar;
	sf::Sprite select;
	sf::Sprite moveSelect;
	sf::Sprite arrow;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void updateArrowPosition();

	bool selectingMove;
	int selected;
	sf::Vector2f selectPositions[4];
	sf::Vector2f movePositions[4];
public:
	BattleBar();
	void keyPressed(sf::Keyboard::Key key);
	void clicked(sf::Vector2i location);
	~BattleBar();
};

