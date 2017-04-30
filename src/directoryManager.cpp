// directoryManager.cpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjacobson2@alaska.edu)  
// 		Jarye Murphy (jmurphy11@alaska.edu)
// 		Cameron Showalter (cjshowalter@alaska.edu) 
//
// Source file for directoryManager
#include "../include/directoryManager.hpp" 


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

//------TEMP METHODS FOR TESTING / PRINTING (WILL BE DELETED)------
void printVec(std::vector<std::string> & songList) 
{
	//note: strings are in form "../res/audio/(songname)"
	std::cout << "Song List:" << std::endl;
	for(unsigned int i=0; i<songList.size(); ++i) 
	{
		std::cout << "   " << songList[i] << std::endl;
	}
	std::cout << "End list;" << std::endl << std::endl;
}


//------END TEMP METHODS------






DirectoryManager::DirectoryManager()
{
	//default overide values. they get changed later if needed
	operatingSystemOverride = 0;
	uniqueSongOverride = false;

	//read from file and set overide there
	handleFile();
	printVec(songList);
	std::cout << "Size of Playlist: " << songList.size() << std::endl;
}

//getOsName
//	returns the name of the user Opperating System
//	if not found, returns "Other"
//	can be overridden
std::string DirectoryManager::getOsName()
{
	//If override is set:
	if(operatingSystemOverride == 1)
	{
		return "linux/MacOS";
	}
	else if(operatingSystemOverride == 2)
	{
		return "Windows";
	}
	else if(operatingSystemOverride == 3)
	{
		return "Other";
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

void DirectoryManager::handleFile()
{
//because operatingsystem override is inside file, and i need to know the operating system to find
//the file, try to open the file with linux/mac, then windows. if both fail, then no file exists

	//where DirectoryConfig.txt file is located, only declared here
	//	Windows users: still use forward slash below. if Windows is detected, "/" is autochanged to "\\"
	std::string configPath = "../res/DirectoryConfig.txt";
	std::string savePath = configPath;

	//try to open file with linux/mac directory
	file.open(configPath);
	if(file.is_open())
	{
		yourOS = "linux/MacOS";
		configFileFound();
		file.close();
		return;
	}
	//clears flags, tries to open the file with windows
	//this does not mean youre on windows, it runs getOsName() if file not found
	yourOS = "Windows";
	formatPathForCorrectOS(configPath);

	file.clear();
	file.open(configPath);
	if(file.is_open())
	{	
		configFileFound();
		file.close();
		return;
	}
	//else could not open windows path either, file not found. Do default task
	else
	{
		//file not found, overrides are never set, so check for OS, then run explorer with default path if OS != "Other"
		yourOS = getOsName();
		if(yourOS == "Other")
		{
			//if you trip this, it could not find file, and getOsName only checks for linux/mac/windows
			//best way to fix: add file back. Program tries both the linux and windows directory paths
			//so even if your not on one of those three, if it has the same directory, it will still work
			std::cout << "UNKNOWN OS: set override located inside \"" << configPath <<"\"" << std::endl;
			return;
		}
		configPath = savePath;
		std::cout << "----------------------------------WARNING----------------------------------" 		<< std::endl;
		std::cout << "Failed to find \"DirectoryConfig.txt\", looked inside \"" << configPath << "\"" 	<< std::endl;
		std::cout << "Switched to default: only looking for music in \"musicplayer372/res/audio\"" 		<< std::endl;
		std::cout << "				Or looking in \"..\\res\\audio\" if on Windows"						<< std::endl;
		std::cout << "---------------------------------------------------------------------------" 		<< std::endl;

		if(yourOS == "Windows")
		{
			explorer( (char*) "..\\res\\audio");
		}
		else
		{
			// "linux/MacOS"
			explorer( (char*) "../res/audio");
		}
	}
	file.clear();
}

void DirectoryManager::formatPathForCorrectOS(std::string &currLine)
{
	//if on windows, and currLine is surrounded in quotes, Its already been formated so do nothing
	if(yourOS == "Windows" && currLine.at(0) == '\"' && currLine.at( currLine.size()-1 ) == '\"')
	{
		return;
	}
	//remove all whitespace but '\ ', incase there is whitespace on either side of currLine
	currLine.erase( std::remove_if(currLine.begin(), currLine.end(), isspace), currLine.end() );

	if(yourOS == "Windows")
	{
		std::replace( currLine.begin(), currLine.end(), '/', '\\' );
		currLine = "\"" + currLine + "\"";
	}
}


void DirectoryManager::configFileFound()
{
	//go through file line by line with currLine
	std::string currLine;

	while(!file.eof())
	{
		std::getline(file, currLine);

		//	removes all whitespace from a string, exept for '\ '
		//	if yourOS = "Windows", also removes '\' from '\ ' and puts quotes around currLine
		formatPathForCorrectOS(currLine);



		//if empty, comment or overide, do nothing
		//note: handleFileOverride also sets the overrides if fouond
		if( currLine == "" || currLine.at(0) == '#' || handleFileOverride(currLine) )
		{
			continue;
		}
		//else try to run everything else as a directory
		//if it's not, should still not break/crash
		else
		{
			//may need to add currLine length check here and on the recursive call inside explorer
			//no idea how long c_strings can be. Wiki says .data() included by string does same thing. better?
			explorer( (char*) currLine.c_str());
		}
	}
}



bool DirectoryManager::handleFileOverride(std::string currLine)
{
	currLine.erase( std::remove_if(currLine.begin(), currLine.end(), isspace), currLine.end() );
	//convert currLine to all lowercase
	for(unsigned int i = 0; i < currLine.length(); ++i)
	{
    	currLine[i] = (char) tolower(currLine[i]);
	}
	//check for if it equals any override options
	if( currLine == "uniquesongoverride=false" )
	{
		uniqueSongOverride = false;
		return true;
	}
	else if ( currLine == "uniquesongoverride=true" )
	{
		uniqueSongOverride = true;
		std::cout << "Override Detected: Will add repeat songs to playlist" << std::endl;
		return true;
	}
	else if ( currLine == "operatingsystemoverride=0" )
	{
		operatingSystemOverride = 0;
		return true;
	}
	else if ( currLine == "operatingsystemoverride=1" )
	{
		operatingSystemOverride = 1;
		std::cout << "Override Detected: OS is \"linux/MacOS\"" << std::endl;
		return true;
	}
	else if ( currLine == "operatingsystemoverride=2" )
	{
		operatingSystemOverride = 2;
		std::cout << "Override Detected: OS is \"Windows\"" << std::endl;
		return true;
	}
	else if ( currLine == "operatingsystemoverride=3" )
	{
		operatingSystemOverride = 3;
		std::cout << "Override Detected: OS is \"Other\"" << std::endl;
		return true;
	}
	return false;
}

//tutorial for a basic explorer method copied from https://www.youtube.com/watch?v=w9l8kLPQ39c
//		returns a vector of all song names inside directory, and recursivly calls all directorys in itself
//		does not put directories inside vector, just strings of paths to supported songs
void DirectoryManager::explorer(char *dir_name)
{
	DIR *dir = NULL; //pointer to an open directory
	struct dirent *entry; //stuff in current directory
	struct stat info; //information about each entry

	std::string path; //directory name of everything before it + current file


	//open:
	dir = opendir(dir_name);
	//if bad directory name or can't open, do nothing else
	if(!dir) 
	{
		std::cout << "Failed to Open Directory: \"" << dir_name << "\"" << std::endl;
		return;
	}

	//read:
	while(( entry = readdir(dir) ) != NULL) 
	{
		//if its not the name if the directory you are in
		if(entry->d_name[0] != '.') 
		{	
			if(yourOS == "linux/MacOS")
			{
				path = std::string(dir_name) + "/" + std::string(entry->d_name);
			}
			else // if(yourOS == "Windows")
			{
				//can't use convertPathToWindows because this is a recursive method, and that adds " " every time its called
				path = std::string(dir_name) + "\\" + std::string(entry->d_name);
			}
			//if the current path a song and the song is not in unique,add path/song to songlist and song to unique
			//std::cout << "Path: " << dir_name << " song: " << std::string(entry->d_name) << std::endl;
			if( isMusicFile(std::string(entry->d_name)) )
			{

				//if find reaches the end, the song is not already in uniquesongs, add it to both
				if( find(uniqueSongs.begin(), uniqueSongs.end(), std::string(entry->d_name)) == uniqueSongs.end() )
				{
					uniqueSongs.push_back(std::string(entry->d_name));
					songList.push_back(path);
				}
				//else it has the song in uniqueSongs already, check flag to see if it gets added to songlist
				else if(uniqueSongOverride != 0)
				{
					songList.push_back(std::string(path));
				}
			}
			//checks to see if file or folder
			stat(path.c_str(),&info); 
			if(S_ISDIR(info.st_mode)) 
			{
				//if folder, then run this method again on new folder
				explorer((char*)path.c_str());
			}
		}
	}

	//close:
	closedir(dir);
}

//note: .mp3 is not supported, and not on this list
//isMusicFile
//	returns true if fileName is audio file supported by SFML
//	.mp3 files will not be included
bool DirectoryManager::isMusicFile(std::string fileName)
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
	
std::vector<std::string> DirectoryManager::getPlaylist()
{
	return songList;
}

