/*
 * ws2812b.h
 * Controller for the WS2812B - Intelligent control LED integrated light source
 * https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf
 * Author: Fabio Crestani
 */

#ifndef __WS2812B_H__
#define __WS2812B_H__

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_tpm.h"
#include "pin_mux.h"

void ws2812b_init(void);
void ws2812b_next_state(void);
void ws2812b_set_red(uint8_t value);
void ws2812b_set_green(uint8_t value);
void ws2812b_set_blue(uint8_t value);
void ws2812b_set(uint8_t green, uint8_t red, uint8_t blue);

#endif // __WS2812B_H__
