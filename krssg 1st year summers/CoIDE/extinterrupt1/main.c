#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include <stm32f4xx_tim.h>

void initialise_leds()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;//|GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIOInitStruct.GPIO_OType = GPIO_OType_PP;
	GPIOInitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIOInitStruct);
}



void Configure_PA0(void) {
    /* Set variables used */
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef extistruct;//EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    /* Enable clock for GPIOD */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    /* Enable clock for SYSCFG */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* Set pin as input */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;	//PuPd_DOWN  NOPULL
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Tell system that you will use PD0 for EXTI_Line0 */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

    /* PD0 is connected to EXTI_Line0 */
    extistruct.EXTI_Line = EXTI_Line0;
    /* Enable interrupt */
    extistruct.EXTI_LineCmd = ENABLE;
    /* Interrupt mode */
    extistruct.EXTI_Mode = EXTI_Mode_Interrupt;
    /* Triggers on rising and falling edge */
    extistruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    /* Add to EXTI */
    EXTI_Init(&extistruct);

    /* Add IRQ vector to NVIC */
    /* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    /* Set priority */
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    /* Set sub priority */
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
    /* Enable interrupt */
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    /* Add to NVIC */
    NVIC_Init(&NVIC_InitStruct);
}


/* Set interrupt handlers */
/* Handle PD0 interrupt */
void EXTI0_IRQHandler(void) {
    /* Make sure that interrupt flag is set */
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        /* Do your stuff when PD0 is changed */
    	GPIO_ToggleBits(GPIOD,GPIO_Pin_13);







    	static int j=0;
    	j++;
    	//TM_PWM_Init(j);

    	TIM_OCInitTypeDef TIM_OCStruct;

   	    /* Common settings */

   	    /* PWM mode 2 = Clear on compare match */
   	    /* PWM mode 1 = Set on compare match */
   	    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
   	    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
   	    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
   	    int x;
   	    /*switch(j%3)
   	    {
   	    case 0:
   	    	x=115;
   	    	break;
   	    case 1:
   	    	x=399;
   	    	break;
   	    case 2:
   	       	x=659;
   	    	break;

   	    }*/


   	    x = (j%6)*8;

   	    //int x=((80 + j*160)%480)-1;
   	    TIM_OCStruct.TIM_Pulse = x;//My TIM_PERIOD = 3199 /* 25% duty cycle */
 	    TIM_OC1Init(TIM4, &TIM_OCStruct);
   	    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);




        /* Clear interrupt flag */
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
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



void TIMERInit(void){


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitTypeDef TimerStruct;
	//timer_tick_frequency = Timer_default_frequency / (prescaller_set + 1)
	TimerStruct.TIM_Prescaler=1599;//99;  //timer_tick_frequency = 160000
	TimerStruct.TIM_CounterMode=TIM_CounterMode_Up;
	//PWM_frequency = timer_tick_frequency / (TIM_Period + 1)
	//TIM_Period = timer_tick_frequency / PWM_frequency - 1
	//	timer_tick_frequency = Timer_default_frequency / (prescaller_set + 1)
	TimerStruct.TIM_Period= 200;//3199 ;//50Hz       //8399;  //10kHz PWM
	TimerStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TimerStruct.TIM_RepetitionCounter = 0;
    /* Initialize TIM4 */
    TIM_TimeBaseInit(TIM4, &TimerStruct);
    /* Start count on TIM4 */
    TIM_Cmd(TIM4, ENABLE);
}






void TM_PWM_Init(int i) {
    TIM_OCInitTypeDef TIM_OCStruct;

    /* Common settings */

    /* PWM mode 2 = Clear on compare match */
    /* PWM mode 1 = Set on compare match */
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;





    //int x=((239 + i*160)%400);
    TIM_OCStruct.TIM_Pulse = 239;//My TIM_PERIOD = 3199 /* 25% duty cycle */
    TIM_OC1Init(TIM4, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

}






int main(void) {
    /* System init */
    SystemInit();
    initialise_leds();



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





    TIMERInit();
    //TM_PWM_Init(1);

    /* Configure PD0 as interrupt */
    Configure_PA0();


    while (1) {

    }
}
