// InputManager.hpp
// 29. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Maurphy (@alaska.edu)  
// 		Cameron Showalter (@alaska.edu) 
//
// Header for InputManager class

#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "GUI.hpp"
#include "Music.hpp"
#include <memory>
#include <SFML/Graphics.hpp>

class GUI;

class InputManager {
public:
	InputManager();
	void handleInput();

	void mouseOverHighlight();
	bool clickInSprite(sf::Sprite s, int x, int y);
	std::shared_ptr<Music> music;
	std::shared_ptr<GUI> gui;
};

#endif