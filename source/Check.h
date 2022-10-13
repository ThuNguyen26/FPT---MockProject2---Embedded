#if !defined _CHECK_H
#define _CHECK_H
/*******************************************************************************
 * API
 ******************************************************************************/
/**
 * @brief           Is the character 'S' or not
 *
 * @param[in]       buffer: array of data
 * @param[out]      None
 * @param[inout]    None
 * @returns         true if right, false if not
 */
extern bool checkS(int8_t *buffer);

/**
 * @brief           buffer[1] is the S Type or not
 *
 * @param[in]       buffer: array of data
 * @param[out]      None
 * @param[inout]    None
 * @returns         true if exist, false if not
 */
extern bool checkType(int8_t *buffer);

/**
 * @brief           Is there a non-hexa character starting from buffer[2]
 *                  in the data.
 * @param[in]       buffer: array of data
 * @param[out]      None
 * @param[inout]    None
 * @returns         true if right, false if not
 */
extern bool checkHexa(int8_t *buffer);

/**
 * @brief           Check Byte count is byte address + byte data + byte sum
 *                  or not
 * @param[in]       buffer: array of data
 * @param[out]      None
 * @param[inout]    None
 * @returns         true if right, false if not
 */
extern bool checkByCount(int8_t *buffer);

/**
 * @brief           Data has failed hay do not.
 *
 * @param[in]       buffer: array of data
 * @param[out]      None
 * @param[inout]    None
 * @returns         true if right, false if not
 */
extern bool checkSum(int8_t *buffer);

/**
 * @brief           Check S, Type, Hexa, Byte count, Sum is error or not
 *
 * @param[in]       buffer: array of data
 * @param[out]      None
 * @param[inout]    None
 * @returns         true if right, false if not
 */
extern bool checkERROR(int8_t *buffer);
#endif /* _CHECK_H_ */
/*******************************************************************************
 * End of file
 ******************************************************************************/