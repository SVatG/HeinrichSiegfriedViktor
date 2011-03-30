#include "Utils.h"
#include "DS3D.h"
#include "VoxelBlock.h"
#include "Hardware.h"
#include "Loader.h"
#include "RainbowTable.h"

VoxelBlock block;

void effect6_init() {
	uint16_t* master_bright = (uint16_t*)(0x400006C);
	memset( master_bright, (1<<6) | (16), 2 );
	uint16_t* master_bright_sub = (uint16_t*)(0x400106C);
	memset( master_bright_sub, (1<<6) | (16), 2 );
		
	DISPCNT_A=DISPCNT_MODE_4|DISPCNT_3D|DISPCNT_BG0_ON|DISPCNT_BG3_ON|DISPCNT_ON;

	DISPCNT_B=DISPCNT_MODE_4|DISPCNT_BG3_ON|DISPCNT_ON;

	BG3CNT_A=BGxCNT_BITMAP_BASE_0K|BGxCNT_EXTENDED_BITMAP_8
			|BGxCNT_BITMAP_SIZE_256x256;
	BG3CNT_A = (BG3CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_1;
	BG0CNT_A = (BG0CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_0;
	
	BG3PA_A=0x100;
	BG3PB_A=0;
	BG3PC_A=0;
	BG3PD_A=0x100;
	BG3HOFS_A=0;
	BG3VOFS_A=0;
	BG3X_A = 0;
	BG3Y_A = 0;
	
	BG3CNT_B=BGxCNT_BITMAP_BASE_0K|BGxCNT_EXTENDED_BITMAP_8
			|BGxCNT_BITMAP_SIZE_256x256|BGxCNT_PRIORITY_1;
	BG3PA_B=0x100;
	BG3PB_B=0;
	BG3PC_B=0;
	BG3PD_B=0x100;
	BG3HOFS_B=0;
	BG3VOFS_B=0;

	VRAMCNT_A=VRAMCNT_A_LCDC;
	VRAMCNT_B=VRAMCNT_B_LCDC;
	VRAMCNT_C=VRAMCNT_C_BG_VRAM_B;
	VRAMCNT_D=VRAMCNT_D_BG_VRAM_A;
	VRAMCNT_F=VRAMCNT_F_LCDC;

	load8bVRAMIndirect( "nitro:/gfx/namakubi.img.bin",VRAM_B,256*192);
	loadVRAMIndirect( "nitro:/gfx/namakubi.pal.bin", PALRAM_B,256*2);
	load8bVRAMIndirect( "nitro:/gfx/online.img.bin",VRAM_A,256*192);
	loadVRAMIndirect( "nitro:/gfx/online.pal.bin", PALRAM_A,256*2);
///	loadVRAMIndirect( "nitro:/gfx/online.img.bin", VRAM_LCDC_D,256*192*2);

	loadVRAMIndirect( "nitro:/textures.pal4", VRAM_LCDC_A,16384);

	for(int i=0;i<16;i++) VRAM_LCDC_F[i]=MakeRGB15(i+16,i+16,i+16);

	VRAMCNT_A=VRAMCNT_A_TEXTURE_OFFS_0K;
//	VRAMCNT_D=VRAMCNT_D_TEXTURE_OFFS_256K;
	VRAMCNT_F=VRAMCNT_F_TEXTURE_PALETTE_SLOT_0;

	DSInit3D();
	DSViewport(0,0,255,191);

	DSSetControl(DS_TEXTURING|DS_ANTIALIAS);
	DSClearParams(26,26,26,0,63);

	DSSetPaletteOffset(0,DS_TEX_FORMAT_PAL4);

	DSMatrixMode(DS_PROJECTION);
	DSLoadIdentity();
	DSPerspective(65,256.0/192.0,1,1024);

	InitVoxelBlock(&block,18,18,128,NULL);
/*
	for(int x=0;x<6;x++)
	for(int y=0;y<6;y++)
	for(int z=0;z<64;z++)
	{
		if(Random()%8==0)
		SetVoxelAt(&block,x,y,z,MakeVoxel(31,31,31));
	}
	RefreshVoxelBlock(&block);*/
}

int prob=14;

uint8_t ri = 0;
uint8_t effect6_update( uint32_t t ) {

	DSMatrixMode(DS_POSITION);
	DSLoadIdentity();

		
		if(t%4==0) {
			ScrollVoxelBlockByZ(&block);
		}
/*		prob+=Random()%5-2;
		if(prob<3) prob=3;
		if(prob>15) prob=15;*/

		SetVoxelAt(&block,(icos((t-20)<<6)>>9)+8,(isin((t-20)<<6)>>9)+8,0,0);
		SetVoxelAt(&block,(icos(t<<6)>>9)+8,(isin(t<<6)>>9)+8,0,/*MakeVoxel(31,31,31)*/rainbowTable[++ri]|0x8000);
		
		RefreshVoxelBlock(&block);

	DSTranslatef(0,0,-80);
// 	DSRotateYi(512);
// 	DSRotateXi(256+64);
	DSRotateZi(-t<<4);
	DSScalef(8,8,8);
	DSTranslatef32(DSf32(-1),DSf32(-2),((t&3)<<10)-DSf32(10));
	//DSRotateXi(100);

	DrawVoxelBlock(&block);

	DSSwapBuffers(0);

	if( t <= 16 ) {
		uint16_t* master_bright = (uint16_t*)(0x400006C);
		memset( master_bright, (1<<6) | (16-t), 2 );
		uint16_t* master_bright_sub = (uint16_t*)(0x400106C);
		memset( master_bright_sub, (1<<6) | (16-t), 2 );
	}
// 
// 	if( t >= 684 ) {
// 		uint16_t* master_bright = (uint16_t*)(0x400006C);
// 		memset( master_bright, (1<<6) | (t-684), 2 );
// 		uint16_t* master_bright_sub = (uint16_t*)(0x400106C);
// 		memset( master_bright_sub, (1<<6) | (t-684), 2 );
// 	}
// 	
// 	if( t == 700 ) {
// 		return ( 1 );
// 	}
	
	return 0;
}


void effect6_destroy() {
	CleanupVoxelBlock(&block);
}

