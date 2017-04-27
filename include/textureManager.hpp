// textureManager.hpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Maurphy (@alaska.edu)  
// 		Cameron Showalter (@alaska.edu) 
//
// Header for textureManager

#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <string>
using std::string;
#include <map>
using std::map;

class TextureManager
{

public:
	// Add a texture from a file
	void loadTexture(const string &name, const string &filename);

	// translate an id into a reference
	sf::Texture &getRef(const string &texture);

	TextureManager() {}

private:
	// Array for textures used
	map<string, sf::Texture> textures;
};


#endif // TEXTUREMANAGER_HPP