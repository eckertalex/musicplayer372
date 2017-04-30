// Music.hpp
// 29. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Maurphy (@alaska.edu)  
// 		Cameron Showalter (@alaska.edu) 
//
// Header for Music class

#ifndef MUSIC_HPP
#define MUSIC_HPP
#include <vector>
#include <SFML/Audio/Music.hpp>

class Music {
public:
	Music();

	sf::Music music;

	void callPlayPause();
	void callNextSong();
	void callPrevSong();
	void callIncreaseVolume();
	void callDecreaseVolume();
	void callMuteUnmute();
	void closeProgram();

private:

	std::vector<std::string> songList_;
	unsigned int songListIndex_ = 0;

	unsigned int volSave_;
	bool isMuted_;
};

#endif