/*!
    \file Qmalloc.c
    \brief This is the main implementation file for the QuantumMalloc project.This file contains memory allocation functions, deallocation functions, and memory management utilities.
    \author ramkumar.embsys@gmail.com
    \version 1.0
    \date 11-Jan-2026
    \copyright Copyright (C) 2025 ramkumar.embsys@gmail.com
*/

#include "Qmalloc.h"

/*!< Global quantum memory pool instance */
QMemoryPool_t QMC_MemoryPool; 

uint8_t QMC_PoolTracker[QUANTUM_MEMORY_SIZE];

/*!
    \brief QMC_InitalizePool - This is the function to initialize the Quantum Malloc memory pool it
    creates a temporary variable and Qmnext pointer points to the next block of pool, each pool is reserved for 32 bytes
    the last block next pointer is set to NULL.
    \param [in] No arguments
    \param [out] global variable QMC_MemoryPool is initialized with proper pointers
    \retval 0 No values
    \author ramkumar ramadoss
    \date 15-Jan-2026
*/

void QMC_InitalizePool(void)
{
    QMC_DEBUG_PRINT(">>  QMC_InitalizePool Entry  >>\n"); //Entry debug print
    QMemoryPool_t *pool = &QMC_MemoryPool;
    pool->QmpoolStart = (PQBlock_t)&(pool->QuantumMallocPool[0]);
    pool->QmpoolEnd = (PQBlock_t)&(pool->QuantumMallocPool[QUANTUM_MEMORY_SIZE - 1]) + QUANTUM_MEMORY_SIZE;

    for(int i = 0; i < QUANTUM_MEMORY_SIZE - 1; i++)
    {
        pool->QuantumMallocPool[i].Qmnext = (PQBlock_t)&(pool->QuantumMallocPool[i + 1]);
    }
    pool->QuantumMallocPool[QUANTUM_MEMORY_SIZE - 1].Qmnext = NULL; // Last block points to NULL
    QMC_DEBUG_PRINT("<<  QMC_InitalizePool Exit  <<\n");//Exit debug print
}

/*!
    \brief QMC_AllocatePoolBlock - This is the function to allocate a block of memory from the quantum memory pool.
    It traverses the linked list of blocks and reserves the requested number of units.
    \param [in] units - Number of units to allocate
    \param [out] global variable QMC_MemoryPool is updated with allocated blocks
    \retval void* - Pointer to the allocated memory block or NULL if allocation fails
    \author ramkumar ramadoss
    \date 17-Jan-2026
*/
void* QMC_AllocatePoolBlock(uint8_t units)
{
    void *QMCReqptr = NULL;
    QMemoryPool_t *pool = &QMC_MemoryPool; //get the global pool pointer
    QMCReqptr = (void*) pool->QmpoolStart; //assign the start of the pool to request pointer
	PQBlock_t QMCHdptr = pool->QmpoolStart; //head pointer to traverse the pool
    
	uint8_t count = 0; 
    QMC_DEBUG_PRINT(">>  QMC_AllocatePoolBlock Entry  >>\n"); //Entry debug print

    //store how many units are allocated in the pool tracker
    QMC_PoolTracker[(( (uintptr_t)(pool->QmpoolStart) & 0xFFu) / QUANTUM_MEMORY_SIZE)] = units;

	if (NULL == QMCReqptr) //if the memory pool is empty there is no free block already ex) allocated till 31 last block, next allocation fails
	{
		QMC_DEBUG_PRINT("QMCD:Memory Pool Empty,No Free Block \n");
        return NULL;
	}

	for (count = units; count > 0 && QMCHdptr != NULL; count--)
	{
		//Reserve the block by incrementing the pool and storing the pointer to next block
        QMCHdptr = QMCHdptr->Qmnext;
	}
	if ((units-count) != units) //check if the requested units are allocated fully
	{
		QMC_DEBUG_PRINT("QMCD:Not enough blocks available in the pool,requested=%d,allocated=%d \n", units, (units-count));
        return NULL; //return NULL if not enough blocks are available
	}	
    QMC_DEBUG_PRINT("<<  QMC_AllocatePoolBlock Exit  <<\n");//Exit debug print
	return QMCReqptr;
}

/*!
    \brief QMC_FreePoolBlock - This is the function to free a previously allocated block of memory back to the quantum memory pool.
    It takes the pointer to the memory and retrieves the number of units allocated from the pool tracker, then links the freed blocks back to the pool.
    \param [in] QMCMemptr - Pointer to the memory block to be freed
    \param [out] global variable QMC_MemoryPool is updated with freed blocks
    \retval 0/-1 - Returns 0 on successful deallocation, -1 on failure
    \author ramkumar ramadoss
    \date 17-Jan-2026
*/
int QMC_FreePoolBlock(void *QMCMemptr)
{
	uint8_t QMCfreeunits = 0;
	uint8_t count = 0;

    if(NULL == QMCMemptr) //check for null pointer
    {
        QMC_DEBUG_PRINT("QMCD:NULL/Invalid Pointer, Deallocation Failed \n");
        return -1;
    }
    QMemoryPool_t *pool = &QMC_MemoryPool; //get the global pool pointer
    PQBlock_t QMCTailptr = pool->QmpoolEnd; //tail pointer to traverse the pool

    //retrieve the number of units allocated from the pool tracker
	QMCfreeunits = QMC_PoolTracker[(( (uintptr_t)(QMCMemptr) & 0xFFu) / QUANTUM_MEMORY_SIZE)];
	
    QMCTailptr->Qmnext = (PQBlock_t)QMCMemptr; //pool end next pointer points to null initially, point it to the freed block

    //Iterate the retrieved number of units to link the freed blocks back to the pool
	for (count = QMCfreeunits; count > 0; count--)
	{
		QMCTailptr = QMCTailptr->Qmnext;
        if(QMCTailptr == NULL)
        {
            QMC_DEBUG_PRINT("QMCD:Deallocation Failed, Invalid Block Pointer,Pool Tracker corruption \n");
            return -1  ; //safety check
        }
	}
	QMCTailptr->Qmnext = NULL; //set the last freed block next pointer to NULL
    pool->QmpoolStart = (PQBlock_t)QMCMemptr; //set the pool start pointer to the freed block

    return 0;
}