// directoryManager.hpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjjacobson2@alaska.edu)  
// 		Jarye Maurphy (@alaska.edu)  
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

//dirent.h used for navigtion
//if using VisualS, include one, else include the other
#ifdef _MSC_VER
	#include "../include/dirent.h"
#else
#	include <dirent.h> 
#endif	





//note: printVec will be deleted once testing is done
void printVec(const std::vector<std::string> & returnedPlaylist_);

class DirectoryManager
{
public:
//Everything is in the same order here and in the .cpp file_.

	DirectoryManager();
	void handlefile();
	void defaultSettings();
	void printWarning();
	void formatPathForCorrectOS(std::string & path);
	std::string getOsName();
	void configfileFound();
	bool isOSother();
	void explorer(char *dir_name);
	void removeWhitespaceOutOfQuotes(std::string & currLine);
	std::string checkPathFormatForOS(const std::string &currLine);
	bool handlefileOverride(std::string currLine);
	bool isMusicfile(std::string file_Name);




	std::vector<std::string> getPlaylist();


private:
	//Overrides can be accessed/changed inside DirectoryConfig.txt
	std::string configPath_;
	std::string defaultAudioPath_;

	int operatingSystemOverride_;
	//0 -> program will automatically detect the OS running the program
	//1 -> program will format directories for "linux/MacOS"
	//2 -> program will format directories for "Windows"
	//3 -> program has no idea what path system to use, so "Other"
	//		Note: if "Other", program will not find any songs. Added for testing purposes

	int uniqueSongOverride_;
	//true - > If songs with same name are found in different directories, includes both in playlist
	//false -> If songs with same name are found in different directories, only adds the first one to playlist

	std::string currOperatingSystem_;
	//returns your operating system. IS affected by oppereatingSystemOveride
	//possible returns: "Windows" "linux/MacOS" "Other"

	bool file_Found_;

	bool warningHit_;

	std::vector<std::string> returnedPlaylist_;
	//it's a list of songs...

	std::vector<std::string> uniqueSongs_;
	//private because no reason for others to use this. it's not equal to returnedPlaylist_ if
	//uniqueSongOverride_ is ever set to true

	std::ifstream file_;
	//used in multiple methods. Added to private so i don't have to pass it around.

};



#endif // DIRECTORYMANAGER_HPP
