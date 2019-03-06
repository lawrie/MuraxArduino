#include <Arduino.h>
#include <dev/io.h>
#include "wiring_private.h"

__BEGIN_DECLS

#ifdef __riscv
/* F32C RISC-V is early and currently doesn't have interrupts
** when implemented, #ifdef __riscv
** can be used for code than needs to be specifically compiled
** for riscv architecture
*/
#warning "RISC-V doesn't have interrupts yet. Choose Tools->CPU Architecture->MIPS"
#endif // __riscv

__END_DECLS
