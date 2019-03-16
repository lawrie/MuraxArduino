#ifndef MsTimer2_h
#define MsTimer2_h

#define TIMER_PRESCALER ((Prescaler_Reg*)0xF0020000)
#define TIMER_INTERRUPT ((InterruptCtrl_Reg*)0xF0020010)
#define TIMER_A ((Timer_Reg*)0xF0020040)
#define TIMER_B ((Timer_Reg*)0xF0020050)

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
