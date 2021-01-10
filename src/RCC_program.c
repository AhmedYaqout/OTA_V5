/*
 *  Author  :   Ahmad Yaqoot
 *  Date    :   8/Aug/2020
 *  Type    :   RCC Program Executable File
 *  Version :   V1.0
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

void RCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId){

    if (Copy_u8PerId <= 31)
    {
        switch (Copy_u8BusId)
        {
        case RCC_AHB    :   SET_BIT(RCC_AHBENR,Copy_u8PerId) ;     break;
        case RCC_APB1   :   SET_BIT(RCC_APB1ENR,Copy_u8PerId);     break;
        case RCC_APB2   :   SET_BIT(RCC_APB2ENR,Copy_u8PerId);     break;
       
        }

    }

    
}

/*void RCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId){

    if (Copy_u8PerId <= 31)
    {
        switch (Copy_u8BusId)
        {
        case RCC_AHB    :   CLR_BIT(RCC_AHBENR,Copy_u8PerId) ;     break;
        case RCC_APB1   :   CLR_BIT(RCC_APB1ENR,Copy_u8PerId);     break;
        case RCC_APB2   :   CLR_BIT(RCC_APB2ENR,Copy_u8PerId);     break;
       
        }

    }
    

}*/

void RCC_voidInitSysClock(void){

    #if     RCC_CLOCK_TYPE  ==  RCC_HSE_CRYSTAL
    /*SET_BIT(RCC_CR,HSE_ON);
    CLR_BIT(RCC_CR,HSE_BYP)*/
        RCC_CR  =   0x00010000; /*Enable HSE with no bypass*/
        RCC_CFGR=   0x00000001;

    #elif   RCC_CLOCK_TYPE  ==  RCC_HSE_RC
        RCC_CR  =   0x00050000;  /*Enable HSE with bypass*/
        RCC_CFGR=   0x00000001;

    #elif   RCC_CLOCK_TYPE  ==  RCC_HSI
        RCC_CR  =   0x00000081;  /*Enable HSI + Trimming = 0*/
        RCC_CFGR=   0x00000000;

    #elif   RCC_CLOCK_TYPE  ==  RCC_PLL
        RCC_CR  =   0x00010000
        #if 
        #endif
    #else
            #error("You chose Wrong Clock type")
    #endif

}
