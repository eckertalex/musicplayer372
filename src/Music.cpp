// Music.cpp
// 29. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Murphy (jmurphy11@alaska.edu)
// 		Cameron Showalter (@alaska.edu) 
//
// Source file for Music class

#include <iostream>
#include <memory>
#include <cmath>

#include "../include/Music.hpp"

Music::Music() {
	dirmgr = std::make_unique<DirectoryManager>();
	songList_ = std::move(dirmgr->getPlaylist());
	//if couldn't find song, don't try to play one
	if (songList_[songListIndex_] != "") {
		_music.openFromFile(songList_[songListIndex_]);
	}

	volSave_ = 100;
	isMuted_ = false;
}

void Music::callPlayPause() {
	if (_music.getStatus() != _music.Playing) {
		_music.play();
		std::cout << "Playing song: " << songList_[songListIndex_] << std::endl;
	}
	else {
		_music.pause();
	}
}

void Music::callNextSong() {
	if (songList_.size() != 0) {
		_music.stop();
		//if you're at the end, just go to the beginning (if press next)
		if (songListIndex_ == songList_.size() - 1) {
			songListIndex_ = 0;
		}
		else {
			songListIndex_ += 1;
		}
		_music.openFromFile(songList_[songListIndex_]);
		_music.play();
		std::cout << "Next song: " << songList_[songListIndex_] << " vecIndex: " << songListIndex_ << std::endl;
	}
}

void Music::callPrevSong() {
	if (songList_.size() != 0) {
		_music.stop();

		//if you're at the begining, just go to the end(if press prev)
		if (songListIndex_ == 0) {
			songListIndex_ = (unsigned int) (songList_.size() - 1);
		}
		else {
			songListIndex_ -= 1;
		}
		_music.openFromFile(songList_[songListIndex_]);
		_music.play();
		std::cout << "Previous song: " << songList_[songListIndex_] << " vecIndex: " << songListIndex_ << std::endl;
	}
}

void Music::callIncreaseVolume() {
	//first unmutes if muted
	if (isMuted_) {
		isMuted_ = false;
		_music.setVolume(volSave_); // unmute the music by restoring the volume to previous value
	}
	//if we change the " +1" for music.getVolume, make sure to reduce the "<= 99" in the if statement (100 - number) -CS
	if (_music.getVolume() <= 99) {
		_music.setVolume((float) ceil(_music.getVolume() + 1));
		std::cout << "The volume is " << _music.getVolume() << std::endl;
	}
}

void Music::callDecreaseVolume() {
	//first unmutes if muted
	if (isMuted_) {
		isMuted_ = false;
		_music.setVolume(volSave_); // unmute the music by restoring the volume to previous value
	}
	//if we change the " -1" for music.getVolume, make sure to change the ">= 1" in the if statement to the same value -CS
	if (_music.getVolume() >= 1) {
		_music.setVolume((float) floor(_music.getVolume() - 1));
		std::cout << "The volume is " << _music.getVolume() << std::endl;
	}
}

void Music::callMuteUnmute() {
	//if its not muted than set the volume to 0
	if (!isMuted_) {
		isMuted_ = true;
		volSave_ = (unsigned int) _music.getVolume();
		_music.setVolume(0);
		std::cout << "Muted player." << std::endl;
	}
	else {
		isMuted_ = false;
		_music.setVolume(volSave_); // unmute the music by restoring the volume to previous value
		std::cout << "Unmuted player." << std::endl;
	}
}

void Music::callSetVolume() {
	if (isMuted_) {
		isMuted_ = false;
	}
	_music.setVolume(volSave_);
	std::cout << "The volume is " << _music.getVolume() << std::endl;
}
