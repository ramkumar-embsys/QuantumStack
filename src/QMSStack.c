#include "QMSApi.h"

/*!
    \brief This funtion initializes the stack by allocating memory for the stack and setting the top and size of the stack 
    \param [in] QMSStack pointer to the stack database
    \param [out] QMSStack contaning the element in the stack
    \retval 0,1 0 = Stack initialization failed,due to Qmalloc Allocation failure, 1= Stack initialization successful
    \author ramkumar ramadoss
    \date 05-March-2026
*/
uint32_t QMS_InitStack(QMSStack_t *QMSStack)
{
    QMS_DEBUG_PRINT(">>  QMS_InitStack Entry  >>\n"); //Entry debug print
    QMSStack_t *QMSParsePtr = QMSStack;
    QMSParsePtr->QMSStackPtr = NULL;
    //Allocate memory for the stack using Qmalloc,32 bytes for 8 elements of 4 bytes each
    QMSParsePtr->QMSStackPtr = (uint32_t *)QMC_AllocatePoolBlock(1);

    if(QMSParsePtr->QMSStackPtr == NULL)
    {
        QMS_DEBUG_PRINT("Qmalloc Error\n");
        return FALSE;
    }

    QMSParsePtr->QMSStackSize = QUANTUM_MEMORY_SIZE;
    QMSParsePtr->QMSStackTop = -1;//No elements in the stack
    QMS_DEBUG_PRINT("<<  QMS_InitStack Exit  <<\n");//Exit debug print
    return TRUE;
}
/*!
    \brief This funtion checks whether the stack is full or not 
    \param [in] QMSStackPtr pointer to the stack database
    \param [out] NA Logic checks whether stack is full, does not manipulate the stack
    \retval 0,1 0 = Stack is not full, 1= stack is full
    \author ramkumar ramadoss
    \date 05-March-2026
*/
uint32_t QMS_IsStackFull(QMSStack_t *QMSStackPtr)
{
    QMS_DEBUG_PRINT(">>  QMS_IsStackFull Entry  >>\n"); //Entry debug print
    QMSStack_t *QMSParsePtr = QMSStackPtr;

    if(QMSParsePtr->QMSStackTop >= (int32_t) QMSParsePtr->QMSStackSize)
    {
        QMS_DEBUG_PRINT("Error: Stack is Full Exit\n"); //Exit debug print
        return TRUE;
    }
    QMS_DEBUG_PRINT("<<  QMS_IsStackFull Exit  <<\n"); //Exit debug print
    return FALSE;
}
/*!
    \brief This funtion pushes the element in to the stack after confirming the space inside the stack 
    \param [in] QMSStackPtr pointer to the stack database
    \param [in] data element to be pushed in to the stack
    \param [out] QMSStack contaning the element in the stack
    \retval 0,1 0 = Stack is full,element not pushed, Number of elements  = element pushed successfully
    \author ramkumar ramadoss
    \date 05-March-2026
*/
uint32_t QMS_StackPush(QMSStack_t *QMSStackPtr,uint32_t data)
{
    QMS_DEBUG_PRINT(">>  QMS_StackPush Entry  >>\n"); //Entry debug print
    QMSStack_t *QMSParsePtr = QMSStackPtr;
    uint32_t StackTop = QMSParsePtr->QMSStackTop;

    if(QMS_IsStackFull(QMSStackPtr))
    {
        QMS_DEBUG_PRINT("Error: Stack is Full\n");
        return FALSE;
    }
    QMSParsePtr->QMSStackTop++;
    QMSParsePtr->QMSStackPtr[QMSParsePtr->QMSStackTop] = data;    
    QMS_DEBUG_PRINT("<<  QMS_StackPush Exit  <<\n"); //Exit debug print
    return QMSParsePtr->QMSStackTop - StackTop;
}
/*!
    \brief This funtion checks whether the stack is empty or not 
    \param [in] QMSStackPtr pointer to the stack database
    \param [out] NA Logic checks whether stack is full, does not manipulate the stack
    \retval 0,1 0 = Stack is not empty, 1= stack is empty
    \author ramkumar ramadoss
    \date 05-March-2026
*/
uint32_t QMS_IsStackEmpty(QMSStack_t *QMSStackPtr)
{
    
    QMS_DEBUG_PRINT(">>  QMS_IsStackEmpty Entry  >>\n"); //Entry debug print
    QMSStack_t *QMSParsePtr = QMSStackPtr;
    if(QMSParsePtr->QMSStackTop < 0)
    {
        QMS_DEBUG_PRINT("Error: Stack is Empty\n"); //Exit debug print
        return TRUE;
    }
    QMS_DEBUG_PRINT("<<  QMS_IsStackEmpty Exit  <<\n"); //Exit debug print
    return FALSE;
}
/*!
    \brief This funtion pops the element from the stack after confirming the stack is not empty and returns the popped element through pointer argument
    \param [in] QMSStackPtr pointer to the stack database
    \param [in] Returndata pointer to store the popped element
    \param [out] Returndata containing the element in the stack after pop operation
    \retval 0,1 0 = Stack pop failed due to Stack empty, 1= stack pop successful, element returned through pointer argument
    \author ramkumar ramadoss
    \date 05-March-2026
*/
uint32_t QMS_StackPop(QMSStack_t *QMSStackPtr,uint32_t *Returndata)
{
    
    QMS_DEBUG_PRINT(">>  QMS_StackPop Entry  >>\n"); //Entry debug print
    QMSStack_t *QMSParsePtr = QMSStackPtr;
    uint32_t StackTop = QMSParsePtr->QMSStackTop;
    if(QMS_IsStackEmpty(QMSStackPtr))
    {
        QMS_DEBUG_PRINT("Error: Stack is Empty\n");
        return FALSE;
    }
    *Returndata = QMSParsePtr->QMSStackPtr[StackTop];
    QMSParsePtr->QMSStackTop--;
    QMS_DEBUG_PRINT("<<  QMS_StackPop Exit  <<\n"); //Exit debug print
    return TRUE;
}