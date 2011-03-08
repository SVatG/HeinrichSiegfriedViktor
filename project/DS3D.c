#include "DS3D.h"

#include <string.h>

static uint32_t next_texture_block;
static uint32_t next_palette_block;

void DSInit3D()
{
	while(GXSTAT&(1<<27));

	GXSTAT|=(1<<29);
	DSResetMatrixStack();
	DSSwapBuffers(0);
	DISP3DCNT=0;
	DSClearParams(0,0,0,31,0);
	DSClearDepth(DS_MAX_DEPTH);

	TEXIMAGE_PARAM=0;
	POLYGON_ATTR=0;

	DSFreeAllTextures();
//	DSFreeAllPalettes();
}



void DSRotatef32i(int angle,int32_t x,int32_t y,int32_t z)
{
	int32_t axis[3];
	int32_t sine=isin(angle);
	int32_t cosine=icos(angle);
	int32_t one_minus_cosine=DSf32(1)-cosine;

	axis[0]=x;
	axis[1]=y;
	axis[2]=z;
	inormalize(axis);

	MTX_MULT_3x3=cosine + imul(one_minus_cosine, imul(axis[0], axis[0]));
	MTX_MULT_3x3=imul(one_minus_cosine, imul(axis[0], axis[1])) - imul(axis[2], sine);
	MTX_MULT_3x3=imul(imul(one_minus_cosine, axis[0]), axis[2]) + imul(axis[1], sine);

	MTX_MULT_3x3=imul(imul(one_minus_cosine, axis[0]),  axis[1]) + imul(axis[2], sine);
	MTX_MULT_3x3=cosine + imul(imul(one_minus_cosine, axis[1]), axis[1]);
	MTX_MULT_3x3=imul(imul(one_minus_cosine, axis[1]), axis[2]) - imul(axis[0], sine);

	MTX_MULT_3x3=imul(imul(one_minus_cosine, axis[0]), axis[2]) - imul(axis[1], sine);
	MTX_MULT_3x3=imul(imul(one_minus_cosine, axis[1]), axis[2]) + imul(axis[0], sine);
	MTX_MULT_3x3=cosine + imul(imul(one_minus_cosine, axis[2]), axis[2]);
}

void DSLookAtf32(int32_t eyex,int32_t eyey,int32_t eyez,int32_t lookatx,int32_t lookaty,
int32_t lookatz,int32_t upx,int32_t upy,int32_t upz)
{
	int32_t side[3],forward[3],up[3],eye[3];

	forward[0]=eyex-lookatx; forward[1]=eyey-lookaty; forward[2]=eyez-lookatz;
	up[0]=upx; up[1]=upy; up[2]=upz;
	eye[0]=eyex; eye[1]=eyey; eye[2]=eyez;

	inormalize(forward);
	icross(up,forward,side);
	inormalize(side);
	icross(forward,side,up);

	MTX_MULT_4x3=side[0]; MTX_MULT_4x3=up[0]; MTX_MULT_4x3=forward[0];
	MTX_MULT_4x3=side[1]; MTX_MULT_4x3=up[1]; MTX_MULT_4x3=forward[1];
	MTX_MULT_4x3=side[2]; MTX_MULT_4x3=up[2]; MTX_MULT_4x3=forward[2];
	MTX_MULT_4x3=-idot(eye,side);
	MTX_MULT_4x3=-idot(eye,up);
	MTX_MULT_4x3=-idot(eye,forward);
}



uint32_t DSTextureSize(uint32_t flags)
{
	uint32_t pixels=1<<(((flags>>20)&7)+((flags>>23)&7)+6);

	switch(flags&DS_TEX_FORMAT_MASK)
	{
		case DS_TEX_FORMAT_A3I5:
		case DS_TEX_FORMAT_PAL8:
		case DS_TEX_FORMAT_A5I3:
			return pixels;

		case DS_TEX_FORMAT_NONE:
		case DS_TEX_FORMAT_COMPRESSED:
			return 0;

		case DS_TEX_FORMAT_RGB:
			return pixels*2;

		case DS_TEX_FORMAT_PAL2:
			return pixels/4;

		case DS_TEX_FORMAT_PAL4:
			return pixels/2;
	}
	return 0;
}

uint16_t *DSTextureAddress(uint32_t texture)
{
	return (uint16_t *)(((texture&0xffff)<<3)|0x6800000);
}

static int VRAMAddressIsTextureBank(uint32_t addr)
{
	if((uint16_t *)addr<VRAM_LCDC_A) return 0;
	else if((uint16_t *)addr<VRAM_LCDC_B) return (VRAMCNT_A&3)==(VRAMCNT_A_TEXTURE&3);
	else if((uint16_t *)addr<VRAM_LCDC_C) return (VRAMCNT_B&3)==(VRAMCNT_B_TEXTURE&3);
	else if((uint16_t *)addr<VRAM_LCDC_D) return (VRAMCNT_C&3)==(VRAMCNT_C_TEXTURE&3);
	else if((uint16_t *)addr<VRAM_LCDC_E) return (VRAMCNT_D&3)==(VRAMCNT_D_TEXTURE&3);
	else return 0;
}

uint32_t DSAllocTexture(uint32_t flags)
{
	uint32_t size=DSTextureSize(flags);
	uint32_t addr=next_texture_block;

	next_texture_block+=size;

	// Bug: does not handle non-contiguous texture memory gracefully with large allocations
	while(!VRAMAddressIsTextureBank(next_texture_block-1) && next_texture_block<=(uint32_t)VRAM_LCDC_E)
	{
		addr=next_texture_block=(next_texture_block&~0x1ffff)+0x20000;
		next_texture_block+=size;
	}

	if(next_texture_block>(uint32_t)VRAM_LCDC_E) return DS_INVALID_TEXTURE;

	return flags|((addr>>3)&0xffff);
}

void DSFreeAllTextures()
{
	next_texture_block=(uint32_t)VRAM_LCDC_A;
}

void DSCopyTexture(uint32_t texture,void *data)
{
	uint32_t size=DSTextureSize(texture);
	void *dest=DSTextureAddress(texture);

	uint32_t vramtmp=SaveAndSetMemoryBanks(VRAMCNT_A_LCDC,VRAMCNT_B_LCDC,VRAMCNT_C_LCDC,VRAMCNT_D_LCDC);
	memcpy(dest,data,size); // TODO: check if this works right
	RestoreMemoryBanks(vramtmp);
}

uint32_t DSAllocAndCopyTexture(uint32_t flags,void *data)
{
	uint32_t tex=DSAllocTexture(flags);
	if(tex==DS_INVALID_TEXTURE) return DS_INVALID_TEXTURE;
	DSCopyTexture(tex,data);
	return tex;
}



void DSSetFogWithCallback(uint8_t r,uint8_t g,uint8_t b,uint8_t a,
int32_t start,int32_t end,int32_t near,int32_t far,
int32_t (*callback)(int32_t z,int32_t start,int32_t end))
{
	uint32_t control=DISP3DCNT&~0xf00;

	uint32_t startdepth=imul(0x7fff,idiv(imul(far,near-start),imul(start,near-far)));
	uint32_t enddepth=imul(0x7fff,idiv(imul(far,near-end),imul(end,near-far)));

	uint32_t diff=enddepth-startdepth-1;
	int log=0;
	while(diff>>=1) log++;

	int shift=14-log;
	if(shift>10) shift=10;

	DISP3DCNT=control|DS_FOG_SHIFT(shift);

	FOG_COLOR=((a&0x1f)<<16)|DSPackRGB5(r,g,b);
	FOG_OFFSET=startdepth;

	for(int i=0;i<32;i++)
	{
		uint32_t depth=startdepth+i*(0x400>>shift);
		if(i==0) FOG_TABLE[i]=imul(0x7f,callback(start,start,end));
		else if(depth>=enddepth) FOG_TABLE[i]=imul(0x7f,callback(end,start,end));
		else FOG_TABLE[i]=imul(0x7f,
		callback(idiv(imul(far,near),far+imul(idiv(depth,0x7fff),near-far)),
		start,end));
	}
}

static int32_t LinearZCallback(int32_t z,int32_t start,int32_t end)
{
	return idiv(z-start,end-start);
}

void DSSetFogLinearf32(uint8_t r,uint8_t g,uint8_t b,uint8_t a,int32_t start,int32_t end,int32_t near,int32_t far)
{ DSSetFogWithCallback(r,g,b,a,start,end,near,far,LinearZCallback); }

void DSSetFogLinearf(uint8_t r,uint8_t g,uint8_t b,uint8_t a,float start,float end,float near,float far)
{ DSSetFogLinearf32(r,g,b,a,DSf32(start),DSf32(end),DSf32(near),DSf32(far)); }

