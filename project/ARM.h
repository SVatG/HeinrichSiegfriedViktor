#ifndef __ARM_H__
#define __ARM_H__

#include "Utils.h"
#include <stdint.h>

//void ClaimWRAM();

void ATTR_ITCM Decay(uint16_t *screenbase,int lines);

#endif
