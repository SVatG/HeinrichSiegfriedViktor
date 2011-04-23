/**
 * JBDS main entry point
 */

#include <nds/ndstypes.h>
#include <nds/interrupts.h>
#include <string.h>

// Utilities to make development easier
#include "Utils.h"

// NitroFS access
#include "nitrofs.h"

// Effects!
#include "effects.h"
#include "Truchet.h"
#include "Radial.h"
#include "Tunnel.h"
#include "Pens.h"
#include "ARM.h"

// Sound!
#include <maxmod9.h>
#include "music.h"

volatile uint32_t t;
static void vblank();

static PenFrame pens[60*60*3];

uint8_t ATTR_DTCM dtcm_buffer[12288];

int main()
{
	// Turn on everything.
	POWCNT1 = POWCNT1_ALL_SWAP;
	irqEnable( IRQ_VBLANK );
	irqSet(IRQ_VBLANK,vblank);

//	ClaimWRAM();

	// Init NitroFS for data loading.
	nitroFSInitAdv( BINARY_NAME );

// 	mmInitDefault( "nitro:/zik/music.bin" );
// 	mmLoad( MOD_LIGHTMUSIC3_SHORT );
// 	mmStart( MOD_LIGHTMUSIC3_SHORT, MM_PLAY_ONCE );

	#ifdef DEBUG
	//consoleDemoInit();
	//iprintf( "Debug mode.\n" );
	#endif

	t = 0;

	// Main loop
	InitPensOnSecondaryScreen(true);
	//InitTruchet(t);
	//InitRadial();
	InitTunnel();
	//effect5_init();

	uint8_t *wram=(uint8_t *)0x3000000;
//	memset(wram,0,128*96);

	if(!LoadPenData(pens,sizeof(pens)/sizeof(*pens),"fat:/rainbows.pen"))
	if(!LoadPenData(pens,sizeof(pens)/sizeof(*pens),"nitro:/rainbows.pen"))
	ClearPenData(pens,sizeof(pens)/sizeof(*pens));

	while( t<60*60 ) {
		//Truchet();
		RunPens(pens,sizeof(pens)/sizeof(*pens),t);
//		memcpy(dtcm_buffer,wram,128*96);
//		RunRadial(t,dtcm_buffer);
		RunTunnel(t);
		//Truchet(t);
		//effect5_update(t);

 		swiWaitForVBlank();
	}

	// Superstitious save.
	SavePenData(pens,sizeof(pens)/sizeof(*pens),"fat:/rainbows.pen");
	LoadPenData(pens,sizeof(pens)/sizeof(*pens),"fat:/rainbows.pen");

	POWCNT1 = POWCNT1_ALL;

	for(;;);

	return 0;
}

static void vblank() { t++; }


