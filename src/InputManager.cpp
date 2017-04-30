// InputManager.cpp
// 29. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Maurphy (@alaska.edu)  
// 		Cameron Showalter (@alaska.edu) 
//
// Source file for InputManager class

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "../include/InputManager.hpp"

InputManager::InputManager() {
	music = std::make_unique<Music>();
	gui = std::make_unique<GUI>(music);
}

void InputManager::mouseOverHighlight() {
	auto mousePosX = sf::Mouse::getPosition(gui->window).x; // x position
	auto mousePosY = sf::Mouse::getPosition(gui->window).y; // y position

	if (music->_music.getStatus() != sf::SoundSource::Status::Playing) {
		gui->playPauseButton.setTexture(gui->texmgr->getRef("playTex"));
		if ((mousePosX > 125 && mousePosX < 177) && (mousePosY > 216 && mousePosY < 268)) {
			gui->playPauseButton.setTexture(gui->texmgr->getRef("playTex2"));
		}
	}
	else {
		gui->playPauseButton.setTexture(gui->texmgr->getRef("pauseTex"));
		if ((mousePosX > 125 && mousePosX < 177) && (mousePosY > 216 && mousePosY < 268)) {
			gui->playPauseButton.setTexture(gui->texmgr->getRef("pauseTex2"));
		}
	}
	// mute the volume or unmute
	if (!music->isMuted_) {
		gui->muteButton.setTexture(gui->texmgr->getRef("muteTexv2"));
		if ((mousePosX > 38 && mousePosX < 84) && (mousePosY > 128 && mousePosY < 174)) {
			gui->muteButton.setTexture(gui->texmgr->getRef("muteTexv22"));
		}
	}
	else {
		gui->muteButton.setTexture(gui->texmgr->getRef("muteTex"));
		if ((mousePosX > 38 && mousePosX < 84) && (mousePosY > 128 && mousePosY < 174)) {
			gui->muteButton.setTexture(gui->texmgr->getRef("muteTex2"));
		}
	}
	//Previous song
	if ((mousePosX > 45 && mousePosX < 76) && (mousePosY > 216 && mousePosY < 268)) {
		gui->prevButton.setTexture(gui->texmgr->getRef("prevTex2"));
	}
	//Next Song
	else if ((mousePosX > 225 && mousePosX < 257) && (mousePosY > 216 && mousePosY < 268)) {
		gui->nextButton.setTexture(gui->texmgr->getRef("nextTex2"));
	}
	// // decrease volume
	else if ((mousePosX > 133 && mousePosX < 168) && (mousePosY > 128 && mousePosY < 174)) {
		gui->decreaseVolumeButton.setTexture(gui->texmgr->getRef("decreaseVolumeTex2"));
	}
	// increase volume
	else if ((mousePosX > 218 && mousePosX < 264) && (mousePosY > 128 && mousePosY < 174)) {
		gui->increaseVolumeButton.setTexture(gui->texmgr->getRef("increaseVolumeTex2"));
	}
	else {
		gui->prevButton.setTexture(gui->texmgr->getRef("prevTex"));
		gui->nextButton.setTexture(gui->texmgr->getRef("nextTex"));
		gui->decreaseVolumeButton.setTexture(gui->texmgr->getRef("decreaseVolumeTex"));
		gui->increaseVolumeButton.setTexture(gui->texmgr->getRef("increaseVolumeTex"));
	}
}

void InputManager::handleInput() {
	sf::Event event;
	while (gui->window.pollEvent(event))
	{
		auto mousePosX = sf::Mouse::getPosition(gui->window).x; // x position
		auto mousePosY = sf::Mouse::getPosition(gui->window).y; // y position
		switch (event.type) {
		case sf::Event::Closed: {
			gui->window.close();
			std::cout << "Closed MusicPlayer372\nGood Bye!" << std::endl;
			break;
		}

		// Key Pressed
		case sf::Event::KeyPressed: {
			if (event.key.code == sf::Keyboard::Escape) {
				gui->window.close();
				std::cout << "Closed MusicPlayer372\nGood Bye!" << std::endl;
			}
			if (event.key.code == sf::Keyboard::Right) { music->callNextSong(); }			// Next song
			if (event.key.code == sf::Keyboard::Left) { music->callPrevSong(); }			// Previous song
			if (event.key.code == sf::Keyboard::Space) { music->callPlayPause(); }			// Play/Pause song
			if (event.key.code == sf::Keyboard::Down) { music->callDecreaseVolume(); }		// Decrease volume
			if (event.key.code == sf::Keyboard::Up) { music->callIncreaseVolume(); }		// increse volume
			if (event.key.code == sf::Keyboard::BackSpace) { music->callMuteUnmute(); }		// Mute/Unmute volume
		}

		// Mouse Button Pressed
		case sf::Event::MouseButtonPressed: {
			if (event.mouseButton.button == sf::Mouse::Left) {
				for (unsigned int i = 0; i < gui->spriteVec.size(); ++i) {
					if (gui->clickInSprite(gui->spriteVec[i], mousePosX, mousePosY)) {
						if (i == 0) { music->callPlayPause(); } 		// Play/Pause song
						if (i == 1) { music->callPrevSong(); } 			// Previous song
						if (i == 2) { music->callNextSong(); }			// Next Song
						if (i == 3) { music->callMuteUnmute(); } 		// Mute/Unmute volume
						if (i == 4) { music->callDecreaseVolume(); } 	// Decrease volume
						if (i == 5) { music->callIncreaseVolume(); }	// Increase volume
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