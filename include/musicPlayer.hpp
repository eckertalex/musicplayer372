// musicPlayer.hpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Maurphy (@alaska.edu)  
// 		Cameron Showalter (@alaska.edu) 
//
// Header for MusicPlayer class

#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include <vector>
#include <memory>

#include "GUI.hpp"

// define version numbers
// set in CMakeLists.txt file
#define myproject_VERSION_MAJOR 0
#define myproject_VERSION_MINOR 1

class MusicPlayer {
public:
	void playerLoop();

	MusicPlayer();
	~MusicPlayer() = default;

	void update();

private:

	std::shared_ptr<GUI> gui;
	std::shared_ptr<Music> music;
};

#endif // #ifndef MUSICPLAYER_HPP
