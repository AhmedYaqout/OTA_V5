/*
 *  Author  :   Ahmad Yaqoot
 *  Date    :   24/Oct/2020
 *  Type    :   WIFI Program Executable File
 *  Version :   V1.0
 */
#include<stdio.h>
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"RCC_interface.h"

#include"GPIO_interface.h"
#include"STK_interface.h"
#include"USART_interface.h"
#include"USART_private.h"

#include "WIFI_interface.h"
#include "WIFI_private.h"
#include "WIFI_config.h"


u8 volatile Iterator = 0  ;
u8 volatile DataCome[1350] ;
static  u8 * LineArr = NULL;

/* <NEW> */
#define LINES 30  //  MAX#Lines / packet
#define CHARS 45  //  MAX#chars / line



enum mode { DO_NOTHING,READ_NO_CHARS, READ_CHARS, READ_FILE_SIZE};
enum mode Mode =DO_NOTHING ;

u8 ch=0;

u8 buf[LINES][CHARS];
u8 buffCheck[100];
u8 idxLines = 0;
u8 idxChars = 0;

u8 byte_count_buf[6]={0};
u32 byte_count = 0;
u16 idxDigit = 0;
/******************/
u32 myA2I(char a[], u32 size)
{

	u32 number=0;
	u32 DigitValue = 0;

	for (u32 i = 0; i < size; i++)
	{
		DigitValue = (a[i]-'0');
		for (u32 k = 0; k < (size-1)-i; k++)
		{
			DigitValue *=10;
		}
		number += DigitValue;
	}

	return number;
}


/*****************/
void WIFI_SetLineBuffer(u8 * Copy_u8LineBuffer)
{
	if (Copy_u8LineBuffer!= NULL)
	{
		LineArr = Copy_u8LineBuffer;
	}
}
/*****************/


void MUSART_CallBack ( void ){
	if (GET_BIT(USART1 -> SR, RXNE))
	{
		/* Receive ESP8266 Response */
		//DataCome[ Iterator ] = MUSART1_u8ReadDataRegister();
		/* ------------------ */

		//Iterator++;

		ch = USART1->DR;

		switch(Mode)
		{
		case DO_NOTHING:
			if(ch == ',')
			{
				Mode = READ_NO_CHARS;
			}


			break;


		case READ_NO_CHARS:
			if (ch != ':')
			{
				byte_count_buf[idxDigit] = ch;
				idxDigit++;
			}
			else
			{
				byte_count = myA2I(byte_count_buf,idxDigit);
				Mode = READ_CHARS;
				idxDigit = 0;
			}



			break;


		case READ_CHARS:
			if(ch != '\r')
			{
				if (byte_count != 0)
				{
					byte_count--;
					// save the character in the buffer
					buf[idxLines][idxChars] = ch;

					if (ch == '\n')
					{
						byte_count--; // might be removed based on experimental trials
						idxChars = 0;
						if (idxLines < LINES)
						{
							idxLines++;
						}
					}
					else
					{
						idxChars=(idxChars+1)%CHARS;
					}

				}
				else // we recieved all bytes of a packet
				{
					buf[idxLines][idxChars] = '\n';
					Mode = DO_NOTHING;
					idxLines = 0 ; idxChars= 0;
				}

			}
			break;
		default:
			break;

		}

		MUSART1_VidClearFlags();
		CLR_BIT(USART1 -> SR, RXNE);
	}

}
enum mode1 {entrance,storing};
enum mode1 Mode1=entrance;
void MUSART_CallBackCheck ( void )
{
	if (GET_BIT(USART1 -> SR, RXNE))
	{	static u8 iDx=0;
	/* Receive ESP8266 Response */
	//DataCome[ Iterator ] = MUSART1_u8ReadDataRegister();
	/* ------------------ */

	//Iterator++;

	ch = USART1->DR;

	switch(Mode1){
	case entrance:
		if(ch == 'N' || ch=='+')
		{
			buffCheck[iDx]=ch;
			Mode1=storing;
			if (iDx < 100)
			{
				iDx++;
			}
		}
		break;
	case storing:
		buffCheck[iDx]=ch;
		if (iDx < 100)
		{
			iDx++;
		}
		break;
	}
	}
}

void WIFI_voidInit(void)
{
	//MUSART1_VidSetCallBack(MUSART_CallBack);
	MUSART1_VidSetCallBack(MUSART_CallBackCheck);
	/* Configure A9  (Tx1) as Output AFPP @ 2MHz */
	GPIO_voidSetPinDirection(GPIOA,PIN9,OUTPUT_AF_PP_2MHZ);
	/* Configure A10 (RX1) as input Floating     */
	GPIO_voidSetPinDirection(GPIOA,PIN10,INPUT_FLOATING);

	MUSART1_voidTransmit( (u8 *)"ATE0\r\n" );
	MUSART1_voidTransmit( (u8 *)"AT+CWMODE=1\r\n" );
	MSTK_voidSetBusyWaitms(20000);

}

void WIFI_voidConnectWifi(u8 * Copy_u8SSID, u8 * Copy_u8WifiPassword)
{
	/*	The algorithm is to concatenate the wifi name, password and AT command in one string*/
	static u8 j,k,l,m;
	/*	 The first part of the command from 'A' till the opening quote of the SSID*/
	static u8 Local_u8APConnect1[100] = "AT+CWJAP=\"";

	/*	The second part of the command from the closing quote of the SSID till the opening quote of the password*/
	static u8 Local_u8APConnect2[5] =	"\",\"";

	/*	 The third part of the command from the closing quote of the password till the '\n'*/
	static u8 Local_u8APConnect3[9] =	"\"\r\n";

	static u8 Local_u8APConnect1length=0;

	/*	 It is unnecessary step but just in case sth happens.*/
	/*	 * Store length of the first part of the AP Connect command in a variable*/
	while (Local_u8APConnect1[Local_u8APConnect1length] != '\0') {
		++Local_u8APConnect1length;
	}


	/*	 concatenate SSID to AP Connect Part1*/
	for ( j = 0; Copy_u8SSID[j] != '\0'; ++j, ++Local_u8APConnect1length)
	{
		Local_u8APConnect1[Local_u8APConnect1length] = Copy_u8SSID[j];
	}

	/*	 concatenate AP Connect Part2 with the previous*/
	for ( k = 0; Local_u8APConnect2[k] != '\0'; ++k, ++Local_u8APConnect1length)
	{
		Local_u8APConnect1[Local_u8APConnect1length] = Local_u8APConnect2[k];
	}

	/*	 concatenate WIFI Password with the previous*/
	for ( l = 0; Copy_u8WifiPassword[l] != '\0'; ++l, ++Local_u8APConnect1length)
	{
		Local_u8APConnect1[Local_u8APConnect1length] = Copy_u8WifiPassword[l];
	}

	/*	 concatenate AP Connect Part 3 with the previous*/
	for ( m = 0; Local_u8APConnect3[m] != '\0'; ++m, ++Local_u8APConnect1length)
	{
		Local_u8APConnect1[Local_u8APConnect1length] = Local_u8APConnect3[m];
	}
	u8 connection_status=255;
	connection_status=Private_WIFI_u8CheckConnection();
	while(connection_status!=1)
	{
		connection_status=Private_WIFI_u8CheckConnection();
		MUSART1_voidTransmit(Local_u8APConnect1);
		MSTK_voidSetBusyWaitms(10000);
	}
	MUSART1_VidSetCallBack(MUSART_CallBack);
}

void WIFI_voidLinkServer(u8 * Copy_u8IP)
{

	MUSART1_voidTransmit( (u8 *) "AT+CIPSTART=\"TCP\",\"" );
	MUSART1_voidTransmit( (u8 *) Copy_u8IP );
	MUSART1_voidTransmit( (u8 *) "\"," );
	MUSART1_voidTransmit( (u8 *) "80" );
	MUSART1_voidTransmit( (u8 *) "\r\n" );
	MSTK_voidSetBusyWaitms(20000);
}


/*************************************************/

void WIFI_GetFile(u8 * Copy_u8HyperLink, u8 * Copy_u8FileName)
{
	ESP8266_VidClearBuffer();
	MUSART1_voidTransmit( (u8 *) "AT+CIPSEND=" );
	MUSART1_voidTransmit( (u8 *) "45" );
	MUSART1_voidTransmit((u8 *) "\r\n" );
	MSTK_voidSetBusyWaitms(3000);

	ESP8266_VidClearBuffer();

	MUSART1_voidTransmit( (u8 *) "GET http://" );
	MUSART1_voidTransmit( (u8 *) Copy_u8HyperLink );
	/*		MUSART1_voidTransmit((u8 *) "/status.txt\r\n" );*/
	MUSART1_voidTransmit((u8 *) Copy_u8FileName );

}
void WIFI_RefreshPage(u8 * Copy_u8HyperLink, u8 PageNo)
{
	u8 mainScript[100]={"GET http://"};
	//u8 part1[]=Copy_u8HyperLink;
	u8 part2[]={"/script.php?command=1&page_no="};
	u8 part3[]={"\r\n"};
	u8 main_length=0;
	u8 byteCount[100]={'\0'};
	/************Concatenation of Script******************/
	while (mainScript[main_length]!='\0')
	{
		main_length++;
	}
	int j=0;
	for (j=0;Copy_u8HyperLink[j]!='\0';j++)
	{
		mainScript[main_length]=Copy_u8HyperLink[j];
		main_length++;
	}
	for (j=0;part2[j]!='\0';j++)
	{
		mainScript[main_length]=part2[j];
		main_length++;
	}
	if (PageNo>=0 && PageNo<10)
	{
		mainScript[main_length]=PageNo+48;
		main_length++;
	}
	else if ( PageNo>=10 && PageNo<100)
	{
		mainScript[main_length]=((PageNo/10)+48);
		main_length++;
		mainScript[main_length]=((PageNo%10)+48);
		main_length++;
	}
	for (j=0;part3[j]!='\0';j++)
	{
		mainScript[main_length]=part3[j];
		main_length++;
	}
	/**********Convert length to string*************/
	if (main_length>=0 && main_length<10)
	{
		j=0;
		byteCount[j]=main_length+48;
	}
	else if ( main_length>=10 && main_length<100)
	{
		j=0;
		byteCount[j]=((main_length/10)+48);
		j++;
		byteCount[j]=((main_length%10)+48);
	}

	ESP8266_VidClearBuffer();
	MUSART1_voidTransmit( (u8 *) "AT+CIPSEND=" );
	/* Count whole command first before transmission*/
	MUSART1_voidTransmit( (u8 *) byteCount );
	MUSART1_voidTransmit((u8 *) "\r\n" );
	MSTK_voidSetBusyWaitms(3000);

	MUSART1_voidTransmit((u8 *) mainScript );
	MSTK_voidSetBusyWaitms(1500);
}

/*************************************************/

u8 Private_WIFI_u8CheckConnection(void)
{	ESP8266_VidClearBuffer();
MUSART1_voidTransmit((u8 *)"AT+CWJAP?\r\n");
MSTK_voidSetBusyWaitms(1000);
u8 Local_u8Result	=	255;

if (buffCheck[0]=='N' && buffCheck[1]=='o')
{
	Local_u8Result	=	0;
}
else if (buffCheck[0]=='+' && buffCheck[1]=='C')
{
	Local_u8Result	=	1;
}
return Local_u8Result;

}

u8 Private_WIFI_u8ValidateCmd(void)
{
	u8 Local_u8Response[100]={0};
	u8 i	=	0;
	u8 Local_u8Temp = 0;
	u8 Local_u8Result	=	0;

	while (Local_u8Temp!=255)
	{
		Local_u8Temp=Local_u8Response[i];
		Local_u8Response[i] = MUSART1_u8Receive();
		i++;
	}
	if (Local_u8Response[0]=='O' && Local_u8Response[1]=='K')
	{
		Local_u8Result	=	1;
	}
	return Local_u8Result;

}

u8 Private_WIFI_u8ValidateData(void)
{
	u8 Local_u8Response[100]={0};
	u8 i	=	0;
	u8 Local_u8Temp = 0;
	u8 Local_u8Result	=	0;

	while (Local_u8Temp!=255)
	{
		Local_u8Temp=Local_u8Response[i];
		Local_u8Response[i] = MUSART1_u8Receive();
		i++;
	}
	if (Local_u8Response[0]=='+' && Local_u8Response[1]=='I')
	{
		Local_u8Result	=	1;
	}
	return Local_u8Result;

}

u8 Private_WIFI_u8Data(void)
{
	u8 Local_u8Response[100]={0};
	u8 i	=	0;
	u8 Local_u8Temp = 0;
	u8 Local_u8Result	=	0;

	while (Local_u8Temp!=255)
	{
		Local_u8Temp=Local_u8Response[i];
		Local_u8Response[i] = MUSART1_u8Receive();
		i++;
	}
	Local_u8Result=Local_u8Response[7];

	return Local_u8Result;

}
void ESP8266_VidClearBuffer ( void ){

	u16 LOC_u8Iterator1 = 0 ;
	u16 LOC_u8Iterator2 = 0 ;

	Iterator     = 0 ;

	for( LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < LINES ; LOC_u8Iterator1++ ){
		for( LOC_u8Iterator2 = 0 ; LOC_u8Iterator2 < CHARS ; LOC_u8Iterator2++ ){

			buf[ LOC_u8Iterator1 ][ LOC_u8Iterator2 ] = 0 ;

		}
	}
}
