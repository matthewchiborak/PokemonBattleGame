#include "TextureLoader.h"

TextureLoader::TextureLoader()
{
}

bool TextureLoader::loadTexture(std::string name, std::string location)
{
	Texture *temp = new Texture;
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
		if (textures.at(i)->name == name)
		{
			return &textures.at(i)->tex;
		}
	}
	return nullptr;
}


TextureLoader::~TextureLoader()
{
	for (int i = 0; i < textures.size(); i++)
	{
		delete textures.at(i);
	}
	textures.clear();
}
