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

#include <string>
#include <vector>
#include <iostream>


#include <dirent.h>
#include <sys/stat.h>


//------TEMP METHODS FOR TESTING / PRINTING (WILL BE DELETED)------
void printVec(std::vector<std::string> & songList)
{
	//note: strings are in form "../res/audio/(songname)"
	std::cout << "Song List:" << std::endl;
	for(unsigned int i=0; i<songList.size(); ++i) {
		std::cout << "   " << songList[i] << std::endl;
	}
	std::cout << "End list;" << std::endl << std::endl;
}
//------END TEMP METHODS------

//returns the name of the Opperating System hopfully....
std::string getOsName()
{
	#ifdef _WIN32
		return "Windows";
	#elif _WIN64
		return "Windows";
	#elif __unix
		return "linux/MacOS";
	#elif __unix__
		return "linux/MacOS";
	#elif __linux__
		return "linux/MacOS";
	#elif __APPLE__
		return "linux/MacOS";	
	#elif __MACH__
		return "linux/MacOS";
	#else
		return "Other";
	#endif
}

//returns true if filename is audio file supported by SFML
bool isMusicFile(std::string fileName)
{
	if(fileName.size() > 6) {
		fileName = fileName.substr( fileName.length() - 6 );
		if(fileName == ".ircam" || fileName == ".mpc2k") {
			return true;
		}
	}
	if(fileName.size() > 5) {
		fileName = fileName.substr( fileName.length() - 5 );
		if(fileName == ".flac" || fileName == ".aiff" || fileName == ".nist" || 
			fileName == ".mat4" || fileName == ".mat5" || fileName == ".rf64") {
			return true;
		}
	}
	if(fileName.size() > 4) {
		fileName = fileName.substr( fileName.length() - 4 );
		if(fileName == ".ogg" || fileName == ".wav" || fileName == ".raw" || 
			fileName == ".paf" || fileName == ".svx" || fileName == ".voc" || 
			fileName == ".w64" || fileName == ".pfv" || fileName == ".htk" || 
			fileName == ".sds" || fileName == ".avr" || fileName == ".sd2" || 
			fileName == ".caf" || fileName == ".wve") {
			return true;
		}
	}
	if(fileName.size() > 3) {
		fileName = fileName.substr( fileName.length() - 3 );
		if(fileName == ".au") {
			return true;
		}
	}
	return false;
}

void exploreWindows(char *dir_name, std::vector<string> & songList) {
	return;
}

//tutorial for explorerLinux from https://www.youtube.com/watch?v=w9l8kLPQ39c
//explorerLinux:
//		returns a vector of all song names inside directory, and recursivly calls all directorys in itself
//		does not put directories inside vector, just strings of paths to songs
void exploreLinux(char *dir_name, std::vector<string> & songList) {
	DIR *dir = NULL; //pointer to an open directory
	struct dirent *entry; //stuff in current directory
	struct stat info; //information about each entry

	//open
	dir = opendir(dir_name);
	if(!dir) {
		std::cout << "Failed to Open Directory" << std::endl;
		return;
	}

	//read
	//keeps reading until finished
	while(( entry = readdir(dir) ) != NULL) {
		//if its not the name if the directory you are in
		if(entry->d_name[0] != '.') {	
			std::string path = std::string(dir_name) + "/" + std::string(entry->d_name);
			if(isMusicFile(path)) {
				songList.push_back(path); //string of directory with entry name at end
				//std::cout << "info: " << std::string(info) << std::endl;
			}
			stat(path.c_str(),&info); //checks to see if file or folder
			if(S_ISDIR(info.st_mode)) {
				exploreLinux((char*)path.c_str(), songList); //if folder, then run this method again on that folder
			}
		}
	}

	//close
	closedir(dir);
	return;
}


//Call this to create the vector of songs
//if opperating system not found, returns empty vector
std::vector<std::string> fileTreeMain() {
	std::string yourOS = getOsName();
	std::vector<std::string> songList;

	std::cout << "TESTING---> YOUR OS IS: " << yourOS  << std::endl;

	if(yourOS == "Windows") {
		//windows file tree system here...
		std::cout<< "windows support coming soon" << std::endl;
		//exploreWindows((char*)"../res/audio", songList);	//<---for now, set the file path here
		return songList;
	}
	else if(yourOS == "linux/MacOS") {
		//the better file tree system here...
		exploreLinux((char*)"../res/audio", songList);	//<---for now, set the file path here
		return songList;
	}
	else {
		//no idea what you're running, take an empty vector
		return songList;
	}
}

#endif // #ifndef DIRECTORYMANAGER_HPP