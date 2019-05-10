#ifndef MsTimer2_h
#define MsTimer2_h

#include <dev/io.h>

#define TIMER_PRESCALER ((Prescaler_Reg*) (IO_TIMER + 0x00))
#define TIMER_INTERRUPT ((InterruptCtrl_Reg*) (IO_TIMER + 0x10))
#define TIMER_A ((Timer_Reg*) (IO_TIMER + 0x40))
#define TIMER_B ((Timer_Reg*) (IO_TIMER + 0x50))

#define IO_TIMER_INTERRUPT (*(volatile uint32_t*)0x80002000)

typedef struct
{
  volatile uint32_t LIMIT;
} Prescaler_Reg;


typedef struct
{
  volatile uint32_t CLEARS_TICKS;
  volatile uint32_t LIMIT;
  volatile uint32_t VALUE;
} Timer_Reg;

typedef struct
{
  volatile uint32_t PENDINGS;
  volatile uint32_t MASKS;
} InterruptCtrl_Reg;


namespace MsTimer2 {
	extern unsigned long msecs;
	extern void (*func)();
	
	void set(unsigned long ms, void (*f)());
	void start();
	void stop();
}

#endif
