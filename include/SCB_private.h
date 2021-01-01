/*
 *  Author  :   Ahmad Yaqoot
 *  Date    :   27/Aug/2020
 *  Type    :   System control block Private File
 *  Version :   V1.0
 */

#ifndef SCB_PRIVATE_H
#define SCB_PRIVATE_H

typedef struct
{

    volatile u32 CPUID;  /* The CPUID register contains the processor part number, version, and implementation information. */
    volatile u32 ICSR;   /* Interrupt control and state register */
    volatile u32 VTOR;   /* Vector table offset register */
    volatile u32 AIRCR;  /* Application interrupt and reset control register */
    volatile u32 SCR;    /* System control register  */
    volatile u32 CCR;    /* Configuration and control register */
    volatile u8 PRI[16]; /* System handler priority registers, ONLY [4,5,6,11,14,15] are used  */
    volatile u32 SHCSR;  /* System handler control and state register */
    volatile u32 CFSR;   /* Configurable fault status register  */
    volatile u32 HFSR;   /* Hard fault status register */
    volatile u32 MMFAR;  /* Memory management fault address register */
    volatile u32 BFAR;   /* Bus fault address register */

} SCB_t;

#define SCB ((volatile SCB_t *)0xE000ED00)

#endif