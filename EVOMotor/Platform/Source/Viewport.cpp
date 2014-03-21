#include "Platform/Viewport.h"
#include "Platform/Window.h"
#include "Platform/New.h"
#include "Platform/Leak.h"

float Viewport::cameraPosX = 0;
float Viewport::cameraPosY = 0;

Viewport::Viewport(float width,float height)
{
	this->width = width;
	this->height = height;
	projectionMatrix = glm::ortho(0.f,width,0.f,height, 0.1f, 100.f);
	movement = glm::vec3(0.f,0.f,0.f);
	viewMatrix = glm::translate(movement); 
	camera = EVO_NEW Camera();
}

Viewport::~Viewport()
{

}

void Viewport::draw(Object* object)
{
	//float width = Window::winWidth;
	//float height = Window::winHeight;

	width = Window::winWidth; height = Window::winHeight;
	projectionMatrix = glm::ortho(0.f,width,0.f,height, 0.1f, 100.f)* viewMatrix;
	//projectionMatrix *= viewMatrix;
	
	object->draw(projectionMatrix);
}

void Viewport::moveCamera(float X, float Y)
{
	movement.x += X;
	movement.y += Y;

	cameraPosX = movement.x;
	cameraPosY = movement.y;

	camera->setPosition(movement);
	viewMatrix = camera->getMatrix();
}