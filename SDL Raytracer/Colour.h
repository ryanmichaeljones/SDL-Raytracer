#ifndef COLOUR_H
#define COLOUR_H

#include "Vector3.h"
#include <iostream>

Colour writeColour(Colour pixelColour)
{
	int x = static_cast<int>(255.999 * pixelColour.x());
	int y = static_cast<int>(255.999 * pixelColour.y());
	int z = static_cast<int>(255.999 * pixelColour.z());
	Colour colour(x, y, z);

	return colour;
}
#endif