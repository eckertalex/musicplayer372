// textureManager.hpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Murphy (@alaska.edu)
// 		Cameron Showalter (@alaska.edu) 
//
// Header for textureManager

#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager {
public:
	// Add a texture from a file
	void loadTexture(const std::string &name, const std::string &filename);

	// translate an id into a reference
	sf::Texture &getRef(const std::string &texture);

	TextureManager() {}

private:
	// Array for textures used
	std::map<std::string, sf::Texture> textures;
};


#endif // TEXTUREMANAGER_HPP