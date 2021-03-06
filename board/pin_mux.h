/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define SOPT4_TPM1CH0SRC_TPM1_CH0 0x00u /*!<@brief TPM1 channel 0 input capture source select: TPM1_CH0 signal */
#define SOPT4_TPM2CH0SRC_TPM2_CH0 0x00u /*!<@brief TPM2 channel 0 input capture source select: TPM2_CH0 signal */
#define SOPT5_UART0RXSRC_UART_RX 0x00u  /*!<@brief UART0 receive data source select: UART0_RX pin */
#define SOPT5_UART0TXSRC_UART_TX 0x00u  /*!<@brief UART0 transmit data source select: UART0_TX pin */

/*! @name PORTA2 (number 28), J1[4]/D1/UART0_TX
  @{ */
#define BOARD_INITPINS_DEBUG_UART_TX_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_DEBUG_UART_TX_PIN 2U     /*!<@brief PORTA pin index: 2 */
                                                /* @} */

/*! @name PORTA1 (number 27), J1[2]/D0/UART0_RX
  @{ */
#define BOARD_INITPINS_DEBUG_UART_RX_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_DEBUG_UART_RX_PIN 1U     /*!<@brief PORTA pin index: 1 */
                                                /* @} */

/*! @name PORTB19 (number 54), D3[4]/LEDRGB_GREEN
  @{ */
#define BOARD_INITPINS_LED_GREEN_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_LED_GREEN_PIN 19U    /*!<@brief PORTB pin index: 19 */
                                            /* @} */

/*! @name PORTB18 (number 53), D3[1]/LEDRGB_RED
  @{ */
#define BOARD_INITPINS_LED_RED_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_LED_RED_PIN 18U    /*!<@brief PORTB pin index: 18 */
                                          /* @} */

/*! @name PORTD1 (number 74), J2[12]/D3[3]/D13/LEDRGB_BLUE
  @{ */
#define BOARD_INITPINS_LED_BLUE_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_LED_BLUE_PIN 1U     /*!<@brief PORTD pin index: 1 */
                                           /* @} */

/*! @name PORTC1 (number 56), J10[12]/U6[31]/A5
  @{ */
#define BOARD_INITPINS_TEST_POINT_TIMER_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_INITPINS_TEST_POINT_TIMER_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_INITPINS_TEST_POINT_TIMER_PIN 1U     /*!<@brief PORTC pin index: 1 */
                                                   /* @} */

/*! @name PORTB0 (number 43), J10[2]/A0
  @{ */
#define BOARD_INITPINS_DATA_OUTPUT_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_INITPINS_DATA_OUTPUT_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_DATA_OUTPUT_PIN 0U     /*!<@brief PORTB pin index: 0 */
                                              /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
