#pragma once
#include<SFML\Graphics.hpp>

class HealthBar : public sf::Drawable
{
private:
	sf::Color colours[8];
	sf::VertexArray verts;
	int HP, maxHP;
	sf::Vector2f topLeft, bottomRight;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update();//update the texture to render
public:
	HealthBar();//Empty
	~HealthBar();//Empty
	HealthBar(int health, int maxHealth, sf::Vector2f topLeft, sf::Vector2f bottomRight);//must be used to create a valid healthbar
	void setHealth(int health);//set the health value
	void reset(int health, int maxHealth);//set the health and max health
};
/*
HealthBar Info
Green = Bottom(112,248,168) Top(88,208,128)
Yellow = Bottom(248,224,56) Top(200,168,8)
Red = Bottom(248,88,56) Top(168,64,72)
Black = Bottom(80,104,88) Top(72,64,88)

OpPosition = (52,33) to (99,35)
SelfPositon = (187,88) to (234,90)
*/