// directoryManager.hpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Murphy (jmurphy11@alaska.edu)
// 		Cameron Showalter (cjshowalter@alaska.edu)
//
// Header for the Directory Manager

#ifndef DIRECTORYMANAGER_HPP
#define DIRECTORYMANAGER_HPP

#include <string>			// string erase
#include <vector>			// vector
#include <iostream>			// cout endl
#include <fstream>			// ifstream
#include <algorithm> 		// find replace remove_if
#include <locale>        	// tolower
#include <sys/stat.h>		// used in explorer()

//dirent.h used for navigation
//if using VisualS, include one, else include the other
#ifdef _MSC_VER
	#include "../include/dirent.h"
#else
#	include <dirent.h> 
#endif	


class DirectoryManager
{
public:
//Everything is in the same order here and in the .cpp file_.

	DirectoryManager();
	void handlefile();
	void defaultSettings();
	void printWarning();
	void configfileFound();
	void explorer(char *dir_name);
	bool handlefileOverride(std::string currLine);
	bool isMusicfile(std::string fileName);
	std::vector<std::string> getPlaylist();


private:
	//change in DirectoryManager().
	std::string configPath_;
	std::string defaultAudioPath_;
	bool addLockedFiles_;

	//true - > If songs with same name are found in different directories, includes both in playlist
	//false -> If songs with same name are found in different directories, only adds the first one to playlist
	int uniqueSongOverride_;

	//If file found, look in directories listed. If not, look in defaultAudioPath_
	bool fileFound_;

	//If true, prints warning box around all warnings
	bool warningHit_;

	//I'm stumped, what could these possibly be??
	std::vector<std::string> returnedPlaylist_;
	std::vector<std::string> uniqueSongs_;

	std::ifstream file_;
	//used in multiple methods. Added to private so i don't have to pass it around.

};

#endif // DIRECTORYMANAGER_HPP
