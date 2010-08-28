#include "Utils.h"
#include "DS3D.h"

static int flip;
static uint32_t whitetexture;
static bool fadingout;
static int fadestart;

void effect2_init() {
	VRAMCNT_C=VRAMCNT_C_LCDC;

	//load8bVRAMIndirect( "nitro:/gfx/bolder1.img.bin",VRAM_LCDC_C,256*192 );
	//loadVRAMIndirect( "nitro:/gfx/bolder1.pal.bin", PALRAM_A, 256 * 2 );

	VRAMCNT_A=VRAMCNT_A_LCDC;
	VRAMCNT_B=VRAMCNT_B_LCDC;
	VRAMCNT_C=VRAMCNT_C_BG_VRAM_A_OFFS_0K;
	VRAMCNT_D=VRAMCNT_D_LCDC;

	DISPCNT_A=DISPCNT_MODE_4|DISPCNT_3D|DISPCNT_BG0_ON|/*DISPCNT_BG3_ON|*/DISPCNT_ON;
	BG0CNT_A=BGxCNT_PRIORITY_2;
	BG3CNT_A=BGxCNT_BITMAP_BASE_0K|BGxCNT_EXTENDED_BITMAP_16
			|BGxCNT_BITMAP_SIZE_256x256|BGxCNT_PRIORITY_1; // RGB bitmap mode
	BG3PA_A=0x100;
	BG3PB_A=0;
	BG3PC_A=0;
	BG3PD_A=0x100;
	BG3HOFS_A=0;
	BG3VOFS_A=0;

	DSInit3D();
	DSViewport(0,0,255,191);

	DSSetControl(DS_TEXTURING|DS_ANTIALIAS|DS_ALPHA_BLEND);
	DSClearParams(0,0,0,31,63);

	for(int i=0;i<256*256;i++)
	{
		VRAM_LCDC_A[i]=0x8000;
		VRAM_LCDC_B[i]=0x8000;
	}

	DSCopyColorTexture(DS_TEX_ADDRESS(VRAM_LCDC_A+256*204),0x7fff);
	DSCopyColorTexture(DS_TEX_ADDRESS(VRAM_LCDC_B+256*204),0x7fff);
	whitetexture=DS_TEX_ADDRESS(VRAM_LCDC_A+256*204);

	flip=0;
	fadingout=false;
	//whitetexture=DSMakeWhiteTexture();
//DSTranslatef32(128,96,0);
//DSScalef(100.0/4096,100.0/4096,1);
}

u8 effect2_update( u32 t ) {
	int capsrc;

	uint16_t *ptr;
	if(flip) ptr=VRAM_LCDC_A;
	else ptr=VRAM_LCDC_B;
	for(int i=0;i<256*10;i++)
	{
		ptr[256*192+i]=ptr[256*191+i];
	}

	DISPCNT_A=DISPCNT_MODE_4|DISPCNT_3D|DISPCNT_BG0_ON|/*DISPCNT_BG3_ON|*/DISPCNT_ON;
	capsrc=DISPCAPCNT_SRC_A_3D;

	if(flip)
	{
		VRAMCNT_A=VRAMCNT_A_TEXTURE_OFFS_0K;
		VRAMCNT_B=VRAMCNT_B_LCDC;
		DISPCAPCNT=DISPCAPCNT_WRITE_VRAM_B|DISPCAPCNT_SIZE_256x192
		|capsrc|DISPCAPCNT_SRC_A|DISPCAPCNT_ENABLE;
	}
	else
	{
		VRAMCNT_A=VRAMCNT_A_LCDC;
		VRAMCNT_B=VRAMCNT_B_TEXTURE_OFFS_0K;
		if(t!=0) DISPCAPCNT=DISPCAPCNT_WRITE_VRAM_A|DISPCAPCNT_SIZE_256x192
		|capsrc|DISPCAPCNT_SRC_A|DISPCAPCNT_ENABLE;
	}
	flip^=1;

	DSMatrixMode(DS_PROJECTION);
	DSLoadIdentity();
	DS2DProjection(0);

	DSMatrixMode(DS_MODELVIEW);
	DSLoadIdentity();

	DSSetTexture(0|DS_TEX_SIZE_S_256|DS_TEX_SIZE_T_256|DS_TEX_FORMAT_RGB|DS_TEX_GEN_TEXCOORD);

	DSColor(0x3fff);

	DSMatrixMode(DS_TEXTURE);
	for(int i=1;i<=2;i++)
	{
		int rx=rand()%127-63;
		int ry=rand()%127-63;
//		int x=(128+10)*16+rx,y=(96+10)*16+ry;
		int x=(128+15)*16+rx,y=(96+15)*16+ry;
		DSLoadIdentity();
		DSTranslatef(x,y,0);
		DSScalef((1-(float)i/40),(1-(float)i/40),0);
		DSTranslatef(-x,-y,0);

		DSTranslatef(128*16,96*16,0);
		DSRotateZi(5*i*isin(3*t/2+128)>>12);
		DSTranslatef(-128*16,-96*16,0);

		if(i==1)
//		DSPolygonAttributes(DS_POLY_CULL_NONE|DS_POLY_ALPHA(16));
		DSPolygonAttributes(DS_POLY_CULL_NONE|DS_POLY_ALPHA(31/i));
		else
		DSPolygonAttributes(DS_POLY_MODE_DECAL|DS_POLY_CULL_NONE|DS_POLY_ALPHA(31/i)|DS_POLY_DEPTH_TEST_EQUAL);

		DSBegin(DS_QUADS);
		DSTexCoord2f(0,0); DSVertex3v16(0,0,DSf32(-1));
		DSTexCoord2f(256,0); DSVertex3v16(256,0,DSf32(-1));
		DSTexCoord2f(256,192); DSVertex3v16(256,192,DSf32(-1));
		DSTexCoord2f(0,192); DSVertex3v16(0,192,DSf32(-1));
		DSEnd();
	}

	DSLoadIdentity();



	DSPolygonAttributes(DS_POLY_MODE_DECAL|DS_POLY_CULL_NONE|DS_POLY_ALPHA(31));

	DSSetTexture(whitetexture);

	DSBegin(DS_TRIANGLES);
	for(int i=0;i<10;i++)
	{
		switch(rand()%2)
		{
			case 0: DSColor3b(rand()%15+16,rand()%15,rand()%15); break;
//			case 1: DSColor3b(rand()%15,rand()%15+16,rand()%15); break;
			case 1: DSColor3b(rand()%15,rand()%15,rand()%15+16); break;
		}
//		DSColor(rand()&0x7fff);
		DSVertex3v16(rand()%32+112,rand()%32+80,DSf32(-0.5));
		DSVertex3v16(rand()%32+112,rand()%32+80,DSf32(-0.5));
		DSVertex3v16(rand()%32+112,rand()%32+80,DSf32(-0.5));
	}
	DSEnd();

	DSSwapBuffers(DS_SWAP_NO_SORTING);

	return 0;
}


void effect2_destroy() {
	DISPCAPCNT=0;
}
