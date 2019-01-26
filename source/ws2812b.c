/*
 * ws2812b.c
 * Controller for the WS2812B - Intelligent control LED integrated light source
 * https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf
 * Author: Fabio Crestani
 */

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_tpm.h"
#include "pin_mux.h"

#include "ws2812b.h"
#include "leds.h"

const uint32_t NUMBER_OF_LEDS = 8;

#define HIGH (1)
#define LOW (0)

// Bit timings
#define T1H (800)
#define T1L (450)
#define T0H (400)
#define T0L (850)
#define RES (100 * 1000)

void bit0(void);
void bit1(void);
void reset(void);
static inline void wait_ns(uint32_t time);
static inline void set_pin(uint8_t value);

void ws2812b_init(void)
{
	PRINTF("ws2812b_init\n");

}

void ws2812b_next_state(void)
{
	uint8_t current_state = leds_get_state();

	if (current_state == STATE_RED)
	{
		ws2812b_set_red(255);
		ws2812b_set_green(0);
		ws2812b_set_blue(0);
		return;
	}

	if (current_state == STATE_GREEN)
	{
		ws2812b_set_red(0);
		ws2812b_set_green(255);
		ws2812b_set_blue(0);
		return;
	}

	if (current_state == STATE_BLUE)
	{
		ws2812b_set_red(0);
		ws2812b_set_green(0);
		ws2812b_set_blue(255);
		return;
	}
}

void ws2812b_set_red(uint8_t value)
{
	ws2812b_set(value, 0, 0);
}

void ws2812b_set_green(uint8_t value)
{
	ws2812b_set(0, value, 0);
}

void ws2812b_set_blue(uint8_t value)
{
	ws2812b_set(0, 0, value);
}


/*
 * ws2812b_set(uint8_t green, uint8_t red, uint8_t blue)
 *
 * Data transfer time (TH + TL = 1.25µs ± 600ns)
 * T0H	0 code, high voltage time 	0.4us 		±150ns
 * T1H	1 code, high voltage time 	0.8us 		±150ns
 * T0L	0 code, low voltage time 	0.85us 		±150ns
 * T1L	1 code, low voltage time 	0.45us 		±150ns
 * RES	low voltage time 			Above 50µs
 *
 * Composition of 24bit data:
 * G7 G6 G5 G4 G3 G2 G1 G0 R7 R6 R5 R4 R3 R2 R1 R0 B7 B6 B5 B4 B3 B2 B1 B0
 *
 */
void ws2812b_set(uint8_t green, uint8_t red, uint8_t blue)
{
	reset();
	// TODO send color data
}

// 0 code = T0H + T0L
void bit0(void)
{
	set_pin(HIGH);
	wait_ns(T0H);
	set_pin(LOW);
	wait_ns(T0L);
}

// 1 code = T1H + T1L
void bit1(void)
{
	set_pin(HIGH);
	wait_ns(T1H);
	set_pin(LOW);
	wait_ns(T1L);
}

void reset(void)
{
	set_pin(LOW);
	wait_ns(RES);
	set_pin(HIGH);
}

inline void wait_ns(uint32_t time)
{
	// TODO convert 'time' to match the real time
	uint32_t counter;
	while (counter++ < time)
	{
		__asm("nop");
	}
}

inline void set_pin(uint8_t value)
{
	// TODO
}
