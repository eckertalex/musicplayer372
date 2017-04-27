// main.cpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Maurphy (jmurphy11@alaska.edu)  
// 		Cameron Showalter (@alaska.edu) 
//
// Main file for MusicPlayer372, the project from CS372 
// 		with Professor Chris Hartman

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "config.hpp"
#include "../include/musicPlayer.hpp"

int main()
{	
	std::cout << "MusicPlayer372" << std::endl;
	std::cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << std::endl;
	MusicPlayer musicPlayer;
	
	if (!musicPlayer.music.openFromFile("../res/audio/currency.wav"))
	{
		return -1;
	}
	musicPlayer.music.play();
	
	musicPlayer.playerLoop();

	return 0;
}