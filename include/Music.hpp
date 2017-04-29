#ifndef MUSIC_HPP
#define MUSIC_HPP
#include <vector>
#include <SFML/Audio/Music.hpp>

class Music
{
public:
	Music();

	sf::Music music;

	void callPlayPause();
	void callNextSong();
	void callPrevSong();
	void callIncreaseVolume();
	void callDecreaseVolume();
	void callMuteUnmute();
	void closeProgram();

private:

	std::vector<std::string> songList_;
	unsigned int songListIndex_ = 0;

	unsigned int volSave_;
	bool isMuted_;
};

#endif