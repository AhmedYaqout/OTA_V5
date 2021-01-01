/*
 *  Author  :   Ahmad Yaqoot
 *  Date    :   15/Sept/2020
 *  Type    :   STK Private File
 *  Version :   V1.1
 */

#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

typedef struct
{
    volatile u32 CTRL;   /* SysTick control and status register */
    volatile u32 LOAD;  /* SysTick reload value register */
    volatile u32 VAL;   /* SysTick current value register */
    volatile u32 CALIB; /* SysTick current value register */
} STK_t;

#define STK ((volatile STK_t *)0xE000E010)

#define STK_SINGLE_INTERVAL    0
#define STK_PERIOD_INTERVAL    1
#endif