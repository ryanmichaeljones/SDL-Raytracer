#ifndef UTILITIES_H
#define UTILITIES_H

inline float clamp(float x, float min, float max) 
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

#endif