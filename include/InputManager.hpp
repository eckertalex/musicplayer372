#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "../include/Music.hpp"

class InputManager
{
public:
	InputManager(Music & music);
private:
	Music music;
};

#endif