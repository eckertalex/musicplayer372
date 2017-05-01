// timer.cpp
// 30. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)
// 		Alexander Eckert (aeckert@alaska.edu)
// 		Jeremiah Jacobson (jjacobson2@alaska.edu)
// 		Jarye Murphy (jmurphy11@alaska.edu)
// 		Cameron Showalter (cjshowalter@alaska.edu)
//
// Source file for timer

#include <iomanip>

#include "../include/timer.hpp"

/****** Timer Functions ******/

void Timer::updateCurrentTimer() {
	currentTimer = music->_music.getPlayingOffset();
	currentTimeSeconds = (int)currentTimer.asSeconds();
	currentTimeMinutes = convertToMinutes((int)currentTimer.asSeconds());
	currentTimeHours = convertToHours((int) currentTimeSeconds);
	currentTimerStreamSeconds.str("");
	currentTimerStreamMinutes.str("");
	currentTimerStreamHours.str("");
	currentTimerStreamSeconds << std::fixed << std::setprecision(0) << (int) currentTimeSeconds % 60;
	currentTimerStreamMinutes << std::fixed << std::setprecision(0) << ((int)currentTimeMinutes%60);
	currentTimerStreamHours << std::fixed << std::setprecision(0) << (currentTimeHours);

	// Seconds
	if ((int)currentTimeSeconds%60 < 10) {
		currentSec = "0" + currentTimerStreamSeconds.str() + "/";
	}
	else {
		currentSec = currentTimerStreamSeconds.str() + "/";
	}
	// Minutes
	if((int)currentTimeMinutes%60 < 10) {
		currentMin = "0" + currentTimerStreamMinutes.str() + ":";
	}
	else {
		currentMin = currentTimerStreamMinutes.str() + ":";
	}
	// Hours
	if((int)currentTimeHours < 10) {
		currentHour = "0" + currentTimerStreamHours.str() + ":";
	}
	else {
		currentHour = currentTimerStreamHours.str() + ":";
	}
}

void Timer::updateTotalTimer() {
	totalTimer = music->_music.getDuration();
	totalTimeSeconds = (int)totalTimer.asSeconds();
	totalTimeMinutes = convertToMinutes((int) totalTimeSeconds);
	totalTimeHours = convertToHours((int) totalTimeSeconds);
	totalTimerStreamSeconds.str("");
	totalTimerStreamMinutes.str("");
	totalTimerStreamHours.str("");
	totalTimerStreamSeconds << std::fixed << std::setprecision(0) << (int) totalTimeSeconds % 60;
	totalTimerStreamMinutes << std::fixed << std::setprecision(0) << ((int)totalTimeMinutes%60);
	totalTimerStreamHours << std::fixed << std::setprecision(0) << (totalTimeHours);

	// Seconds
	if ((int)totalTimeSeconds%60 < 10) {
		totalSec = "0" + totalTimerStreamSeconds.str();
	}
	else {
		totalSec = totalTimerStreamSeconds.str();
	}
	// Minutes
	if((int)totalTimeMinutes%60 < 10) {
		totalMin = "0" + totalTimerStreamMinutes.str() + ":";
	}
	else {
		totalMin = totalTimerStreamMinutes.str() + ":";
	}
	// Hours
	if((int)totalTimeHours < 10) {
		totalHour = "0" + totalTimerStreamHours.str() + ":";
	}
	else {
		totalHour = totalTimerStreamHours.str() + ":";
	}
}

std::string Timer::selectDisplayTimer() {
	// 0:xx
	std::string rv = "";
	
	if(music->_music.getStatus() == 0) {
		music->callNextSong();
	}
	if(totalTimeMinutes < 1) {
		rv = "0:";
		rv += currentSec + "0:";
		rv += totalSec;
		return rv;
	}
		// xx:xx
	else if(currentTimeHours < 1 && totalTimeHours < 1 && totalTimeMinutes > 0) {
		return currentMin + currentSec + totalMin + totalSec;
	}
		// xx:xx:xx
	else {
		return currentHour + currentMin + currentSec + totalHour + totalMin + totalSec;
	}

	
}

void Timer::displayTimer() {
	updateCurrentTimer();
	updateTotalTimer();
	selectDisplayTimer();
}

int Timer::convertToMinutes(int seconds) {
	return seconds/60;
}

int Timer::convertToHours(int seconds) {
	return (seconds/(60*60));
}

// void Timer::setStyleTimer(sf::Font font) {
// 	displayTimerText.setFont(font);
// 	displayTimerText.setCharacterSize(24);
// 	displayTimerText.setColor(sf::Color::Red);
// 	displayTimerText.setPosition(40,75);
// }

Timer::Timer(std::shared_ptr<Music> music) : music(music) {
}