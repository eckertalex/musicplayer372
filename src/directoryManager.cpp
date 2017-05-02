// directoryManager.cpp
// 26. April 2017
// Created by:
// 		Bryan Burkhardt (bmburkhardt@alaska.edu)  
// 		Alexander Eckert (aeckert@alaska.edu)  
// 		Jeremiah Jacobson (jjacobson2@alaska.edu)  
// 		Jarye Murphy (jmurphy11@alaska.edu)
// 		Cameron Showalter (cjshowalter@alaska.edu) 
//
// Source file_ for directoryManager

#include "../include/directoryManager.hpp"

 
DirectoryManager::DirectoryManager() 
{
	//Possible changes if DirectoryManager is used in another assignment
	//They are never changed after this point.
	//Note, also change bool isMusicFile(str) to another condition if needed
	configPath_ = "../res/DirectoryConfig.txt";
	defaultAudioPath_ = "../res/audio";
	addLockedFiles_ = false;

	//default values. they get changed later if needed
	uniqueSongOverride_ = false;
	warningHit_ = false;


	handlefile();
	if(!fileFound_) 
	{
		defaultSettings();
	}
	if(warningHit_) {
		std::cout << std::endl << "---------------------------------------------------------------------------" << std::endl << std::endl;
	}
	//leave this cout in for final, take out after
	std::cout << "Size of Playlist: " << returnedPlaylist_.size() << std::endl;
}

void DirectoryManager::handlefile() 
{
	file_.open(configPath_);
	if(file_.is_open()) 
	{
		configfileFound();
		file_.close();
		return;
	}
	fileFound_ = false;
}

void DirectoryManager::defaultSettings() 
{
	printWarning();
	std::cout << "Failed to find \"DirectoryConfig.txt\", looked inside \"" << configPath_ << "\"" << std::endl;
	std::cout << "Switched to default: only looking for music in \"" << defaultAudioPath_  << "\"" << std::endl;
	explorer( (char*) defaultAudioPath_.c_str() );
}

void DirectoryManager::printWarning() 
{
	if(!warningHit_) 
	{
		warningHit_ = true;
		std::cout << std::endl << "----------------------------------WARNING----------------------------------" << std::endl << std::endl;
	}
}


void DirectoryManager::configfileFound() 
{
	std::string currLine;
	fileFound_ = true;
	while(!file_.eof()) 
	{
		std::getline(file_, currLine);
		currLine.erase( std::remove_if(currLine.begin(), currLine.end(), isspace), currLine.end() );
		if( currLine == "" || currLine.at(0) == '#' || handlefileOverride(currLine) ) 
		{
			continue;
		}
		explorer( (char*) currLine.c_str());
	}
}

bool DirectoryManager::handlefileOverride(std::string currLine) 
{
	for(unsigned int i = 0; i < currLine.length(); ++i) 
	{
    	currLine[i] = (char) tolower(currLine[i]);
	}
	if( currLine == "uniquesongoverride=false" ) 
	{
		uniqueSongOverride_ = false;
		return true;
	}
	else if ( currLine == "uniquesongoverride=true" ) 
	{
		uniqueSongOverride_ = true;
		std::cout << "Override Detected: will add repeat songs to playlist" << std::endl;
		return true;
	}
	return false;
}

//tutorial for a basic explorer method copied from https://www.youtube.com/watch?v=w9l8kLPQ39c
void DirectoryManager::explorer(char *dir_name) 
{
	DIR *dir = NULL; //pointer to an open directory
	struct dirent *entry; //stuff in current directory
	struct stat info; //information about each entry
	std::string path; //directory name of everything before it + current file_

	//open:
	dir = opendir(dir_name);
	std::ifstream fileChecker;
	if(!dir) 
	{
		printWarning();
		std::cout << "Failed to Open Directory: \"" << dir_name << "\"" << std::endl;
		return;
	}

	//read:
	while(( entry = readdir(dir) ) != NULL) 
	{
		if(entry->d_name[0] != '.') //if the directory is not itself, NOT if the directory is hidden... i think
		{
			path = std::string(dir_name) + "/" + std::string(entry->d_name);
			stat(path.c_str(),&info);
			if( isMusicfile(std::string(entry->d_name)) )
			{
				fileChecker.open(path);
				if(fileChecker.good() || addLockedFiles_)
				{
					if( find(uniqueSongs_.begin(), uniqueSongs_.end(), std::string(entry->d_name)) == uniqueSongs_.end() )
					{
						uniqueSongs_.push_back(std::string(entry->d_name));
						returnedPlaylist_.push_back(path);
					}
					else if(uniqueSongOverride_)
					{
						returnedPlaylist_.push_back(std::string(path));
					} 
				}
				else
				{
					printWarning();
					std::cout << "Failed to Open File: \"" << path << "\"" << std::endl;
				}
				fileChecker.close();
			}
			else if( S_ISDIR(info.st_mode) ) 
			{
				explorer((char*)path.c_str());
			}
		}
	}

	//close:
	closedir(dir);
}

//note: .mp3 is not supported by SFML, and not on this list
bool DirectoryManager::isMusicfile(std::string fileName)
{
	//convert currLine to all lowercase
	for(unsigned int i = 0; i < fileName.length(); ++i)
	{
    	fileName[i] = tolower(fileName[i]);
	}
	//check size incase fileName is a.au, it won't break with fileName.substr( fileName.length()-6 )
	if(fileName.size() > 6) 
	{
		fileName = fileName.substr( fileName.length() - 6 );
		if(fileName == ".ircam" || fileName == ".mpc2k") 
		{
			return true;
		}
	}
	if(fileName.size() > 5) 
	{
		fileName = fileName.substr( fileName.length() - 5 );
		if(fileName == ".flac" || fileName == ".aiff" || fileName == ".nist" || 
			fileName == ".mat4" || fileName == ".mat5" || fileName == ".rf64") 
		{
			return true;
		}
	}
	if(fileName.size() > 4) {
		fileName = fileName
		.substr( fileName.length() - 4 );
		if(fileName == ".ogg" || fileName == ".wav" || fileName == ".raw" || 
			fileName == ".paf" || fileName == ".svx" || fileName == ".voc" || 
			fileName == ".w64" || fileName == ".pfv" || fileName == ".htk" || 
			fileName == ".sds" || fileName == ".avr" || fileName == ".sd2" || 
			fileName == ".caf" || fileName == ".wve") 
		{
			return true;
		}
	}
	if(fileName.size() > 3) {
		fileName = fileName.substr( fileName.length() - 3 );
		if(fileName == ".au") 
		{
			return true;
		}
	}
	return false;
}
	
std::vector<std::string> DirectoryManager::getPlaylist()
{
	return returnedPlaylist_;
}










//############################################################################################
//---------------------------------------BLOCK OF SHAME---------------------------------------
//############################################################################################
//Will be deleted after final
//Code Refactored to this on May-1-2017
/*

std::string DirectoryManager::checkPathFormatForOS(const std::string &currLine) 
{
	if(currLine.size()!=0 && currLine.at(0) == '\"' && currLine.at( currLine.size()-1 ) == '\"') 
	{
		return "Windows";
	}
	return "linux/MacOS";
}

void DirectoryManager::removeWhitespaceOutOfQuotes(std::string & currLine) 
{
	bool quoteFound = false;
	unsigned int saveIndex = 0;
	for(unsigned int i=0; i<currLine.size(); ++i) 
	{
		if(currLine.at(i) == '"') 
		{
			quoteFound = true;
			saveIndex = i;
			if(i != 0) 
			{
				currLine.erase( std::remove_if(currLine.begin(), currLine.begin()+i, isspace), currLine.end() );
			}
			break;
		}
	}
	if(quoteFound) 
	{
		currLine.erase( std::remove_if(currLine.begin()+saveIndex, currLine.end(), isspace), currLine.end() );
	}
}

bool DirectoryManager::isOSother() 
{
	currOperatingSystem_ = getOsName();
	if(currOperatingSystem_ == "Other")
	{
		printWarning();
		std::cout << "UNKNOWN OS: set override located inside \"" << configPath_ <<"\"" << std::endl;
		return true;
	}
	return false;
}

std::string DirectoryManager::getOsName() {
	//If override is set:
	if(operatingSystemOverride_ == 1) {
		return "linux/MacOS";
	}
	else if(operatingSystemOverride_ == 2) {
		return "Windows";
	}
	else if(operatingSystemOverride_ == 3) {
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

void DirectoryManager::formatPathForCorrectOS(std::string &currLine) 
{
	//unknown OS, don't know how to format. leave as is
	if( currOperatingSystem_ == "Other" ) 
	{
		return;
	}
	//if there is a valad quote, it will now be at currLine.at(0). linux directories dont have quotes so they aren't affected
	removeWhitespaceOutOfQuotes(currLine);
	//if currLine is formated for windows, and OS = windows: erase possible whitespace outside of quotes
	if(checkPathFormatForOS(currLine) == "Windows" && currOperatingSystem_ == "Windows") 
	{
		//do nothing, Already a windows directory
		return;
	}
	//if currLine is formated for linux, and OS = linux: erase all whitespace. (won't erase '\ ')
	else if(checkPathFormatForOS(currLine) == "linux/MacOS" && currOperatingSystem_ == "linux/MacOS") 
	{
		currLine.erase( std::remove_if(currLine.begin(), currLine.end(), isspace), currLine.end() );
	}
	//if currLine is formated for windows, and OS = linux: remove whitespace outside of quotes, replace '\' with '/' ,replace ' ' with '\ '
	else if(checkPathFormatForOS(currLine) == "Windows" && currOperatingSystem_ == "linux/MacOS") 
	{
		std::replace( currLine.begin(), currLine.end(), '\\', '/' );
		for(unsigned int i=0; i<currLine.size(); ++i) 
		{
			if(currLine.at(i) == ' ') 
			{
				currLine.insert(i,"\\");
			}
		}
		currLine.erase(0,1);
		currLine.pop_back();
	}
	//if currLine is formated for linux, and OS = windows: erase all whitespace. (won't erase '\ '), remove all '\' replace '/' with '\'
	else if(checkPathFormatForOS(currLine) == "linux/MacOS" && currOperatingSystem_ == "Windows") 
	{
		for(unsigned int i=0; i<currLine.size(); ++i) 
		{
			if(currLine[i] == '\\') 
			{
				currLine.erase(i,0);
			}
		}
		std::replace( currLine.begin(), currLine.end(), '/', '\\' );
		currLine = "\"" + currLine + "\"";
	}
}


*/
//############################################################################################
//--------------------------------------------------------------------------------------------
//############################################################################################