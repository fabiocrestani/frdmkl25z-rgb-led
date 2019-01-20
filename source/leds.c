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
tpm_chnl_pwm_signal_param_t tpmParam[2];
tpm_chnl_pwm_signal_param_t tpmParamBlue[2];

const char LED_RED = 0;
const char LED_GREEN = 1;
const char LED_BLUE = 2;

void leds_init(void)
{
	PRINTF("leds_init\n");

    /* Configure tpm params with frequency 24kHZ */
    tpmParam[0].chnlNumber = (tpm_chnl_t)BOARD_FIRST_TPM_CHANNEL;
    tpmParam[0].level = kTPM_LowTrue;
    tpmParam[0].dutyCyclePercent = 0;

    tpmParam[1].chnlNumber = (tpm_chnl_t)BOARD_SECOND_TPM_CHANNEL;
    tpmParam[1].level = kTPM_LowTrue;
    tpmParam[1].dutyCyclePercent = 0;

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

    TPM_SetupPwm(BOARD_TPM2_BASEADDR, tpmParam, 2U, kTPM_EdgeAlignedPwm, 24000U, TPM_SOURCE_CLOCK);
    TPM_StartTimer(BOARD_TPM2_BASEADDR, kTPM_SystemClock);

    TPM_SetupPwm(BOARD_TPM0_BASEADDR, tpmParamBlue, 2U, kTPM_EdgeAlignedPwm, 24000U, TPM_SOURCE_CLOCK);
    TPM_StartTimer(BOARD_TPM0_BASEADDR, kTPM_SystemClock);
}

void leds_set_red(int value)
{
	TPM_UpdatePwmDutycycle(BOARD_TPM2_BASEADDR, (tpm_chnl_t)BOARD_FIRST_TPM_CHANNEL, kTPM_EdgeAlignedPwm, value);
}

void leds_set_green(int value)
{
	TPM_UpdatePwmDutycycle(BOARD_TPM2_BASEADDR, (tpm_chnl_t)BOARD_SECOND_TPM_CHANNEL, kTPM_EdgeAlignedPwm, value);
}

void leds_set_blue(int value)
{
	TPM_UpdatePwmDutycycle(BOARD_TPM0_BASEADDR, (tpm_chnl_t)BOARD_SECOND_TPM_CHANNEL, kTPM_EdgeAlignedPwm, value);
}
