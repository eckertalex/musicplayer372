// musicPlayer.hpp
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

#include "config.hpp"
#include "../include/textureManager.hpp"
#include "../include/musicPlayer.hpp"
#include "../include/directoryManager.hpp"



bool MusicPlayer::clickInSprite(sf::Sprite s, int x , int y) {
	if (x > s.getGlobalBounds().left && x <
			(s.getGlobalBounds().left + s.getGlobalBounds().width) && 
			y > s.getGlobalBounds().top && y < (s.getGlobalBounds().top 
			+ s.getGlobalBounds().height)) {
		return true;
	}
	return false;
}

void MusicPlayer::draw(const float dt) {
	window.clear(sf::Color::Green);

	// draw buttons
	window.draw(playPauseButton);			//0
	window.draw(prevButton); 				//1
	window.draw(nextButton);				//2
	window.draw(muteButton); 				//3
	window.draw(increaseVolumeButton);		//4
	window.draw(decreaseVolumeButton);		//5

	return;
}

void MusicPlayer::update(const float dt) {
	if (music.getStatus() != sf::SoundSource::Status::Playing) {
		playPauseButton.setTexture(this->texmgr.getRef("playTex"));
	}
	else {
		playPauseButton.setTexture(this->texmgr.getRef("pauseTex"));
	}
	return;
}

void MusicPlayer::handleInput() {
	sf::Event event;
	while(window.pollEvent(event))
	{
		switch(event.type) {
			case sf::Event::Closed: {
				window.close();
				std::cout << "Closed Game\nGood Bye!" << std::endl;
				break;
			}
			case sf::Event::KeyPressed: {
				if(event.key.code == sf::Keyboard::Escape) {
					window.close();
					std::cout << "Closed Game\nGood Bye!" << std::endl;
				}
			}
			case sf::Event::MouseButtonPressed: {
				if(event.mouseButton.button == sf::Mouse::Left) {
					auto mousePosX = sf::Mouse::getPosition(window).x; // x position 
					auto mousePosY = sf::Mouse::getPosition(window).y; // y position
					for (unsigned int i = 0; i < spriteVec.size(); ++i)	{
						//std::cout << " xPos " << mousePosX << " yPos " << mousePosY <<   std::endl;
						if (clickInSprite(spriteVec[i], mousePosX, mousePosY) == true) {
							//Pause/Play song
							if (i == 0)	{
								if (music.getStatus() != music.Playing) {
									music.play();
									std::cout << "Playing song: " << songList_[songListIndex_] << std::endl;
								}
								else {
									music.pause();
								}
							}
							//Previous song
							if (i == 1)	{
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
									std::cout << "prevSong: " << songList_[songListIndex_] << " vecIndex: " << songListIndex_ << std::endl;
								}
							}
							//Next Song
							if (i == 2)	{
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
									std::cout << "NextSong: " << songList_[songListIndex_] << " vecIndex: " << songListIndex_ << std::endl;
									std::cout << "Playing song: " << songList_[songListIndex_] << std::endl;
								}
							}
							// mute the volume or unmute
							if (i == 3) {
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
							// decrease volume
							if (i == 4 ) {
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
							// increase volume
							if (i == 5) {
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
						}
					}
				}
				break;
			}
			case sf::Event::MouseMoved: {
				auto mousePosX = sf::Mouse::getPosition(window).x; // x position 
				auto mousePosY = sf::Mouse::getPosition(window).y; // y position
				std::cout << " xPos " << mousePosX << " yPos " << mousePosY <<   std::endl;
				//Pause/Play song
				if ((mousePosX > 125 && mousePosX < 177) && (mousePosY > 216 && mousePosY < 268)) {
					playPauseButton.setTexture(this->texmgr.getRef("playTex2"));
				}
				//Previous song
				else if ((mousePosX > 45 && mousePosX < 76) && (mousePosY > 216 && mousePosY < 268)) {
					prevButton.setTexture(this->texmgr.getRef("prevTex2"));
				}
				//Next Song
				else if ((mousePosX > 225 && mousePosX < 257) && (mousePosY > 216 && mousePosY < 268)) {
					nextButton.setTexture(this->texmgr.getRef("nextTex2"));
				}
				// mute the volume or unmute
				else if ((mousePosX > 38 && mousePosX < 84) && (mousePosY > 128 && mousePosY < 174)) {
				  	muteButton.setTexture(this->texmgr.getRef("muteTex2"));
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
			  		playPauseButton.setTexture(this->texmgr.getRef("playTex"));
					prevButton.setTexture(this->texmgr.getRef("prevTex"));
					nextButton.setTexture(this->texmgr.getRef("nextTex"));
					muteButton.setTexture(this->texmgr.getRef("muteTex"));
					decreaseVolumeButton.setTexture(this->texmgr.getRef("decreaseVolumeTex"));
					increaseVolumeButton.setTexture(this->texmgr.getRef("increaseVolumeTex"));
				}
			}
			
			default:
			break;
		}
	}
	return;
}

void MusicPlayer::loadTextures() {
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
	texmgr.loadTexture("muteTex2",				"../res/icons/mute2.png");
	std::cout << "Textures loaded" << std::endl;
}

void MusicPlayer::playerLoop() {
	sf::Clock clock;

	while(window.isOpen()) {
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();
		handleInput();
		update(dt);
		window.clear(sf::Color::White);
		draw(dt);
		window.display();
	}
}

MusicPlayer::MusicPlayer() {
	loadTextures();
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MusicPlayer", 
		sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	// set textures
	playPauseButton.setTexture(this->texmgr.getRef("pauseTex"));
	prevButton.setTexture(this->texmgr.getRef("prevTex"));
	nextButton.setTexture(this->texmgr.getRef("nextTex"));
	muteButton.setTexture(this->texmgr.getRef("muteTex"));
	decreaseVolumeButton.setTexture(this->texmgr.getRef("decreaseVolumeTex"));
	increaseVolumeButton.setTexture(this->texmgr.getRef("increaseVolumeTex"));
	// playPauseButton2.setTexture(this->texmgr.getRef("pauseTex2"));
	// prevButton2.setTexture(this->texmgr.getRef("prevTex2"));
	// nextButton2.setTexture(this->texmgr.getRef("nextTex2"));
	// muteButton2.setTexture(this->texmgr.getRef("muteTex2"));
	// decreaseVolumeButton2.setTexture(this->texmgr.getRef("decreaseVolumeTex2"));
	// increaseVolumeButton2.setTexture(this->texmgr.getRef("increaseVolumeTex2"));

	// set positions
	playPauseButton.setPosition(120,210);
	prevButton.setPosition(30,210);
	nextButton.setPosition(210,210);
	decreaseVolumeButton.setPosition(120,120);
	muteButton.setPosition(30,120);
	increaseVolumeButton.setPosition(210,120);
	// playPauseButton2.setPosition(120,210);
	// prevButton2.setPosition(30,210);
	// nextButton2.setPosition(210,210);
	// decreaseVolumeButton2.setPosition(120,120);
	// muteButton2.setPosition(30,120);
	// increaseVolumeButton2.setPosition(210,120);

	spriteVec = { 
		playPauseButton,			// 0
		prevButton, 				// 1
		nextButton, 				// 2
		muteButton, 				// 3
		decreaseVolumeButton, 		// 4
		increaseVolumeButton };		// 5

	//create full songlist
	songList_ = std::move(fileTreeMain()); //fileTreeMain inside directoryManager.hpp
	music.openFromFile(songList_[songListIndex_]);
	//print for testing, delete later
	printVec(songList_);

	volSave_ = 100;
	isMuted_ = false;

	std::cout << "MusicPlayer initialized" << std::endl;
}