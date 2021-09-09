/*
 * main.c
 *
 *  Created on: Sep 1, 2021
 *      Author: root
 */
/*
 Author : Ashwin Jayakumar Pillai
 Date : 8th September, 2021
 Note : This is a program for PLL on stm32F401RE starting from scratch. Edited files are : main.c,it.c,msp.c,it.h,main.h
 */
#include "main.h"
#include <string.h>
#include <stdio.h>
#define COMPLETE 1
#define INCOMPLETE 0

void UART2_Init(void);
void errorHandler(void);
void pll_config(void);

UART_HandleTypeDef huart2; //Defining a handle variable

//char *msg = "Transmission has started!!!\n\r";
char buff[100];

int main(void) {
	HAL_Init();
	UART2_Init();
	strncpy(buff, "Transmission has started for PLL !!!!\r\n", 100);
	HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), HAL_MAX_DELAY);
	pll_config();

	UART2_Init();
    memset(buff,0,sizeof(buff));
    sprintf(buff,"HCLK after PLL : %ld Hz \r\n",HAL_RCC_GetHCLKFreq());
    HAL_UART_Transmit(&huart2, (uint8_t*) buff, strlen(buff), HAL_MAX_DELAY);
	while (1)
		;
	return 0;
}

void pll_config(void) {
	RCC_OscInitTypeDef osc_init;     //initialize a struct of RCC_OscInitTypeDef
	RCC_ClkInitTypeDef clk_init;     //initialize a struct of RCC_ClkInitTypeDef
	memset(&osc_init, 0, sizeof(osc_init));
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE; //setting the hse according to the task
	osc_init.HSEState = RCC_HSE_BYPASS;		//as per the datasheet
	osc_init.PLL.PLLState = RCC_PLL_ON;		//PLL is turned on
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;   //PLL is sourced from HSE
	osc_init.PLL.PLLM = 4;
	osc_init.PLL.PLLN = 84;
	osc_init.PLL.PLLP = RCC_PLLP_DIV2;

	if (HAL_RCC_OscConfig(&osc_init) != HAL_OK)
		errorHandler();

	clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK         \
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
	clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&clk_init, FLASH_ACR_LATENCY_2WS) != HAL_OK)
		errorHandler();

	__HAL_RCC_HSI_DISABLE();    //this will save some current

	/*Configuring the systick */

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}

void UART2_Init(void) {
	huart2.Instance = USART2;				//Linking handler to the peripheral
	huart2.Init.BaudRate = 115200;					//Setting up parameters
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if ((HAL_UART_Init(&huart2)) != HAL_OK)
		errorHandler();
}

void errorHandler(void) {
	while (1)
		;
}

