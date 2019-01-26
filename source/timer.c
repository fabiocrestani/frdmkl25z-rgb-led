/*
 * timer.c
 * Author: Fabio Crestani
 */

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_tpm.h"
#include "pin_mux.h"

#include "timer.h"

#define BOARD_TPM1_BASEADDR TPM1
#define BOARD_TPM1_IRQ_NUM TPM1_IRQn
#define BOARD_TPM1_HANDLER TPM1_IRQHandler

// Get source clock for TPM driver
#define TPM1_SOURCE_CLOCK (CLOCK_GetFreq(kCLOCK_PllFllSelClk))

volatile bool tpm1IsrFlag = false;
volatile uint32_t timer_counter = 0U;
tpm_config_t tpm1Info;

void timer_init(void)
{
	PRINTF("timer_init\n");

	TPM_GetDefaultConfig(&tpm1Info);
	TPM_Init(BOARD_TPM1_BASEADDR, &tpm1Info);
	TPM_SetTimerPeriod(BOARD_TPM1_BASEADDR, USEC_TO_COUNT(TPM1_PERIOD_US, TPM1_SOURCE_CLOCK));
}

void timer_start(void)
{
	PRINTF("timer_start\n");

	TPM_EnableInterrupts(BOARD_TPM1_BASEADDR, kTPM_TimeOverflowInterruptEnable);
	EnableIRQ(BOARD_TPM1_IRQ_NUM);
	TPM_StartTimer(BOARD_TPM1_BASEADDR, kTPM_SystemClock);
}

void BOARD_TPM1_HANDLER(void)
{
	tpm1IsrFlag = true;
	TPM_ClearStatusFlags(BOARD_TPM1_BASEADDR, kTPM_TimeOverflowFlag);
}
