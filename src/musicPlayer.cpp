// musicPlayer.hpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Maurphy (@alaska.edu)  
// 		Cameron Showalter (@alaska.edu) 
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

bool MusicPlayer::clickInSprite(sf::Sprite s, int x , int y)
{
	if (x > s.getGlobalBounds().left && x <
		(s.getGlobalBounds().left + s.getGlobalBounds().width) && y > s.getGlobalBounds().top &&
			y < (s.getGlobalBounds().top + s.getGlobalBounds().height))
	{
		return true;
	}
	
	return false;
}

void MusicPlayer::draw(const float dt) {
	window.clear(sf::Color::Green);

	// draw buttons
	window.draw(playPauseButton);
	window.draw(prevButton);
	window.draw(nextButton);
	window.draw(muteButton);
	window.draw(increaseVolumeButton);
	window.draw(decreaseVolumeButton);

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
	int volSave = music.getVolume(); // restore point for when you unmute the music
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
				std::vector<sf::Sprite> spriteVec = { playPauseButton, prevButton, 
													nextButton, decreaseVolumeButton, 
													muteButton, increaseVolumeButton };
				if(event.mouseButton.button == sf::Mouse::Left) {
					auto mousePosX = sf::Mouse::getPosition(window).x; // x position 
					auto mousePosY = sf::Mouse::getPosition(window).y; // y position
					for (auto i = 0; i < spriteVec.size(); ++i)
					{
						std::cout << " xPos " << mousePosX << " yPos " << mousePosY <<   std::endl;
						if (clickInSprite(spriteVec[i], mousePosX, mousePosY) == true)
						{
							if (i == 0)
							{
								music.pause();
							}
							if (i == 3) // decrease the volume
							{
								music.setVolume(music.getVolume() - 1);
								std::cout << "the volume is " << music.getVolume() << "/n";
							}
							if (i == 4 ) // mute the voluem or unmute
							{
								if (music.getVolume() != 0)//if its not muted than set the volume to 0
								{
									music.setVolume(0);
									
								}
								else
								{
									music.setVolume(volSave); // unmute the music by restoring the volume to previous value
								}
								
							}
							if (i == 5)
							{
								music.setVolume(music.getVolume() + 1);
								
								std::cout << "the volume is " << music.getVolume() << "/n";
							}
						
							
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
	texmgr.loadTexture("playTex",    			"../res/icons/play.png");
	texmgr.loadTexture("pauseTex",   			"../res/icons/pause.png");
	texmgr.loadTexture("prevTex",    			"../res/icons/previous.png");
	texmgr.loadTexture("nextTex",    			"../res/icons/next.png");
	texmgr.loadTexture("decreaseVolumeTex",    	"../res/icons/volume_down.png");
	texmgr.loadTexture("increaseVolumeTex",    	"../res/icons/volume_up.png");
	texmgr.loadTexture("muteTex",				"../res/icons/mute.png");
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

	// set positions
	playPauseButton.setPosition(120,210);
	prevButton.setPosition(30,210);
	nextButton.setPosition(210,210);
	decreaseVolumeButton.setPosition(120,120);
	muteButton.setPosition(30,120);
	increaseVolumeButton.setPosition(210,120);

	spriteVec = { playPauseButton, prevButton, 
				nextButton, decreaseVolumeButton, 
				muteButton, increaseVolumeButton };

	std::cout << "MusicPlayer initialized" << std::endl;
}