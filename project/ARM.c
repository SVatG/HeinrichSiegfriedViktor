#include "ARM.h"

#include <math.h>

void ATTR_ITCM Decay(uint16_t *screenbase,int lines)
{
/*	uint32_t *ptr=(uint32_t *)screenbase;

	for(int i=0;i<256*192/4;i++)
	{
		uint32_t val=*ptr;

//		uint32_t mask=val&0x0f0f0f0f;
//		mask|=mask<<1;
//		mask|=mask>>1;
//		mask|=mask<<2;
//		mask|=mask>>2;
//		val-=mask&0x01010101;
//		mask=mask<<4;
//		mask|=0x0f0f0f0f;
//		val&=mask;

		uint32_t mask=val;
		mask|=mask>>1;
		mask|=mask>>2;
		mask&=0x01010101;
		val-=mask;
		mask*=0xff;
		val&=mask;

//		uint32_t newval=val-0x01010101;
//		uint32_t mask=(val^newval)&0x10101010;
//		newval+=mask>>4;
//		val=newval;

		*ptr++=val;
	}
*/

	register uint32_t r0 asm("r0")=(uint32_t)screenbase;
	register uint32_t r1 asm("r1")=lines*256/4/8;
	register uint32_t r2 asm("r2")=0x01010101;

	asm volatile (
	".decayloop:					\n"
/*	"	ldr		r4,[r0]				\n"
	"	orr		r3,r4,r4,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r4,r4,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r4,r4,r3			\n"
	"	str		r4,[r0],#4			\n"*/

	"	ldm		r0,{r4-r11}			\n"

	"	orr		r3,r4,r4,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r4,r4,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r4,r4,r3			\n"

	"	orr		r3,r5,r5,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r5,r5,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r5,r5,r3			\n"

	"	orr		r3,r6,r6,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r6,r6,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r6,r6,r3			\n"

	"	orr		r3,r7,r7,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r7,r7,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r7,r7,r3			\n"

	"	orr		r3,r8,r8,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r8,r8,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r8,r8,r3			\n"

	"	orr		r3,r9,r9,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r9,r9,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r9,r9,r3			\n"

	"	orr		r3,r10,r10,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r10,r10,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r10,r10,r3			\n"

	"	orr		r3,r11,r11,lsr #1		\n"
	"	orr		r3,r3,r3,lsr #2		\n"
	"	and		r3,r3,r2			\n"
	"	sub		r11,r11,r3			\n"
	"	rsb		r3,r3,r3,lsl #8		\n"
	"	and		r11,r11,r3			\n"

	"	stmia	r0!,{r4-r11}		\n"

	"	subs	r1,r1,#1			\n"
	"	bne		.decayloop			\n"
	:
	:"r" (r0),"r" (r1),"r" (r2)
	:"r3","r4","r5","r6","r7","r8","r9","r10","r11"
	);


/*	"	ldmia		r0!,{r5,r6,r7,r8,r9,r10,r11,r12}	\n"

	"	ldr		r4,[r2,r5,lsr #16]	\n"
	"	and		r5,r5,r3			\n"
	"	ldrh	r5,[r2,r5]			\n"
	"	orr		r5,r5,r4,lsl #16	\n"

	"	ldr		r4,[r2,r6,lsr #16]	\n"
	"	and		r6,r6,r3			\n"
	"	ldrh	r6,[r2,r6]			\n"
	"	orr		r6,r6,r4,lsl #16	\n"

	"	ldr		r4,[r2,r7,lsr #16]	\n"
	"	and		r7,r7,r3			\n"
	"	ldrh	r7,[r2,r7]			\n"
	"	orr		r7,r7,r4,lsl #16	\n"

	"	ldr		r4,[r2,r8,lsr #16]	\n"
	"	and		r8,r8,r3			\n"
	"	ldrh	r8,[r2,r8]			\n"
	"	orr		r8,r8,r4,lsl #16	\n"

	"	ldr		r4,[r2,r9,lsr #16]	\n"
	"	and		r9,r9,r3			\n"
	"	ldrh	r9,[r2,r9]			\n"
	"	orr		r9,r9,r4,lsl #16	\n"

	"	ldr		r4,[r2,r10,lsr #16]	\n"
	"	and		r10,r10,r3			\n"
	"	ldrh	r10,[r2,r10]		\n"
	"	orr		r10,r10,r4,lsl #16	\n"

	"	ldr		r4,[r2,r11,lsr #16]	\n"
	"	and		r11,r11,r3			\n"
	"	ldrh	r11,[r2,r11]		\n"
	"	orr		r11,r11,r4,lsl #16	\n"

	"	ldr		r4,[r2,r12,lsr #16]	\n"
	"	and		r12,r12,r3			\n"
	"	ldrh	r12,[r2,r12]		\n"
	"	orr		r12,r12,r4,lsl #16	\n"

	"	stmia	r1!,{r5,r6,r7,r8,r9,r10,r11,r12}		\n"

	"	subs	r14,r14,#1			\n"
	"	bne		.tunnelloop			\n"*/

}
