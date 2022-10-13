/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "ParseData.h"
/*******************************************************************************
 * Difinitions
 ******************************************************************************/
/* Max element for data array 1 byte */
#define MAX_ARRAY_DATA 16
/* Convert character '0' - '9' -> decimal 0 - 9 */
#define H1(x) (x - ('0'))
/* Convert character 'A' - 'F' -> decimal 10 - 15 */
#define H2(x) (x - ('A') + 10)
/* Convert 2 chr hexa to decimal */
#define CONVERT(Arr)                                                           \
    ((((Arr[0]) >= '0') & ((Arr[0]) <= '9') ? H1(Arr[0]) : H2(Arr[0])) << 4) | \
        (((Arr[1]) >= 'A') & ((Arr[1]) <= 'F') ? H2(Arr[1]) : H1(Arr[1]))
/*******************************************************************************
 * Functions
 ******************************************************************************/
uint32_t GetAddress(int8_t *buffer)
{
    /* buffer[1] = '1' -> 2 byte
     * buffer[1] = '2' -> 3 byte
     * buffer[1] = '3' -> 4 byte */
    uint8_t byte = H1(buffer[1]) + 1;
    uint32_t address = 0;
    int8_t hex[2] = {'0', '0'};
    uint8_t index;
    /* 1 byte -> address = buffer[4: 8]
     * 2 byte -> address = buffer[4: 10]
     * 3 byte -> address = buffer[4: 12]
     * -> address = buffer[4: 4 + 2 * byte] */
    for (index = 4; index < 4 + 2 * byte; index++)
    {
        hex[0] = buffer[index];
        hex[1] = buffer[++index];
        address |= CONVERT(hex);
        if (index != (2 * byte + 3))
        {
            address = address << 8;
        }
    }
    return address;
}
uint8_t *GetData(int8_t *buffer)
{
    static uint8_t data[MAX_ARRAY_DATA]; /* Array data */
    int8_t hex[2] = {'0', '0'};
    uint8_t index_data;
    uint8_t index_buffer;
    uint8_t length = 0; /* Length of buffer */
    while (buffer[length] != '\r')
    {
        length++;
    }
    for (index_data = 0; index_data < MAX_ARRAY_DATA; index_data++)
    {
        data[index_data] = 0xff;
    }
    for (index_data = 0, index_buffer = 8; index_data < 16,
        index_buffer < length - 2;
         index_data++, index_buffer++)
    {
        hex[0] = buffer[index_buffer];
        hex[1] = buffer[++index_buffer];
        data[index_data] = CONVERT(hex);
    }
    return data;
}
/*******************************************************************************
 * End of file
 ******************************************************************************/