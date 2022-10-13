/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <MKL46Z4.h>
#include <stdint.h>
#include <stdbool.h>
#include "Uart.h"
#include "Queue.h"
#include "Check.h"
#include "ParseData.h"
#include "Flash.h"
/*******************************************************************************
 * Variable
 ******************************************************************************/
int8_t queue_array[4][80];
Queue q;
/*******************************************************************************
 * Codes
 ******************************************************************************/
int main()
{
    init_uart();
    InitQueue(&q);
    uint8_t index;
    int8_t ok = 0;
    Erase_Multi_Sector(0xA000, 215);
    while (1)
    {
        while (!IsEmpty(q))
        {
            if (checkERROR(queue_array[q.pop]) == true)
            {
                if (queue_array[q.pop][1] == '1')
                {
                    for (index = 0; index < 16; index = index + 4)
                    {
                        /* Disable interrupts before writing data to Flash Rom */
                        __disable_irq();
                        Program_LongWord_8B(GetAddress(queue_array[q.pop]) + index,
                                            &GetData(queue_array[q.pop])[index]);
                        /* Re-enable interrupts after writing data to Flash Rom */
                        __enable_irq();
                    }
                }
                else if (queue_array[q.pop][1] == '9')
                {
                    ok = 1; /* Program test break point */
                }
            }
            else
            {
                send_message("Data error!\r\n");
                send_message("Please send file again!\r\n");
                return 0;
            }
            if (q.pop == 3)
            {
                q.pop = 0; /* Come back line 0 */
            }
            else
            {
                (q.pop)++;
            }
            (q.level)--;
        }
    }
}
/* Interrupt handler function */
void UART0_IRQHandler(void)
{
    int8_t temp;
    temp = UART0->D;
    if (temp != '\0')
    {
        Push(&q, temp);
    }
}
/*******************************************************************************
 * End of file
 ******************************************************************************/