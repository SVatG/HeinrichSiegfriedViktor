#include "DS3D/Utils.h"
#include "DS3D/DS3D.h"
#include "BoxBlock.h"
#include "Hardware.h"
#include "Loader.h"
#include "RainbowTable.h"

BoxBlock balls;

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

	loadVRAMIndirect( "nitro:/textures.pal4", VRAM_LCDC_D,16384);
	
	for(int i=0;i<16;i++) VRAM_LCDC_F[i]=MakeRGB15(i+16,i+16,i+16);

	VRAMCNT_D=VRAMCNT_D_TEXTURE_OFFS_0K;
	VRAMCNT_F=VRAMCNT_F_TEXTURE_PALETTE_SLOT_0;

	DSInit3D();
	DSViewport(0,0,255,191);
	
	DSSetControl(DS_ALPHA_BLEND|DS_ANTIALIAS);
	DSClearParams(26,26,26,0,63);

	DSSetPaletteOffset(0,DS_TEX_FORMAT_PAL4);

	DSMatrixMode(DS_PROJECTION);
	DSLoadIdentity();
	DSPerspectivef(100,256.0/192.0,1,1024);

	InitBoxBlock(&balls,26,24,20);

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

int ballRound = 0;
void MetaBallsA(int t) {
	static uint8_t ri = 0;
	DSMatrixMode(DS_POSITION);
	DSLoadIdentity();

	float dx = -14+((float)isin(t<<3))/256.0;
	float dy = -12;
	float dz = -10;
	uint16_t c = rainbowTable[++ri]|0x8000;
	uint16_t d = rainbowTable[(ri+40)%255]|0x8000;
	uint16_t e = rainbowTable[(ri+90)%255]|0x8000;
	int det = 0;
	for( int x = 0; x < 26; x++ ) {
		for( int y = ballRound; y < ballRound+8; y++ ) {
			for( int z = 0; z < 20; z++ ) {
				det = ((dx+x)*(dx+x)+(dy+y)*(dy+y)+(dz+z)*(dz+z));
				if(det<15) {
					SetBoxAt(&balls,x,y,z,c,15-det);
				}
				else {
					SetBoxAt(&balls,x,y,z,0,0);
				}
			}
		}
	}
	ballRound += 8;
	if(ballRound == 24 ) {
		ballRound = 0;
	}

	// Move things
	DSRotateZi(-t<<2);
	DSRotateYi(t>>3);
	DSTranslatef(0,0,-10);
	DrawBoxBlock(&balls);
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
	CleanupBoxBlock(&balls);
}

