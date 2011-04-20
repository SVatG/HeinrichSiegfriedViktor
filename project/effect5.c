#include "Utils.h"
#include "DS3D.h"
#include "VoxelBlock.h"
#include "Hardware.h"
#include "Loader.h"
#include "RainbowTable.h"

VoxelBlock balls;

void effect5_init() {
	uint16_t* master_bright = (uint16_t*)(0x400006C);
	memset( master_bright, (1<<6) | (16), 2 );
	uint16_t* master_bright_sub = (uint16_t*)(0x400106C);
	memset( master_bright_sub, (1<<6) | (16), 2 );

	DISPCNT_A=DISPCNT_MODE_5|DISPCNT_3D|DISPCNT_BG0_ON|DISPCNT_BG3_ON|DISPCNT_ON;

	VRAMCNT_A = VRAMCNT_A_LCDC;
	VRAMCNT_C = VRAMCNT_C_BG_VRAM_B;
	DISPCNT_B = DISPCNT_MODE_5 | DISPCNT_BG2_ON | DISPCNT_ON;
	BG2CNT_B = BGxCNT_EXTENDED_BITMAP_16 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_BASE_0K;
	BG2CNT_B = (BG2CNT_B&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_0;
	BG2PA_B = (1 << 8);
	BG2PB_B = 0;
	BG2PC_B = 0;
	BG2PD_B = (1 << 8);
	BG2X_B = 0;
	BG2Y_B = 0;

	int dx = icos(128)/26.5;
	int dy = isin(128)/26.5;
	BG2PA_B = dx;
	BG2PB_B = dy;
	BG2PC_B = -dy;
	BG2PD_B = dx;
	BG2X_B = 4000;
	BG2Y_B = 10000;

	// Set up voxelcubes
	VRAMCNT_D=VRAMCNT_D_LCDC;
	VRAMCNT_F=VRAMCNT_F_LCDC;

	for(int i=0;i<16;i++) VRAM_LCDC_F[i]=MakeRGB15(i+16,i+16,i+16);

	VRAMCNT_D=VRAMCNT_D_TEXTURE_OFFS_0K;
	VRAMCNT_F=VRAMCNT_F_TEXTURE_PALETTE_SLOT_0;

	DSInit3D();
	DSViewport(0,0,255,191);

	DSSetControl(DS_TEXTURING|DS_ANTIALIAS);
	DSClearParams(26,26,26,0,63);

	DSSetPaletteOffset(0,DS_TEX_FORMAT_PAL4);

	DSMatrixMode(DS_PROJECTION);
	DSLoadIdentity();
	DSPerspective(100,256.0/192.0,1,1024);

	InitVoxelBlock(&balls,17,17,64,NULL);

	// Background
	VRAMCNT_B = VRAMCNT_B_BG_VRAM_A_OFFS_0K;
	BG3CNT_A = BGxCNT_EXTENDED_BITMAP_8 | BGxCNT_BITMAP_SIZE_256x256 | BGxCNT_OVERFLOW_WRAP | BGxCNT_BITMAP_BASE_0K;
	BG3CNT_A = (BG3CNT_A&~BGxCNT_PRIORITY_MASK)|BGxCNT_PRIORITY_0;
	BG3PA_A = (1 << 8);
	BG3PB_A = 0;
	BG3PC_A = 0;
	BG3PD_A = (1 << 8);
	BG3X_A = 0;
	BG3Y_A = 0;
}

void MetaBallsA(int t) {
	static uint8_t ri = 0;
	DSMatrixMode(DS_POSITION);
	DSLoadIdentity();

	// Move blocks
	if(t%4==0) {
		ScrollVoxelBlockByZ(&balls);
	}

	// Spiral rainbows
	float dxp = (icos((t-3)<<3)>>9);
	float dyp = (isin((t-3)<<3)>>9);
	float dx = (icos(t<<3)>>9);
	float dy = (isin(t<<3)>>9);
	u16 c = rainbowTable[++ri]|0x8000;
	u16 d = rainbowTable[(ri+40)%255]|0x8000;
	u16 e = rainbowTable[(ri+90)%255]|0x8000;
	u16 f = rainbowTable[(ri+170)%255]|0x8000;
	for( int i = 0; i < 3; i++ ) {
		SetVoxelAt(&balls,i+8+dxp,8+dyp,0,0);
		SetVoxelAt(&balls,i+8+dx,8+dy,0,c);
		SetVoxelAt(&balls,i+8+dyp,8-dxp,0,0);
		SetVoxelAt(&balls,i+8+dy,8-dx,0,d);
		SetVoxelAt(&balls,i+8-dxp,8-dyp,0,0);
		SetVoxelAt(&balls,i+8-dx,8-dy,0,e);
		SetVoxelAt(&balls,i+8-dyp,8+dxp,0,0);
		SetVoxelAt(&balls,i+8-dy,8+dx,0,f);
	}
	for( int i = -1; i < 2; i+=2 ) {
		SetVoxelAt(&balls,9+dxp,i+8+dyp,0,0);
		SetVoxelAt(&balls,9+dx,i+8+dy,0,c);
		SetVoxelAt(&balls,9+dyp,i+8-dxp,0,0);
		SetVoxelAt(&balls,9+dy,i+8-dx,0,d);
		SetVoxelAt(&balls,9-dxp,i+8-dyp,0,0);
		SetVoxelAt(&balls,9-dx,i+8-dy,0,e);
		SetVoxelAt(&balls,9-dyp,i+8+dxp,0,0);
		SetVoxelAt(&balls,9-dy,i+8+dx,0,f);
	}
	RefreshVoxelBlock(&balls);

	// Move things
	DSTranslatef(0,0,200);
	DSRotateZi(-t<<2);
	DSScalef(8,8,8);
	DSTranslatef32(DSf32(0),DSf32(0),((t&3)<<10)-DSf32(33));
	DrawVoxelBlock(&balls);
	DSSwapBuffers(0);
}

uint8_t effect5_update( uint32_t t ) {
	MetaBallsA(t);

	// Fadein
	if( t <= 16 ) {
		uint16_t* master_bright = (uint16_t*)(0x400006C);
		memset( master_bright, (1<<6) | (16-t), 2 );
		uint16_t* master_bright_sub = (uint16_t*)(0x400106C);
		memset( master_bright_sub, (1<<6) | (16-t), 2 );
	}

	return 0;
}


void effect5_destroy() {
	CleanupVoxelBlock(&balls);
}

