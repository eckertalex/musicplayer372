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
#include <sstream>

#include "textureManager.hpp"

// define version numbers
// set in CMakeLists.txt file
#define myproject_VERSION_MAJOR 0
#define myproject_VERSION_MINOR 1

// define window size
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 300

class MusicPlayer {
public:
	sf::RenderWindow window;
	TextureManager texmgr;
	
	std::vector<sf::Sprite> spriteVec;

	sf::SoundBuffer buffer;
	sf::Music music;

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

	/****** Timer Variables ******/
	// Current Time Elapsed Stuff
	std::stringstream currentTimerStreamSeconds;
	std::stringstream currentTimerStreamMinutes;
	std::stringstream currentTimerStreamHours;
	sf::Time currentTimer;
	float currentTimeSeconds;
	float currentTimeMinutes;
	float currentTimeHours;
	
	// Total Time Stuff
	std::stringstream totalTimerStreamSeconds;
	std::stringstream totalTimerStreamMinutes;
	std::stringstream totalTimerStreamHours;
	sf::Time totalTimer;
	float totalTimeSeconds;
	float totalTimeMinutes;
	float totalTimeHours;

	// Onscreen Timer Display Stuff
	std::string currentSec;
	std::string currentMin;
	std::string currentHour;
	std::string totalSec;
	std::string totalMin;
	std::string totalHour;
	sf::Text displayTimerText;

	void playerLoop();

	MusicPlayer();
	~MusicPlayer() = default;

	void draw();
	void update();
	void handleInput();
	bool clickInSprite(sf::Sprite s, int x , int y);

	/****** Functionality Functions ******/
	void callPlayPause();
	void callNextSong();
	void callPrevSong();
	void callIncreaseVolume();
	void callDecreaseVolume();
	void callMuteUnmute();
	void closeProgram();
	
	/****** Update Functions ******/
	void mouseOverHighlight();
	void displayPlaylist();

	/****** Timer Functions ******/
	void updateCurrentTimer();
	void updateTotalTimer();
	void selectDisplayTimer();
	void displayTimer();
	int convertToMinutes(int seconds);
	int convertToHours(int seconds);

private:
	void loadTextures();

	std::vector<std::string> songList_;
	unsigned int songListIndex_ = 0;

	unsigned int volSave_;
	bool isMuted_;

	std::unique_ptr<MusicPlayer> musicPlayer;
};

#endif // #ifndef MUSICPLAYER_HPP
