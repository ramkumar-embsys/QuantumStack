#include "QMSApi.h"

int main()
{
    QMSStack_t QMSStack;
    uint32_t QMSOpResult = 0;
    uint32_t StackData = 0;
    QMC_InitalizePool(); //Initialize the Qmalloc list pool


    QMSOpResult = QMS_InitStack(&QMSStack);


    if(FALSE == QMSOpResult)
    {
        printf("Stack Init Error\n");
    }


    QMSOpResult = QMS_StackPush(&QMSStack,12);

    if(FALSE == QMSOpResult)
    {
        printf("Stack Push Error\n");
    }
    QMSOpResult = QMS_StackPop(&QMSStack,&StackData);
    printf("Popped Data = %d\n",StackData);
    QMSOpResult = QMS_StackPop(&QMSStack,&StackData);
    if(FALSE == QMSOpResult)
    {
        printf("Stack Pop Error\n");
    }

}