#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx.h>
#include <stm32f4xx_tim.h>

#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx.h>
#include <stm32f4xx_tim.h>


void initialise_leds()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_12;//|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIOInitStruct.GPIO_OType = GPIO_OType_PP;
	GPIOInitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIOInitStruct);
}





void TM_LEDS_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;

    /* Clock for GPIOD */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    /* Alternating functions for pins */
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
    /*GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

    /* Set pins */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 ;//| GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
}





void TM_PWM_Init_1(void) {
    TIM_OCInitTypeDef TIM_OCStruct;

    /* Common settings */

    /* PWM mode 2 = Clear on compare match */
    /* PWM mode 1 = Set on compare match */
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;

/*
    To get proper duty cycle, you have simple equation

    pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 - 1

    where DutyCycle is in percent, between 0 and 100%

    25% duty cycle:     pulse_length = ((8399 + 1) * 25) / 100 - 1 = 2099
    50% duty cycle:     pulse_length = ((8399 + 1) * 50) / 100 - 1 = 4199
    75% duty cycle:     pulse_length = ((8399 + 1) * 75) / 100 - 1 = 6299
    100% duty cycle:    pulse_length = ((8399 + 1) * 100) / 100 - 1 = 8399

    Remember: if pulse_length is larger than TIM_Period, you will have output HIGH all the time
*/

    TIM_OCStruct.TIM_Pulse = 1599; //8399 //2099; /* 25% duty cycle */
    TIM_OC1Init(TIM4, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

}







void TM_PWM_Init(void) {
    TIM_OCInitTypeDef TIM_OCStruct;

    /* Common settings */

    /* PWM mode 2 = Clear on compare match */
    /* PWM mode 1 = Set on compare match */
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;

/*
    To get proper duty cycle, you have simple equation
    My TIM_PERIOD = 3199

    pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 - 1

    where DutyCycle is in percent, between 0 and 100%

    25% duty cycle:     pulse_length = ((8399 + 1) * 25) / 100 - 1 = 2099
    50% duty cycle:     pulse_length = ((8399 + 1) * 50) / 100 - 1 = 4199
    75% duty cycle:     pulse_length = ((8399 + 1) * 75) / 100 - 1 = 6299
    100% duty cycle:    pulse_length = ((8399 + 1) * 100) / 100 - 1 = 8399

    Remember: if pulse_length is larger than TIM_Period, you will have output HIGH all the time
*/  static int i=0;
	++i;
    TIM_OCStruct.TIM_Pulse = 399;	//My TIM_PERIOD = 3199  , 160->90+, 0==239 /* 25% duty cycle */
    TIM_OC1Init(TIM4, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

    /*TIM_OCStruct.TIM_Pulse = 1599; /* 50% duty cycle */
    /*TIM_OC2Init(TIM4, &TIM_OCStruct);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_OCStruct.TIM_Pulse = 2399; /* 75% duty cycle */
    /*TIM_OC3Init(TIM4, &TIM_OCStruct);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_OCStruct.TIM_Pulse = 3199; /* 100% duty cycle */
    /*TIM_OC4Init(TIM4, &TIM_OCStruct);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	*/

}







void TIMERInit(void){


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitTypeDef TimerStruct;
	//timer_tick_frequency = Timer_default_frequency / (prescaller_set + 1)
	TimerStruct.TIM_Prescaler=99;  //timer_tick_frequency = 160000
	TimerStruct.TIM_CounterMode=TIM_CounterMode_Up;
	//PWM_frequency = timer_tick_frequency / (TIM_Period + 1)
	//TIM_Period = timer_tick_frequency / PWM_frequency - 1
	//	timer_tick_frequency = Timer_default_frequency / (prescaller_set + 1)
	TimerStruct.TIM_Period= 3199 ;//50Hz       //8399;  //10kHz PWM
	TimerStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TimerStruct.TIM_RepetitionCounter = 0;
    /* Initialize TIM4 */
    TIM_TimeBaseInit(TIM4, &TimerStruct);
    /* Start count on TIM4 */
    TIM_Cmd(TIM4, ENABLE);
}






int main(void)
{
	TM_LEDS_Init();
	TIMERInit();
	TM_PWM_Init();

	/*TIM_TimeBaseInitTypeDef SetupTimer;
	/* Enable timer 2, using the Reset and Clock Control register */
	/*RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// Get the clock frequencies
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);

	SetupTimer.TIM_Prescaler = (RCC_Clocks.PCLK2_Frequency/10000) - 1; // Prescale to 1Mhz
	SetupTimer.TIM_CounterMode = TIM_CounterMode_Up;
	SetupTimer.TIM_Period = 10000;
	SetupTimer.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &SetupTimer);
	TIM_Cmd(TIM2, ENABLE); // start counting by enabling CEN in CR1 */
	/*/**//**//**/

	/*RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitTypeDef TimerStruct;
	//timer_tick_frequency = Timer_default_frequency / (prescaller_set + 1)
	TimerStruct.TIM_Prescaler=99;  //timer_tick_frequency = 160000
	TimerStruct.TIM_CounterMode=TIM_CounterMode_Up;
	//PWM_frequency = timer_tick_frequency / (TIM_Period + 1)
	//TIM_Period = timer_tick_frequency / PWM_frequency - 1
	//	timer_tick_frequency = Timer_default_frequency / (prescaller_set + 1)
	TimerStruct.TIM_Period= 3199 ;//50Hz       //8399;  //10kHz PWM
	TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_BaseStruct.TIM_RepetitionCounter = 0;
    /* Initialize TIM4 */
    /*TIM_TimeBaseInit(TIM4, &TIM_BaseStruct);
    /* Start count on TIM4 */
    /*TIM_Cmd(TIM4, ENABLE);
	*/


	//int count = 0;

	while(1){

	}

}

	/*count = TIM_GetCounter(TIM2);
	if (count >= 1000){
		 GPIO_SetBits(GPIOD, GPIO_Pin_12);
	}

	if (count >= 2000){
			 GPIO_SetBits(GPIOD, GPIO_Pin_14);
		}
	if (count >= 3000){
			 GPIO_SetBits(GPIOD, GPIO_Pin_13);
		}
	if (count >= 4000){
			 GPIO_SetBits(GPIOD, GPIO_Pin_15);
		}
	if (count >= 5000){
		 GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	}

	if (count >= 6000){
			 GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		}
	if (count >= 7000){
			 GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		}
	if (count >= 8000){
			 GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		}
	}
}
*/


/*
int main(void)
{


	GPIO_TypeDef *GPIOD

	void  GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct)




    while(1)
    {
    }
}
*/
