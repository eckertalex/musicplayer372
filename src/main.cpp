// main.cpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Maurphy (jmurphy11@alaska.edu)  
// 		Cameron Showalter (cjshowalter@alaska.edu) 
//
// Main file for MusicPlayer372, the project from CS372 
// 		with Professor Chris Hartman

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "config.hpp"
#include "../include/musicPlayer.hpp"

//for testing with fileTreeMain(), delete later
#include <vector>
#include <string>
#include <algorithm>
#include "../include/directoryManager.hpp"
//end testing includes


int main()
{	
	std::cout << "MusicPlayer372" << std::endl;
	std::cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << std::endl;
	MusicPlayer musicPlayer;

	//temp testing for directoryManager.hpp
	//will delete soon
		std::vector<std::string> songList;
		songList = std::move(fileTreeMain());//moves vector of songs into songlist<string>
		//note: strings are in form "../res/audio/(songname)"
		std::cout << "Song List:" << std::endl;
		for(auto i=0; i<songList.size(); ++i)
		{
			std::cout << "   " << songList[i] << std::endl;
		}
		std::cout << "End list;" << std::endl << std::endl;
	//end delete soon



	if (!musicPlayer.music.openFromFile("../res/audio/AMemoryAway.ogg"))
	{
		return -1;
	}
	musicPlayer.music.play();
	
	musicPlayer.playerLoop();

	return 0;
}