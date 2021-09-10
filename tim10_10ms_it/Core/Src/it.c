/*
 * it.c
 *
 *  Created on: Sep 1, 2021
 *      Author: root
 */

#include "main.h"


void SysTick_Handler (void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void USART2_IRQHandler (void)
{
	HAL_UART_IRQHandler(&huart2);
}
