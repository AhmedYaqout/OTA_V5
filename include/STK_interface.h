/*
 *  Author  :   Ahmad Yaqoot
 *  Date    :   25/Aug/2020
 *  Type    :   SysTick Interface File
 *  Version :   V1.0
 */

#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

#define STK_AHB_FREQUENCY       8000000
#define STK_AHB_DIV_8           0x0000
#define STK_AHB                 0x0004
#define STK_INTERRUPT_EN        0x0002
#define STK_INTERRUPT_NOT_EN    0x0000
#define STK_ENABLE              0x0001
#define STK_DISABLE             0x0000

#define STK_CLKSOURCE_LOCATION      2
#define STK_TICKINT_LOCATION        1
#define STK_ENABLE_LOCATION         0
#define STK_COUNTFLAG_LOCATION      16

void STK_voidInit(void);
void STK_voidSetBusyDelayMs(u32 Copy_u32TimeValue);
void STK_voidSetSingleIntervalDelayMs(u32 Copy_u32TimeValue, void (*Copy_pfFunction)(void));
void STK_voidSetPeriodicDelayMs(u32 Copy_u32TimeValue, void (*Copy_pfFunction)(void));
void STK_voidSetBusyDelayUs(u32 Copy_u32TimeValue);
void STK_voidSetSingleIntervalDelayUs(u32 Copy_u32TimeValue, void (*Copy_pfFunction)(void));
void STK_voidSetPeriodicDelayUs(u32 Copy_u32TimeValue, void (*Copy_pfFunction)(void));
void STK_voidStartTimer(void);
void STK_voidStopTimer(void);
u32 STK_u32GetElapsedTime(void);
u32 STK_u32GetRemainingTime(void);

#endif