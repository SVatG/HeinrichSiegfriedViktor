#include "VoxelBlock.h"
#include "BoxBlock.h"
#include "DS3D.h"

#include <stdlib.h>
#include <math.h>

void InitBoxBlock(BoxBlock *self,int width,int height,int depth)
{
	self->width=width;
	self->height=height;
	self->depth=depth;

	self->boxes=malloc(width*height*depth*sizeof(self->boxes[0]));

	for(int i=0;i<width*height*depth;i++) {
		self->boxes[i].colour=0;
		self->boxes[i].size=0;
	}
}

void CleanupBoxBlock(BoxBlock *self) {
	free(self->boxes);
}


inline void SetBoxAt(BoxBlock *self,int x,int y,int z,uint16_t val,uint8_t size) {
	Box *box=&self->boxes[x+(y+z*self->height)*self->width];

	box->colour=val;
	box->size=size;
}

static uint32_t LightFunction(vec3_t lightdir,float nx,float ny,float nz);

// This has changes, though
static void DrawBoxFace(int fx,int fy,int fz,int dxdu,int dydu,int dzdu,int dxdv,int dydv,int dzdv);

void DrawBoxBlock(BoxBlock *self) {
	DSMatrixMode(DS_POSITION);
	DSStoreMatrix(0);
	DSTranslatef32(-DSf32(self->width)/2,-DSf32(self->height)/2,-DSf32(self->depth)/2);
	
	DSMatrixMode(DS_POSITION);
	DSScalef32(DSf32(4096),DSf32(4096),DSf32(4096));

	DSPolygonAttributes(DS_POLY_MODE_MODULATION|DS_POLY_CULL_NONE|DS_POLY_LIGHT0|DS_POLY_ALPHA(10));
	DSLight3f(0,0xffff,1,1,1);

	DSBegin(DS_QUADS);

	Box *box=self->boxes;
	for(int z=0;z<self->depth;z++)
	for(int y=0;y<self->height;y++)
	for(int x=0;x<self->width;x++)
	{
		if(IsBoxFilled(box->colour)) {
			DSMaterialDiffuseAndAmbient(box->colour,10);
			DSNormal3f(-1,0,0);
			DrawBoxFace(x,y,z,0,1,0,0,0,1);
			DSNormal3f(1,0,0);
			DrawBoxFace(x+1,y,z,0,1,0,0,0,1);
			DSNormal3f(0,-1,0);
			DrawBoxFace(x,y,z,0,0,1,1,0,0);
			DSNormal3f(0,1,0);
			DrawBoxFace(x,y+1,z,0,0,1,1,0,0);
			DSNormal3f(0,0,-1);
			DrawBoxFace(x,y,z,1,0,0,0,1,0);
			DSNormal3f(0,0,1);
			DrawBoxFace(x,y,z+1,1,0,0,0,1,0);
		}

		box++;
	}
	DSEnd();
	DSMatrixMode(DS_POSITION);
	DSRestoreMatrix(0);
}

static void DrawBoxFace(int fx,int fy,int fz,int dxdu,int dydu,int dzdu,int dxdv,int dydv,int dzdv) {
	DSSetTexture(0);

	DSVertex3v16(fx,fy,fz);
	DSVertex3v16(fx+dxdu,fy+dydu,fz+dzdu);
	DSVertex3v16(fx+dxdu+dxdv,fy+dydu+dydv,fz+dzdu+dzdv);
	DSVertex3v16(fx+dxdv,fy+dydv,fz+dzdv);
}

static inline float TransformRange(float val,float oldlow,float oldhigh,float newlow,float newhigh)
{
	return (val-oldlow)/(oldhigh-oldlow)*(newhigh-newlow)+newlow;
}

static inline float ClampRange(float val,float low,float high)
{
	if(val<low) return low;
	if(val>high) return high;
	return val;
}

static uint32_t LightFunction(vec3_t lightdir,float nx,float ny,float nz)
{
	float lx=lightdir.x;
	float ly=lightdir.y;
	float lz=lightdir.z;
	float l=sqrt(lx*lx+ly*ly+lz*lz);
	lx/=l; ly/=l; lz/=l;

	float light=ClampRange(TransformRange(lx*nx+ly*ny+lz*nz,-0.5,1,0.5,1),0.5,1);

	return ((int)(light*511))&0x3ff;
}
