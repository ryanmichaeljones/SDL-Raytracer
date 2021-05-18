#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray
{
public:
	Ray() {}
	Ray(const Point3& origin, const Vector3& direction) : orig(origin), dir(direction) {}

	Point3 origin() const { return orig; }
	Vector3 direction() const { return dir; }

	Point3 at(float t) const
	{
		return orig + (t * dir);
	}

	Point3 orig;
	Vector3 dir;
};

#endif