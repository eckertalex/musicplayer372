#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
using std::vector;
int main()
{
	
	sf::SoundBuffer buffer;
	sf::Music music;
	vector<std::string> musicFiles;
	musicFiles.emplace_back("currency.wav");
	musicFiles.emplace_back("Explosion.wav");
	
	
	if (!music.openFromFile(musicFiles[0]))
	{
		return -1;
	}
	music.play();
	if (!music.openFromFile(musicFiles[1]))
	{
		return -1;
	}
	music.play();
	
	sf::RenderWindow window(sf::VideoMode(200, 200), "Chat");
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		window.display();
	}

	return 0;
}