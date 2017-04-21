#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
	
	sf::SoundBuffer buffer;
	sf::Music music;
	if (!music.openFromFile("currency.wav"))
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