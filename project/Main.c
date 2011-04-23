/**
 * JBDS main entry point
 */

#include <nds/ndstypes.h>
#include <nds/interrupts.h>

// Utilities to make development easier
#include "Utils.h"

// NitroFS access
#include "nitrofs.h"

// Effects!
#include "effects.h"
#include "Truchet.h"
#include "Pens.h"

// Sound!
#include <maxmod9.h>
#include "music.h"

volatile uint32_t t;
static void vblank();

static PenFrame pens[60*60*3];
extern int tempImage;

int main()
{
	// Turn on everything.
	POWCNT1 = POWCNT1_ALL_SWAP;
	irqEnable( IRQ_VBLANK );
	irqSet(IRQ_VBLANK,vblank);

	// Init NitroFS for data loading.
	nitroFSInitAdv( BINARY_NAME );

// 	mmInitDefault( "nitro:/zik/music.bin" );
// 	mmLoad( MOD_LIGHTMUSIC3_SHORT );
// 	mmStart( MOD_LIGHTMUSIC3_SHORT, MM_PLAY_ONCE );

	tempImage = malloc(256*256*2);

	#ifdef DEBUG
	//consoleDemoInit();
	//iprintf( "Debug mode.\n" );
	#endif

	t = 0;

	// Main loop
	InitPensOnSecondaryScreen(true);
// 	InitTruchet(t);
	effect6_init();

	if(!LoadPenData(pens,sizeof(pens)/sizeof(*pens),"fat:/rainbows.pen"))
	if(!LoadPenData(pens,sizeof(pens)/sizeof(*pens),"nitro:/rainbows.pen"))
	ClearPenData(pens,sizeof(pens)/sizeof(*pens));

	while( t<60*60 ) {
// 		Truchet();
		RunPens(pens,sizeof(pens)/sizeof(*pens),t);
// 		Truchet(t);
		effect6_update(t);
		
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


