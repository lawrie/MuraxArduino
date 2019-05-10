#include <MsTimer2.h>

unsigned long MsTimer2::msecs;
void (*MsTimer2::func)();

void MsTimer2::set(unsigned long ms, void (*f)()) {

  msecs = (ms == 0 ? 1 : ms);
  func = f;
  
  TIMER_INTERRUPT->MASKS = 0;
  TIMER_PRESCALER->LIMIT = 50000-1; //1 ms rate
  TIMER_INTERRUPT->PENDINGS = 0xF;

  TIMER_A->VALUE = 0;
  TIMER_A->LIMIT = msecs -1; 
  TIMER_A->CLEARS_TICKS = 0x00010002;

  IO_TIMER_INTERRUPT = (uint32_t) f;
}

void MsTimer2::start() {
  TIMER_INTERRUPT->MASKS = 0x1;	
}


void MsTimer2::stop() {
  TIMER_INTERRUPT->MASKS = 0x0;	
}

