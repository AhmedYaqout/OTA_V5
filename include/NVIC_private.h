/*
 *  Author  :   Ahmad Yaqoot
 *  Date    :   26/September/2020
 *  Type    :   NVIC Private File
 *  Version :   V1.1
 */ 

#ifndef NVIC_PRIVATE_H 
#define NVIC_PRIVATE_H

#define NVIC_BASE_ADDRESS   0xE000E100

#define NVIC_ISER0  *((u32*)(NVIC_BASE_ADDRESS)) /* Enable External Interrupts fro 0 to 31*/
#define NVIC_ISER1  *((u32*)(NVIC_BASE_ADDRESS+0x004)) 
#define NVIC_ISER2  *((u32*)(NVIC_BASE_ADDRESS+0x008))

#define NVIC_ICER0  *((u32*)(NVIC_BASE_ADDRESS+0x080))
#define NVIC_ICER1  *((u32*)(NVIC_BASE_ADDRESS+0x084))
#define NVIC_ICER2  *((u32*)(NVIC_BASE_ADDRESS+0x088))

#define NVIC_ISPR0  *((u32*)(NVIC_BASE_ADDRESS+0x100))
#define NVIC_ISPR1  *((u32*)(NVIC_BASE_ADDRESS+0x104))
#define NVIC_ISPR2  *((u32*)(NVIC_BASE_ADDRESS+0x108))

#define NVIC_ICPR0  *((u32*)(NVIC_BASE_ADDRESS+0x180))
#define NVIC_ICPR1  *((u32*)(NVIC_BASE_ADDRESS+0x184))
#define NVIC_ICPR2  *((u32*)(NVIC_BASE_ADDRESS+0x188))

#define NVIC_IABR0  *((volatile u32*)(NVIC_BASE_ADDRESS+0x200))
#define NVIC_IABR1  *((volatile u32*)(NVIC_BASE_ADDRESS+0x204))
#define NVIC_IABR2  *((volatile u32*)(NVIC_BASE_ADDRESS+0x208))

#define NVIC_IPR    ((u8*)(NVIC_BASE_ADDRESS+0x300))


#define NVIC_STIR   (NVIC_BASE_ADDRESS+0xE00)



#define NVIC_GROUP_4_SUB_0  0x05FA0300  /* 4 Bits for group  (IPR)*/
#define NVIC_GROUP_3_SUB_1  0x05FA0400/* 3 Bits for group  and 1 bit for sub(IPR)*/
#define NVIC_GROUP_2_SUB_2  0x05FA0500/* 2 Bits for group and 2 bits for subgroup  (IPR)*/
#define NVIC_GROUP_1_SUB_3  0x05FA0600/* 1 Bit for group and 3 bits for subgroup (IPR)*/
#define NVIC_GROUP_0_SUB_4  0x05FA0700/* no Bits for group and 4 bits for subgroup  (IPR)*/

#endif