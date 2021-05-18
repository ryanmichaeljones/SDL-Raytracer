#include <SDL.h>
#include <iostream>
#include "Graphics.h"

bool Graphics::InitialiseGraphics()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Failed to initialize SDL : " << SDL_GetError() << std::endl;
		return -1;
	}
	CreateWindow();
	CreateRenderer();
	return 0;
}

bool Graphics::CreateWindow()
{
	window = SDL_CreateWindow("raytracer",
		screenPositionX, screenPositionY, screenWidth, screenHeight, 0);
	if (window == nullptr)
	{
		std::cout << "Failed to create window : " << SDL_GetError();
		return -1;
	}
}

bool Graphics::CreateRenderer()
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::cout << "Failed to create renderer : " << SDL_GetError();
		return -1;
	}
	SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
}