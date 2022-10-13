/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "Queue.h"
/*******************************************************************************
 * Variable
 ******************************************************************************/
extern int8_t queue_array[4][80];
/*******************************************************************************
 * Functions
 ******************************************************************************/
void InitQueue(Queue *Q)
{
    Q->push = 0;
    Q->index = 0;
    Q->pop = 0;
    Q->level = 0;
}
bool IsEmpty(Queue Q)
{
    bool checkEmpty = false;
    if (Q.level == 0)
    {
        checkEmpty = true;
    }
    return checkEmpty;
}
bool IsFull(Queue Q)
{
    bool checkFull = false;
    if (Q.level > 4)
    {
        checkFull = true;
    }
    return checkFull;
}
void Push(Queue *Q, int8_t temp)
{
    queue_array[Q->push][Q->index] = temp;
    Q->index++;
    if (temp == '\n')
    {
        Q->index = 0;
        if (Q->push == 3)
        {
            Q->push = 0; /* Come back line 0 */
        }
        else
        {
            Q->push++;
        }
        Q->level++;
    }
}
int8_t *Pop(Queue Q)
{
    return queue_array[Q.pop];
}
/*******************************************************************************
 * End of file
 ******************************************************************************/