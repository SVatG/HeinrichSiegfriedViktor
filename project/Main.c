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
//#include "effects.h"
#include "Truchet.h"

// Sound!
#include <maxmod9.h>
#include "music.h"

int main()
{
	// Turn on everything.
	POWCNT1 = POWCNT1_ALL;
	irqEnable( IRQ_VBLANK );
	
	// Init NitroFS for data loading.
	nitroFSInitAdv( BINARY_NAME );

// 	mmInitDefault( "nitro:/zik/music.bin" );
// 	mmLoad( MOD_LIGHTMUSIC3_SHORT );
// 	mmStart( MOD_LIGHTMUSIC3_SHORT, MM_PLAY_ONCE );
	
	#ifdef DEBUG
	consoleDemoInit();
	iprintf( "Debug mode.\n" );
	#endif

	// Main loop
	InitTruchet();

	while( 1 ) {
		Truchet();
		
		// 60fps, or less if in DOUBLETHREEDEE MODE, or doing fancy
		// things like that, the effect in question should know.
 		swiWaitForVBlank();
	}
	
	return 0;
}
