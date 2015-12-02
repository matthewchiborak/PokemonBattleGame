#ifndef BATTLESCREEN_H
#define BATTLESCREEN_H
#include <SFML\Graphics.hpp>
#include "PokeText.h"
#include "HealthBar.h"
#include "BattleBar.h"
#include "PokeSelectBox.h"
#include "TextureLoader.h"

class BattleScreen : public sf::Drawable
{
	//this class is the container for all of the GUI of hte battle screen
	//The GUI is rendered at the GBA native resolution (240 x 160) and then upscaled to the size of the window
private:
	//initialize the required variables
	sf::Font font;

	TextureLoader loader;

	Pokemon *oppPokemon, *selfPokemon;

	PokeText SelfName;
	PokeText OpName;
	PokeText HealthText;

	HealthBar OpHealth;
	HealthBar SelfHealth;

	BattleBar battleBar;

	sf::RenderTexture ScreenTex;

	sf::Sprite Screen;
	sf::Sprite OpInfo;
	sf::Sprite SelfInfo;
	sf::Sprite SelfInfoFrame;
	sf::Sprite BackGround;
	sf::Sprite OpPokemon;
	sf::Sprite SelfPokemon;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;//draw everything on to the render target
public:
	BattleScreen(const sf::Vector2i WIN_SIZE);//Constuctor, pass the size of the window you want it to upsample to.
	void refresh();//refresh the texture/image to be displayed
	void SetOPHealth(int health);//set the HP of the opponet
	void SetSelfHealth(int health);//set the health of the user's current pokemone
	void refreshHealth();
	void keysPressed(std::vector<sf::Keyboard::Key> key);//respond to pressed keys
	void setOppPokemon(Pokemon * p);
	void setSelfPokemon(Pokemon * p);
	void setRandomBackground();
};

#endif