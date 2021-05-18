#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#include <SDL.h>
#include <iostream>

class Graphics
{
public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	float aspect_ratio = 16 / 9;
	int screenWidth = 400;
	int screenHeight = static_cast<int>(screenWidth / aspect_ratio);
	int screenPositionX = 600;
	int screenPositionY = 100;

	bool InitialiseGraphics();

private:
	bool CreateWindow();
	bool CreateRenderer();
};
#endif