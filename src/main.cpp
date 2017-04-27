// main.cpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Maurphy (@alaska.edu)  
// 		Cameron Showalter (@alaska.edu) 
//
// Main file for MusicPlayer372, the project from CS372 
// 		with Professor Chris Hartman

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
	sf::RectangleShape divline(sf::Vector2f(2, 300));

	sf::Texture playtex;
	playtex.loadFromFile("../res/icons/play.png");
	sf::Sprite play;
	play.setTexture(playtex);

	sf::Texture prevtex;
	prevtex.loadFromFile("../res/icons/previous.png");
	sf::Sprite prev;
	prev.setTexture(prevtex);

	sf::Texture nexttex;
	nexttex.loadFromFile("../res/icons/next.png");
	sf::Sprite next;
	next.setTexture(nexttex);

	sf::Texture mutetex;
	mutetex.loadFromFile("../res/icons/mute.png");
	sf::Sprite mute;
	mute.setTexture(mutetex);

	sf::Texture increasetex;
	increasetex.loadFromFile("../res/icons/volume_up.png");
	sf::Sprite increase;
	increase.setTexture(increasetex);

	sf::Texture decreasetex;
	decreasetex.loadFromFile("../res/icons/volume_down.png");
	sf::Sprite decrease;
	decrease.setTexture(decreasetex);

	
	sf::RenderWindow window(sf::VideoMode(700, 300), "MusicPlayer", sf::Style::Titlebar | sf::Style::Close);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::White);
		play.setPosition(120,210);
		prev.setPosition(30,210);
		next.setPosition(210,210);
		decrease.setPosition(120,120);
		mute.setPosition(30,120);
		increase.setPosition(210,120);
		divline.setPosition(300,0);
		divline.setFillColor(sf::Color::Black);
		window.draw(play);
		window.draw(prev);
		window.draw(next);
		window.draw(mute);
		window.draw(increase);
		window.draw(decrease);
		window.draw(divline);

		window.display();
	}

	return 0;
}