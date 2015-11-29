#include "TextureLoader.h"



TextureLoader::TextureLoader()
{
}

bool TextureLoader::loadTexture(std::string name, std::string location)
{
	texture *temp = new texture;
	temp->name = name;
	if (temp->tex.loadFromFile(location))
	{
		textures.push_back(temp);
		return true;
	}
	return false;
}

sf::Texture * TextureLoader::getTexture(std::string name)
{
	for (int i = 0; i < textures.size(); i++)
	{
		if (textures[i]->name == name)
		{
			return &textures[i]->tex;
		}
	}
	return nullptr;
}


TextureLoader::~TextureLoader()
{
	for (int i = 0; i < textures.size(); i++)
	{
		delete textures[i];
	}
	textures.clear();
}
