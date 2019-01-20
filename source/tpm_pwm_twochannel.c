/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_tpm.h"
#include "pin_mux.h"

#include "leds.h"

// TODO change this to a interruption of a timer
void delay(void)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 2000; j++);
	}
}

int main(void)
{
	leds_init();

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    CLOCK_SetTpmClock(1U); /* Select the clock source for the TPM counter as kCLOCK_PllFllSelClk */

    leds_start();

    int counter;

    while (1)
    {
        PRINTF("g\r\n");
        counter = 0;
    	while (counter < 100)
    	{
    		counter++;
    		leds_set_red(0);
    		leds_set_green(100);
    		leds_set_blue(0);
    		delay();
    	}

    	PRINTF("r\r\n");
    	counter = 0;
    	while (counter < 100)
    	{
    		counter++;
    		leds_set_red(100);
    		leds_set_green(0);
    		leds_set_blue(0);
    		delay();
    	}

    	PRINTF("b\r\n");
    	counter = 0;
    	while (counter < 100)
    	{
    		counter++;
    		leds_set_red(0);
    		leds_set_green(0);
    		leds_set_blue(100);
    		delay();
    	}

        PRINTF("r/b\r\n");
        counter = 0;
    	while (counter < 100)
    	{
    		counter++;
    		leds_set_red(100);
    		leds_set_green(0);
    		leds_set_blue(100);
    		delay();
    	}

        PRINTF("r/b/g\r\n");
        counter = 0;
    	while (counter < 100)
    	{
    		counter++;
    		leds_set_red(100);
    		leds_set_green(100);
    		leds_set_blue(100);
    		delay();
    	}
    }
}
