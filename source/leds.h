/*
 * leds.h
 * Author: Fabio Crestani
 */

#ifndef __LEDS_H__
#define __LEDS_H__

#define STATE_RED (0)
#define STATE_GREEN (1)
#define STATE_BLUE (2)

void leds_init(void);
void leds_start(void);
uint8_t leds_get_state(void);
void leds_next_state(void);

void leds_set_red(uint8_t value);
void leds_set_green(uint8_t value);
void leds_set_blue(uint8_t value);

#endif // __LEDS_H__
