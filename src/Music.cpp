/****** Functionality Function Definitions ******/

#include "../include/Music.hpp"
#include <iostream>
#include "../include/directoryManager.hpp"

Music::Music()
{
	//directoryM
	songList_ = std::move(fileTreeMain());
	//if couldn't find song, don't try to play one
	if (songList_[songListIndex_] != "")
	{
		music.openFromFile(songList_[songListIndex_]);
	}

	volSave_ = 100;
	isMuted_ = false;
}

void Music::callPlayPause() {
	if (music.getStatus() != music.Playing) {
		music.play();
		std::cout << "Playing song: " << songList_[songListIndex_] << std::endl;
	}
	else {
		music.pause();
	}
}

void Music::callNextSong() {
	if (songList_.size() != 0) {
		music.stop();
		//if you're at the end, just go to the begining(if press next)
		if (songListIndex_ == songList_.size() - 1) {
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

void Music::callPrevSong() {
	if (songList_.size() != 0) {
		music.stop();

		//if you're at the begining, just go to the end(if press prev)
		if (songListIndex_ == 0) {
			songListIndex_ = songList_.size() - 1;
		}
		else {
			songListIndex_ -= 1;
		}
		music.openFromFile(songList_[songListIndex_]);
		music.play();
		std::cout << "Previous song: " << songList_[songListIndex_] << " vecIndex: " << songListIndex_ << std::endl;
	}
}

void Music::callIncreaseVolume() {
	//first unmutes if muted
	if (isMuted_ == true)
	{
		isMuted_ = false;
		music.setVolume(volSave_); // unmute the music by restoring the volume to previous value
	}
	//if we change the " +1" for music.getVolume, make sure to reduce the "<= 99" in the if statement (100 - number) -CS
	if (music.getVolume() <= 99) {
		music.setVolume(music.getVolume() + 1);
		std::cout << "The volume is " << music.getVolume() << std::endl;
	}
}

void Music::callDecreaseVolume() {
	//first unmutes if muted
	if (isMuted_ == true)
	{
		isMuted_ = false;
		music.setVolume(volSave_); // unmute the music by restoring the volume to previous value
	}
	//if we change the " -1" for music.getVolume, make sure to change the ">= 1" in the if statement to the same value -CS
	if (music.getVolume() >= 1) {
		music.setVolume(music.getVolume() - 1);
		std::cout << "The volume is " << music.getVolume() << std::endl;
	}
}

void Music::callMuteUnmute() {
	//if its not muted than set the volume to 0
	if (isMuted_ == false) {
		isMuted_ = true;
		volSave_ = music.getVolume();
		music.setVolume(0);
		std::cout << "Muted player." << std::endl;
	}
	else {
		isMuted_ = false;
		music.setVolume(volSave_); // unmute the music by restoring the volume to previous value
		std::cout << "Unmuted player." << std::endl;
	}
}