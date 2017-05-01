// musicPlayer.cpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjacobson2@alaska.edu)  
// 		Jarye Murphy (jmurphy11@alaska.edu)
// 		Cameron Showalter (cjshowalter@alaska.edu) 
//
// Source file for MusicPlayer class

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstddef>
#include <math.h>
#include <iomanip>

#include "../include/textureManager.hpp"
#include "../include/musicPlayer.hpp"

std::string trimFilename(const std::string& str) {
  std::size_t found = str.find_last_of("/\\");
  return str.substr(found+1);
}

bool MusicPlayer::clickInSprite(sf::Sprite s, int x , int y) {
	if (s.getGlobalBounds().top
		+ s.getGlobalBounds().height > y) {
		return s.getGlobalBounds().left + s.getGlobalBounds().width > x && x > s.getGlobalBounds().left &&
			   y > s.getGlobalBounds().top;
	}
	else {
		return x >= s.getGlobalBounds().left + s.getGlobalBounds().width && false;
	}
}

void MusicPlayer::draw() {
	window.clear(sf::Color::Green);

	// draw buttons
	window.draw(musicPlayerBG);
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

	window.draw(displayTimerText);

	return;
}

void MusicPlayer::update() {
	mouseOverHighlight();
	displayPlaylist();
	displayTimer();

	return;
}

void MusicPlayer::handleInput() {
	sf::Event event;
	while(window.pollEvent(event)) {
		auto mousePosX = sf::Mouse::getPosition(window).x; // x position 
		auto mousePosY = sf::Mouse::getPosition(window).y; // y position
		switch(event.type) {
			case sf::Event::Closed: {
				closeProgram();
				break;
			}
			
			// Key Pressed
			case sf::Event::KeyPressed: {
				if(event.key.code == sf::Keyboard::Escape) {
					closeProgram();
				}
			 	if(event.key.code == sf::Keyboard::Right) { callNextSong(); }			// Next song
			 	if(event.key.code == sf::Keyboard::Left) { callPrevSong(); }			// Previous song
			 	if(event.key.code == sf::Keyboard::Space) { callPlayPause(); }			// Play/Pause song
			 	if(event.key.code == sf::Keyboard::Down) { callDecreaseVolume(); }		// Decrease volume
			 	if(event.key.code == sf::Keyboard::Up) { callIncreaseVolume(); }		// increse volume
			 	if(event.key.code == sf::Keyboard::BackSpace) { callMuteUnmute(); }		// Mute/Unmute volume
			}
			
			// Mouse Button Pressed
			case sf::Event::MouseButtonPressed: {
				if(event.mouseButton.button == sf::Mouse::Left) {
					for (unsigned int i = 0; i < spriteVec.size(); ++i)	{
						//std::cout << " xPos " << mousePosX << " yPos " << mousePosY <<   std::endl;
						if (clickInSprite(spriteVec[i], mousePosX, mousePosY)) {
							if (i == 0)	{ callPlayPause(); } 		// Play/Pause song
							if (i == 1)	{ callPrevSong(); } 		// Previous song
							if (i == 2)	{ callNextSong(); }			// Next Song
							if (i == 3) { callMuteUnmute(); } 		// Mute/Unmute volume
							if (i == 4 ) { callDecreaseVolume(); } 	// Decrease volume
							if (i == 5) { callIncreaseVolume(); }	// Increase volume
						}
					}
				}
				break;
			}
			default:
			break;
		}
	}
	return;
}

void MusicPlayer::loadTextures() {
	texmgr.loadTexture("musicPlayerBGTex",      "../res/background/musicplayerbg.png");
	texmgr.loadTexture("playTex",    			"../res/icons/play.png");
	texmgr.loadTexture("pauseTex",   			"../res/icons/pause.png");
	texmgr.loadTexture("prevTex",    			"../res/icons/previous.png");
	texmgr.loadTexture("nextTex",    			"../res/icons/next.png");
	texmgr.loadTexture("decreaseVolumeTex",    	"../res/icons/volume_down.png");
	texmgr.loadTexture("increaseVolumeTex",    	"../res/icons/volume_up.png");
	texmgr.loadTexture("muteTex",				"../res/icons/mute.png");
	texmgr.loadTexture("playTex2",    			"../res/icons/play2.png");
	texmgr.loadTexture("pauseTex2",   			"../res/icons/pause2.png");
	texmgr.loadTexture("prevTex2",    			"../res/icons/previous2.png");
	texmgr.loadTexture("nextTex2",    			"../res/icons/next2.png");
	texmgr.loadTexture("decreaseVolumeTex2",    "../res/icons/volume_down2.png");
	texmgr.loadTexture("increaseVolumeTex2",    "../res/icons/volume_up2.png");
	texmgr.loadTexture("muteTexv2",				"../res/icons/mutev2.png");
	texmgr.loadTexture("muteTex2",				"../res/icons/mute2.png");
	texmgr.loadTexture("muteTexv22",				"../res/icons/mutev2-2.png");
	std::cout << "Textures loaded" << std::endl;
}

void MusicPlayer::playerLoop() {
	while(window.isOpen()) {
		handleInput();
		update();
		window.clear(sf::Color::White);
		draw();
		window.display();
	}
}

MusicPlayer::MusicPlayer() {
	loadTextures();
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MusicPlayer", 
		sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	// set textures
	musicPlayerBG.setTexture(this->texmgr.getRef("musicPlayerBGTex"));
	playPauseButton.setTexture(this->texmgr.getRef("pauseTex"));
	prevButton.setTexture(this->texmgr.getRef("prevTex"));
	nextButton.setTexture(this->texmgr.getRef("nextTex"));
	muteButton.setTexture(this->texmgr.getRef("muteTex"));
	decreaseVolumeButton.setTexture(this->texmgr.getRef("decreaseVolumeTex"));
	increaseVolumeButton.setTexture(this->texmgr.getRef("increaseVolumeTex"));

	// set positions
	playPauseButton.setPosition(120,210);
	prevButton.setPosition(30,210);
	nextButton.setPosition(210,210);
	decreaseVolumeButton.setPosition(120,120);
	muteButton.setPosition(30,120);
	increaseVolumeButton.setPosition(210,120);

	if(!font.loadFromFile("../res/fonts/TravelingTypewriter.ttf"))
		std::cout << "Font couldn't be found" << std::endl;
	else 
		std::cout << "Font was found" << std::endl;

	prevSong.setFont(font);
	prevSong.setCharacterSize(24);
	prevSong.setColor(sf::Color::Black);
	prevSong.setPosition(360,35);

	currentSong.setFont(font);
	currentSong.setCharacterSize(24);
	currentSong.setColor(sf::Color::Blue);
	currentSong.setPosition(360,60);

	nextSong.setFont(font);
	nextSong.setCharacterSize(24);
	nextSong.setColor(sf::Color::Black);
	nextSong.setPosition(360,85);

	next2Song.setFont(font);
	next2Song.setCharacterSize(24);
	next2Song.setColor(sf::Color::Black);
	next2Song.setPosition(360,110);

	next3Song.setFont(font);
	next3Song.setCharacterSize(24);
	next3Song.setColor(sf::Color::Black);
	next3Song.setPosition(360,135);

	next4Song.setFont(font);
	next4Song.setCharacterSize(24);
	next4Song.setColor(sf::Color::Black);
	next4Song.setPosition(360,160);

	displayTimerText.setFont(font);
	displayTimerText.setCharacterSize(24);
	displayTimerText.setColor(sf::Color::Red);
	displayTimerText.setPosition(40,75);

	spriteVec = { 
		playPauseButton,			// 0
		prevButton, 				// 1
		nextButton, 				// 2
		muteButton, 				// 3
		decreaseVolumeButton, 		// 4
		increaseVolumeButton };		// 5

	//create full songlist
	songList_ = std::move(dirmgr.getPlaylist());
	//if couldn't find song, don't try to play one
	if( songList_[songListIndex_] != "" ) {
		music.openFromFile(songList_[songListIndex_]);
	}


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
			songListIndex_ = (unsigned int) (songList_.size() - 1);
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
	if(isMuted_) {
		isMuted_=  false;
		music.setVolume(volSave_); // unmute the music by restoring the volume to previous value
	}
	//if we change the " +1" for music.getVolume, make sure to reduce the "<= 99" in the if statement (100 - number) -CS
	if(music.getVolume() <= 99) {
		music.setVolume(music.getVolume() + 1);
		std::cout << "The volume is " << music.getVolume() << std::endl;
	}
}
void MusicPlayer::callDecreaseVolume() {
	//first unmutes if muted
	if(isMuted_) {
		isMuted_=  false;
		music.setVolume(volSave_); // unmute the music by restoring the volume to previous value
	}
	//if we change the " -1" for music.getVolume, make sure to change the ">= 1" in the if statement to the same value -CS
	if(music.getVolume() >= 1) {
		music.setVolume(music.getVolume() - 1);
		std::cout << "The volume is " << music.getVolume() << std::endl;
	}
}
void MusicPlayer::callMuteUnmute() {
	//if its not muted than set the volume to 0
	if (!isMuted_) {
		isMuted_ = true;
		volSave_ = (unsigned int) music.getVolume();
		music.setVolume(0);
		std::cout << "Muted player." << std::endl;
	}
	else {
		isMuted_=  false;
		music.setVolume(volSave_); // unmute the music by restoring the volume to previous value
		std::cout << "Unmuted player." << std::endl;
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

/****** Timer Functions ******/

void MusicPlayer::updateCurrentTimer() {
	currentTimer = music.getPlayingOffset();
	currentTimeSeconds = (int)currentTimer.asSeconds();
	currentTimeMinutes = convertToMinutes((int)currentTimer.asSeconds());
	currentTimeHours = convertToHours((int) currentTimeSeconds);
	currentTimerStreamSeconds.str("");
	currentTimerStreamMinutes.str("");
	currentTimerStreamHours.str("");
	currentTimerStreamSeconds << std::fixed << std::setprecision(0) << (int) currentTimeSeconds % 60;
	currentTimerStreamMinutes << std::fixed << std::setprecision(0) << ((int)currentTimeMinutes%60);
	currentTimerStreamHours << std::fixed << std::setprecision(0) << (currentTimeHours);

	// Seconds
	if ((int)currentTimeSeconds%60 < 10) {
		currentSec = "0" + currentTimerStreamSeconds.str() + "/";
	}
	else {
		currentSec = currentTimerStreamSeconds.str() + "/";
	}
	// Minutes
	if((int)currentTimeMinutes%60 < 10) {
		currentMin = "0" + currentTimerStreamMinutes.str() + ":";
	}
	else {
		currentMin = currentTimerStreamMinutes.str() + ":";
	}
	// Hours
	if((int)currentTimeHours < 10) {
		currentHour = "0" + currentTimerStreamHours.str() + ":";
	}
	else {
		currentHour = currentTimerStreamHours.str() + ":";
	}
}

void MusicPlayer::updateTotalTimer() {
	totalTimer = music.getDuration();
	totalTimeSeconds = (int)totalTimer.asSeconds();
	totalTimeMinutes = convertToMinutes((int) totalTimeSeconds);
	totalTimeHours = convertToHours((int) totalTimeSeconds);
	totalTimerStreamSeconds.str("");
	totalTimerStreamMinutes.str("");
	totalTimerStreamHours.str("");
	totalTimerStreamSeconds << std::fixed << std::setprecision(0) << (int) totalTimeSeconds % 60;
	totalTimerStreamMinutes << std::fixed << std::setprecision(0) << ((int)totalTimeMinutes%60);
	totalTimerStreamHours << std::fixed << std::setprecision(0) << (totalTimeHours);
	
	// Seconds
	if ((int)totalTimeSeconds%60 < 10) {
		totalSec = "0" + totalTimerStreamSeconds.str();
	}
	else {
		totalSec = totalTimerStreamSeconds.str();
	}
	// Minutes
	if((int)totalTimeMinutes%60 < 10) {
		totalMin = "0" + totalTimerStreamMinutes.str() + ":";
	}
	else {
		totalMin = totalTimerStreamMinutes.str() + ":";
	}
	// Hours
	if((int)totalTimeHours < 10) {
		totalHour = "0" + totalTimerStreamHours.str() + ":";
	}
	else {
		totalHour = totalTimerStreamHours.str() + ":";
	}
}

void MusicPlayer::selectDisplayTimer() {
	// 0:xx
	if(totalTimeMinutes < 1) {
		displayTimerText.setString("0:" + currentSec + "0:" + totalSec);
	}
	// xx:xx
	else if(currentTimeHours < 1 && totalTimeHours < 1 && totalTimeMinutes > 0) {
		displayTimerText.setString(currentMin + currentSec + totalMin + totalSec);
	}
	// xx:xx:xx
	else {
		displayTimerText.setString(currentHour + currentMin + currentSec + totalHour + totalMin + totalSec);
	}

	if(music.getStatus() == 0) {
		callNextSong();
	}
}

void MusicPlayer::displayTimer() {
	updateCurrentTimer();
	updateTotalTimer();
	selectDisplayTimer();
	
}
int MusicPlayer::convertToMinutes(int seconds) {
	return seconds/60;
}

int MusicPlayer::convertToHours(int seconds) {
	return (seconds/(60*60));
}

void MusicPlayer::closeProgram() {
	window.close();
	std::cout << "Closed MusicPlayer372\nGood Bye!" << std::endl;
}
