/*
 * tpm_pwm_twochannel.c
 * Author: Fabio Crestani
 */

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_tpm.h"
#include "pin_mux.h"

#include "leds.h"
#include "timer.h"

int main(void)
{
	leds_init();
	timer_init();	// Edit timer.h to set the timer period

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Select the clock source for the TPM counter as kCLOCK_PllFllSelClk */
    CLOCK_SetTpmClock(1U);

    leds_start();
	timer_start();

    uint32_t secondLoop = 1000 * 4;

    while (1)
    {
    	if (tpm1IsrFlag)
		{
			milisecondCounts++;
			tpm1IsrFlag = false;

			if (milisecondCounts >= secondLoop)
			{
				GPIO_TogglePinsOutput(BOARD_INITPINS_TEST_POINT_TIMER_GPIO, 1U << BOARD_INITPINS_TEST_POINT_TIMER_PIN);
				leds_next_state();
				milisecondCounts = 0U;
			}

		}
		__WFI();
    }
}
