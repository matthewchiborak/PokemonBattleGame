#include "HealthBar.h"



void HealthBar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(verts, states);
}

void HealthBar::update()
{
	float size = (bottomRight.x - topLeft.x);
	float middle = size * ((float)HP / maxHP);
	verts.resize(16);
	//top left rect
	verts[0].position = sf::Vector2f(topLeft);
	verts[1].position = sf::Vector2f(topLeft + sf::Vector2f(middle, 0));
	verts[2].position = sf::Vector2f(topLeft + sf::Vector2f(middle, 1));
	verts[3].position = sf::Vector2f(topLeft + sf::Vector2f(0, 1));

	//bottom left rect
	verts[4].position = sf::Vector2f(topLeft + sf::Vector2f(0, 1));
	verts[5].position = sf::Vector2f(topLeft + sf::Vector2f(middle, 1));
	verts[6].position = sf::Vector2f(topLeft + sf::Vector2f(middle, 3));
	verts[7].position = sf::Vector2f(topLeft + sf::Vector2f(0, 3));

	//colour left rects
	if (((float)HP / maxHP) < 0.2f)//red health bar
	{
		verts[0].color = colours[2];
		verts[1].color = colours[2];
		verts[2].color = colours[2];
		verts[3].color = colours[2];

		verts[4].color = colours[6];
		verts[5].color = colours[6];
		verts[6].color = colours[6];
		verts[7].color = colours[6];
	}
	else if (((float)HP / maxHP) < 0.5f)//yellow healthbar
	{
		verts[0].color = colours[1];
		verts[1].color = colours[1];
		verts[2].color = colours[1];
		verts[3].color = colours[1];

		verts[4].color = colours[5];
		verts[5].color = colours[5];
		verts[6].color = colours[5];
		verts[7].color = colours[5];
	}

	else//green health bar
	{
		verts[0].color = colours[0];
		verts[1].color = colours[0];
		verts[2].color = colours[0];
		verts[3].color = colours[0];

		verts[4].color = colours[4];
		verts[5].color = colours[4];
		verts[6].color = colours[4];
		verts[7].color = colours[4];
	}

	//bottom right rect
	verts[8].position = sf::Vector2f(bottomRight);
	verts[9].position = sf::Vector2f(bottomRight - sf::Vector2f(0, 2));
	verts[10].position = sf::Vector2f(bottomRight - sf::Vector2f(size - middle, 2));
	verts[11].position = sf::Vector2f(bottomRight - sf::Vector2f(size - middle, 0));

	verts[8].color = colours[7];
	verts[9].color = colours[7];
	verts[10].color = colours[7];
	verts[11].color = colours[7];

	//top right rect
	verts[12].position = sf::Vector2f(bottomRight - sf::Vector2f(0, 2));
	verts[13].position = sf::Vector2f(bottomRight - sf::Vector2f(size - middle, 2));
	verts[14].position = sf::Vector2f(bottomRight - sf::Vector2f(size - middle, 3));
	verts[15].position = sf::Vector2f(bottomRight - sf::Vector2f(0, 3));

	verts[12].color = colours[3];
	verts[13].color = colours[3];
	verts[14].color = colours[3];
	verts[15].color = colours[3];
}

HealthBar::HealthBar()
{
}


HealthBar::~HealthBar()
{
}

HealthBar::HealthBar(int health, int maxHealth, sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
	this->HP = health;
	this->maxHP = maxHealth;
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
	colours[0] = sf::Color(88, 208, 128);//GreenTop
	colours[1] = sf::Color(200, 168, 8);//YellowTop
	colours[2] = sf::Color(168, 64, 72);//RedTop
	colours[3] = sf::Color(72, 64, 88);//GreyTop
	colours[4] = sf::Color(112, 248, 168);//GreenBottom
	colours[5] = sf::Color(248, 224, 56);//YellowBottom
	colours[6] = sf::Color(248, 88, 56);//RedBottom
	colours[7] = sf::Color(80, 104, 88);//GreyBottom
	verts.setPrimitiveType(sf::Quads);
	verts.resize(16);
	update();
}

void HealthBar::setHealth(int health)
{
	this->HP = health;
	update();
}

void HealthBar::reset(int health, int maxHealth)
{
	this->HP = health;
	this->maxHP = maxHealth;
	update();
}

void HealthBar::setPosition(sf::Vector2f position)
{
	sf::Vector2f size = bottomRight - topLeft;
	topLeft = position;
	bottomRight = topLeft + size;
	update();
}

void HealthBar::setPosition(sf::Vector2f topleft, sf::Vector2f bottomRight)
{
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
	update();
}

