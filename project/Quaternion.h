#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "Vector.h"
#include "Matrix.h"



// Definitions

typedef struct { scalar_t r; vec3_t i; } quat_t;

#define quatzero quatreal(F(0))
#define quatone quatreal(F(1))



// Constructors

static inline quat_t quat(scalar_t r,vec3_t i) { return (quat_t){r,i}; }
static inline quat_t quatreal(scalar_t r) { return (quat_t){r,vec3zero}; }
static inline quat_t quatimag(vec3_t i) { return (quat_t){0,i}; }

static inline quat_t quatrotation(scalar_t angle,vec3_t axis)
{
	return quat(_cos(angle/2),vec3setlength(axis,_sin(angle/2)));
}


// Extractors

static inline scalar_t quat_real(quat_t q) { return q.r; }
static inline vec3_t quat_imag(quat_t q) { return q.i; }



// Unary operations

static inline quat_t quatneg(quat_t q) { return quat(-q.r,vec3neg(q.i)); }
static inline quat_t quatconj(quat_t q) { return quat(q.r,vec3neg(q.i)); }



// Norms

static inline scalar_t quatsq(quat_t q) { return _mul(q.r,q.r)+vec3sq(q.i); }
static inline scalar_t quatabs(quat_t q) { return _sqrt(quatsq(q)); }

static inline quat_t quatnorm(quat_t q)
{
	scalar_t abs=quatabs(q);
	if(abs==0) return quatzero;
	return quat(_div(q.r,abs),vec3div(q.i,abs));
}



// Inverse 

static inline quat_t quatinverse(quat_t q)
{
	scalar_t sq=quatsq(q);
	return quat(_div(q.r,sq),vec3div(q.i,sq));
}



// Arithmetic operations

static inline quat_t quatadd(quat_t a,quat_t b) { return quat(a.r+b.r,vec3add(a.i,b.i)); }
static inline quat_t quatsub(quat_t a,quat_t b) { return quat(a.r-b.r,vec3sub(a.i,b.i)); }
static inline quat_t quatmul(quat_t a,quat_t b)
{
	return quat(_mul(a.r,b.r)-vec3dot(a.i,b.i),
	            vec3add3(vec3mul(b.i,a.r),vec3mul(a.i,b.r),vec3cross(a.i,b.i)));
}
static inline quat_t quatdiv(quat_t a,quat_t b) { return quatmul(a,quatinverse(b)); }




// Blending

static inline quat_t quatmidpoint(quat_t a,quat_t b) { return quat((a.r+b.r)/2,vec3midpoint(a.i,b.i)); }
static inline quat_t quatmix(quat_t a,quat_t b,scalar_t x) { return quat(a.r+_mul(b.r-a.r,x),vec3mix(a.i,b.i,x)); }


// Matrix conversion

static inline vec3_t quattransform(quat_t q,vec3_t v)
{
	return quatmul(quatmul(q,quatimag(v)),quatconj(q)).i;
}

mat3x3_t mat3x3quat(quat_t q);
mat4x3_t mat4x3quat(quat_t q);
mat4x4_t mat4x4quat(quat_t q);

#endif
