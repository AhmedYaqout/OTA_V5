/*
 *  Author  :   Ahmad Yaqoot
 *  Date    :   13/Sept/2020
 *  Type    :   RCC Interface File
 *  Version :   V2.0
 */ 

#ifndef RCC_INTERFACE_H 
#define RCC_INTERFACE_H

#define RCC_AHB     0
#define RCC_APB1    1
#define RCC_APB2    2


/*VERY IMPORTANT NOTE:     The following can only be enabled from APB2 Bus      */
#define RCC_GPIOA   2
#define RCC_GPIOB   3
#define RCC_GPIOC   4
#define RCC_GPIOD   5
#define RCC_GPIOE   6
#define RCC_GPIOF   7
#define RCC_GPIOG   8

#define RCC_AFIO    0
#define RCC_ADC1    9
#define RCC_ADC2    10
#define RCC_TIM1    11
#define RCC_SPI1    12
#define RCC_TIM8    13
#define RCC_USART1  14
#define RCC_ADC3    15
#define RCC_TIM9    19
#define RCC_TIM10   20
#define RCC_TIM11   21


void RCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId);
void RCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId);
void RCC_voidInitSysClock(void);

#endif