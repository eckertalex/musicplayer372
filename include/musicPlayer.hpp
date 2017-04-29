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
	sf::SoundBuffer buffer;
	sf::Music music;

	void playerLoop();

	MusicPlayer();
	~MusicPlayer() = default;

	void draw();
	void update();
	void handleInput();
private:

	void callPlayPause();
	void callNextSong();
	void callPrevSong();
	void callIncreaseVolume();
	void callDecreaseVolume();
	void callMuteUnmute();
	void closeProgram();
	
	/****** Update Functions ******/
	void mouseOverHighlight();
	void displayPlaylist();

private:
	void loadTextures();
	std::vector<std::string> songList_;
	unsigned int songListIndex_ = 0;

	unsigned int volSave_;
	bool isMuted_;

	std::unique_ptr<GUI> gui;
};

#endif // #ifndef MUSICPLAYER_HPP
