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



//note: printVec will be deleted once testing is done
void printVec(std::vector<std::string> & songList);

class DirectoryManager
{
public:
	DirectoryManager();

	void handleFile();

	std::string getOsName();

	void configFileFound();

	bool handleFileOverride(std::string currLine);

	void formatPathForCorrectOS(std::string & path);

	void explorer(char *dir_name);

	std::vector<std::string> getPlaylist();

	bool isMusicFile(std::string fileName);

private:
	//Overrides can be accessed/changed inside DirectoryConfig.txt

	int operatingSystemOverride;
	//0 -> program will automatically detect the OS running the program
	//1 -> program will format directories for "linux/MacOS"
	//2 -> program will format directories for "Windows"
	//3 -> program has no idea what path system to use, so "Other"
	//		Note: if "Other", program will not find any songs. Added for testing purposes

	int uniqueSongOverride;
	//true - > If songs with same name are found in different directories, includes both in playlist
	//false -> If songs with same name are found in different directories, only adds the first one to playlist

	std::string yourOS;
	//returns your operating system. IS affected by oppereatingSystemOveride
	//possible returns: "Windows" "linux/MacOS" "Other"


	std::vector<std::string> songList;
	//it's a list of songs...

	std::vector<std::string> uniqueSongs;
	//private because no reason for others to use this. it's not equal to songList if
	//uniqueSongOverride is ever set to true

	std::ifstream file;
	//used in multiple methods. Added to private so i don't have to pass it around.

};



#endif // DIRECTORYMANAGER_HPP
