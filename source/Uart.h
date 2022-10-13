#if !defined _UART_H
#define _UART_H
/*******************************************************************************
 * API
 ******************************************************************************/
/**
 * @brief           Initialize UART
 *
 * @param[in]       None
 * @param[out]      None
 * @param[inout]    None
 * @returns         None
 */
void init_uart();

/**
 * @brief           Transmit a string to terminal PC
 *
 * @param[in]       data: string or data
 * @param[out]      None
 * @param[inout]    None
 * @returns         None
 */
void send_message(int8_t *data);
#endif /* _UART_H_ */
/*******************************************************************************
 * End of file
 ******************************************************************************/
