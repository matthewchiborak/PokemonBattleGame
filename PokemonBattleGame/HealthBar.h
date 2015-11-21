#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include<SFML\Graphics.hpp>

class HealthBar : public sf::Drawable
{
	//A class that handles the rendering of health bars on the battlescreen
private:
	sf::Color colours[8];//a array of colours to use
	sf::VertexArray verts;// the vertexes used to draw the health bar
	int HP, maxHP;// to store the current and max health values
	sf::Vector2f topLeft, bottomRight;//the area across where to draw the healthbar (must not be more than 3 pixels high)
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;//draw the healthbar
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
#endif