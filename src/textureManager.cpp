// textureManager.cpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Murphy (@alaska.edu)
// 		Cameron Showalter (@alaska.edu) 
//
// Source file for textureManager

#include <SFML/Graphics.hpp>

#include "../include/textureManager.hpp"

void TextureManager::loadTexture(const std::string &name, const std::string &filename) {
	// Load the texture
	sf::Texture tex;
	tex.loadFromFile(filename);

	// Add it to the list of textures
	this->textures[name] = tex;

	return;
}

sf::Texture & TextureManager::getRef(const std::string &texture) {
	return this->textures.at(texture);
}