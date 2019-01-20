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
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* The Flextimer instance/channel used for board */
#define BOARD_TPM0_BASEADDR TPM0
#define BOARD_TPM2_BASEADDR TPM2
#define BOARD_FIRST_TPM_CHANNEL 0U
#define BOARD_SECOND_TPM_CHANNEL 1U

/* Get source clock for TPM driver */
#define TPM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_PllFllSelClk)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint8_t updatedDutycycle = 10U;

/*******************************************************************************
 * Code
 ******************************************************************************/
void delay(void)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10000; j++);
	}
}

/*!
 * @brief Main function
 */
int main(void)
{
    tpm_config_t tpmInfo;
    tpm_chnl_pwm_signal_param_t tpmParam[2];
    tpm_chnl_pwm_signal_param_t tpmParamBlue[2];

    /* Configure tpm params with frequency 24kHZ */
    tpmParam[0].chnlNumber = (tpm_chnl_t)BOARD_FIRST_TPM_CHANNEL;
    tpmParam[0].level = kTPM_LowTrue;
    tpmParam[0].dutyCyclePercent = updatedDutycycle;

    tpmParam[1].chnlNumber = (tpm_chnl_t)BOARD_SECOND_TPM_CHANNEL;
    tpmParam[1].level = kTPM_LowTrue;
    tpmParam[1].dutyCyclePercent = updatedDutycycle;

    tpmParamBlue[0].chnlNumber = (tpm_chnl_t)BOARD_SECOND_TPM_CHANNEL;
	tpmParamBlue[0].level = kTPM_LowTrue;
	tpmParamBlue[0].dutyCyclePercent = updatedDutycycle;


    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    /* Select the clock source for the TPM counter as kCLOCK_PllFllSelClk */
    CLOCK_SetTpmClock(1U);

    /* Initialize TPM modules */
    TPM_GetDefaultConfig(&tpmInfo);
    TPM_Init(BOARD_TPM2_BASEADDR, &tpmInfo);
    TPM_Init(BOARD_TPM0_BASEADDR, &tpmInfo);

    TPM_SetupPwm(BOARD_TPM2_BASEADDR, tpmParam, 2U, kTPM_EdgeAlignedPwm, 24000U, TPM_SOURCE_CLOCK);
    TPM_StartTimer(BOARD_TPM2_BASEADDR, kTPM_SystemClock);

    TPM_SetupPwm(BOARD_TPM0_BASEADDR, tpmParamBlue, 2U, kTPM_EdgeAlignedPwm, 24000U, TPM_SOURCE_CLOCK);
    TPM_StartTimer(BOARD_TPM0_BASEADDR, kTPM_SystemClock);

    int counter;

    while (1)
    {
        PRINTF("g\r\n");
        counter = 0;
    	while (counter++ < 100)
    	{
            TPM_UpdatePwmDutycycle(BOARD_TPM2_BASEADDR, (tpm_chnl_t)BOARD_FIRST_TPM_CHANNEL, kTPM_EdgeAlignedPwm, 0);
            TPM_UpdatePwmDutycycle(BOARD_TPM2_BASEADDR, (tpm_chnl_t)BOARD_SECOND_TPM_CHANNEL, kTPM_EdgeAlignedPwm, 100);
            TPM_UpdatePwmDutycycle(BOARD_TPM0_BASEADDR, (tpm_chnl_t)BOARD_SECOND_TPM_CHANNEL, kTPM_EdgeAlignedPwm, 0);
    		delay();
    	}

    	PRINTF("r\r\n");
    	counter = 0;
    	while (counter++ < 100)
    	{
            TPM_UpdatePwmDutycycle(BOARD_TPM2_BASEADDR, (tpm_chnl_t)BOARD_FIRST_TPM_CHANNEL, kTPM_EdgeAlignedPwm, 100);
            TPM_UpdatePwmDutycycle(BOARD_TPM2_BASEADDR, (tpm_chnl_t)BOARD_SECOND_TPM_CHANNEL, kTPM_EdgeAlignedPwm, 0);
            TPM_UpdatePwmDutycycle(BOARD_TPM0_BASEADDR, (tpm_chnl_t)BOARD_SECOND_TPM_CHANNEL, kTPM_EdgeAlignedPwm, 0);
    		delay();
    	}

    	PRINTF("b\r\n");
    	counter = 0;
    	while (counter++ < 100)
    	{
            TPM_UpdatePwmDutycycle(BOARD_TPM2_BASEADDR, (tpm_chnl_t)BOARD_FIRST_TPM_CHANNEL, kTPM_EdgeAlignedPwm, 0);
            TPM_UpdatePwmDutycycle(BOARD_TPM2_BASEADDR, (tpm_chnl_t)BOARD_SECOND_TPM_CHANNEL, kTPM_EdgeAlignedPwm, 0);
            TPM_UpdatePwmDutycycle(BOARD_TPM0_BASEADDR, (tpm_chnl_t)BOARD_SECOND_TPM_CHANNEL, kTPM_EdgeAlignedPwm, 100);
    		delay();
    	}
    }
}
