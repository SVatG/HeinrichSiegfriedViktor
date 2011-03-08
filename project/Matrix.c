#include "Matrix.h"

mat3x3_t mat3x3rotate(scalar_t angle,vec3_t axis)
{
	scalar_t sine=_sin(angle);
	scalar_t cosine=_cos(angle);
	scalar_t one_minus_cosine=F(1)-cosine;

	axis=vec3norm(axis);

	return mat3x3(
	cosine + _mul3(one_minus_cosine,axis.x,axis.x),
	_mul3(one_minus_cosine,axis.x,axis.y) + _mul(axis.z,sine),
	_mul3(one_minus_cosine,axis.x,axis.z) - _mul(axis.y,sine),

	_mul3(one_minus_cosine,axis.x,axis.y) - _mul(axis.z,sine),
	cosine + _mul3(one_minus_cosine,axis.y,axis.y),
	_mul3(one_minus_cosine,axis.y,axis.z) + _mul(axis.x,sine),

	_mul3(one_minus_cosine,axis.x,axis.z) + _mul(axis.y,sine),
	_mul3(one_minus_cosine,axis.y,axis.z) - _mul(axis.x,sine),
	cosine + _mul3(one_minus_cosine,axis.z,axis.z));
}

mat4x3_t mat4x3rotate(scalar_t angle,vec3_t axis) { return mat4x3affine3x3(mat3x3rotate(angle,axis)); }

mat4x4_t mat4x4rotate(scalar_t angle,vec3_t axis) { return mat4x4affine3x3(mat3x3rotate(angle,axis)); }


mat2x2_t mat2x2mul(mat2x2_t a,mat2x2_t b)
{
	return mat2x2(_mul(a.m[0],b.m[0])+_mul(a.m[2],b.m[1]),
	              _mul(a.m[0],b.m[2])+_mul(a.m[2],b.m[3]),

	              _mul(a.m[1],b.m[0])+_mul(a.m[3],b.m[1]),
	              _mul(a.m[1],b.m[2])+_mul(a.m[3],b.m[3]));
}

mat3x3_t mat3x3mul(mat3x3_t a,mat3x3_t b)
{
	return mat3x3(_mul(a.m[0],b.m[0])+_mul(a.m[3],b.m[1])+_mul(a.m[6],b.m[2]),
	              _mul(a.m[0],b.m[3])+_mul(a.m[3],b.m[4])+_mul(a.m[6],b.m[5]),
	              _mul(a.m[0],b.m[6])+_mul(a.m[3],b.m[7])+_mul(a.m[6],b.m[8]),

	              _mul(a.m[1],b.m[0])+_mul(a.m[4],b.m[1])+_mul(a.m[7],b.m[2]),
	              _mul(a.m[1],b.m[3])+_mul(a.m[4],b.m[4])+_mul(a.m[7],b.m[5]),
	              _mul(a.m[1],b.m[6])+_mul(a.m[4],b.m[7])+_mul(a.m[7],b.m[8]),

	              _mul(a.m[2],b.m[0])+_mul(a.m[5],b.m[1])+_mul(a.m[8],b.m[2]),
	              _mul(a.m[2],b.m[3])+_mul(a.m[5],b.m[4])+_mul(a.m[8],b.m[5]),
	              _mul(a.m[2],b.m[6])+_mul(a.m[5],b.m[7])+_mul(a.m[8],b.m[8]));
}

mat4x4_t mat4x4mul(mat4x4_t a,mat4x4_t b)
{
        mat4x4_t res;
        for(int i=0;i<16;i++)
        {
                int row=i&3,column=i&12;
                scalar_t val=0;
                for(int j=0;j<4;j++) val+=a.m[row+j*4]*b.m[column+j];
                res.m[i]=val;
        }
        return res;
}

mat3x2_t mat3x2affinemul(mat3x2_t a,mat3x2_t b)
{
	return mat3x2(_mul(a.m[0],b.m[0])+_mul(a.m[2],b.m[1]),
	              _mul(a.m[0],b.m[2])+_mul(a.m[2],b.m[3]),
	              _mul(a.m[0],b.m[4])+_mul(a.m[2],b.m[5])+a.m[4],

	              _mul(a.m[1],b.m[0])+_mul(a.m[3],b.m[1]),
	              _mul(a.m[1],b.m[2])+_mul(a.m[3],b.m[3]),
	              _mul(a.m[1],b.m[4])+_mul(a.m[3],b.m[5])+a.m[5]);
}

mat3x3_t mat3x3affinemul(mat3x3_t a,mat3x3_t b)
{
	return mat3x3(_mul(a.m[0],b.m[0])+_mul(a.m[3],b.m[1]),
	              _mul(a.m[0],b.m[3])+_mul(a.m[3],b.m[4]),
	              _mul(a.m[0],b.m[6])+_mul(a.m[3],b.m[7])+a.m[6],

	              _mul(a.m[1],b.m[0])+_mul(a.m[4],b.m[1]),
	              _mul(a.m[1],b.m[3])+_mul(a.m[4],b.m[4]),
	              _mul(a.m[1],b.m[6])+_mul(a.m[4],b.m[7])+a.m[7],

	              F(0),F(0),F(1));
}

mat4x3_t mat4x3affinemul(mat4x3_t a,mat4x3_t b)
{
	return mat4x3(_mul(a.m[0],b.m[0])+_mul(a.m[3],b.m[1])+_mul(a.m[6],b.m[2]),
	              _mul(a.m[0],b.m[3])+_mul(a.m[3],b.m[4])+_mul(a.m[6],b.m[5]),
	              _mul(a.m[0],b.m[6])+_mul(a.m[3],b.m[7])+_mul(a.m[6],b.m[8]),
	              _mul(a.m[0],b.m[9])+_mul(a.m[3],b.m[10])+_mul(a.m[6],b.m[11])+a.m[9],

	              _mul(a.m[1],b.m[0])+_mul(a.m[4],b.m[1])+_mul(a.m[7],b.m[2]),
	              _mul(a.m[1],b.m[3])+_mul(a.m[4],b.m[4])+_mul(a.m[7],b.m[5]),
	              _mul(a.m[1],b.m[6])+_mul(a.m[4],b.m[7])+_mul(a.m[7],b.m[8]),
	              _mul(a.m[1],b.m[9])+_mul(a.m[4],b.m[10])+_mul(a.m[7],b.m[11])+a.m[10],

	              _mul(a.m[2],b.m[0])+_mul(a.m[5],b.m[1])+_mul(a.m[8],b.m[2]),
	              _mul(a.m[2],b.m[3])+_mul(a.m[5],b.m[4])+_mul(a.m[8],b.m[5]),
	              _mul(a.m[2],b.m[6])+_mul(a.m[5],b.m[7])+_mul(a.m[8],b.m[8]),
	              _mul(a.m[2],b.m[9])+_mul(a.m[5],b.m[10])+_mul(a.m[8],b.m[11])+a.m[11]);
}

mat4x4_t mat4x4affinemul(mat4x4_t a,mat4x4_t b)
{
	return mat4x4(_mul(a.m[0],b.m[0])+_mul(a.m[4],b.m[1])+_mul(a.m[8],b.m[2]),
	              _mul(a.m[0],b.m[4])+_mul(a.m[4],b.m[5])+_mul(a.m[8],b.m[6]),
	              _mul(a.m[0],b.m[8])+_mul(a.m[4],b.m[9])+_mul(a.m[8],b.m[10]),
	              _mul(a.m[0],b.m[12])+_mul(a.m[4],b.m[13])+_mul(a.m[8],b.m[14])+a.m[12],

	              _mul(a.m[1],b.m[0])+_mul(a.m[5],b.m[1])+_mul(a.m[9],b.m[2]),
	              _mul(a.m[1],b.m[4])+_mul(a.m[5],b.m[5])+_mul(a.m[9],b.m[6]),
	              _mul(a.m[1],b.m[8])+_mul(a.m[5],b.m[9])+_mul(a.m[9],b.m[10]),
	              _mul(a.m[1],b.m[12])+_mul(a.m[5],b.m[13])+_mul(a.m[9],b.m[14])+a.m[13],

	              _mul(a.m[2],b.m[0])+_mul(a.m[6],b.m[1])+_mul(a.m[10],b.m[2]),
	              _mul(a.m[2],b.m[4])+_mul(a.m[6],b.m[5])+_mul(a.m[10],b.m[6]),
	              _mul(a.m[2],b.m[8])+_mul(a.m[6],b.m[9])+_mul(a.m[10],b.m[10]),
	              _mul(a.m[2],b.m[12])+_mul(a.m[6],b.m[13])+_mul(a.m[10],b.m[14])+a.m[14],

	              F(0),F(0),F(0),F(1));
}

mat2x2_t mat2x2inverse(mat2x2_t m)
{
	mat2x2_t res;
	scalar_t det=_mul(m.m[0],m.m[2])-_mul(m.m[1],m.m[2]);
	// singular if det==0

	res.m[0]=_div(m.m[0],det);
	res.m[2]=_div(m.m[1],det);

	res.m[1]=_div(m.m[2],det);
	res.m[3]=_div(m.m[3],det);

	return res;
}

mat3x3_t mat3x3inverse(mat3x3_t m)
{
	mat3x3_t res;
	scalar_t det=_mul3(m.m[0],m.m[4],m.m[8])-_mul3(m.m[0],m.m[5],m.m[7])+
	            _mul3(m.m[1],m.m[5],m.m[6])-_mul3(m.m[1],m.m[3],m.m[8])+
			    _mul3(m.m[2],m.m[3],m.m[7])-_mul3(m.m[2],m.m[4],m.m[6]);
	// singular if det==0

	res.m[0]=_div((_mul(m.m[4],m.m[8])-_mul(m.m[5],m.m[7])),det);
	res.m[3]=-_div((_mul(m.m[3],m.m[8])-_mul(m.m[5],m.m[6])),det);
	res.m[6]=_div((_mul(m.m[3],m.m[7])-_mul(m.m[4],m.m[6])),det);

	res.m[1]=-_div((_mul(m.m[1],m.m[8])-_mul(m.m[2],m.m[7])),det);
	res.m[4]=_div((_mul(m.m[0],m.m[8])-_mul(m.m[2],m.m[6])),det);
	res.m[7]=-_div((_mul(m.m[0],m.m[7])-_mul(m.m[1],m.m[6])),det);

	res.m[2]=_div((_mul(m.m[1],m.m[5])-_mul(m.m[2],m.m[4])),det);
	res.m[5]=-_div((_mul(m.m[0],m.m[5])-_mul(m.m[2],m.m[3])),det);
	res.m[8]=_div((_mul(m.m[0],m.m[4])-_mul(m.m[1],m.m[3])),det);

	return res;
}

mat3x3_t mat3x3affineinverse(mat3x3_t m)
{
	mat3x3_t res;
	scalar_t det=_mul(m.m[0],m.m[3])-_mul(m.m[1],m.m[4]);
	// singular if det==0

	res.m[0]=_div(m.m[0],det);
	res.m[3]=_div(m.m[1],det);

	res.m[1]=_div(m.m[3],det);
	res.m[4]=_div(m.m[4],det);

	res.m[2]=0;
	res.m[6]=0;

	res.m[6]=-(_mul(m.m[6],res.m[0])+_mul(m.m[7],res.m[3]));
	res.m[7]=-(_mul(m.m[6],res.m[1])+_mul(m.m[7],res.m[4]));
	res.m[8]=F(1);

	return res;
}

mat3x2_t mat3x2affineinverse(mat3x2_t m)
{
	mat3x2_t res;
	scalar_t det=_mul(m.m[0],m.m[2])-_mul(m.m[1],m.m[2]);
	// singular if det==0

	res.m[0]=_div(m.m[0],det);
	res.m[2]=_div(m.m[1],det);

	res.m[1]=_div(m.m[2],det);
	res.m[3]=_div(m.m[3],det);

	res.m[4]=-(_mul(m.m[4],res.m[0])+_mul(m.m[5],res.m[2]));
	res.m[5]=-(_mul(m.m[4],res.m[1])+_mul(m.m[5],res.m[3]));

	return res;
}

mat4x3_t mat4x3affineinverse(mat4x3_t m)
{
	mat4x3_t res;
	scalar_t det=_mul3(m.m[0],m.m[4],m.m[8])-_mul3(m.m[0],m.m[5],m.m[7])+
	            _mul3(m.m[1],m.m[5],m.m[6])-_mul3(m.m[1],m.m[3],m.m[8])+
			    _mul3(m.m[2],m.m[3],m.m[7])-_mul3(m.m[2],m.m[4],m.m[6]);
	// singular if det==0

	res.m[0]=_div((_mul(m.m[4],m.m[8])-_mul(m.m[5],m.m[7])),det);
	res.m[3]=-_div((_mul(m.m[3],m.m[8])-_mul(m.m[5],m.m[6])),det);
	res.m[6]=_div((_mul(m.m[3],m.m[7])-_mul(m.m[4],m.m[6])),det);

	res.m[1]=-_div((_mul(m.m[1],m.m[8])-_mul(m.m[2],m.m[7])),det);
	res.m[4]=_div((_mul(m.m[0],m.m[8])-_mul(m.m[2],m.m[6])),det);
	res.m[7]=-_div((_mul(m.m[0],m.m[7])-_mul(m.m[1],m.m[6])),det);

	res.m[2]=_div((_mul(m.m[1],m.m[5])-_mul(m.m[2],m.m[4])),det);
	res.m[5]=-_div((_mul(m.m[0],m.m[5])-_mul(m.m[2],m.m[3])),det);
	res.m[8]=_div((_mul(m.m[0],m.m[4])-_mul(m.m[1],m.m[3])),det);

	res.m[9]=-(_mul(m.m[9],res.m[0])+_mul(m.m[10],res.m[3])+_mul(m.m[11],res.m[6]));
	res.m[10]=-(_mul(m.m[9],res.m[1])+_mul(m.m[10],res.m[4])+_mul(m.m[11],res.m[7]));
	res.m[11]=-(_mul(m.m[9],res.m[2])+_mul(m.m[10],res.m[5])+_mul(m.m[11],res.m[8]));


	return res;
}

mat4x4_t mat4x4affineinverse(mat4x4_t m)
{
	mat4x4_t res;
	scalar_t det=_mul3(m.m[0],m.m[5],m.m[10])-_mul3(m.m[0],m.m[6],m.m[9])+
	            _mul3(m.m[1],m.m[6],m.m[8])-_mul3(m.m[1],m.m[4],m.m[10])+
			    _mul3(m.m[2],m.m[4],m.m[9])-_mul3(m.m[2],m.m[5],m.m[8]);
	// singular if det==0

	res.m[0]=_div((_mul(m.m[5],m.m[10])-_mul(m.m[6],m.m[9])),det);
	res.m[4]=-_div((_mul(m.m[4],m.m[10])-_mul(m.m[6],m.m[8])),det);
	res.m[8]=_div((_mul(m.m[4],m.m[9])-_mul(m.m[5],m.m[8])),det);

	res.m[1]=-_div((_mul(m.m[1],m.m[10])-_mul(m.m[2],m.m[9])),det);
	res.m[5]=_div((_mul(m.m[0],m.m[10])-_mul(m.m[2],m.m[8])),det);
	res.m[9]=-_div((_mul(m.m[0],m.m[9])-_mul(m.m[1],m.m[8])),det);

	res.m[2]=_div((_mul(m.m[1],m.m[6])-_mul(m.m[2],m.m[5])),det);
	res.m[6]=-_div((_mul(m.m[0],m.m[6])-_mul(m.m[2],m.m[4])),det);
	res.m[10]=_div((_mul(m.m[0],m.m[5])-_mul(m.m[1],m.m[4])),det);

	res.m[3]=0;
	res.m[7]=0;
	res.m[11]=0;

	res.m[12]=-(_mul(m.m[12],res.m[0])+_mul(m.m[13],res.m[4])+_mul(m.m[14],res.m[8]));
	res.m[13]=-(_mul(m.m[12],res.m[1])+_mul(m.m[13],res.m[5])+_mul(m.m[14],res.m[9]));
	res.m[14]=-(_mul(m.m[12],res.m[2])+_mul(m.m[13],res.m[6])+_mul(m.m[14],res.m[10]));
	res.m[15]=F(1);

	return res;
}

vec2_t mat2x2transform(mat2x2_t m,vec2_t v)
{
	return vec2(
	_mul(v.x,m.m[0])+_mul(v.y,m.m[2]),
	_mul(v.x,m.m[1])+_mul(v.y,m.m[3]));
}

vec2_t mat3x2transform(mat3x2_t m,vec2_t v)
{
	return vec2(
	_mul(v.x,m.m[0])+_mul(v.y,m.m[2])+m.m[4],
	_mul(v.x,m.m[1])+_mul(v.y,m.m[3])+m.m[5]);
}

vec3_t mat3x3transform(mat3x3_t m,vec3_t v)
{
	return vec3(
	_mul(v.x,m.m[0])+_mul(v.y,m.m[3])+_mul(v.z,m.m[6]),
	_mul(v.x,m.m[1])+_mul(v.y,m.m[4])+_mul(v.z,m.m[7]),
	_mul(v.x,m.m[2])+_mul(v.y,m.m[5])+_mul(v.z,m.m[8]));
}

vec3_t mat4x3transform(mat4x3_t m,vec3_t v)
{
	return vec3(
	_mul(v.x,m.m[0])+_mul(v.y,m.m[3])+_mul(v.z,m.m[6])+m.m[9],
	_mul(v.x,m.m[1])+_mul(v.y,m.m[4])+_mul(v.z,m.m[7])+m.m[10],
	_mul(v.x,m.m[2])+_mul(v.y,m.m[5])+_mul(v.z,m.m[8])+m.m[11]);
}

vec4_t mat4x4transform(mat4x4_t m,vec4_t v)
{
	return vec4(
	_mul(v.x,m.m[0])+_mul(v.y,m.m[4])+_mul(v.z,m.m[8])+_mul(v.w,m.m[12]),
	_mul(v.x,m.m[1])+_mul(v.y,m.m[5])+_mul(v.z,m.m[9])+_mul(v.w,m.m[13]),
	_mul(v.x,m.m[2])+_mul(v.y,m.m[6])+_mul(v.z,m.m[10])+_mul(v.w,m.m[14]),
	_mul(v.x,m.m[3])+_mul(v.y,m.m[7])+_mul(v.z,m.m[11])+_mul(v.w,m.m[15]));
}

