/*-
 * Copyright (c) 2013-2015 Marko Zec, University of Zagreb
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id$
 */

#ifndef _IO_H_
#define	_IO_H_

#ifdef __riscv
#include <riscv/io.h>
#endif


#define	IO_BASE		0xF0000000

#define	IO_ADDR(a)	(IO_BASE | (a))

#define	IO_GPIO_DATA	IO_ADDR(0x004)	          /* word, RW */
#define	IO_GPIO_CTL	IO_ADDR(0x008)	          /* word, WR */
#define	IO_GPIO_INPUT	IO_ADDR(0x000)	          /* word, RW */

#define	IO_GPIOB_DATA	IO_ADDR(0x8004)	          /* word, RW */
#define	IO_GPIOB_CTL	IO_ADDR(0x8008)	          /* word, WR */
#define	IO_GPIOB_INPUT	IO_ADDR(0x8000)	          /* word, RW */

#define	IO_PWM_DUTY	IO_ADDR(0x30000)	  /* word , WR */

#define	IO_PULSE_VALUE	IO_ADDR(0x80000)	  /* word , WR */
#define	IO_PULSE_TIMEOUT IO_ADDR(0x80004)	  /* word , WR */
#define	IO_PULSE_LENGTH IO_ADDR(0x80008)	  /* word , RD */

#define	IO_UART 	IO_ADDR(0x10000)	  /* word , RW */
#define	IO_TONE_PERIOD 	IO_ADDR(0x40000)	  /* word , WR */
#define	IO_TONE_DURATION IO_ADDR(0x40004)	  /* word , WR */

#define	IO_SHIFT_OUT_BYTE_VALUE IO_ADDR(0x50000)  /* word , WR */
#define	IO_SHIFT_OUT_BIT_ORDER IO_ADDR(0x50004)	  /* word , WR */
#define	IO_SHIFT_OUT_PRE_SCALE IO_ADDR(0x50008)	  /* word , WR */

#define	IO_SPI IO_ADDR(0x60000)  /* word , WR */

#define	IO_I2C IO_ADDR(0x70000)  /* word , WR */

#define	IO_SHIFT_IN_BIT_ORDER IO_ADDR(0xA0008)	  /* word , WR */
#define	IO_SHIFT_IN_PRE_SCALE IO_ADDR(0xA0004)	  /* word , WR */
#define	IO_SHIFT_IN_BYTE_VALUE IO_ADDR(0xA0000)	  /* word , RD */

#define	IO_MACHINE_TIMER IO_ADDR(0xB0000)	  /* word, RD */

#define	IO_SIO_BYTE	IO_ADDR(0x10000)	  /* word, RW */
#define	IO_SIO_STATUS	IO_ADDR(0x10004)	  /* word, RD */
#define	IO_SIO_BAUD	IO_ADDR(0x10008)	  /* word, WR */

#define IO_MUX IO_ADDR(0xD0000)                   /* word, RW */

#define	IO_ANALOG IO_ADDR(0xF0000)	          /* 6 words, RD */

#define IO_QUADRATURE IO_ADDR(0xF8000)

#define IO_PIN_INTERRUPT_RISING IO_ADDR(0xE0000)  /* word, WR */
#define IO_PIN_INTERRUPT_FALLING IO_ADDR(0xE0004) /* word, WR */
#define IO_PIN_INTERRUPT_PENDING IO_ADDR(0xE0010) /* word. RW */
#define IO_PIN_INTERRUPT_MASKS IO_ADDR(0xE0014)    /* word, RW */

#define IO_TIMER_INTERRUPT_MASKS IO_ADDR(0x20014)  /* word, RW */

#define IO_TIMER_INTERRUPT 0x80002000             /* word, RW */
#define IO_PIN_INTERRUPT 0x80002004               /* word, RW */

/* SIO status bitmask - TODO: get rid of this */
#define	SIO_TX_BUSY	0x4

#endif /* !_IO_H_ */
