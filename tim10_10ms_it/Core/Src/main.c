/*
 * main.c
 *
 *  Created on: Sep 1, 2021
 *      Author: root
 */
/*
Author : Ashwin Jayakumar Pillai
Date : 3rd September, 2021
Note : This is a program for UART on stm32F401RE starting from scratch. Edited files are : main.c,it.c,msp.c,it.h,main.h
*/
#include "main.h"
#include <string.h>
#define COMPLETE 1
#define INCOMPLETE 0

void SystemClockConfig(void);
void UART2_Init(void);
void errorHandler(void);

UART_HandleTypeDef huart2; //Defining a handle variable

char *msg="Transmission has started!!!\n\r";
char buff[100];
uint8_t count=0;
uint8_t temp;
uint8_t recComp=INCOMPLETE;

int main(void)
{
uint16_t size=strlen(msg);
HAL_Init();
SystemClockConfig();
UART2_Init();

HAL_UART_Transmit(&huart2, (uint8_t*)msg, size, HAL_MAX_DELAY);
	//errorHandler();
while(1){
	HAL_UART_Receive_IT(&huart2 , &temp , 1);

	if(recComp == COMPLETE)
	{
		HAL_UART_Transmit(&huart2, (uint8_t*)buff, count, HAL_MAX_DELAY);
		recComp = INCOMPLETE;
		count = 0;
	}
/*	if(temp == '\r')
	{
		buff[count++]='\r';
		break;
	}
	else
	{
		buff[count++]=(char)temp;

	}
*/
}

//HAL_UART_Transmit(&huart2, (uint8_t*)buff, count, HAL_MAX_DELAY);
	//errorHandler();
return 0;
}

void SystemClockConfig(void)
{}

void UART2_Init(void)
{
	huart2.Instance = USART2;						//Linking handler to the peripheral
	huart2.Init.BaudRate = 115200;					//Setting up parameters
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if((HAL_UART_Init(&huart2))!= HAL_OK)
		errorHandler();
}

void errorHandler(void)
{
while(1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
if(temp=='\r')
{
	recComp=COMPLETE;
	buff[count++]=temp;
}
else
{
	buff[count++]=temp;
}
}
