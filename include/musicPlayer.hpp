// musicPlayer.hpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Maurphy (@alaska.edu)  
// 		Cameron Showalter (@alaska.edu) 
//
// Header for MusicPlayer class

#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include <vector>
#include <memory>

#include "textureManager.hpp"

class MusicPlayer {
public:
	sf::RenderWindow window;
	TextureManager texmgr;
	
	std::vector<sf::Sprite> spriteVec;

	sf::SoundBuffer buffer;
	sf::Music music;

	sf::Sprite playPauseButton;
	sf::Sprite prevButton;
	sf::Sprite nextButton;
	sf::Sprite muteButton;
	sf::Sprite decreaseVolumeButton;
	sf::Sprite increaseVolumeButton;

	void playerLoop();

	MusicPlayer();
	~MusicPlayer() = default;

	void draw(const float dt);
	void update(const float dt);
	void handleInput();
	bool clickInSprite(sf::Sprite s, int x , int y);

private:
	void loadTextures();

	std::vector<std::string> songList_;
	unsigned int songListIndex_;

	unsigned int volSave_;
	bool isMuted_;

	std::unique_ptr<MusicPlayer> musicPlayer;
};

#endif // #ifndef MUSICPLAYER_HPP