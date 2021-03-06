// GUI.hpp
// 29. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Murphy (jmurphy11@alaska.edu)
// 		Cameron Showalter (cjshowalter@alaska.edu)
//
// Header for GUI class

#ifndef GUI_HPP
#define GUI_HPP

#include "InputManager.hpp"
#include "textureManager.hpp"
#include "timer.hpp"
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
	void loadTextures();
	void setTextures();
	void stylePlaylist();
	void displayPlaylist();
	void setText(sf::Text& tex, const sf::Color& col, float x, float y);
	
	std::string trimFilename(const std::string& str, unsigned long cutoff);

	std::unique_ptr<TextureManager> texmgr;
	std::shared_ptr<Music> music;
	std::shared_ptr<Timer> timer;

	std::vector<sf::Sprite> spriteVec;
	sf::Font font;
	sf::Text prevSong;
	sf::Text currentSong;
	sf::Text currentSongInfo;
	sf::Text nextSong;
	sf::Text next2Song;
	sf::Text next3Song;
	sf::Text next4Song;
	sf::Text next5Song;
	sf::Text next6Song;
	sf::Text next7Song;
	sf::Text next8Song;
	sf::Text songNumber;

	sf::Text timerText;

	sf::Sprite musicPlayerBG;
	sf::Sprite playPauseButton;
	sf::Sprite prevButton;
	sf::Sprite nextButton;
	sf::Sprite muteButton;
	sf::Sprite decreaseVolumeButton;
	sf::Sprite increaseVolumeButton;
	sf::RectangleShape volumeBar;
};

// define window size
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 300

#endif // GUI_HPP