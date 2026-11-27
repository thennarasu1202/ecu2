#include<LPC21XX.H>

/* Timer1 runs freely, 1 count = 1 ms.
   CAN2_INIT() sets VPBDIV=1, so PCLK = 60 MHz after it.
   -> call tick_init() AFTER CAN2_INIT(). */
void tick_init(void)
{
	T1PR=60000-1;
	T1TCR=0x01;
}
unsigned int millis(void)
{
	return T1TC;
}
