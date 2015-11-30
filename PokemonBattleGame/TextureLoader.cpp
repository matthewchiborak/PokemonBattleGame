#include "TextureLoader.h"

std::vector<Texture*> TextureLoader::textures;//initialize the static vector in TextureLoader

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

sf::Texture * TextureLoader::tryLoadTexture(std::string name, std::string location)
{
	sf::Texture* temp = getTexture(name);
	if (temp == nullptr)
	{
		loadTexture(name, location);
		return getTexture(name);
	}
	return temp;
}


TextureLoader::~TextureLoader()
{
	for (int i = 0; i < textures.size(); i++)
	{
		delete textures.at(i);
	}
	textures.clear();
}
