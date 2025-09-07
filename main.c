#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"

#define LED_1 GPIO_Pin_0

void GPIO_Config(void) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		GPIO_InitTypeDef gpio;
		gpio.GPIO_Pin = LED_1;
		gpio.GPIO_Mode = GPIO_Mode_Out_PP;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &gpio);
}

void TIM_Config(void) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		TIM_TimeBaseInitTypeDef tim;
		tim.TIM_Prescaler = 7200 - 1;
		tim.TIM_Period 		= 5000 - 1;
		tim.TIM_CounterMode = TIM_CounterMode_Up;
		tim.TIM_ClockDivision  = 0;
		tim.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM2,&tim);
			
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
		
		NVIC_InitTypeDef nvic;
		nvic.NVIC_IRQChannel = TIM2_IRQn;
		nvic.NVIC_IRQChannelPreemptionPriority = 0;
		nvic.NVIC_IRQChannelSubPriority = 0;
		nvic.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&nvic);
		
		TIM_Cmd(TIM2,ENABLE);
}

void TIM2_IRQHandler(void) {
		if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET){
				TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
				GPIOA ->ODR ^= LED_1;
}
		}

int main (void){
	GPIO_Config();
	TIM_Config();
	GPIO_ResetBits(GPIOA, LED_1);
	while(1){
		
	}
}
