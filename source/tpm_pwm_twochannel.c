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
#include "ws2812b.h"

int main(void)
{
	// This is the adjusted time to trigger the timer every one second
	uint32_t empirical_adjust = 290;
	uint32_t secondLoop = (2 * 1000 * (1000 / TPM1_PERIOD_US)) + empirical_adjust;

	leds_init();
	timer_init();	// Edit timer.h to set the timer period
	ws2812b_init();

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Select the clock source for the TPM counter as kCLOCK_PllFllSelClk */
    CLOCK_SetTpmClock(1U);

    leds_start();
	timer_start();

    while (1)
    {
    	if (tpm1IsrFlag)
		{
    		timer_counter++;
			tpm1IsrFlag = false;

			// The next block must execute before the next timer trigger
			if (timer_counter >= secondLoop)
			{
				// For measuring the period of the timer
				GPIO_TogglePinsOutput(BOARD_INITPINS_TEST_POINT_TIMER_GPIO, 1U << BOARD_INITPINS_TEST_POINT_TIMER_PIN);

				leds_next_state();
				ws2812b_next_state();
				timer_counter = 0U;
			}
		}
		__WFI();
    }
}
