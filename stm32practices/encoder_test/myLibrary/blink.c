#include "stdio.h"
#include "stm32f1xx_hal.h"

void blink(void){
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1);
	HAL_Delay(300);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,0);
	HAL_Delay(200);

}
