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
	for (int i = 0; i != musicFiles.size(); ++i)
	{
		if (!music.openFromFile(musicFiles[i]))
		{
			return -1;
		}
		else
		{
			music.play();
			music.setLoop(true);
			
		}
	}
	
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