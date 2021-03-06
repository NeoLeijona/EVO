#ifndef INPUT_H_
#define INPUT_H_

#include <iostream>
#include <Platform/OpenGL.hpp>
#include "Platform/Android/Keyboard.h"
#include "Platform/Android/Mouse.h"
#include <incl/glm/glm.hpp>

class Input
{
public:
	Input();
	~Input();

	bool isKeyPressed;
	bool isMouseButtonPressed;
	bool MouseButtonPress(int button);
	bool keyPress(int key);
	void Update();
	glm::vec2 getCursorPos();
	double *posX;
	float X,Y;
	double *posY;


private:
	

};
#endif