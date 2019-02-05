/*
 * ws2812b.c
 * Controller for the WS2812B - Intelligent control LED integrated light source
 * https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf
 * Author: Fabio Crestani
 */

// Force loop unrolling to improve speed
#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_tpm.h"
#include "pin_mux.h"

#include "ws2812b.h"
#include "leds.h"

// addr of gpiob
#define BIT_ZERO __asm("ldr r0,=0x400ff040");\
				 __asm("ldr r1,=0x00000001");\
				 __asm("str r1,[r0]");\
				 __asm("ldr r1,=0x00000000");\
				 __asm("str r1,[r0]");\
				 __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");\
				 __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");\
				 __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");\
				 __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");\
				 __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");\
				 __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop")

#define BIT_ONE GPIO_SetPinsOutput(BOARD_INITPINS_DATA_OUTPUT_GPIO, 1U);\
				__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");\
				__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");\
				__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop");\
				GPIO_ClearPinsOutput(BOARD_INITPINS_DATA_OUTPUT_GPIO, 1U);\
				__asm("nop"); __asm("nop"); __asm("nop"); __asm("nop"); __asm("nop")

const uint32_t NUMBER_OF_LEDS = 8;

void reset(void);

void ws2812b_init(void)
{
	PRINTF("ws2812b_init\n");
}

void ws2812b_next_state(void)
{
	uint8_t current_state = leds_get_state();

	if (current_state == STATE_RED)
	{
		ws2812b_set_leds_red();
		return;
	}

	if (current_state == STATE_GREEN)
	{
		ws2812b_set_leds_green();
		return;
	}

	if (current_state == STATE_BLUE)
	{
		ws2812b_set_leds_blue();
		return;
	}
}

void reset(void)
{
	int i;
	GPIO_ClearPinsOutput(BOARD_INITPINS_DATA_OUTPUT_GPIO, 1U);
	for (i = 0; i < 50; i++)
	{
		__asm("nop");
	}
	GPIO_SetPinsOutput(BOARD_INITPINS_DATA_OUTPUT_GPIO, 1U);
}

void ws2812b_set_leds_green(void)
{
	uint32_t i, j;

	for (j = 0; j < NUMBER_OF_LEDS; j++)
	{
		for (i = 0; i < 8; i++)
		{
			BIT_ONE;
		}

		for (i = 0; i < 8; i++)
		{
			BIT_ZERO;
		}

		for (i = 0; i < 8; i++)
		{
			BIT_ZERO;
		}

		reset();
	}
}

void ws2812b_set_leds_red(void)
{
	uint32_t i, j;

	for (j = 0; j < NUMBER_OF_LEDS; j++)
	{
		for (i = 0; i < 8; i++)
		{
			BIT_ZERO;
		}

		for (i = 0; i < 8; i++)
		{
			BIT_ONE;
		}

		for (i = 0; i < 8; i++)
		{
			BIT_ZERO;
		}

		reset();
	}
}

void ws2812b_set_leds_blue(void)
{
	uint32_t i, j;

	for (j = 0; j < NUMBER_OF_LEDS; j++)
	{
		for (i = 0; i < 8; i++)
		{
			BIT_ZERO;
		}

		for (i = 0; i < 8; i++)
		{
			BIT_ZERO;
		}

		for (i = 0; i < 8; i++)
		{
			BIT_ONE;
		}

		reset();
	}
}

#pragma GCC pop_options
