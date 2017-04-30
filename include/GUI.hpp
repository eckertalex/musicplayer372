// GUI.hpp
// 29. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Maurphy (@alaska.edu)  
// 		Cameron Showalter (@alaska.edu) 
//
// Header for GUI class

#ifndef GUI_HPP
#define GUI_HPP

#include "InputManager.hpp"
#include "textureManager.hpp"
#include "Music.hpp"
#include <memory>

class GUI {
public:
	sf::RenderWindow window;

	GUI(std::shared_ptr<Music> music);
	~GUI() = default;

	void draw();
	void update();
	void handleInput();
	bool clickInSprite(sf::Sprite s, int x , int y);
	void loadTextures();
	void setTextures();
	void stylePlaylist();
	void displayPlaylist();
	
	std::string trimFilename(const std::string& str);

	std::unique_ptr<TextureManager> texmgr;
	std::shared_ptr<Music> music;

	std::vector<sf::Sprite> spriteVec;
	std::vector<sf::Text> textVec;
	sf::Font font;
	sf::Text prevSong;
	sf::Text currentSong;
	sf::Text nextSong;
	sf::Text next2Song;
	sf::Text next3Song;
	sf::Text next4Song;

	sf::Sprite musicPlayerBG;
	sf::Sprite playPauseButton;
	sf::Sprite prevButton;
	sf::Sprite nextButton;
	sf::Sprite muteButton;
	sf::Sprite decreaseVolumeButton;
	sf::Sprite increaseVolumeButton;
};

// define window size
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 300

#endif // GUI_HPP