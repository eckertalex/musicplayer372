// directoryManager.cpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjacobson2@alaska.edu)  
// 		Jarye Maurphy (jmurphy11@alaska.edu)  
// 		Cameron Showalter (cjshowalter@alaska.edu) 
//
// Source file for directoryManager
#include "../include/directoryManager.hpp" 

#include <string>			// string erase
#include <vector>			// vector
#include <iostream>			// cout endl
#include <fstream>			// file reading
#include <algorithm> 		// find replace remove_if
#include <cctype> 			// isspace

#include <dirent.h> 		//directory navagation
#include <sys/stat.h>		//directory navagation


//------TEMP METHODS FOR TESTING / PRINTING (WILL BE DELETED)------
void printVec(const std::vector<std::string> &songList)
{
	//note: strings are in form "../res/audio/(songname)"
	std::cout << "Song List:" << std::endl;
	for(unsigned int i=0; i<songList.size(); ++i) {
		std::cout << "   " << songList[i] << std::endl;
	}
	std::cout << "End list;" << std::endl << std::endl;
}

//------END TEMP METHODS------


//Overrides can be accessed/changed inside DirectoryConfig.txt

//OPERATINGSYSTEMOVERRIDE
	//0 -> program returns empty vector if os not reconized
	//1 -> program will treat your computer as "linux/MacOS" REGUARDLESS of if it knows your os
	//2 -> program will treat your computer as "Windows" REGUARDLESS of if it knows your os
static int OPERATINGSYSTEMOVERRIDE = 0;

//REPEATSONGSOVERRIDE
	//false -> if program finds multiple songs of same name if different directories, will NOT add both
	//true  -> if program finds multiple songs of same name if different directories, it adds both
static bool REPEATSONGSOVERRIDE = false;




//deleteStringPaths
//	goes through the playlist vector and adds all the songs to a new vector without the path before
//	note: it is assumed that fileTreeMain() was used to generate pathList, so no error checking is done
std::vector<std::string> deleteStringPaths(std::vector<std::string> &pathList, std::string &yourOS)
{
	std::vector<std::string> playlist;
	//if pathList is empty, do nothing
	if(pathList[0] == "")
	{
		return playlist;
	}
	for(unsigned int i=0; i<pathList.size(); ++i)
	{	
		if(yourOS == "Windows")
		{
			//if windows path, remove the last char from string, should be a (")
			pathList[i].pop_back();
		}

		std::string songName = "";
		//search through string backwards for '/' or '\', and add everything after to playlist
		if(yourOS == "Windows")
		{
			songName = pathList[i].substr( pathList[i].find_last_of('\\')+1 );
		}
		else // yourOS == "linux/MacOS"
		{
			songName = pathList[i].substr( pathList[i].find_last_of('/')+1 );
		}
		playlist.push_back(songName);
	}
	return playlist;
}

//formatPath:
//	removes all whitespace from a string, exept for '\ '
//	if yourOS = "Windows", removes '\' from '\ ' and puts quotes around currLine
void formatPath(std::string &str, std::string & yourOS)
{
	if(yourOS == "Windows"){
		//if on Windows, put quotes around possible paths to read spaces
		str = "\"" + str + "\"";
	}
	for(unsigned int i=0; i<str.size(); ++i)
	{
		// i!=0 to keep str.at(i) from being out of range
		if( i!=0 && str.at(i) == ' ' && str.at(i-1) == '\\'){
			if(yourOS == "Windows"){
				//if on Windows, erase the back slash but leave the space
				str.erase( str.begin()+(i-1) );
			}
			continue;
		}
		//now that '\ ' has been ignored, remove all other whitespace
		if( std::isspace(str.at(i)) == true )
		{
			str.erase(str.begin()+i);
		}
	}
}

//isFileOverride
//checks to see if str is a override command
//Note: will also set the override
bool isFileOverride(std::string str)
{
	if(str == "REPEATSONGSOVERRIDE=false")
	{
		REPEATSONGSOVERRIDE = false;
		return true;
	}
	else if (str == "REPEATSONGSOVERRIDE=true")
	{
		REPEATSONGSOVERRIDE = true;
		std::cout << "Override Detected: Will add repeat songs to playlist" << std::endl;
		return true;
	}
	else if (str == "OPERATINGSYSTEMOVERRIDE=0")
	{
		OPERATINGSYSTEMOVERRIDE = 0;
		return true;
	}
	else if (str == "OPERATINGSYSTEMOVERRIDE=1")
	{
		OPERATINGSYSTEMOVERRIDE = 1;
		std::cout << "Override Detected: OS is \"linux/MacOS\"" << std::endl;
		return true;
	}
	else if (str == "OPERATINGSYSTEMOVERRIDE=2")
	{
		OPERATINGSYSTEMOVERRIDE = 2;
		std::cout << "Override Detected: OS is \"Windows\"" << std::endl;
		return true;
	}
	return false;
}

//getOsName
//	returns the name of the user Opperating System
//	if not found, returns "Other"
//	can be overridden
std::string getOsName()
{
	//If override is set:
	if(OPERATINGSYSTEMOVERRIDE == 1){
		return "linux/MacOS";
	}
	else if(OPERATINGSYSTEMOVERRIDE == 2){
		return "Windows";
	}

	//check for OS
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

//note: .mp3 is not supported, and not on this list
//isMusicFile
//	returns true if fileName is audio file supported by SFML
//	.mp3 files will not be included
bool isMusicFile(std::string fileName)
{
	//check size incase fileName is a.au, it won't break with fileName.substr( fileName.length()-6 )
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

//tutorial for a more basic explorer from https://www.youtube.com/watch?v=w9l8kLPQ39c
//explorer:
//		returns a vector of all song names inside directory, and recursivly calls all directorys in itself
//		does not put directories inside vector, just strings of paths to supported songs
void explorer(char *dir_name, std::vector<std::string> & songList, std::vector<std::string> & uniqueSongs, std::string & yourOS)
{
	DIR *dir = NULL; //pointer to an open directory
	struct dirent *entry; //stuff in current directory
	struct stat info; //information about each entry

	std::string path; //directory name of everything before it + current file


	//open
	dir = opendir(dir_name);
	//if bad directory name or can't open, do nothing else
	if(!dir) {
		std::cout << "Failed to Open Directory: \"" << dir_name << "\"" << std::endl;
		return;
	}

	//read
	//keeps reading until finished
	while(( entry = readdir(dir) ) != NULL) {
		//if its not the name if the directory you are in
		if(entry->d_name[0] != '.') {	
			if(yourOS == "linux/MacOS")
			{
				path = std::string(dir_name) + "/" + std::string(entry->d_name);
			}
			else // if(yourOS == "Windows")
			{
				path = std::string(dir_name) + "\\" + std::string(entry->d_name);
			}
			//if the current path a song and the song is not in unique,add path/song to songlist and song to unique
			if( isMusicFile(path) && !(find(uniqueSongs.begin(), uniqueSongs.end(), std::string(entry->d_name)) != uniqueSongs.end()) )
			{
				 //push baack a string of directory with entry name at end
				songList.push_back(path);
				//if REPEATSONGOVERIDE is true, it never can pushback so uniqueSongs stays empty;
				if(REPEATSONGSOVERRIDE == false){
					uniqueSongs.push_back(std::string(entry->d_name));
				}
			}
			//checks to see if file or folder
			stat(path.c_str(),&info); 
			if(S_ISDIR(info.st_mode)) {
				//if folder, then run this method again on new folder
				explorer((char*)path.c_str(), songList, uniqueSongs, yourOS);
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
	//where DirectoryConfig.txt file is located, only declared here
	//	Windows users: still use forward slash below. if Windows is detected, "/" is autochanged to "\\"
	std::string filePath = "../res/DirectoryConfig.txt";

	//songList is what is eventually returned, filled of paths to all songs found
	std::vector<std::string> songList;
	//uniqueSongs is NOT returned, only fills with unique songs if REPEATSONGSOVERRIDE=false
	std::vector<std::string> uniqueSongs;

	//try to open the file. if can't, only look in "../res/audio"
	std::string yourOS = getOsName();
	std::cout << "TESTING---> YOUR OS IS: " << yourOS  << std::endl;
	if(yourOS == "Other")
	{
		std::cout << "UNKNOWN OS: set override located inside \"" << filePath <<"\"" << std::endl;
		return songList;
	}
	else if( yourOS == "Windows" )
	{
		//changes all '/' in file path to '\\'
		std::replace( filePath.begin(), filePath.end(), '/', '\\');
		//add quotes around of path incase of spaces 
		filePath = "\"" + filePath + "\"";
	}
	//else if not "Windows" and not "Other", then yourOS = "linux/MacOS"


	//file open, start running through all directories inside it
	std::ifstream file (filePath);

	if(file.is_open())
	{	

		//go through file line by line with currLine
		std::string currLine;

		while(!file.eof())
		{
			getline(file, currLine);

			//	removes all whitespace from a string, exept for '\ '
			//	if yourOS = "Windows", removes '\' from '\ ' and puts quotes around currLine
			formatPath(currLine, yourOS);

			//removes possible white space, makes for easy comparing
			//next line found on http://stackoverflow.com/questions/14233065/remove-whitespace-in-stdstring
			currLine.erase( std::remove_if( currLine.begin(), currLine.end(), ::isspace ), currLine.end() );

			//if empty, comment or overide, do nothing
			//note: isFileOverride also sets the overrides
			if( currLine == "" || currLine.at(0) == '#' || isFileOverride(currLine) ){
				continue;
			}
			//else try to run everything else as a directory
			//if it's not, should still not crash
			else{
				if(yourOS == "Windows")
				{	//if you're on windows, change to back slashes
					std::replace( currLine.begin(), currLine.end(), '/', '\\');
				}
				explorer( (char*) currLine.c_str(), songList, uniqueSongs, yourOS );
			}
		}
		file.close();

	}
	//failed to find/open file. Only looks in default audio file. Even if audio file is deleted, program won't break,
	//	It will just return an empty vector
	else
	{
		std::cout << "Failed to find \"DirectoryConfig.txt\", looked inside \"" << filePath << "\"" << std::endl;
		std::cout << "Switched to default: only looking for music in \"musicplayer372/res/audio\"" << std::endl;

		if(yourOS == "Windows"){
			explorer( (char*) "..\\res\\audio", songList, uniqueSongs, yourOS);
		}
		else{// "linux/MacOS"
			explorer( (char*) "../res/audio", songList, uniqueSongs, yourOS);
		}

	}

	std::cout<< "TESTING REMOVEPATH: " << std::endl;
	printVec(deleteStringPaths(songList, yourOS));
	std::cout<< "TESTING REMOVEPATH END" << std::endl;

	

//program crashes if passed an empty vector.
//temp fix: if empty, add default song
	if(songList[0] == "")
	{
		std::cout << "SONGLIST RETURNED EMPTY: adding default song to prevent program from crashing. do real fix later" << std::endl;
		if(yourOS == "Windows"){
			songList.push_back("..\\res\\audio\\AMemoryAway.ogg");
		}
		else{
			songList.push_back("../res/audio/AMemoryAway.ogg");
		}
	}
	return songList;
}