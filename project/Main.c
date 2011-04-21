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
	
	#ifdef DEBUG
	//consoleDemoInit();
	//iprintf( "Debug mode.\n" );
	#endif

	t = 0;

	// Main loop
	InitPensOnSecondaryScreen(true);
	InitTruchet(t);
	//effect5_init();

	ClearPenData(pens,60*60*3);

	while( 1 ) {
		//Truchet();
		RunPens(pens,60*60*3,t);
		Truchet(t);
		//effect5_update(t);
		
 		swiWaitForVBlank();
	}
	
	return 0;
}

static void vblank() { t++; }


