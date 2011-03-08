#include "Quaternion.h"

mat3x3_t mat3x3quat(quat_t q)
{
	scalar_t s2=_mul(q.r,q.r);
	scalar_t x2=_mul(q.i.x,q.i.x);
	scalar_t y2=_mul(q.i.y,q.i.y);
	scalar_t z2=_mul(q.i.z,q.i.z);

	return mat3x3(
	s2+x2-y2-z2,
	2*(_mul(q.i.x,q.i.y)-_mul(q.r,q.i.z)),
	2*(_mul(q.i.x,q.i.z)+_mul(q.r,q.i.y)),

	2*(_mul(q.i.x,q.i.y)+_mul(q.r,q.i.z)),
	s2-x2+y2-z2,
	2*(_mul(q.i.y,q.i.z)-_mul(q.r,q.i.x)),

	2*(_mul(q.i.x,q.i.z)-_mul(q.r,q.i.y)),
	2*(_mul(q.i.y,q.i.z)+_mul(q.r,q.i.x)),
	s2-x2-y2+z2);
}

mat4x3_t mat4x3quat(quat_t q) { return mat4x3affine3x3(mat3x3quat(q)); }

mat4x4_t mat4x4quat(quat_t q) { return mat4x4affine3x3(mat3x3quat(q)); }
