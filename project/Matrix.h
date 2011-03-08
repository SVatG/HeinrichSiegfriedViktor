#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "Vector.h"



// Definitions

typedef struct { scalar_t m[4]; } mat2x2_t;
typedef struct { scalar_t m[6]; } mat3x2_t;
typedef struct { scalar_t m[9]; } mat3x3_t;
typedef struct { scalar_t m[12]; } mat4x3_t;
typedef struct { scalar_t m[16]; } mat4x4_t;

#define mat2x2one mat2x2(F(1),F(0), F(0),F(1))
#define mat3x2one mat3x2(F(1),F(0),F(0), F(0),F(1),F(0))
#define mat3x3one mat3x3(F(1),F(0),F(0), F(0),F(1),F(0), F(0),F(0),F(1))
#define mat4x3one mat4x3(F(1),F(0),F(0),F(0), F(0),F(1),F(0),F(0), F(0),F(0),F(1),F(0))
#define mat4x4one mat4x4(F(1),F(0),F(0),F(0), F(0),F(1),F(0),F(0), F(0),F(0),F(1),F(0), F(0),F(0),F(0),F(1))



// Basic constructors

static inline mat2x2_t mat2x2(scalar_t a00,scalar_t a01,
                              scalar_t a10,scalar_t a11)
{ return (mat2x2_t){a00,a10,a01,a11}; }

static inline mat3x2_t mat3x2(scalar_t a00,scalar_t a01,scalar_t a02,
                              scalar_t a10,scalar_t a11,scalar_t a12)
{ return (mat3x2_t){a00,a10,a01,a11,a02,a12}; }

static inline mat3x3_t mat3x3(scalar_t a00,scalar_t a01,scalar_t a02,
                              scalar_t a10,scalar_t a11,scalar_t a12,
                              scalar_t a20,scalar_t a21,scalar_t a22)
{ return (mat3x3_t){a00,a10,a20,a01,a11,a21,a02,a12,a22}; }

static inline mat4x3_t mat4x3(scalar_t a00,scalar_t a01,scalar_t a02,scalar_t a03,
                              scalar_t a10,scalar_t a11,scalar_t a12,scalar_t a13,
                              scalar_t a20,scalar_t a21,scalar_t a22,scalar_t a23)
{ return (mat4x3_t){a00,a10,a20,a01,a11,a21,a02,a12,a22,a03,a13,a23}; }

static inline mat4x4_t mat4x4(scalar_t a00,scalar_t a01,scalar_t a02,scalar_t a03,
                              scalar_t a10,scalar_t a11,scalar_t a12,scalar_t a13,
                              scalar_t a20,scalar_t a21,scalar_t a22,scalar_t a23,
                              scalar_t a30,scalar_t a31,scalar_t a32,scalar_t a33)
{ return (mat4x4_t){a00,a10,a20,a30,a01,a11,a21,a31,a02,a12,a22,a32,a03,a13,a23,a33}; }




// Vector base constructors

static inline mat2x2_t mat2x2vec2(vec2_t x,vec2_t y)
{
	return mat2x2(x.x,y.x,
	              x.y,y.y);
}

static inline mat3x2_t mat3x2vec2(vec2_t x,vec2_t y,vec2_t z)
{
	return mat3x2(x.x,y.x,z.x,
	              x.y,y.y,z.y);
}

static inline mat3x3_t mat3x3vec3(vec3_t x,vec3_t y,vec3_t z)
{
	return mat3x3(x.x,y.x,z.x,
	              x.y,y.y,z.y,
	              x.z,y.z,z.z);
}

static inline mat4x3_t mat4x3vec3(vec3_t x,vec3_t y,vec3_t z,vec3_t w)
{
	return mat4x3(x.x,y.x,z.x,w.x,
	              x.y,y.y,z.y,w.y,
	              x.z,y.z,z.z,w.z);
}

static inline mat4x4_t mat4x4vec4(vec4_t x,vec4_t y,vec4_t z,vec4_t w)
{
	return mat4x4(x.x,y.x,z.x,w.x,
	              x.y,y.y,z.y,w.y,
	              x.z,y.z,z.z,w.z,
	              x.w,y.z,z.w,w.w);
}



// Extractors

static inline vec2_t mat2x2_x(mat2x2_t m) { return vec2(m.m[0],m.m[1]); }
static inline vec2_t mat2x2_y(mat2x2_t m) { return vec2(m.m[2],m.m[3]); }

static inline vec2_t mat3x2_x(mat3x2_t m) { return vec2(m.m[0],m.m[1]); }
static inline vec2_t mat3x2_y(mat3x2_t m) { return vec2(m.m[2],m.m[3]); }
static inline vec2_t mat3x2_z(mat3x2_t m) { return vec2(m.m[4],m.m[5]); }

static inline vec3_t mat3x3_x(mat3x3_t m) { return vec3(m.m[0],m.m[1],m.m[2]); }
static inline vec3_t mat3x3_y(mat3x3_t m) { return vec3(m.m[3],m.m[4],m.m[5]); }
static inline vec3_t mat3x3_z(mat3x3_t m) { return vec3(m.m[6],m.m[7],m.m[8]); }

static inline vec3_t mat4x3_x(mat4x3_t m) { return vec3(m.m[0],m.m[1],m.m[2]); }
static inline vec3_t mat4x3_y(mat4x3_t m) { return vec3(m.m[3],m.m[4],m.m[5]); }
static inline vec3_t mat4x3_z(mat4x3_t m) { return vec3(m.m[6],m.m[7],m.m[8]); }
static inline vec3_t mat4x3_w(mat4x3_t m) { return vec3(m.m[9],m.m[10],m.m[11]); }

static inline vec4_t mat4x4_x(mat4x4_t m) { return vec4(m.m[0],m.m[1],m.m[2],m.m[3]); }
static inline vec4_t mat4x4_y(mat4x4_t m) { return vec4(m.m[4],m.m[5],m.m[6],m.m[7]); }
static inline vec4_t mat4x4_z(mat4x4_t m) { return vec4(m.m[8],m.m[9],m.m[10],m.m[11]); }
static inline vec4_t mat4x4_w(mat4x4_t m) { return vec4(m.m[12],m.m[13],m.m[14],m.m[15]); }

static inline mat2x2_t mat3x2_mat2x2(mat3x2_t m) { return mat2x2vec2(mat3x2_x(m),mat3x2_y(m)); }
static inline mat2x2_t mat3x3_mat2x2(mat3x3_t m) { return mat2x2vec2(vec3_xy(mat3x3_x(m)),vec3_xy(mat3x3_y(m))); }
static inline mat3x2_t mat3x3_mat3x2(mat3x3_t m) { return mat3x2vec2(vec3_xy(mat3x3_x(m)),vec3_xy(mat3x3_y(m)),vec3_xy(mat3x3_z(m))); }
static inline mat3x3_t mat4x3_mat3x3(mat4x3_t m) { return mat3x3vec3(mat4x3_x(m),mat4x3_y(m),mat4x3_z(m)); }
static inline mat3x3_t mat4x4_mat3x3(mat4x4_t m) { return mat3x3vec3(vec4_xyz(mat4x4_x(m)),vec4_xyz(mat4x4_y(m)),vec4_xyz(mat4x4_z(m))); }
static inline mat4x3_t mat4x4_mat4x3(mat4x4_t m) { return mat4x3vec3(vec4_xyz(mat4x4_x(m)),vec4_xyz(mat4x4_y(m)),vec4_xyz(mat4x4_z(m)),vec4_xyz(mat4x4_w(m))); }



// Upgrade constructors

static inline mat3x2_t mat3x2affine2x2(mat2x2_t m)
{
	vec2_t x=mat2x2_x(m),y=mat2x2_y(m);
	return mat3x2( x.x, y.x,F(0),
	               x.y, y.y,F(0));
}

static inline mat3x3_t mat3x3affine2x2(mat2x2_t m)
{
	vec2_t x=mat2x2_x(m),y=mat2x2_y(m);
	return mat3x3( x.x, y.x,F(0),
	               x.y, y.y,F(0),
	              F(0),F(0),F(1));
}

static inline mat3x3_t mat3x3affine3x2(mat3x2_t m)
{
	vec2_t x=mat3x2_x(m),y=mat3x2_y(m),z=mat3x2_z(m);
	return mat3x3( x.x, y.x, z.x,
	               x.y, y.y, z.y,
	              F(0),F(0),F(1));
}

static inline mat4x3_t mat4x3affine3x3(mat3x3_t m)
{
	vec3_t x=mat3x3_x(m),y=mat3x3_y(m),z=mat3x3_z(m);
	return mat4x3( x.x, y.x, z.x,F(0),
	               x.y, y.y, z.y,F(0),
	               x.z, y.z, z.z,F(0));
}

static inline mat4x4_t mat4x4affine3x3(mat3x3_t m)
{
	vec3_t x=mat3x3_x(m),y=mat3x3_y(m),z=mat3x3_z(m);
	return mat4x4( x.x, y.x, z.x,F(0),
	               x.y, y.y, z.y,F(0),
	               x.z, y.z, z.z,F(0),
	              F(0),F(0),F(0),F(1));
}

static inline mat4x4_t mat4x4affine4x3(mat4x3_t m)
{
	vec3_t x=mat4x3_x(m),y=mat4x3_y(m),z=mat4x3_z(m),w=mat4x3_w(m);
	return mat4x4( x.x, y.x, z.x, w.x,
	               x.y, y.y, z.y, w.y,
	               x.z, y.z, z.z, w.z,
	              F(0),F(0),F(0),F(1));
}



// Translation constructors

static inline mat3x2_t mat3x2translate(vec2_t v)
{
	return mat3x2(F(1),F(0),v.x,
	              F(0),F(1),v.y);
}

static inline mat4x3_t mat4x3translate(vec3_t v)
{
	return mat4x3(F(1),F(0),F(0),v.x,
	              F(0),F(1),F(0),v.y,
	              F(0),F(0),F(1),v.z);
}
static inline mat4x4_t mat4x4translate(vec3_t v) { return mat4x4affine4x3(mat4x3translate(v)); }



// Scaling constructors

static inline mat2x2_t mat2x2scale(scalar_t x,scalar_t y)
{
	return mat2x2(   x,F(0),
	              F(0),   y);
}
static inline mat3x2_t mat3x2scale(scalar_t x,scalar_t y) { return mat3x2affine2x2(mat2x2scale(x,y)); }

static inline mat3x3_t mat3x3scale(scalar_t x,scalar_t y,scalar_t z)
{
	return mat3x3(   x,F(0),F(0),
	              F(0),   y,F(0),
	              F(0),F(0),   z);
}
static inline mat4x3_t mat4x3scale(scalar_t x,scalar_t y,scalar_t z) { return mat4x3affine3x3(mat3x3scale(x,y,z)); }
static inline mat4x4_t mat4x4scale(scalar_t x,scalar_t y,scalar_t z) { return mat4x4affine3x3(mat3x3scale(x,y,z)); }



// Rotation constructors

static inline mat2x2_t mat2x2rotate(scalar_t a)
{
	return mat2x2(_cos(a),-_sin(a),
	              _sin(a), _cos(a));
}
static inline mat3x2_t mat3x2rotate(scalar_t a) { return mat3x2affine2x2(mat2x2rotate(a)); }

static inline mat3x3_t mat3x3rotatex(scalar_t a)
{
	return mat3x3(F(1),   F(0),    F(0),
	              F(0),_cos(a),-_sin(a),
	              F(0),_sin(a), _cos(a));
}
static inline mat4x3_t mat4x3rotatex(scalar_t a) { return mat4x3affine3x3(mat3x3rotatex(a)); }
static inline mat4x4_t mat4x4rotatex(scalar_t a) { return mat4x4affine3x3(mat3x3rotatex(a)); }

static inline mat3x3_t mat3x3rotatey(scalar_t a)
{
	return mat3x3( _cos(a),F(0),_sin(a),
	                  F(0),F(1),   F(0),
	              -_sin(a),F(0),_cos(a));
}
static inline mat4x3_t mat4x3rotatey(scalar_t a) { return mat4x3affine3x3(mat3x3rotatey(a)); }
static inline mat4x4_t mat4x4rotatey(scalar_t a) { return mat4x4affine3x3(mat3x3rotatey(a)); }

static inline mat3x3_t mat3x3rotatez(scalar_t a)
{
	return mat3x3(_cos(a),-_sin(a),F(0),
	              _sin(a), _cos(a),F(0),
	                 F(0),    F(0),F(1));
}
static inline mat4x3_t mat4x3rotatez(scalar_t a) { return mat4x3affine3x3(mat3x3rotatez(a)); }
static inline mat4x4_t mat4x4rotatez(scalar_t a) { return mat4x4affine3x3(mat3x3rotatez(a)); }

mat3x3_t mat3x3rotate(scalar_t angle,vec3_t axis);
mat4x3_t mat4x3rotate(scalar_t angle,vec3_t axis);
mat4x4_t mat4x4rotate(scalar_t angle,vec3_t axis);



// Multiplication

mat2x2_t mat2x2mul(mat2x2_t a,mat2x2_t b);
mat3x3_t mat3x3mul(mat3x3_t a,mat3x3_t b);
mat4x4_t mat4x4mul(mat4x4_t a,mat4x4_t b);

mat3x2_t mat3x2affinemul(mat3x2_t a,mat3x2_t b);
mat3x3_t mat3x3affinemul(mat3x3_t a,mat3x3_t b);
mat4x3_t mat4x3affinemul(mat4x3_t a,mat4x3_t b);
mat4x4_t mat4x4affinemul(mat4x4_t a,mat4x4_t b);




// Transpose

static inline mat2x2_t mat2x2transpose(mat2x2_t m)
{
	return mat2x2(m.m[0],m.m[1],
	              m.m[2],m.m[3]);
}

static inline mat3x3_t mat3x3transpose(mat3x3_t m)
{
	return mat3x3(m.m[0],m.m[1],m.m[2],
	              m.m[3],m.m[4],m.m[5],
	              m.m[6],m.m[7],m.m[8]);
}

static inline mat4x4_t mat4x4transpose(mat4x4_t m)
{
	return mat4x4( m.m[0], m.m[1], m.m[2], m.m[3],
	               m.m[4], m.m[5], m.m[6], m.m[7],
	               m.m[8], m.m[9],m.m[10],m.m[11],
	              m.m[12],m.m[13],m.m[14],m.m[15]);
}



// Inverse

mat2x2_t mat2x2inverse(mat2x2_t m);
mat3x3_t mat3x3inverse(mat3x3_t m);
//mat4x4_t mat4x4inverse(mat4x4_t m);

mat3x2_t mat3x2affineinverse(mat3x2_t m);
mat4x3_t mat4x3affineinverse(mat4x3_t m);
mat3x3_t mat3x3affineinverse(mat3x3_t m);
mat4x4_t mat4x4affineinverse(mat4x4_t m);



// Transformations

vec2_t mat2x2transform(mat2x2_t m,vec2_t v);
vec2_t mat3x2transform(mat3x2_t m,vec2_t v);
vec3_t mat3x3transform(mat3x3_t m,vec3_t v);
vec3_t mat4x3transform(mat4x3_t m,vec3_t v);
vec4_t mat4x4transform(mat4x4_t m,vec4_t v);

#endif
