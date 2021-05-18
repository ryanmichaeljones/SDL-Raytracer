#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Ray.h"

class Camera 
{
public:
	Camera() {}

	float aspectRatio = 16 / 9;
	float viewportHeight = 2.0;
	float viewportWidth = aspectRatio * viewportHeight;
	float focalLength = 1.0;
	Point3 origin = Point3(0, 0, 0);
	Vector3 horizontal = Vector3(viewportWidth, 0, 0);
	Vector3 vertical = Vector3(0, viewportHeight, 0);
	Vector3 lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vector3(0, 0, focalLength);

	Ray getRay(float u, float v) const {
		return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}

};
#endif