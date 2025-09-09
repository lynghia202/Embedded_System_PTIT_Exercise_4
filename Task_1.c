#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#define LED GPIO_Pin_0
void GPIO_Config(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef g;
	g.GPIO_Mode = GPIO_Mode_Out_PP;
	g.GPIO_Pin	=	LED;
	g.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&g);
}

void TIM_Config(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_TimeBaseInitTypeDef t;
	t.TIM_Prescaler = 7200 - 1;
	t.TIM_Period	=	10000 - 1;
	t.TIM_CounterMode =	TIM_CounterMode_Up;
	t.TIM_ClockDivision =	0;
	t.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &t);
}

void delay_1s(void){
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_SetCounter(TIM2, 0);
	TIM_Cmd(TIM2, ENABLE);
	while(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update) == 0);
	TIM_Cmd(TIM2,DISABLE);
}


int main (void){
	GPIO_Config();
	TIM_Config();
	while(1){
		GPIOA->ODR^=LED;
		delay_1s();
	}

}
