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
	//These two paths are only defined here so you can change them easy if needed
	//directory configuation does not matter, Program tries to open with both
	//linux/MacOS and Windows style repositories.
	configPath_ = "../res/DirectoryConfig.txt";
	defaultAudioPath_ = "../res/audio";

	//default overide values. they get changed later if needed
	operatingSystemOverride_ = 0;
	uniqueSongOverride_ = false;
	warningHit_ = false;


	handlefile();
	if(!file_Found_)
	{
		defaultSettings();
	}
	if(warningHit_)
	{
		std::cout << "---------------------------------------------------------------------------" << std::endl << std::endl;
	}
	std::cout << "Size of Playlist: " << returnedPlaylist_.size() << std::endl;

}

void DirectoryManager::handlefile()
{
//because operatingsystem override is inside file_, and i need to know the operating system to find
//the file_, try to open the file_ with linux/mac, then windows. if both fail, then no file_ exists


	//try to open file_ with linux/mac directory
	currOperatingSystem_ = "linux/MacOS";
	formatPathForCorrectOS(configPath_);
	file_.open(configPath_);
	if(file_.is_open())
	{
		configfileFound();
		file_.close();
		return;
	}
	//clears flags, tries to open the file_ with windows
	//this does not mean youre on windows, it runs getOsName() if file_ not found
	currOperatingSystem_ = "Windows";
	formatPathForCorrectOS(configPath_);
	file_.clear();
	file_.open(configPath_);
	if(file_.is_open())
	{	
		configfileFound();
		file_.close();
		return;
	}
	//else could not open windows path either, file_ not found. Do default task
	else
	{
		currOperatingSystem_ = getOsName();
		file_Found_ = false;
	}
	file_.clear();
}

void DirectoryManager::defaultSettings()
{
	//calls getOsName().
	//if unknown OS, then do nothing. isOSother() takes care of warning user
	if(isOSother())
	{
		return;
	}
	formatPathForCorrectOS(configPath_);
	printWarning();
	std::cout << "Failed to find \"DirectoryConfig.txt\", looked inside \"" << configPath_ << "\"" 	<< std::endl;
	std::cout << "Switched to default: only looking for music in \"musicplayer372/res/audio\"" 		<< std::endl;
	std::cout << "		Or looking in \"..\\res\\audio\" if on Windows"						<< std::endl;

	formatPathForCorrectOS(defaultAudioPath_);
	explorer( (char*) defaultAudioPath_.c_str() );
}

void DirectoryManager::printWarning()
{
	if(!warningHit_)
	{
		warningHit_ = true;
		std::cout << std::endl << "----------------------------------WARNING----------------------------------" << std::endl;
	}
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

//getOsName
//	returns the name of the user Opperating System
//	if not found, returns "Other"
//	can be overridden
std::string DirectoryManager::getOsName()
{
	//If override is set:
	if(operatingSystemOverride_ == 1)
	{
		return "linux/MacOS";
	}
	else if(operatingSystemOverride_ == 2)
	{
		return "Windows";
	}
	else if(operatingSystemOverride_ == 3)
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

void DirectoryManager::configfileFound()
{
	//go through file_ line by line with currLine
	std::string currLine;
	file_Found_ = true;
	while(!file_.eof())
	{
		std::getline(file_, currLine);
		//	removes all whitespace from a string, exept for '\ '
		//	if currOperatingSystem_ = "Windows", also removes '\' from '\ ' and puts quotes around currLine

		//if empty, comment or overide, do nothing
		//note: handlefileOverride also sets the overrides if found
		//isOSother() stops the program from exploring while the OS override = "Other"
		if( currLine == "" || currLine.at(0) == '#' || handlefileOverride(currLine) || isOSother() )
		{
			continue;
		}
		//else try to run everything else as a directory
		//if it's not, should still not break/crash

		formatPathForCorrectOS(currLine);
		//may need to add currLine length check here and on the recursive call inside explorer
		//no idea how long c_strings can be. Wiki says .data() included by string does same thing. better?
		explorer( (char*) currLine.c_str());
	}
}

bool DirectoryManager::isOSother()
{
	//file_ not found, overrides are never set, so check for OS, then run explorer with default path if OS != "Other"
	currOperatingSystem_ = getOsName();
	if(currOperatingSystem_ == "Other")
	{

		//if you trip this, it could not find file_, and getOsName only checks for linux/mac/windows
		//best way to fix: add file_ back. Program tries both the linux and windows directory paths
		//so even if your not on one of those three, if it has the same directory, it will still work
		printWarning();
		std::cout << "UNKNOWN OS: set override located inside \"" << configPath_ <<"\"" << std::endl;
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

	std::string path; //directory name of everything before it + current file_


	//open:
	dir = opendir(dir_name);
	//if bad directory name or can't open, do nothing else
	if(!dir) 
	{
		printWarning();
		std::cout << "Failed to Open Directory: \"" << dir_name << "\"" << std::endl;
		return;
	}

	//read:
	while(( entry = readdir(dir) ) != NULL) 
	{
		if(entry->d_name[0] != '.') 
		{	
			if(currOperatingSystem_ == "linux/MacOS")
			{
				path = std::string(dir_name) + "/" + std::string(entry->d_name);
			}
			else // if(currOperatingSystem_ == "Windows")
			{
				//can't use convertPathToWindows because this is a recursive method, and that adds " " every time its called
				path = std::string(dir_name) + "\\" + std::string(entry->d_name);
			}
			//if the current path a song and the song is not in unique,add path/song to returnedPlaylist_ and song to unique
			//std::cout << "Path: " << dir_name << " song: " << std::string(entry->d_name) << std::endl;
			if( isMusicfile(std::string(entry->d_name)) )
			{

				//if find reaches the end, the song is not already in uniqueSongs_, add it to both
				if( find(uniqueSongs_.begin(), uniqueSongs_.end(), std::string(entry->d_name)) == uniqueSongs_.end() )
				{
					uniqueSongs_.push_back(std::string(entry->d_name));
					returnedPlaylist_.push_back(path);
				}
				//else it has the song in uniqueSongs_ already, check flag to see if it gets added to returnedPlaylist_
				else if(uniqueSongOverride_)
				{
					returnedPlaylist_.push_back(std::string(path));
				}
			}
			//checks to see if file_ or folder
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

//if it finds quotes, it removes whitespace outside of it. else, do nothing
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


std::string DirectoryManager::checkPathFormatForOS(const std::string &currLine)
{
	if(currLine.size()!=0 && currLine.at(0) == '\"' && currLine.at( currLine.size()-1 ) == '\"')
	{
		return "Windows";
	}
	return "linux/MacOS";
}

bool DirectoryManager::handlefileOverride(std::string currLine)
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
		uniqueSongOverride_ = false;
		return true;
	}
	else if ( currLine == "uniquesongoverride=true" )
	{
		uniqueSongOverride_ = true;
		std::cout << "Override Detected: Will add repeat songs to playlist" << std::endl;
		return true;
	}
	else if ( currLine == "operatingsystemoverride=0" )
	{
		operatingSystemOverride_ = 0;
		return true;
	}
	else if ( currLine == "operatingsystemoverride=1" )
	{
		operatingSystemOverride_ = 1;
		std::cout << "Override Detected: OS is \"linux/MacOS\"" << std::endl;
		return true;
	}
	else if ( currLine == "operatingsystemoverride=2" )
	{
		operatingSystemOverride_ = 2;
		std::cout << "Override Detected: OS is \"Windows\"" << std::endl;
		return true;
	}
	else if ( currLine == "operatingsystemoverride=3" )
	{
		operatingSystemOverride_ = 3;
		std::cout << "Override Detected: OS is \"Other\"" << std::endl;
		return true;
	}
	return false;
}

//note: .mp3 is not supported, and not on this list
//isMusicfile
//	returns true if file_Name is audio file_ supported by SFML
//	.mp3 file_s will not be included
bool DirectoryManager::isMusicfile(std::string file_Name)
{
	//check size incase file_Name is a.au, it won't break with file_Name.substr( file_Name.length()-6 )
	if(file_Name.size() > 6) {
		file_Name = file_Name.substr( file_Name.length() - 6 );
		if(file_Name == ".ircam" || file_Name == ".mpc2k") {
			return true;
		}
	}
	if(file_Name.size() > 5) {
		file_Name = file_Name.substr( file_Name.length() - 5 );
		if(file_Name == ".flac" || file_Name == ".aiff" || file_Name == ".nist" || 
			file_Name == ".mat4" || file_Name == ".mat5" || file_Name == ".rf64") {
			return true;
		}
	}
	if(file_Name.size() > 4) {
		file_Name = file_Name.substr( file_Name.length() - 4 );
		if(file_Name == ".ogg" || file_Name == ".wav" || file_Name == ".raw" || 
			file_Name == ".paf" || file_Name == ".svx" || file_Name == ".voc" || 
			file_Name == ".w64" || file_Name == ".pfv" || file_Name == ".htk" || 
			file_Name == ".sds" || file_Name == ".avr" || file_Name == ".sd2" || 
			file_Name == ".caf" || file_Name == ".wve") {
			return true;
		}
	}
	if(file_Name.size() > 3) {
		file_Name = file_Name.substr( file_Name.length() - 3 );
		if(file_Name == ".au") {
			return true;
		}
	}
	return false;
}
	
std::vector<std::string> DirectoryManager::getPlaylist()
{
	return returnedPlaylist_;
}

