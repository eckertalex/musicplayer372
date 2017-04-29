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

void MusicPlayer::playerLoop() {
	while(gui->window.isOpen()) {
		gui->handleInput();
		gui->update();
		gui->draw();
	}
}
MusicPlayer::MusicPlayer() {
	//create full songlist
	music = Music();
	return;
}


void MusicPlayer::update() {
	
	mouseOverHighlight();
	displayPlaylist();

	return;
}

void MusicPlayer::playerLoop() {
	sf::Clock clock;

	while(window.isOpen()) {
		gui->handleInput();
		update();
		window.clear(sf::Color::White);
		draw();
		window.display();
	}
}

/****** Update Functions ******/
void MusicPlayer::mouseOverHighlight() {
	auto mousePosX = sf::Mouse::getPosition(window).x; // x position 
	auto mousePosY = sf::Mouse::getPosition(window).y; // y position

	if (music.getStatus() != sf::SoundSource::Status::Playing) {
		playPauseButton.setTexture(this->texmgr.getRef("playTex"));
		if ((mousePosX > 125 && mousePosX < 177) && (mousePosY > 216 && mousePosY < 268)) {
			playPauseButton.setTexture(this->texmgr.getRef("playTex2"));
		}
	}
	else {
		playPauseButton.setTexture(this->texmgr.getRef("pauseTex"));
		if ((mousePosX > 125 && mousePosX < 177) && (mousePosY > 216 && mousePosY < 268)) {
			playPauseButton.setTexture(this->texmgr.getRef("pauseTex2"));
		}
	}
	// mute the volume or unmute
	if(!isMuted_) {
		muteButton.setTexture(this->texmgr.getRef("muteTexv2"));
		if ((mousePosX > 38 && mousePosX < 84) && (mousePosY > 128 && mousePosY < 174)) {
		  	muteButton.setTexture(this->texmgr.getRef("muteTexv22"));
		}
	}
	else {
		muteButton.setTexture(this->texmgr.getRef("muteTex"));
		if ((mousePosX > 38 && mousePosX < 84) && (mousePosY > 128 && mousePosY < 174)) {
		  	muteButton.setTexture(this->texmgr.getRef("muteTex2"));
		}
	}
	//Previous song
	if ((mousePosX > 45 && mousePosX < 76) && (mousePosY > 216 && mousePosY < 268)) {
		prevButton.setTexture(this->texmgr.getRef("prevTex2"));
	}
	//Next Song
	else if ((mousePosX > 225 && mousePosX < 257) && (mousePosY > 216 && mousePosY < 268)) {
		nextButton.setTexture(this->texmgr.getRef("nextTex2"));
	}
	// // decrease volume
	else if ((mousePosX > 133 && mousePosX < 168) && (mousePosY > 128 && mousePosY < 174)) {
	    decreaseVolumeButton.setTexture(this->texmgr.getRef("decreaseVolumeTex2"));
	}
	// increase volume
	else if ((mousePosX > 218 && mousePosX < 264) && (mousePosY > 128 && mousePosY < 174)) {
		increaseVolumeButton.setTexture(this->texmgr.getRef("increaseVolumeTex2"));
	}
	else {
		prevButton.setTexture(this->texmgr.getRef("prevTex"));
		nextButton.setTexture(this->texmgr.getRef("nextTex"));
		decreaseVolumeButton.setTexture(this->texmgr.getRef("decreaseVolumeTex"));
		increaseVolumeButton.setTexture(this->texmgr.getRef("increaseVolumeTex"));
	}
}

void MusicPlayer::displayPlaylist() {
	if(songListIndex_ == 0) {
		prevSong.setString(trimFilename(songList_[songList_.size()-1]));
	}
	else {
		prevSong.setString(trimFilename(songList_[songListIndex_ - 1]));
	}

	currentSong.setString(trimFilename(songList_[songListIndex_]));

	if(songListIndex_ == songList_.size()-1) { 
		nextSong.setString(trimFilename(songList_[0]));
	}
	else {
		nextSong.setString(trimFilename(songList_[songListIndex_ + 1]));
	}

	if(songListIndex_ == songList_.size()-2) { 
		next2Song.setString(trimFilename(songList_[0]));
	}
	else if(songListIndex_ == songList_.size()-1) {
		next2Song.setString(trimFilename(songList_[1]));
	}
	else {
		next2Song.setString(trimFilename(songList_[songListIndex_ +2]));
	}

	if(songListIndex_ == songList_.size()-3) { 
		next3Song.setString(trimFilename(songList_[0]));
	}
	else if(songListIndex_ == songList_.size()-2) {
		next3Song.setString(trimFilename(songList_[1]));
	}
	else if(songListIndex_ == songList_.size()-1) {
		next3Song.setString(trimFilename(songList_[2]));
	}
	else {
		next3Song.setString(trimFilename(songList_[songListIndex_ + 3]));
	}

	if(songListIndex_ == songList_.size()-4) { 
		next4Song.setString(trimFilename(songList_[0]));
	}
	else if(songListIndex_ == songList_.size()-3) { 
		next4Song.setString(trimFilename(songList_[1]));
	}
	else if(songListIndex_ == songList_.size()-2) { 
		next4Song.setString(trimFilename(songList_[2]));
	}
	else if(songListIndex_ == songList_.size()-1) { 
		next4Song.setString(trimFilename(songList_[3]));
	}
	else {
		next4Song.setString(trimFilename(songList_[songListIndex_ + 4]));
	}
}