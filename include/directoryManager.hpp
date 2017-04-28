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
#include <fstream>			// file reading
#include <algorithm> 		// find replace remove_if
#include <cctype> 			// isspace

#include <dirent.h> 		//directory navagation
#include <sys/stat.h>		//directory navagation


//------TEMP METHODS FOR TESTING / PRINTING (WILL BE DELETED)------
void printVec(const std::vector<std::string> & songList);

//------END TEMP METHODS------



//------------------------------------------NOTICE------------------------------------------
//The following global variables exist, but only in directoryManager.hpp
//
//	static int OPERATINGSYSTEMOVERRIDE
//	static bool REPEATSONGSOVERRIDE
//---------------------------------------------------------------------



//deleteStringPaths
//	goes through the playlist vector and adds all the songs to a new vector without the path before
//	note: it is assumed that fileTreeMain() was used to generate pathList, so no error checking is done
std::vector<std::string> deleteStringPaths(std::vector<std::string> &pathList, std::string &yourOS);

//formatPath:
//	removes all whitespace from a string, exept for '\ '
//	if yourOS = "Windows", removes '\' from '\ ' and puts quotes around currLine
void formatPath(std::string &str, std::string &yourOS);

//isFileOverride
//checks to see if str is a override command
//Note: will also set the override
bool isFileOverride(std::string str);

//getOsName
//	returns the name of the user Opperating System
//	if not found, returns "Other"
//	can be overridden
std::string getOsName();

//note: .mp3 is not supported, and not on this list
//isMusicFile
//	returns true if filename is audio file supported by SFML
//	.mp3 files will not be included
bool isMusicFile(std::string fileName);

//tutorial for a more basic explorer from https://www.youtube.com/watch?v=w9l8kLPQ39c
//explorer:
//		returns a vector of all song names inside directory, and recursivly calls all directorys in itself
//		does not put directories inside vector, just strings of paths to supported songs
void explorer(char *dir_name, std::vector<std::string> & songList, std::vector<std::string> & uniqueSongs, std::string & yourOS);

//Call this to create the vector of songs
//if opperating system not found, returns empty vector
std::vector<std::string> fileTreeMain();




#endif // DIRECTORYMANAGER_HPP
