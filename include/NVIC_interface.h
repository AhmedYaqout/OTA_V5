/*
 *  Author  :   Ahmad Yaqoot
 *  Date    :   26/September/2020
 *  Type    :   NVIC Interface File
 *  Version :   V2.0
 */ 

#ifndef NVIC_INTERFACE_H 
#define NVIC_INTERFACE_H

void NVIC_voidInit(void);
void NVIC_voidSetPriority(s8 Copy_PeripheralId, u8 Copy_u8Priority);
void NVIC_voidEnableInterrupt(u8 Copy_u8InterruptNo);
void NVIC_voidDisableInterrupt(u8 Copy_u8InterruptNo);
void NVIC_voidSetPendingInterrupt(u8 Copy_u8InterruptNo);
void NVIC_voidClearPendingInterrupt(u8 Copy_u8InterruptNo);
u8 NVIC_u8GetActiveInterrupt(u8 Copy_u8InterruptNo);


#endif