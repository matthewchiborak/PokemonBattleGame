#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include "SFML\Graphics.hpp"
#include <string>
#include <iostream>
#include <vector>
struct Texture// container used to associate a texture and a name
{
	sf::Texture tex;
	std::string name;
};

class TextureLoader
{
private:
	static std::vector<Texture*> textures;
public:

	TextureLoader();
	bool loadTexture(std::string name, std::string location);//try to load the texture at the give location and save it under the given name
	sf::Texture* getTexture(std::string name);//get a texture already loaded
	sf::Texture* tryLoadTexture(std::string name, std::string location);// if the texture is loaded return it, if not load it and then return it.
	~TextureLoader();//clean up pointers.
};

#endif
