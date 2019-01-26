/*
 * timer.h
 * Author: Fabio Crestani
 */

#ifndef __TIMER_H__
#define __TIMER_H__

// Define here the period of this timer in microseconds
#define TPM1_PERIOD_US (250)

extern volatile bool tpm1IsrFlag;
extern volatile uint32_t systick;

void timer_init(void);
void timer_start(void);

void timer_clear_interrupt_flag(void);

#endif // __TIMER_H__
