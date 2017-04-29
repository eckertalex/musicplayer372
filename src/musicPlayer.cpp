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

void MusicPlayer::draw() {
	gui->draw();
	return;
}

void MusicPlayer::update() {
	gui->update();
	return;
}

void MusicPlayer::handleInput() {
	gui->handleInput();
	return;
}

void MusicPlayer::playerLoop() {
	while(gui->window.isOpen()) {
		gui->handleInput();
		gui->update();
		gui->draw();
	}
}

MusicPlayer::MusicPlayer() {
	//create full songlist
	songList_ = std::move(fileTreeMain());
	//if couldn't find song, don't try to play one
	if( songList_[songListIndex_] != "" )
	{
		music.openFromFile(songList_[songListIndex_]);
	}

	//print for testing, delete later
	printVec(songList_);

	volSave_ = 100;
	isMuted_ = false;

	std::cout << "MusicPlayer initialized" << std::endl;
}

/****** Functionality Function Definitions ******/

void MusicPlayer::callPlayPause() {
	if (music.getStatus() != music.Playing) {
		music.play();
		std::cout << "Playing song: " << songList_[songListIndex_] << std::endl;
	}
	else {
		music.pause();
	}
}

void MusicPlayer::callNextSong() {
	if(songList_.size() != 0) {
		music.stop();
		//if you're at the end, just go to the begining(if press next)
		if(songListIndex_ == songList_.size()-1) {
			songListIndex_ = 0;
		}
		else {
			songListIndex_ += 1;
		}
		music.openFromFile(songList_[songListIndex_]);
		music.play();
		std::cout << "Next song: " << songList_[songListIndex_] << " vecIndex: " << songListIndex_ << std::endl;
	}
}

void MusicPlayer::callPrevSong() {
	if(songList_.size() != 0) {
		music.stop();

		//if you're at the begining, just go to the end(if press prev)
		if(songListIndex_ == 0) {
			songListIndex_ = songList_.size()-1;
		}
		else {
			songListIndex_ -= 1;
		}
		music.openFromFile(songList_[songListIndex_]);
		music.play();
		std::cout << "Previous song: " << songList_[songListIndex_] << " vecIndex: " << songListIndex_ << std::endl;
	}
}

void MusicPlayer::callIncreaseVolume() {
	//first unmutes if muted
	if(isMuted_ == true)
	{
		isMuted_=  false;
		music.setVolume(volSave_); // unmute the music by restoring the volume to previous value
	}
	//if we change the " +1" for music.getVolume, make sure to reduce the "<= 99" in the if statement (100 - number) -CS
	if(music.getVolume() <= 99){
		music.setVolume(music.getVolume() + 1);
		std::cout << "The volume is " << music.getVolume() << std::endl;
	}
}

void MusicPlayer::callDecreaseVolume() {
	//first unmutes if muted
	if(isMuted_ == true)
	{
		isMuted_=  false;
		music.setVolume(volSave_); // unmute the music by restoring the volume to previous value
	}
	//if we change the " -1" for music.getVolume, make sure to change the ">= 1" in the if statement to the same value -CS
	if(music.getVolume() >= 1){
		music.setVolume(music.getVolume() - 1);
		std::cout << "The volume is " << music.getVolume() << std::endl;
	}
}

void MusicPlayer::callMuteUnmute() {
	//if its not muted than set the volume to 0
	if (isMuted_ == false) {
		isMuted_ = true;
		volSave_ = music.getVolume();
		music.setVolume(0);
		std::cout << "Muted player." << std::endl;
	}
	else {
		isMuted_=  false;
		music.setVolume(volSave_); // unmute the music by restoring the volume to previous value
		std::cout << "Unmuted player." << std::endl;
	}
}
