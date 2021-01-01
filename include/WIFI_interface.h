/*
 *  Author  :   Ahmad Yaqoot
 *  Date    :   24/Oct/2020
 *  Type    :   WIFI Interface File
 *  Version :   V1.0
 */

#ifndef WIFI_INTERFACE_H
#define WIFI_INTERFACE_H

void WIFI_voidInit(void);
void WIFI_voidConnectWifi(u8 * Copy_u8SSID, u8 * Copy_u8WifiPassword);
void WIFI_voidLinkServer(u8 * Copy_u8IP);
u8 WIFI_u8ReceiveSingle(u8 * Copy_u8HyperLink);
void ESP8266_VidClearBuffer ( void );
void MUSART_CallBack (void);

#endif
