// musicPlayer.cpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjacobson2@alaska.edu)  
// 		Jarye Maurphy (jmurphy11@alaska.edu)  
// 		Cameron Showalter (cjshowalter@alaska.edu) 
//
// Source file for MusicPlayer class

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <cstddef>

#include "../include/textureManager.hpp"
#include "../include/musicPlayer.hpp"
#include "../include/directoryManager.hpp" // for fileTreeMain()

MusicPlayer::MusicPlayer() {
	//create full songlist
	music = std::make_shared<Music>();
	gui = std::make_shared<GUI>(music);
	return;
}

void MusicPlayer::playerLoop() {
	while(gui->window.isOpen()) {
		gui->handleInput();
		gui->update();
		gui->draw();
	}
}