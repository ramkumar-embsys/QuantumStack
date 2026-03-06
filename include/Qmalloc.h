/*!
    \file Qmalloc.h
    \brief This is the header file for the QuantumMalloc project. It contains declarations for memory allocation functions, deallocation functions, and memory management utilities.
    \author ramkumar.ramadoss@sandisk.com
    \version 1.0
    \date 2024-06-10
    \copyright Copyright (C) 2025 ramkumar.embsys@gmail.com
*/
#pragma once
#include <stdint.h>
#include <stdio.h>


/*!< Size of the quantum memory pool */
#define QUANTUM_MEMORY_SIZE 32

/*!< Data block for the quantum memory allocator - each of size 32 bytes */
typedef struct Qmblock_u
{
	/*!< Data block for the quantum memory allocator */
    uint8_t QmData[QUANTUM_MEMORY_SIZE];
    /*!< Pointer to the next block in the linked list */
	struct Qmblock_u *Qmnext;
}QBlock_t,*PQBlock_t;

/*!< Quantum memory pool structure of 32 * 32 bytes*/
typedef struct QmemoryPool_u
{
    /*!< Pointer to the start of the quantum memory pool */
    QBlock_t *QmpoolStart;
    /*!< Pointer to the end of the quantum memory pool */
    QBlock_t   *QmpoolEnd;
    /*!< Total size of the quantum memory pool */
    QBlock_t QuantumMallocPool[QUANTUM_MEMORY_SIZE];
}QMemoryPool_t;


#ifdef QMC_DEBUG_PRINTF
    #define QMC_DEBUG_PRINT(...)    printf(__VA_ARGS__)
#else
    #define QMC_DEBUG_PRINT(...)
#endif

/*!Function definition for initializing the quantum memory pool */
void QMC_InitalizePool(void);
void* QMC_AllocatePoolBlock(uint8_t units); 
int QMC_FreePoolBlock(void *QMCMemptr);