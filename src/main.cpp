// main.cpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Murphy (jmurphy11@alaska.edu)
// 		Cameron Showalter (cjshowalter@alaska.edu) 
//
// Main file for MusicPlayer372, the project from CS372 
// 		with Professor Chris Hartman

#include <iostream>

#include "../include/musicPlayer.hpp"

int main()
{	
	std::cout << "MusicPlayer372" << std::endl;
	std::cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << std::endl;
	MusicPlayer musicPlayer;
	
	musicPlayer.playerLoop();

	return 0;
}