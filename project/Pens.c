#include "Pens.h"
#include "ARM.h"
#include "Drawing.h"
#include "DS3D/Hardware.h"
#include "DS3D/Utils.h"

static void GeneratePaletteBlock(int block,int h)
{
	for(int i=0;i<16;i++)
	{
		int col=MakeHSV(h,IntToFixed(1),IntToFixed(i)/15);
		PALRAM_B[block*16+i]=col;
	}
}

void InitPensOnSecondaryScreen()
{
	VRAMCNT_H=VRAMCNT_H_BG_VRAM_B;
	VRAMCNT_I=VRAMCNT_I_BG_VRAM_B_OFFS_32K;

	DISPCNT_B=DISPCNT_MODE_3|DISPCNT_ON|DISPCNT_BG3_ON;
	BG3CNT_B=BGxCNT_BITMAP_BASE_0K|BGxCNT_EXTENDED_BITMAP_8
			|BGxCNT_BITMAP_SIZE_256x256|BGxCNT_PRIORITY_1;
	BG3PA_B=0x100;
	BG3PB_B=0;
	BG3PC_B=0;
	BG3PD_B=0x100;
	BG3HOFS_B=0;
	BG3VOFS_B=0;

	PALRAM_B[0]=0;
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

void RunPens()
{
	Decay(VRAM_B_OFFS_0K,192);
//	Decay(VRAM_B_OFFS_0K);

	for(int i=0;i<10;i++)
	{
		DrawLineWithClip(VRAM_B_OFFS_0K,
		Random()%256,Random()%192,Random()%256,Random()%192,
		(Random()%12)*16+15+16,false);
	}

}

void ClearPenData(PenFrame *frames,int numframes)
{
}

void LoadPenData(PenFrame *frames,int numframes,const char *filename)
{
}

void SavePenData(PenFrame *frames,int numframes,const char *filename)
{
}
