#include "Graphics.h"
#include "Utilities.h"
#include "Vector3.h"
#include "Colour.h"
#include "Ray.h"
#include "Camera.h"
#include <SDL.h>
#include <iostream>
#include <thread>
#include <mutex>

Colour RayColour(const Ray& r);
float HitSphere(const Point3& centre, float radius, const Ray& r);
void DrawPixel(Vector3 position, Colour colour, SDL_Renderer* renderer);
void Render();
void Trace(int threadIndex);

Camera camera;
Graphics graphics;
const int maxThreads = 2;
std::thread threads[maxThreads];
std::mutex threadLock;

int main(int argc, char* args[])
{
	//Initialise graphics
	graphics.InitialiseGraphics();

	//SDL event loop
	SDL_Event event;
	bool quit = false;
	bool raytraced = false;
	while (!quit && SDL_WaitEvent(&event))
	{
		if (raytraced == false)
		{
			int startTime = clock();
			Render();
			int endTime = clock();
			std::cout << "exec time: " << (endTime - startTime) / double(CLOCKS_PER_SEC) << std::endl;
			raytraced = true;
		}
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		default:
			break;
		}
		SDL_RenderPresent(graphics.renderer);
	}

	return 0;
}

Colour RayColour(const Ray& r)
{
	float t = HitSphere(Point3(0, 0, -1), 0.5, r);
	if (t > 0)
	{
		Vector3 n = unitvector(r.at(t) - Vector3(0, 0, -1));
		return 0.5 * Colour(n.x() + 1, n.y() + 1, n.z() + 1);
	}
	Vector3 unitDirection = unitvector(r.direction());
	t = 0.5 * (unitDirection.y() + 1.0);
	return ((1.0 - t) * Colour(1.0, 1.0, 1.0)) + (t * Colour(0.5, 0.7, 1.0));
}

float HitSphere(const Point3& centre, float radius, const Ray& r)
{
	Vector3 oc = r.origin() - centre;
	float a = dot(r.direction(), r.direction());
	float b = 2 * dot(oc, r.direction());
	float c = dot(oc, oc) - (radius * radius);
	float discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
	{
		return -1;
	}
	else
	{
		return (-b - sqrt(discriminant)) / (2 * a);
	}
}

void DrawPixel(Vector3 position, Colour colour, SDL_Renderer* renderer)
{
	threadLock.lock();
	SDL_SetRenderDrawColor(renderer, colour.x(), colour.y(), colour.z(), 255);
	SDL_RenderDrawPoint(renderer, position.x(), position.y());
	threadLock.unlock();
}

void Render()
{
	for (int threadIndex = 0; threadIndex < maxThreads; ++threadIndex)
	{
		threads[threadIndex] = std::thread(Trace, threadIndex);
	}

	for (int threadIndex = 0; threadIndex < maxThreads; ++threadIndex)
	{
		threads[threadIndex].join();
	}
}

void Trace(int threadIndex)
{
	for (int row = 0; row < graphics.screenHeight; ++row)
	{
		for (int col = (((float)threadIndex / (float)maxThreads) * graphics.screenWidth); col <
			(((float)(threadIndex + 1) / (float)maxThreads) * graphics.screenWidth); ++col)
		{
			float u = float(col) / (graphics.screenWidth - 1);
			float v = float(row) / (graphics.screenHeight - 1);
			Ray r = camera.getRay(u, v);
			Colour pixelColour = RayColour(r);
			Vector3 position = Vector3(col, row, 0);

			DrawPixel(position, writeColour(pixelColour), graphics.renderer);
		}
	}
}