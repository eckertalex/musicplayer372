// GUI.cpp
// 29. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Murphy (jmurphy11@alaska.edu)
// 		Cameron Showalter (@alaska.edu) 
//
// Source file for GUI class

#include <SFML/Graphics.hpp>

#include "../include/GUI.hpp"

GUI::GUI(std::shared_ptr<Music> music) : music(music) {
	texmgr = std::make_unique<TextureManager>();
	timer = std::make_unique<Timer>(music);
	loadTextures();
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MusicPlayer",
		sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	setTextures();
	stylePlaylist();
	volumeBar.rotate(270);
	volumeBar.setPosition(307, 245);
	sf::Color lineColor(0x080A58ff);
	volumeBar.setFillColor(lineColor);
	if(!font.loadFromFile("../res/fonts/TravelingTypewriter.ttf"))
		std::cout << "Font couldn't be found" << std::endl;
	else
		std::cout << "Font was found" << std::endl;

	spriteVec = {
			playPauseButton,			// 0
			prevButton, 				// 1
			nextButton, 				// 2
			muteButton, 				// 3
			decreaseVolumeButton, 		// 4
			increaseVolumeButton		// 5
	};
}

std::string GUI::trimFilename(const std::string& str, unsigned long cutoff) {
	std::size_t foundSlash = str.find_last_of("/\\");
	std::string temp = str.substr(foundSlash+1);
	std::size_t foundDot = temp.find_last_of(".");
	temp.erase(foundDot);
	if (temp.length() <= cutoff)
		return temp;
	else
		return temp.erase(cutoff-2, temp.length()) + "...";
}

void GUI::draw() {
	window.clear(sf::Color::Green);

	// draw buttons
	window.draw(musicPlayerBG  );
	window.draw(playPauseButton);			//0
	window.draw(prevButton); 				//1
	window.draw(nextButton);				//2
	window.draw(muteButton); 				//3
	window.draw(increaseVolumeButton);		//4
	window.draw(decreaseVolumeButton);		//5

	window.draw(prevSong);
	window.draw(currentSong);
	window.draw(nextSong);
	window.draw(next2Song);
	window.draw(next3Song);
	window.draw(next4Song);
	window.draw(next5Song);
	window.draw(next6Song);
	window.draw(next7Song);
	window.draw(next8Song);
	window.draw(songNumber);
	window.draw(currentSongInfo);
	window.draw(timerText);
	volumeBar.setSize(sf::Vector2f(music->_music.getVolume()*2, 5));
	window.draw(volumeBar);

	window.display();
}

void GUI::loadTextures() {
	texmgr->loadTexture("musicPlayerBGTex", "../res/background/musicplayerbg.png");
	texmgr->loadTexture("playTex", "../res/icons/play.png");
	texmgr->loadTexture("pauseTex", "../res/icons/pause.png");
	texmgr->loadTexture("prevTex", "../res/icons/previous.png");
	texmgr->loadTexture("nextTex", "../res/icons/next.png");
	texmgr->loadTexture("decreaseVolumeTex", "../res/icons/volume_down.png");
	texmgr->loadTexture("increaseVolumeTex", "../res/icons/volume_up.png");
	texmgr->loadTexture("muteTex", "../res/icons/mute.png");
	texmgr->loadTexture("playTex2", "../res/icons/play2.png");
	texmgr->loadTexture("pauseTex2", "../res/icons/pause2.png");
	texmgr->loadTexture("prevTex2", "../res/icons/previous2.png");
	texmgr->loadTexture("nextTex2", "../res/icons/next2.png");
	texmgr->loadTexture("decreaseVolumeTex2", "../res/icons/volume_down2.png");
	texmgr->loadTexture("increaseVolumeTex2", "../res/icons/volume_up2.png");
	texmgr->loadTexture("muteTexv2", "../res/icons/mutev2.png");
	texmgr->loadTexture("muteTex2", "../res/icons/mute2.png");
	texmgr->loadTexture("muteTexv22", "../res/icons/mutev2-2.png");
	std::cout << "Textures loaded" << std::endl;
}

void GUI::setTextures() {
	// set textures
	musicPlayerBG.setTexture(this->texmgr->getRef("musicPlayerBGTex"));
	playPauseButton.setTexture(this->texmgr->getRef("pauseTex"));
	prevButton.setTexture(this->texmgr->getRef("prevTex"));
	nextButton.setTexture(this->texmgr->getRef("nextTex"));
	muteButton.setTexture(this->texmgr->getRef("muteTex"));
	decreaseVolumeButton.setTexture(this->texmgr->getRef("decreaseVolumeTex"));
	increaseVolumeButton.setTexture(this->texmgr->getRef("increaseVolumeTex"));

	// set positions
	playPauseButton.setPosition(120,210);
	prevButton.setPosition(30,210);
	nextButton.setPosition(210,210);
	decreaseVolumeButton.setPosition(120,120);
	muteButton.setPosition(30,120);
	increaseVolumeButton.setPosition(210,120);
}

void GUI::setText(sf::Text& tex, const sf::Color& col, float x, float y) {
	tex.setFont(font);
	tex.setCharacterSize(24);
	tex.setColor(col);
	tex.setPosition(x,y);
}

void GUI::stylePlaylist() {
	sf::Color songsColor(0x080A58ff);
	sf::Color currColor(0x1E25EAff);
	sf::Color timerColor(0x080A58ff);

	setText(prevSong, songsColor, 360, 12);
	setText(currentSong, currColor, 360, 37);
	setText(nextSong, songsColor, 360, 62);
	setText(next2Song, songsColor, 360, 87);
	setText(next3Song, songsColor, 360, 112);
	setText(next4Song, songsColor, 360, 137);
	setText(next5Song, songsColor, 360, 162);
	setText(next6Song, songsColor, 360, 187);
	setText(next7Song, songsColor, 360, 212);
	setText(next8Song, songsColor, 360, 237);
	setText(currentSongInfo, currColor, 40, 14);
	setText(songNumber, songsColor, 40, 42);
	setText(timerText, timerColor, 40, 70);
}

void GUI::displayPlaylist() {
	if (music->songListIndex_+1 < 10) {
		songNumber.setString("0" + std::to_string(music->songListIndex_+1)
							 + "/" + std::to_string(music->songList_.size()));
	}
	else {
		songNumber.setString(std::to_string(music->songListIndex_+1)
							 + "/" + std::to_string(music->songList_.size()));
	}

	if (music->songListIndex_ == 0) {
		prevSong.setString(trimFilename(music->songList_[music->songList_.size() - 1], 23));
	}
	else {
		prevSong.setString(trimFilename(music->songList_[music->songListIndex_ - 1], 23));
	}

	currentSong.setString(trimFilename(music->songList_[music->songListIndex_], 23));
	currentSongInfo.setString(trimFilename(music->songList_[music->songListIndex_], 16));

	if (music->songListIndex_ == music->songList_.size() - 1) {
		nextSong.setString(trimFilename(music->songList_[0], 23));
	}
	else {
		nextSong.setString(trimFilename(music->songList_[music->songListIndex_ + 1], 23));
	}

	if (music->songListIndex_ == music->songList_.size() - 2) {
		next2Song.setString(trimFilename(music->songList_[0], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 1) {
		next2Song.setString(trimFilename(music->songList_[1], 23));
	}
	else {
		next2Song.setString(trimFilename(music->songList_[music->songListIndex_ + 2], 23));
	}

	if (music->songListIndex_ == music->songList_.size() - 3) {
		next3Song.setString(trimFilename(music->songList_[0], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 2) {
		next3Song.setString(trimFilename(music->songList_[1], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 1) {
		next3Song.setString(trimFilename(music->songList_[2], 23));
	}
	else {
		next3Song.setString(trimFilename(music->songList_[music->songListIndex_ + 3], 23));
	}

	if (music->songListIndex_ == music->songList_.size() - 4) {
		next4Song.setString(trimFilename(music->songList_[0], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 3) {
		next4Song.setString(trimFilename(music->songList_[1], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 2) {
		next4Song.setString(trimFilename(music->songList_[2], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 1) {
		next4Song.setString(trimFilename(music->songList_[3], 23));
	}
	else {
		next4Song.setString(trimFilename(music->songList_[music->songListIndex_ + 4], 23));
	}

	if (music->songListIndex_ == music->songList_.size() - 5) {
		next5Song.setString(trimFilename(music->songList_[0], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 4) {
		next5Song.setString(trimFilename(music->songList_[1], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 3) {
		next5Song.setString(trimFilename(music->songList_[2], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 2) {
		next5Song.setString(trimFilename(music->songList_[3], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 1) {
		next5Song.setString(trimFilename(music->songList_[4], 23));
	}
	else {
		next5Song.setString(trimFilename(music->songList_[music->songListIndex_ + 5], 23));
	}

	if (music->songListIndex_ == music->songList_.size() - 6) {
		next6Song.setString(trimFilename(music->songList_[0], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 5) {
		next6Song.setString(trimFilename(music->songList_[1], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 4) {
		next6Song.setString(trimFilename(music->songList_[2], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 3) {
		next6Song.setString(trimFilename(music->songList_[3], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 2) {
		next6Song.setString(trimFilename(music->songList_[4], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 1) {
		next6Song.setString(trimFilename(music->songList_[5], 23));
	}
	else {
		next6Song.setString(trimFilename(music->songList_[music->songListIndex_ + 6], 23));
	}

	if (music->songListIndex_ == music->songList_.size() - 7) {
		next7Song.setString(trimFilename(music->songList_[0], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 6) {
		next7Song.setString(trimFilename(music->songList_[1], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 5) {
		next7Song.setString(trimFilename(music->songList_[2], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 4) {
		next7Song.setString(trimFilename(music->songList_[3], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 3) {
		next7Song.setString(trimFilename(music->songList_[4], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 2) {
		next7Song.setString(trimFilename(music->songList_[5], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 1) {
		next7Song.setString(trimFilename(music->songList_[6], 23));
	}
	else {
		next7Song.setString(trimFilename(music->songList_[music->songListIndex_ + 7], 23));
	}

	if (music->songListIndex_ == music->songList_.size() - 8) {
		next8Song.setString(trimFilename(music->songList_[0], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 7) {
		next8Song.setString(trimFilename(music->songList_[1], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 6) {
		next8Song.setString(trimFilename(music->songList_[2], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 5) {
		next8Song.setString(trimFilename(music->songList_[3], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 4) {
		next8Song.setString(trimFilename(music->songList_[4], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 3) {
		next8Song.setString(trimFilename(music->songList_[5], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 2) {
		next8Song.setString(trimFilename(music->songList_[6], 23));
	}
	else if (music->songListIndex_ == music->songList_.size() - 1) {
		next8Song.setString(trimFilename(music->songList_[7], 23));
	}
	else {
		next8Song.setString(trimFilename(music->songList_[music->songListIndex_ + 8], 23));
	}
}

void GUI::update() {
	displayPlaylist();
	timerText.setString(timer->selectDisplayTimer());
	timer->displayTimer();
}