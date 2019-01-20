/*
 * leds.h
 * Author: Fabio Crestani
 */

#ifndef __LEDS_H__
#define __LEDS_H__

void leds_init(void);
void leds_start(void);

void leds_set_red(int value);
void leds_set_green(int value);
void leds_set_blue(int value);

#endif // __LEDS_H__
