#if !defined _PARSE_DATA_H
#define _PARSE_DATA_H
/*******************************************************************************
 * API
 ******************************************************************************/
/**
 * @brief           Return Address of line
 *
 * @param[in]       buffer: data or array
 * @param[out]      None
 * @param[inout]    None
 * @returns         Address
 */
extern uint32_t GetAddress(int8_t *buffer);
/**
 * @brief           Return array 16 element data 8 bit
 *
 * @param[in]       Q: Queue
 * @param[out]      None
 * @param[inout]    None
 * @returns         array data
 */
extern uint8_t *GetData(int8_t *buffer);
#endif /* _PARSE_DATA_H_ */
/*******************************************************************************
 * End of file
******************************************************************************/