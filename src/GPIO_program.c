/*
 *  Author  :   Ahmad Yaqoot
 *  Date    :   8/Aug/2020
 *  Type    :   GPIO Program Executable File
 *  Version :   V1.0
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

void GPIO_voidSetPinDirection(u8 Copy_u8PortNo, u8 Copy_u8PinNo, u8 Copy_u8Mode)
{
switch (Copy_u8PortNo)
{
case GPIOA:
            if(Copy_u8PinNo<8)
            {
                GPIOA_CRL   &=  ~(0xF<<(Copy_u8PinNo*4));
                GPIOA_CRL   |=  (Copy_u8Mode<<(Copy_u8PinNo*4));
            }
            else if (Copy_u8PinNo<16)
            {
                Copy_u8PinNo = Copy_u8PinNo-8;
                GPIOA_CRH   &=  ~(0xF<<(Copy_u8PinNo*4));
                GPIOA_CRH   |=  (Copy_u8Mode<<(Copy_u8PinNo*4));        
            }
            
break;
case GPIOB:
            if(Copy_u8PinNo<8)
            {
                GPIOB_CRL   &=  ~(0xF<<(Copy_u8PinNo*4));
                GPIOB_CRL   |=  (Copy_u8Mode<<(Copy_u8PinNo*4));
            }
            else if (Copy_u8PinNo<16)
            {
                Copy_u8PinNo = Copy_u8PinNo-8;
                GPIOB_CRH   &=  ~(0xF<<(Copy_u8PinNo*4));
                GPIOB_CRH   |=  (Copy_u8Mode<<(Copy_u8PinNo*4));        
            }
break;
case GPIOC:
            if(Copy_u8PinNo<8)
            {
                GPIOC_CRL   &=  ~(0xF<<(Copy_u8PinNo*4));
                GPIOC_CRL   |=  (Copy_u8Mode<<(Copy_u8PinNo*4));
            }
            else if (Copy_u8PinNo<16)
            {
                Copy_u8PinNo = Copy_u8PinNo-8;
                GPIOC_CRH   &=  ~(0xF<<(Copy_u8PinNo*4));
                GPIOC_CRH   |=  (Copy_u8Mode<<(Copy_u8PinNo*4));        
            }
break;

default:
    break;
}
}

void GPIO_voidSetPinValue(u8 Copy_u8PortNo, u8 Copy_u8PinNo, u8 Copy_u8Value)
{
switch (Copy_u8PortNo)
{
/*
 * BSRR sets and/or clears the ODR Registers faster than normal SET/CLR_BIT Commands 
 * BRR only clears the ODR Registers
 */
case GPIOA:

            if(Copy_u8Value == GPIO_HIGH)
            {
                /*
                 * Sets ODR of PORTA to HIGH 
                 */
             GPIOA_BSRR =   (1<<Copy_u8PinNo); 
               
            }
            else if (Copy_u8Value == GPIO_LOW)
            {
                /*
                 * Sets ODR of PORTA to LOW 
                 */
             GPIOA_BRR =   (1<<Copy_u8PinNo); 
    
            }
            
break;
case GPIOB:
            if(Copy_u8Value == GPIO_HIGH)
            {
                /*
                 * Sets ODR of PORTB to HIGH 
                 */
             GPIOB_BSRR =   (1<<Copy_u8PinNo); 
               
            }
            else if (Copy_u8Value == GPIO_LOW)
            {
                /*
                 * Sets ODR of PORTB to LOW 
                 */
             GPIOB_BRR =   (1<<Copy_u8PinNo); 
    
            }
            
break;
case GPIOC:
            if(Copy_u8Value == GPIO_HIGH)
            {
                /*
                 * Sets ODR of PORTC to HIGH 
                 */
             GPIOC_BSRR =   (1<<Copy_u8PinNo); 
               
            }
            else if (Copy_u8Value == GPIO_LOW)
            {
                /*
                 * Sets ODR of PORTC to LOW 
                 */
             GPIOC_BRR =   (1<<Copy_u8PinNo); 
    
            }
            
break;
default:
    break;
}
}

u8 GPIO_u8GetPinValue(u8 Copy_u8PortNo, u8 Copy_u8PinNo)
{   /*
     * Declare Local Variable to store the pin's value 
     */
    u8 LOC_u8PinValue  =   0;
switch (Copy_u8PortNo)
{
case GPIOA:
     LOC_u8PinValue  =   GET_BIT(GPIOA_IDR,Copy_u8PinNo);      
break;

case GPIOB:          
     LOC_u8PinValue  =   GET_BIT(GPIOB_IDR,Copy_u8PinNo);     
break;

case GPIOC:
     LOC_u8PinValue  =    GET_BIT(GPIOC_IDR,Copy_u8PinNo);          
break;

default:
    break;
}
return LOC_u8PinValue;
}

void GPIO_voidLockPinValue(u8 Copy_u8PortNo, u8 Copy_u8PinNo)
{/*
 * LCKR should lock the "State" of the pin to either low or high so it can't ve changed in the runtime for safety
 */
switch (Copy_u8PortNo)
{

case GPIOA:
           GPIOA_LCKR |= (1<<Copy_u8PinNo);
break;
case GPIOB:
           GPIOB_LCKR |= (1<<Copy_u8PinNo);
break;

case GPIOC:
           GPIOC_LCKR |= (1<<Copy_u8PinNo);                        
break;

default:
    break;
}
}
