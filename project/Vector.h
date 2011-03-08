#ifndef __VECTOR_H__
#define __VECTOR_H__

#ifdef USE_FIXEDPOINT

#include "Utils.h"

typedef int32_t scalar_t;
static inline int32_t _mul(int32_t a,int32_t b) { return imul(a,b); }
static inline int32_t _mul3(int32_t a,int32_t b,int32_t c) { return imul3(a,b,c); }
static inline int32_t _div(int32_t a,int32_t b) { return idiv(a,b); }
static inline int32_t _sqrt(int32_t a) { return isqrt(a); }
static inline int32_t _sin(int32_t a) { return isin(a); }
static inline int32_t _cos(int32_t a) { return icos(a); }

#else

#include <math.h>

#define F(x) (x)
typedef float scalar_t;
static inline float _mul(float a,float b) { return a*b; }
static inline float _mul3(float a,float b,float c) { return a*b*c; }
static inline float _div(float a,float b) { return a/b; }
static inline float _sqrt(float a) { return sqrtf(a); }
static inline float _sin(float a) { return sinf(a); }
static inline float _cos(float a) { return cosf(a); }

#endif



// Definitions

typedef struct { scalar_t x,y; } vec2_t;
typedef struct { scalar_t x,y,z; } vec3_t;
typedef struct { scalar_t x,y,z,w; } vec4_t;

#define vec2zero vec2(0,0)
#define vec3zero vec3(0,0,0)
#define vec4zero vec4(0,0,0,0)



// Constructors

static inline vec2_t vec2(scalar_t x,scalar_t y) { return (vec2_t){x,y}; }
static inline vec3_t vec3(scalar_t x,scalar_t y,scalar_t z) { return (vec3_t){x,y,z}; }
static inline vec4_t vec4(scalar_t x,scalar_t y,scalar_t z,scalar_t w) { return (vec4_t){x,y,z,w}; }

static inline vec2_t vec2cyl(scalar_t r,scalar_t angle)
{
	return vec2(_mul(r,_cos(angle)),_mul(r,_sin(angle)));
}

static inline vec4_t vec4vec3(vec3_t v) { return vec4(v.x,v.y,v.z,F(1)); }


// Extractors

static inline vec2_t vec3_xy(vec3_t v) { return vec2(v.x,v.y); }
static inline vec2_t vec3_xz(vec3_t v) { return vec2(v.x,v.z); }
static inline vec2_t vec3_yz(vec3_t v) { return vec2(v.y,v.z); }

static inline vec3_t vec4_xyz(vec4_t v) { return vec3(v.x,v.y,v.z); }



// Unary operations

static inline vec2_t vec2neg(vec2_t v) { return vec2(-v.x,-v.y); }
static inline vec3_t vec3neg(vec3_t v) { return vec3(-v.x,-v.y,-v.z); }
static inline vec4_t vec4neg(vec4_t v) { return vec4(-v.x,-v.y,-v.z,-v.w); }



// Arithmetic operations

static inline vec2_t vec2add(vec2_t a,vec2_t b) { return vec2(a.x+b.x,a.y+b.y); }
static inline vec3_t vec3add(vec3_t a,vec3_t b) { return vec3(a.x+b.x,a.y+b.y,a.z+b.z); }
static inline vec4_t vec4add(vec4_t a,vec4_t b) { return vec4(a.x+b.x,a.y+b.y,a.z+b.z,a.w+b.w); }

static inline vec2_t vec2add3(vec2_t a,vec2_t b,vec2_t c) { return vec2(a.x+b.x+c.x,a.y+b.y+c.y); }
static inline vec3_t vec3add3(vec3_t a,vec3_t b,vec3_t c) { return vec3(a.x+b.x+c.x,a.y+b.y+c.y,a.z+b.z+c.z); }
static inline vec4_t vec4add3(vec4_t a,vec4_t b,vec4_t c) { return vec4(a.x+b.x+c.x,a.y+b.y+c.y,a.z+b.z+c.z,a.w+b.w+c.w); }

static inline vec2_t vec2sub(vec2_t a,vec2_t b) { return vec2(a.x-b.x,a.y-b.y); }
static inline vec3_t vec3sub(vec3_t a,vec3_t b) { return vec3(a.x-b.x,a.y-b.y,a.z-b.z); }
static inline vec4_t vec4sub(vec4_t a,vec4_t b) { return vec4(a.x-b.x,a.y-b.y,a.z-b.z,a.w-b.w); }

static inline vec2_t vec2mul(vec2_t v,scalar_t s) { return vec2(_mul(v.x,s),_mul(v.y,s)); }
static inline vec3_t vec3mul(vec3_t v,scalar_t s) { return vec3(_mul(v.x,s),_mul(v.y,s),_mul(v.z,s)); }
static inline vec4_t vec4mul(vec4_t v,scalar_t s) { return vec4(_mul(v.x,s),_mul(v.y,s),_mul(v.z,s),_mul(v.w,s)); }

static inline vec2_t vec2div(vec2_t v,scalar_t s) { return vec2(_div(v.x,s),_div(v.y,s)); }
static inline vec3_t vec3div(vec3_t v,scalar_t s) { return vec3(_div(v.x,s),_div(v.y,s),_div(v.z,s)); }
static inline vec4_t vec4div(vec4_t v,scalar_t s) { return vec4(_div(v.x,s),_div(v.y,s),_div(v.z,s),_div(v.w,s)); }



// Norms

static inline scalar_t vec2dot(vec2_t a,vec2_t b) { return _mul(a.x,b.x)+_mul(a.y,b.y); }
static inline scalar_t vec3dot(vec3_t a,vec3_t b) { return _mul(a.x,b.x)+_mul(a.y,b.y)+_mul(a.z,b.z); }
static inline scalar_t vec4dot(vec4_t a,vec4_t b) { return _mul(a.x,b.x)+_mul(a.y,b.y)+_mul(a.z,b.z)+_mul(a.w,b.w); }

static inline scalar_t vec2sq(vec2_t v) { return vec2dot(v,v); }
static inline scalar_t vec3sq(vec3_t v) { return vec3dot(v,v); }
static inline scalar_t vec4sq(vec4_t v) { return vec4dot(v,v); }

static inline scalar_t vec2abs(vec2_t v) { return _sqrt(vec2sq(v)); }
static inline scalar_t vec3abs(vec3_t v) { return _sqrt(vec3sq(v)); }
static inline scalar_t vec4abs(vec4_t v) { return _sqrt(vec4sq(v)); }

static inline scalar_t vec2distsq(vec2_t a,vec2_t b) { return vec2sq(vec2sub(a,b)); }
static inline scalar_t vec3distsq(vec3_t a,vec3_t b) { return vec3sq(vec3sub(a,b)); }
static inline scalar_t vec4distsq(vec4_t a,vec4_t b) { return vec4sq(vec4sub(a,b)); }

static inline scalar_t vec2dist(vec2_t a,vec2_t b) { return vec2abs(vec2sub(a,b)); }
static inline scalar_t vec3dist(vec3_t a,vec3_t b) { return vec3abs(vec3sub(a,b)); }
static inline scalar_t vec4dist(vec4_t a,vec4_t b) { return vec4abs(vec4sub(a,b)); }

#ifdef USE_FIXEDPOINT64
static inline int64_t vec2dot64(vec2_t a,vec2_t b) { return imul64(a.x,b.x)+imul64(a.y,b.y); }
static inline int64_t vec3dot64(vec3_t a,vec3_t b) { return imul64(a.x,b.x)+imul64(a.y,b.y)+imul64(a.z,b.z); }
static inline int64_t vec4dot64(vec4_t a,vec4_t b) { return imul64(a.x,b.x)+imul64(a.y,b.y)+imul64(a.z,b.z)+imul64(a.w,b.w); }

static inline int64_t vec2sq64(vec2_t v) { return vec2dot64(v,v); }
static inline int64_t vec3sq64(vec3_t v) { return vec3dot64(v,v); }
static inline int64_t vec4sq64(vec4_t v) { return vec4dot64(v,v); }

static inline int64_t vec2abs64(vec2_t v) { return isqrt64(vec2sq64(v)); }
static inline int64_t vec3abs64(vec3_t v) { return isqrt64(vec3sq64(v)); }
static inline int64_t vec4abs64(vec4_t v) { return isqrt64(vec4sq64(v)); }

static inline int64_t vec2distsq64(vec2_t a,vec2_t b) { return vec2sq64(vec2sub(a,b)); }
static inline int64_t vec3distsq64(vec3_t a,vec3_t b) { return vec3sq64(vec3sub(a,b)); }
static inline int64_t vec4distsq64(vec4_t a,vec4_t b) { return vec4sq64(vec4sub(a,b)); }

static inline int64_t vec2dist64(vec2_t a,vec2_t b) { return vec2abs64(vec2sub(a,b)); }
static inline int64_t vec3dist64(vec3_t a,vec3_t b) { return vec3abs64(vec3sub(a,b)); }
static inline int64_t vec4dist64(vec4_t a,vec4_t b) { return vec4abs64(vec4sub(a,b)); }
#endif

static inline vec2_t vec2norm(vec2_t v)
{
	scalar_t len=vec2abs(v);
	if(len==0) return vec2zero;
	else return vec2div(v,len);
}

static inline vec3_t vec3norm(vec3_t v)
{
	scalar_t len=vec3abs(v);
	if(len==0) return vec3zero;
	else return vec3div(v,len);
}

static inline vec4_t vec4norm(vec4_t v)
{
	scalar_t len=vec4abs(v);
	if(len==0) return vec4zero;
	else return vec4div(v,len);
}

static inline vec2_t vec2setlength(vec2_t v,scalar_t length) { return vec2mul(vec2norm(v),length); }
static inline vec3_t vec3setlength(vec3_t v,scalar_t length) { return vec3mul(vec3norm(v),length); }
static inline vec4_t vec4setlength(vec4_t v,scalar_t length) { return vec4mul(vec4norm(v),length); }



// Blending

static inline vec2_t vec2midpoint(vec2_t a,vec2_t b) { return vec2((a.x+b.x)/2,(a.y+b.y)/2); }
static inline vec3_t vec3midpoint(vec3_t a,vec3_t b) { return vec3((a.x+b.x)/2,(a.y+b.y)/2,(a.z+b.z)/2); }
static inline vec4_t vec4midpoint(vec4_t a,vec4_t b) { return vec4((a.x+b.x)/2,(a.y+b.y)/2,(a.z+b.z)/2,(a.w+b.w)/2); }

static inline vec2_t vec2mix(vec2_t a,vec2_t b,scalar_t x) { return vec2add(a,vec2mul(vec2sub(b,a),x)); }
static inline vec3_t vec3mix(vec3_t a,vec3_t b,scalar_t x) { return vec3add(a,vec3mul(vec3sub(b,a),x)); }
static inline vec4_t vec4mix(vec4_t a,vec4_t b,scalar_t x) { return vec4add(a,vec4mul(vec4sub(b,a),x)); }



// 2D specifics

static inline vec2_t vec2perp(vec2_t v) { return vec2(-v.y,v.x); }

static inline scalar_t vec2pdot(vec2_t a,vec2_t b) { return vec2dot(a,vec2perp(b)); }
#ifdef USE_FIXEDPOINT64
static inline scalar_t vec2pdot64(vec2_t a,vec2_t b) { return vec2dot64(a,vec2perp(b)); }
#endif

static inline vec2_t vec2rot(vec2_t v,scalar_t angle)
{
	return vec2(
	_mul(v.x,_cos(angle))-_mul(v.y,_sin(angle)),
	_mul(v.x,_sin(angle))+_mul(v.y,_cos(angle)));
}



// 3D specifics

vec3_t vec3cross(vec3_t a,vec3_t b);

#endif

