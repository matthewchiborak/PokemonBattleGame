#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include "SFML\Graphics.hpp"
#include <string>
#include <iostream>
#include <vector>
class TextureLoader
{
	struct texture// container used to associate a texture and a name
	{
		sf::Texture tex;
		std::string name;
	};

	static std::vector<texture*> textures;

public:
	TextureLoader();
	bool loadTexture(std::string name, std::string location);//try to load the texture at the give location and save it under the given name
	sf::Texture* getTexture(std::string name);//get a texture already loaded
	~TextureLoader();//clean up pointers.
};

#endif