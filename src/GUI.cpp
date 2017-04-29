// GUI.cpp
// 29. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Maurphy (@alaska.edu)  
// 		Cameron Showalter (@alaska.edu) 
//
// Source file for GUI class

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cstddef>
#include <iostream>

#include "../include/textureManager.hpp"
#include "../include/GUI.hpp"

GUI::GUI(Music & music) : music(music) {
	loadTextures();
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MusicPlayer",
		sf::Style::Titlebar | sf::Style::Close);
}

bool GUI::clickInSprite(sf::Sprite s, int x , int y) {
	if (x > s.getGlobalBounds().left && x <
			(s.getGlobalBounds().left + s.getGlobalBounds().width) && 
			y > s.getGlobalBounds().top && y < (s.getGlobalBounds().top 
			+ s.getGlobalBounds().height)) {
		return true;
	}
	return false;
}

std::string GUI::trimFilename(const std::string& str) {
  std::size_t found = str.find_last_of("/\\");
  return str.substr(found+1);
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
	window.display();

	return;
}

void GUI::loadTextures() {
	texmgr.loadTexture("musicPlayerBGTex", "../res/background/musicplayerbg.png");
	texmgr.loadTexture("playTex", "../res/icons/play.png");
	texmgr.loadTexture("pauseTex", "../res/icons/pause.png");
	texmgr.loadTexture("prevTex", "../res/icons/previous.png");
	texmgr.loadTexture("nextTex", "../res/icons/next.png");
	texmgr.loadTexture("decreaseVolumeTex", "../res/icons/volume_down.png");
	texmgr.loadTexture("increaseVolumeTex", "../res/icons/volume_up.png");
	texmgr.loadTexture("muteTex", "../res/icons/mute.png");
	texmgr.loadTexture("playTex2", "../res/icons/play2.png");
	texmgr.loadTexture("pauseTex2", "../res/icons/pause2.png");
	texmgr.loadTexture("prevTex2", "../res/icons/previous2.png");
	texmgr.loadTexture("nextTex2", "../res/icons/next2.png");
	texmgr.loadTexture("decreaseVolumeTex2", "../res/icons/volume_down2.png");
	texmgr.loadTexture("increaseVolumeTex2", "../res/icons/volume_up2.png");
	texmgr.loadTexture("muteTexv2", "../res/icons/mutev2.png");
	texmgr.loadTexture("muteTex2", "../res/icons/mute2.png");
	texmgr.loadTexture("muteTexv22", "../res/icons/mutev2-2.png");
	std::cout << "Textures loaded" << std::endl;
}

void GUI::setTextures() {
	spriteVec = { 
		playPauseButton,			// 0
		prevButton, 				// 1
		nextButton, 				// 2
		muteButton, 				// 3
		decreaseVolumeButton, 		// 4
		increaseVolumeButton
	};

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
}

void GUI::stylePlaylist() {
	if(!font.loadFromFile("../res/fonts/TravelingTypewriter.ttf"))
		std::cout << "Font couldn't be found" << std::endl;
	else 
		std::cout << "Font was found" << std::endl;

	textVec = {
		prevSong,
		currentSong,
		nextSong,
		next2Song,
		next3Song,
		next4Song
	};

	int counter = 35;
	for(auto i=0; textVec.size()-1; ++i) {
		textVec[i].setFont(font);
		textVec[i].setCharacterSize(24);
		if(i == 1)
			textVec[i].setColor(sf::Color::Blue);
		else
			textVec[i].setColor(sf::Color::Black);
		textVec[i].setPosition(360,counter);
		counter += 25;
	}
}

void GUI::update() {
	mouseOverHighlight();
	displayPlaylist();
	return;
}

void GUI::handleInput() {
	sf::Event event;
	while(window.pollEvent(event))
	{
		auto mousePosX = sf::Mouse::getPosition(window).x; // x position 
		auto mousePosY = sf::Mouse::getPosition(window).y; // y position
		switch(event.type) {
			case sf::Event::Closed: {
				window.close();
				std::cout << "Closed MusicPlayer372\nGood Bye!" << std::endl;
				break;
			}
			
			// Key Pressed
			case sf::Event::KeyPressed: {
				if(event.key.code == sf::Keyboard::Escape) {
					window.close();
					std::cout << "Closed MusicPlayer372\nGood Bye!" << std::endl;
				}
			 	if(event.key.code == sf::Keyboard::Right) { music.callNextSong(); }			// Next song
			 	if(event.key.code == sf::Keyboard::Left) { music.callPrevSong(); }			// Previous song
			 	if(event.key.code == sf::Keyboard::Space) { music.callPlayPause(); }			// Play/Pause song
			 	if(event.key.code == sf::Keyboard::Down) { music.callDecreaseVolume(); }		// Decrease volume
			 	if(event.key.code == sf::Keyboard::Up) { music.callIncreaseVolume(); }		// increse volume
			 	if(event.key.code == sf::Keyboard::BackSpace) { music.callMuteUnmute(); }		// Mute/Unmute volume
			}
			
			// Mouse Button Pressed
			case sf::Event::MouseButtonPressed: {
				if(event.mouseButton.button == sf::Mouse::Left) {
					for (unsigned int i = 0; i < spriteVec.size(); ++i)	{
						//std::cout << " xPos " << mousePosX << " yPos " << mousePosY <<   std::endl;
						if (clickInSprite(spriteVec[i], mousePosX, mousePosY) == true) {
							if (i == 0)	{ music.callPlayPause(); } 		// Play/Pause song
							if (i == 1)	{ music.callPrevSong(); } 		// Previous song
							if (i == 2)	{ music.callNextSong(); }			// Next Song
							if (i == 3) { music.callMuteUnmute(); } 		// Mute/Unmute volume
							if (i == 4 ) { music.callDecreaseVolume(); } 	// Decrease volume
							if (i == 5) { music.callIncreaseVolume(); }	// Increase volume
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