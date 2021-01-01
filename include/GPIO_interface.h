/*
 *  Author  :   Ahmad Yaqoot
 *  Date    :   17/Aug/2020
 *  Type    :   GPIO Interface File
 *  Version :   V1.0
 */ 

#ifndef GPIO_INTERFACE_H 
#define GPIO_INTERFACE_H

#define     GPIOA   0
#define     GPIOB   1
#define     GPIOC   2

#define     PIN0    0
#define     PIN1    1
#define     PIN2    2
#define     PIN3    3
#define     PIN4    4
#define     PIN5    5
#define     PIN6    6
#define     PIN7    7
#define     PIN8    8
#define     PIN9    9
#define     PIN10   10
#define     PIN11   11
#define     PIN12   12
#define     PIN13   13
#define     PIN14   14
#define     PIN15   15

#define GPIO_HIGH   1
#define GPIO_LOW    0

#define INPUT_ANALOG                0b0000
#define INPUT_FLOATING              0b0100
#define INPUT_PULL_UP_DOWN          0b1000

#define OUTPUT_GP_PP_10MHZ          0b0001
#define OUTPUT_GP_PP_2MHZ           0b0010
#define OUTPUT_GP_PP_50MHZ          0b0011

#define OUTPUT_GP_OD_10MHZ          0b0101
#define OUTPUT_GP_OD_2MHZ           0b0110
#define OUTPUT_GP_OD_50MHZ          0b0111

#define OUTPUT_AF_PP_10MHZ          0b1001
#define OUTPUT_AF_PP_2MHZ           0b1010
#define OUTPUT_AF_PP_50MHZ          0b1011

#define OUTPUT_AF_OD_10MHZ          0b1101
#define OUTPUT_AF_OD_2MHZ           0b1110
#define OUTPUT_AF_OD_50MHZ          0b1111

void GPIO_voidSetPinDirection(u8 Copy_u8PortNo, u8 Copy_u8PinNo, u8 Copy_u8Mode);
void GPIO_voidSetPinValue(u8 Copy_u8PortNo, u8 Copy_u8PinNo, u8 Copy_u8Value);
u8 GPIO_u8GetPinValue(u8 Copy_u8PortNo, u8 Copy_u8PinNo);
void GPIO_voidLockPinValue(u8 Copy_u8PortNo, u8 Copy_u8PinNo);



#endif