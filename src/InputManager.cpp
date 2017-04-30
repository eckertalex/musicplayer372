#include "../include/InputManager.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "../include/GUI.hpp"

InputManager::InputManager(std::shared_ptr<GUI> gui, std::shared_ptr<Music> music) : gui(gui), music(music)
{
	
}

void InputManager::mouseOverHighlight() {
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
	if (!isMuted_) {
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

void InputManager::handleInput() {
	sf::Event event;
	while (window.pollEvent(event))
	{
		auto mousePosX = sf::Mouse::getPosition(window).x; // x position 
		auto mousePosY = sf::Mouse::getPosition(window).y; // y position
		switch (event.type) {
		case sf::Event::Closed: {
			window.close();
			std::cout << "Closed MusicPlayer372\nGood Bye!" << std::endl;
			break;
		}

								// Key Pressed
		case sf::Event::KeyPressed: {
			if (event.key.code == sf::Keyboard::Escape) {
				window.close();
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
				for (unsigned int i = 0; i < spriteVec.size(); ++i) {
					//std::cout << " xPos " << mousePosX << " yPos " << mousePosY <<   std::endl;
					if (clickInSprite(spriteVec[i], mousePosX, mousePosY) == true) {
						if (i == 0) { music->callPlayPause(); } 		// Play/Pause song
						if (i == 1) { music->callPrevSong(); } 		// Previous song
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