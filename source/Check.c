/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "Check.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
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
bool checkS(int8_t *buffer)
{
    bool check_S = true;

    if (buffer[0] != 'S')
    {
        check_S = false;
    }

    return check_S;
}
bool checkType(int8_t *buffer)
{
    bool check_Type = true;

    if ((buffer[1] < '0') || (buffer[1] > '9'))
    {
        check_Type = false;
    }

    return check_Type;
}
bool checkHexa(int8_t *buffer)
{
    bool checkHexa = true;
    uint8_t index = 2; /* Omit the first two checked characters */
    /* Loop until see 'r' or see any chr other hexa */
    while ((buffer[index] != '\r') && (checkHexa == true))
    {
        if (((buffer[index] < '0') || (buffer[index] > '9')) &&
            ((buffer[index] < 'A') || (buffer[index] > 'F')))
        {
            checkHexa = false;
        }
        index++;
    }

    return checkHexa;
}
bool checkByCount(int8_t *buffer)
{
    bool check_Bytecount = true;
    uint8_t bytecount = 0;
    int8_t hex[2] = {'0', '0'};
    uint8_t length = 0; /* length of buffer */

    while (buffer[length] != '\r')
    {
        length++;
    }
    hex[0] = buffer[2];
    hex[1] = buffer[3];
    bytecount = CONVERT(hex);
    /* Stype + Byte Count = 4 character -> bytecount = (length - 4) / 2 */
    if (bytecount != ((length - 4) / 2))
    {
        check_Bytecount = false;
    }

    return check_Bytecount;
}
bool checkSum(int8_t *buffer)
{
    uint8_t Sum = 0;
    uint32_t Total = 0;
    bool check_Sum = true;
    uint8_t index;
    uint8_t length = 0; /* length of buffer */
    int8_t hex[2] = {'0', '0'};

    while (buffer[length] != '\r')
    {
        length++;
    }
    hex[0] = buffer[length - 2];
    hex[1] = buffer[length - 1];
    Sum = CONVERT(hex);
    /* Loop from index = 2 : length - 2
     * convert every 2 characters to number and add to total */
    for (index = 2; index < length - 2; index = index + 2)
    {
        hex[0] = buffer[index];
        hex[1] = buffer[index + 1];
        Total += CONVERT(hex);
    }
    if ((Sum + (Total & 0x00ff)) != 0xff)
    {
        check_Sum = false;
    }

    return check_Sum;
}
bool checkERROR(int8_t *buffer)
{
    bool check_Error = false;
    bool check_S;
    bool check_Type;
    bool check_Hexa;
    bool check_Bycount;
    bool check_Sum;

    check_S = checkS(buffer);
    check_Type = checkType(buffer);
    check_Hexa = checkHexa(buffer);
    check_Bycount = checkByCount(buffer);
    check_Sum = checkSum(buffer);
    if ((check_S == true) && (check_Type == true) && (check_Hexa == true) &&
        (check_Bycount == true) && (check_Sum == true))
    {
        check_Error = true;
    }

    return check_Error;
}
/*******************************************************************************
 * End of file
 ******************************************************************************/