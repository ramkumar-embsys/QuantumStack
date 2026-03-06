#pragma once

#include "Qmalloc.h"

#define TRUE 1
#define FALSE 0

#ifdef QMS_DEBUG_PRINTF
    #define QMS_DEBUG_PRINT(...)    printf(__VA_ARGS__)
#else
    #define QMS_DEBUG_PRINT(...)
#endif

typedef struct QMSStack_s
{
    /*! Stack Memory Pointer holder */
    uint32_t* QMSStackPtr;
    /*! Stack size holder */
    uint32_t QMSStackSize;
    /*! Stack Top */
    int32_t QMSStackTop;    
}QMSStack_t;

/*! Function Declarations */
uint32_t QMS_StackPop(QMSStack_t *QMSStackPtr,uint32_t *Returndata);
uint32_t QMS_IsStackEmpty(QMSStack_t *QMSStackPtr);
uint32_t QMS_StackPush(QMSStack_t *QMSStackPtr,uint32_t data);
uint32_t QMS_IsStackFull(QMSStack_t *QMSStackPtr);
uint32_t QMS_InitStack(QMSStack_t *QMSStackPtr);