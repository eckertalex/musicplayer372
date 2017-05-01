// musicPlayer.cpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjacobson2@alaska.edu)  
// 		Jarye Murphy (jmurphy11@alaska.edu)
// 		Cameron Showalter (cjshowalter@alaska.edu) 
//
// Source file for MusicPlayer class

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstddef>

#include "../include/musicPlayer.hpp"


MusicPlayer::MusicPlayer() {
	inputmgr = std::make_unique<InputManager>();
}

void MusicPlayer::playerLoop() {
	while(inputmgr->gui->window.isOpen()) {
		inputmgr->handleInput();
		inputmgr->mouseOverHighlight();
		inputmgr->gui->update();
		inputmgr->gui->draw();
	}
}