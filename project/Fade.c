#include "Fade.h"
#include "ARM.h"

void GeneratePaletteBlock(int block,int h)
{
	for(int i=0;i<16;i++)
	{
		int col=MakeHSV(h,IntToFixed(1),IntToFixed(i)/15);
		PALRAM_A[block*16+i]=col;
		PALRAM_B[block*16+i]=col;
	}
}

void InitFade()
{
	VRAMCNT_A=VRAMCNT_A_BG_VRAM_A;

	DISPCNT_A=DISPCNT_MODE_3|DISPCNT_ON|DISPCNT_BG3_ON;
	BG3CNT_A=BGxCNT_BITMAP_BASE_0K|BGxCNT_EXTENDED_BITMAP_8
			|BGxCNT_BITMAP_SIZE_256x256|BGxCNT_PRIORITY_1;
	BG3PA_A=0x100;
	BG3PB_A=0;
	BG3PC_A=0;
	BG3PD_A=0x100;
	BG3HOFS_A=0;
	BG3VOFS_A=0;

//	BLDCNT_A=BLDCNT_SRC_A_BG3|BLDCNT_SRC_B_BG0|BLDCNT_EFFECT_ALPHA;
//	BLDALPHA_A=BLDALPHA_EVA(16)|BLDALPHA_EVB(16);

	PALRAM_A[0]=PALRAM_B[0]=0;
	GeneratePaletteBlock(1,0);
	GeneratePaletteBlock(2,30);
	GeneratePaletteBlock(3,60);
	GeneratePaletteBlock(4,90);
	GeneratePaletteBlock(5,120);
	GeneratePaletteBlock(6,150);
	GeneratePaletteBlock(7,180);
	GeneratePaletteBlock(8,210);
	GeneratePaletteBlock(9,240);
	GeneratePaletteBlock(10,270);
	GeneratePaletteBlock(11,300);
	GeneratePaletteBlock(12,330);
}

void Fade()
{
	Decay(VRAM_A_OFFS_0K);
//	Decay(VRAM_B_OFFS_0K);

	for(int i=0;i<10;i++)
	{
		DrawLineWithClip(VRAM_A_OFFS_0K,
		Random()%256,Random()%192,Random()%256,Random()%192,
		(Random()%16)*16+15,false);
	}
}
