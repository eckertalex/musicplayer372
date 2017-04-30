#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "../include/GUI.hpp"
#include "../include/Music.hpp"
#include <memory>

class InputManager
{
public:
	InputManager(std::shared_ptr<GUI> gui, std::shared_ptr<Music> music);
	void mouseOverHighlight();
private:
	std::shared_ptr<Music> music;
	std::shared_ptr<GUI> gui;
};

#endif