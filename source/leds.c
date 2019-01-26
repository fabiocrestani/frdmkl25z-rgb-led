/*
 * leds.c
 * Author: Fabio Crestani
 */

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_tpm.h"
#include "pin_mux.h"

#include "leds.h"

#define BOARD_TPM0_BASEADDR TPM0
#define BOARD_TPM2_BASEADDR TPM2
#define BOARD_FIRST_TPM_CHANNEL 0U
#define BOARD_SECOND_TPM_CHANNEL 1U

/* Get source clock for TPM driver */
#define TPM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_PllFllSelClk)

tpm_config_t tpmInfo;
tpm_chnl_pwm_signal_param_t tpmParamRedGreen[2];
tpm_chnl_pwm_signal_param_t tpmParamBlue[2];

uint8_t current_state;

void leds_init(void)
{
	PRINTF("leds_init\n");

    /* Configure tpm params with frequency 24kHZ */
    tpmParamRedGreen[0].chnlNumber = (tpm_chnl_t)BOARD_FIRST_TPM_CHANNEL;
    tpmParamRedGreen[0].level = kTPM_LowTrue;
    tpmParamRedGreen[0].dutyCyclePercent = 0;

    tpmParamRedGreen[1].chnlNumber = (tpm_chnl_t)BOARD_SECOND_TPM_CHANNEL;
    tpmParamRedGreen[1].level = kTPM_LowTrue;
    tpmParamRedGreen[1].dutyCyclePercent = 0;

    tpmParamBlue[0].chnlNumber = (tpm_chnl_t)BOARD_SECOND_TPM_CHANNEL;
	tpmParamBlue[0].level = kTPM_LowTrue;
	tpmParamBlue[0].dutyCyclePercent = 0;
}

void leds_start(void)
{
	PRINTF("leds_start\n");

    /* Initialize TPM modules */
    TPM_GetDefaultConfig(&tpmInfo);
    TPM_Init(BOARD_TPM2_BASEADDR, &tpmInfo);
    TPM_Init(BOARD_TPM0_BASEADDR, &tpmInfo);

    TPM_SetupPwm(BOARD_TPM2_BASEADDR, tpmParamRedGreen, 2U, kTPM_EdgeAlignedPwm, 24000U, TPM_SOURCE_CLOCK);
    TPM_StartTimer(BOARD_TPM2_BASEADDR, kTPM_SystemClock);

    TPM_SetupPwm(BOARD_TPM0_BASEADDR, tpmParamBlue, 2U, kTPM_EdgeAlignedPwm, 24000U, TPM_SOURCE_CLOCK);
    TPM_StartTimer(BOARD_TPM0_BASEADDR, kTPM_SystemClock);

    current_state = STATE_RED;
}

uint8_t leds_get_state(void)
{
	return current_state;
}

void leds_next_state(void)
{
	current_state = (current_state + 1) % 3;

	if (current_state == STATE_RED)
	{
		PRINTF("r\r\n");
		leds_set_red(2);
		leds_set_green(0);
		leds_set_blue(0);
		return;
	}

	if (current_state == STATE_GREEN)
	{
		PRINTF("g\r\n");
		leds_set_red(0);
		leds_set_green(2);
		leds_set_blue(0);
		return;
	}

	if (current_state == STATE_BLUE)
	{
		PRINTF("b\r\n");
		leds_set_red(0);
		leds_set_green(0);
		leds_set_blue(2);
		return;
	}
}

void leds_set_red(uint8_t value)
{
	TPM_UpdatePwmDutycycle(BOARD_TPM2_BASEADDR, (tpm_chnl_t)BOARD_FIRST_TPM_CHANNEL, kTPM_EdgeAlignedPwm, value);
}

void leds_set_green(uint8_t value)
{
	TPM_UpdatePwmDutycycle(BOARD_TPM2_BASEADDR, (tpm_chnl_t)BOARD_SECOND_TPM_CHANNEL, kTPM_EdgeAlignedPwm, value);
}

void leds_set_blue(uint8_t value)
{
	TPM_UpdatePwmDutycycle(BOARD_TPM0_BASEADDR, (tpm_chnl_t)BOARD_SECOND_TPM_CHANNEL, kTPM_EdgeAlignedPwm, value);
}
