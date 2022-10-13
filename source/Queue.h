#if !defined _QUEUE_H
#define _QUEUE_H
/*******************************************************************************
 * Type Difination
 ******************************************************************************/
struct Queue
{
    uint8_t push;  /* Indicate line position being push */
    uint8_t index; /* Indicate the position of the second dimension of array */
    uint8_t pop;   /* Only line position being processed */
    uint8_t level; /* Unprocessed line count */
};
typedef struct Queue Queue;
/*******************************************************************************
 * API
 ******************************************************************************/
/**
 * @brief           Initialize Queue
 *
 * @param[in]       Q: Queue
 * @param[out]      None
 * @param[inout]    None
 * @returns         None
 */
extern void InitQueue(Queue *Q);

/**
 * @brief           Check Queue is empty or not
 *
 * @param[in]       Q: Queue
 * @param[out]      None
 * @param[inout]    None
 * @returns         true if Queue empty, false if not
 */
extern bool IsEmpty(Queue Q);

/**
 * @brief           Check Queue is Full or not
 *
 * @param[in]       Q: Queue
 * @param[out]      None
 * @param[inout]    None
 * @returns         true if Queue full, false if not
 */
extern bool IsFull(Queue Q);

/**
 * @brief           Push an element to the Queue
 *
 * @param[in]       Q: Queue
 * @param[in]       temp:
 * @param[out]      None
 * @param[inout]    None
 * @returns         true if right, false if not
 */
extern void Push(Queue *Q, int8_t temp);

/**
 * @brief           Return String to process
 *
 * @param[in]       Q: Queue
 * @param[out]      None
 * @param[inout]    None
 * @returns         string to process
 */
extern int8_t *Pop(Queue Q);
#endif /* _QUEUE_H_ */
/*******************************************************************************
 * End of file
 ******************************************************************************/
