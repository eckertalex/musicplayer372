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



//tutorial for exploreLinux from https://www.youtube.com/watch?v=w9l8kLPQ39c
void explorerLinux(char *dir_name, std::vector<string> & songList)
{
	DIR *dir = NULL; //pointer to an open directory
	struct dirent *entry; //stuff in current directory
	struct stat info; //information about each entry

	//open
	dir = opendir(dir_name);
	if(!dir)
	{
		std::cout << "Failed to Open Directory" << std::endl;
		return;
	}

	//read
	while(( entry = readdir(dir) ) != NULL) //keeps reading until finished
	{
		if(entry->d_name[0] != '.')//if its not the name if the directory you are in
		{	
			std::string path;
			if(true)//TODO: CHANGE THIS TO ONLY BE TRUE FOR MUSIC FILES (no idea how at the moment... maybe use info? note: exclude .mp3 still)
			{
				path = std::string(dir_name) + "/" + std::string(entry->d_name);
				songList.push_back(path); //string of directory with entry name at end
			}
			stat(path.c_str(),&info); //checks to see if file or folder
			if(S_ISDIR(info.st_mode))
			{
				explorerLinux((char*)path.c_str(), songList); //if folder, then run this method again on that folder
			}
		}
	}

	//close
	closedir(dir);
	return;
}


//Call this to create the vector of songs
//if opperating system not found, returns empty vector
std::vector<std::string> fileTreeMain()
{
	std::string yourOS = getOsName();
	std::vector<std::string> songList;

	std::cout << "TESTING---> YOUR OS IS: " << yourOS  << std::endl;

	if(yourOS == "Windows")
	{
		//windows file tree system here...
		std::cout<< "windows support coming soon" << std::endl;
		return songList;
	}
	else if(yourOS == "linux/MacOS")
	{
		//the better file tree system here...
		explorerLinux((char*)"../res/audio", songList);	//<---for now, set the file path here
		return songList;
	}
	else
	{
		//no idea what you're running
		return songList;
	}
}



#endif // #ifndef DIRECTORYMANAGER_HPP