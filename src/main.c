#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "USART_INTERFACE.h"
#include "FPEC_interface.h"
#include "WIFI_interface.h"
#include "WIFI_config.h"

/*  Bug report */
/*
 * - FIXED: wifi connect checking while loop never breaks
 * - server might return errors and not read file
 *
 *
 * */




#define LINES 30  //  MAX#Lines / packet
#define CHARS 45  //  MAX#chars / line
extern u8 buf[LINES][CHARS];
extern u8 status;
extern u8 iDx;

typedef void (*Function_t)(void);
Function_t addr_to_call = 0;

void ExecuteApp(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08002000;

	addr_to_call = *(Function_t*)(0x08002004);
	addr_to_call();
}
void Parser_voidParseRecord(u8* Copy_u8BufData);

/*****************************************************/
void parsebuffer(u8 buff[], u8 *cc, u8 address[], u8 *RecType, u8 data[])
{
	u8 i = 0, y = 0 , z = 0;
	u16 byte_count = 0;

	/* Parsing the first few blocks before the data */
	for (i = 0; i < 10; i++)
	{
		/* Bypass the colon ':' character */
		if (i == 0)
		{
			continue;
		}

		/* parsing the byte count of the data record*/
		else if (i >= 1 && i <= 2)
		{
			//u8 data_length[2] = {buff[1], buff[2]};
			//u16 character_length = 2;
			static u16 base = 16;
			if (buff[i] >= '0' && buff[i] <= '9')
			{
				byte_count += (buff[i] - 48) * base;
				base /= 16;
			}
			else if (buff[i] >= 'A' && buff[i] <= 'F')
			{
				byte_count += (buff[i] - 55) * base;
				base /= 16;
			}

			*cc = byte_count * 2;
		}

		/* parsing the address*/
		else if (i >= 3 && i < 7)
		{
			if (buff[i] >= '0' && buff[i] <= '9')
			{
				/*each hex character is in one array element*/
				address[y] = (buff[i] - 48);
				y++;
			}
			else if (buff[i] >= 'A' && buff[i] <= 'F')
			{
				/*each hex character is in one array element */
				address[y] = (buff[i] - 55);
				y++;
			}
		}

		/* parsing the Record Type*/
		else if (i > 7 && i < 9)
		{
			//static int y1 = 0;
			if (buff[i] >= '0' && buff[i] <= '9')
			{
				*RecType = (buff[i] - 48);
			}
		}
	}

	/* parsing the data*/
	for (i = 9; i < (*cc + 9); i++)
	{
		if (buff[i] >= '0' && buff[i] <= '9')
		{
			data[z] = (buff[i] - 48);
			z++;
		}
		else if (buff[i] >= 'A' && buff[i] <= 'F')
		{
			data[z] = (buff[i] - 55);
			z++;
		}
	}
}
/*****************************************************/

void BurnNewAPP(void)
{

	MUSART1_VidSetCallBack(MUSART_CallBack);

	FPEC_voidEraseAppArea();

	u8 CC=0,RecordType=0,Address[4]={0},DataBuffer[32]={0};
	u8 z=1;
	u8 * tempLine;
	//		Refresh the buffer with "GET"ing new page with wifi
	do
	{
		WIFI_voidLinkServer(webIP);
		WIFI_RefreshPage(webLink,z);
		MSTK_voidSetBusyWaitms(1000);
		WIFI_voidLinkServer(webIP);
		WIFI_GetFile(webLink,BufferTXT);
		MSTK_voidSetBusyWaitms(1000);
		//			Parsing and flashing line by line
		for (u8 y=0;y<30;y++)
		{
			tempLine=buf[y];
			parsebuffer(tempLine, &CC,Address,&RecordType, DataBuffer);
			if (RecordType==4||RecordType==0)
			{
				Parser_voidParseRecord(tempLine);
			}
		}
		z++;
	}while(RecordType != 1);

	status = 2;
	WIFI_voidLinkServer(webIP);
	WIFI_GetFile(webLink,NoUpdate);

}
void main (void)
{
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,RCC_GPIOA);

	NVIC_voidInit();
	NVIC_voidSetPriority(37,0b00110000);

	MSTK_voidInit();
	MUSART1_voidInit();
	NVIC_voidEnableInterrupt (37) ;
	WIFI_voidInit();

	GPIO_voidSetPinDirection(GPIOA,PIN0,OUTPUT_GP_PP_10MHZ);
	//u8 receivedData=255;


	//u8 StatusVar=2;
	//MUSART1_voidTransmit((u8 *)"AT+CWQAP\r\n");
	//MUSART1_voidTransmit((u8 *)"AT+CWJAP?\r\n");
	//STK_voidSetBusyDelayMs(1500);
	WIFI_voidConnectWifi(mySSID,myPassword);
	MUSART1_VidSetCallBack(MUSART_CallBackStatus);

	WIFI_voidLinkServer(webIP);
//	ESP8266_VidClearCheckBuffer();
	WIFI_GetFile(webLink,StatusTXT);




	if(status == 1)
	{
		BurnNewAPP();
		ExecuteApp();

	}
	else
	{
		ExecuteApp();
	}



}

