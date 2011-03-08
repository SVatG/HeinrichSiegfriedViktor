#include "Vector.h"

vec3_t vec3cross(vec3_t a,vec3_t b)
{
	return vec3(_mul(a.y,b.z)-_mul(a.z,b.y),
	            _mul(a.z,b.x)-_mul(a.x,b.z),
	            _mul(a.x,b.y)-_mul(a.y,b.x));
}

