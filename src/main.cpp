#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
	
	sf::SoundBuffer buffer;
	sf::Music music;
	if (!music.openFromFile("../currency.wav"))
	{
		return -1;
	}
	music.play();
	sf::RectangleShape play(sf::Vector2f(60, 60));
	sf::RectangleShape prev(sf::Vector2f(60, 60));
	sf::RectangleShape next(sf::Vector2f(60, 60));
	sf::RectangleShape mute(sf::Vector2f(60, 60));
	sf::RectangleShape volumeDecrease(sf::Vector2f(60, 60));
	sf::RectangleShape volumeIncrease(sf::Vector2f(60, 60));
	sf::RectangleShape divline(sf::Vector2f(2, 300));
	
	sf::RenderWindow window(sf::VideoMode(700, 300), "Chat");
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		play.setPosition(120,210);
		prev.setPosition(30,210);
		next.setPosition(210,210);
		volumeDecrease.setPosition(120,120);
		mute.setPosition(30,120);
		volumeIncrease.setPosition(210,120);
		divline.setPosition(300,0);
		window.draw(play);
		window.draw(prev);
		window.draw(next);
		window.draw(mute);
		window.draw(volumeDecrease);
		window.draw(volumeIncrease);
		window.draw(divline);

		window.display();
	}

	return 0;
}