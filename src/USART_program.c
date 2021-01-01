
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "USART_INTERFACE.h"
#include "USART_private.h"
#include "USART_config.h"



void (*MUSART1_CallBack)(void ) = NULL;

void MUSART1_voidInit(void)
{
	RCC_voidEnableClock(RCC_APB2,RCC_USART1);

	/*	baud rate = 9600	FOR Putty	*/
	/*	USART1 -> BRR = 0x341;*/
	/*	baud rate = 115200	For ESP	*/
	USART1 -> BRR = 0x45;

	SET_BIT((USART1-> CR[0]), 3);			/* Enabling Transmitter */
	SET_BIT((USART1-> CR[0]), 2);			/* Enabling Receiver */
	SET_BIT((USART1-> CR[0]), 5);			/* Enabling RX interrupt */
	/*SET_BIT((USART1-> CR[0]), 7);*/            /* Enabling TX interrupt */
	SET_BIT((USART1-> CR[0]), 13);			/* Enabling USART */

	USART1 -> SR = 0;						/* Clearing status register */
}

void MUSART1_voidTransmit(u8 arr[])
{
	/*u16 Local_u16Timeout=0;

	u8 i = 0;
	while(arr[i] != '\0')
	{
		USART1 -> DR = arr[i];
		while((GET_BIT((USART1 -> SR), 6)) == 0)
		{
			Local_u16Timeout++;
			if (Local_u16Timeout == 10000)
			{
				break;
			}
		i++;
		}
	}*/
	u16 Local_u16Timeout=0;
	u8 i = 0;
	while(arr[i] != '\0'){
		USART1 -> DR = arr[i];
		while((GET_BIT((USART1 -> SR), 6)) == 0)
		{
			Local_u16Timeout++;
			if (Local_u16Timeout == 10000)
			{
				break;
			}
		}
		i++;
	}

}

u8 MUSART1_u8Receive(void)
{
	u16 Local_u16Timeout=0;
	u8 Local_u8ReceivedData = 0;
	while((GET_BIT((USART1->SR),5))== 0)
	{
		Local_u16Timeout++;
		if (Local_u16Timeout == 10000)
		{
			Local_u8ReceivedData=255;
			break;
		}
	}

	if (Local_u8ReceivedData==0)
	{
		Local_u8ReceivedData	=	USART1 -> DR;
	}
	return (Local_u8ReceivedData);
}


void MUSART1_VidSetCallBack( void (*ptr) (void ) ){

	if(ptr != NULL)
	{
		MUSART1_CallBack = ptr ;
	}


}

void USART1_IRQHandler(void)
{

	MUSART1_CallBack();

	MUSART1_VidClearFlags();

}

void MUSART1_VidClearFlags( void )
{
	/* Clear all flags */
	USART1 -> SR = 0;}


void MUSART1_VidDisableRX(void)
{
	CLR_BIT((USART1-> CR[0]), 2);			/* Enabling Receiver */
	CLR_BIT((USART1-> CR[0]), 5);
}

u8 MUSART1_u8ReadDataRegister ( void ){

	return ( USART1 -> DR );

}














