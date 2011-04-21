#ifndef __PENS_H__
#define __PENS_H__

#include <stdint.h>

#define MaxPens 4

typedef struct PenFrame
{
	struct { uint8_t x,y; } coords[MaxPens];
} PenFrame;

void InitPensOnSecondaryScreen();

void RunPens(PenFrame *frames,int numframes,int frame);

void ClearPenData(PenFrame *frames,int numframes);
void LoadPenData(PenFrame *frames,int numframes,const char *filename);
void SavePenData(PenFrame *frames,int numframes,const char *filename);

#endif
