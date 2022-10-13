/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <MKL46Z4.h>
#include <stdint.h>
#include "Uart.h"
/*******************************************************************************
 * Functions
 ******************************************************************************/
void init_uart()
{
    /* Config clock source for UART0 as 20M */
    SIM->SOPT2 &= ~(1 << 16);
    SIM->SOPT2 |= (1 << 26);
    SIM->SOPT2 &= ~(1 << 27);

    /* Enable clock for uart0 */
    SIM->SCGC4 |= (1 << 10);

    /* Enable clock for port A */
    SIM->SCGC5 |= (1 << 9);

    /* Config uart for pin PTA1, PTA2 */
    PORTA->PCR[1] = PORT_PCR_MUX(2);
    PORTA->PCR[2] = PORT_PCR_MUX(2);

    /* Receiver and transmitter use 8-bit or 9-bit data characters. */
    UART0->C4 &= ~(1 << 5);

    /* Receiver and transmitter use 8-bit data characters */
    UART0->C1 &= ~(1 << 4);

    /* No parity */
    UART0->C1 &= ~(1 << 1);

    /* LSB fisrt */
    UART0->S2 &= ~(1 << 5);

    /* Receive data not inverted */
    UART0->S2 &= ~(1 << 4);

    /* Transmit data not inverted. */
    UART0->C3 &= ~(1 << 4);

    /* Config baudrate UART0 as 9600 */
    UART0->C4 = 22;
    UART0->BDL = 95;

    /* Receiver Enable - Transmitter Enable */
    UART0->C2 |= 3 << 2;

    /* One stop bit */
    UART0->BDH &= ~(1 << 5);

    /* Receiver Interrupt Enable for RDRF */
    UART0->C2 |= 1 << 5;

    NVIC_EnableIRQ(UART0_IRQn);
}
void send_message(int8_t *data)
{
    while (*data != '\n')
    {
        UART0->D = *data;
        while ((UART0->S1 & 0x80) == 0x00)
        {
        }
        data++;
    }
    UART0->D = '\n';
    while ((UART0->S1 & 0x80) == 0x00)
    {
    }
}
/*******************************************************************************
 * End of file
 ******************************************************************************/