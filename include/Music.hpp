// Music.hpp
// 29. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Murphy (jmurphy11@alaska.edu)
// 		Cameron Showalter (cjshowalter@alaska.edu)
//
// Header for Music class

#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <vector>
#include <memory>
#include <SFML/Audio/Music.hpp>

#include "directoryManager.hpp"

class Music {
public:
	Music();

	sf::Music _music;

	void callPlayPause();
	void callNextSong();
	void callPrevSong();
	void callIncreaseVolume();
	void callDecreaseVolume();
	void callMuteUnmute();
	void closeProgram();


	std::unique_ptr<DirectoryManager> dirmgr;
	std::vector<std::string> songList_;
	unsigned int songListIndex_ = 0;

	unsigned int volSave_;
	bool isMuted_;
};

#endif