#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_adc.h"

volatile uint16_t a,b;

void uart_init(void)
{
RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
USART_InitTypeDef rx;
rx.USART_BaudRate=9600;
rx.USART_Mode=USART_Mode_Rx;
rx.USART_Parity=USART_Parity_No;
rx.USART_StopBits=USART_StopBits_1;
rx.USART_WordLength=USART_WordLength_8b;
rx.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
USART_Init(UART4,&rx);
USART_Cmd(UART4,ENABLE);

USART_InitTypeDef tx;
tx.USART_BaudRate=9600;
tx.USART_Mode=USART_Mode_Tx;
tx.USART_Parity=USART_Parity_No;
tx.USART_StopBits=USART_StopBits_1;
tx.USART_WordLength=USART_WordLength_8b;
tx.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
USART_Init(UART5,&tx);
USART_Cmd(UART5,ENABLE);
}
void gpio_init()
{
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
GPIO_InitTypeDef new;
new.GPIO_Mode=GPIO_Mode_AF;
new.GPIO_OType=GPIO_OType_PP;
new.GPIO_PuPd=GPIO_PuPd_NOPULL;
new.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_11;
new.GPIO_Speed=GPIO_Speed_25MHz;

GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5);
GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4);
GPIO_Init(GPIOC,&new);
}
void user()
{
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
GPIO_InitTypeDef input;
input.GPIO_Mode=GPIO_Mode_IN;
input.GPIO_OType=GPIO_OType_PP;
input.GPIO_Speed=GPIO_Speed_50MHz;
input.GPIO_PuPd=GPIO_PuPd_NOPULL;
input.GPIO_Pin=GPIO_Pin_0;
GPIO_Init(GPIOA,&input);
}
/*void init_tim4(void)
{
	TIM_TimeBaseInitTypeDef SetupTimer;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

		// Get the clock frequencies
		RCC_ClocksTypeDef RCC_Clocks;
		RCC_GetClocksFreq(&RCC_Clocks);

		SetupTimer.TIM_Prescaler = (RCC_Clocks.PCLK2_Frequency/10000) - 1;
		SetupTimer.TIM_CounterMode = TIM_CounterMode_Up;
		SetupTimer.TIM_Period = 256-1;
		SetupTimer.TIM_ClockDivision = TIM_CKD_DIV1;

		TIM_TimeBaseInit(TIM4, &SetupTimer);
		TIM_Cmd(TIM4, ENABLE);


}*/
/*void init_pwm(uint16_t p)
{

	TIM_OCInitTypeDef oc4;
	oc4.TIM_OCMode=TIM_OCMode_PWM1;
	oc4.TIM_OCPolarity=TIM_OCPolarity_High;
	oc4.TIM_OutputState=TIM_OutputState_Enable;
	oc4.TIM_Pulse= a;
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC1Init(TIM4,&oc4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
}*/
void init_gpio()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	GPIO_InitTypeDef pwm;
	pwm.GPIO_Mode=GPIO_Mode_OUT;
	pwm.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;
	pwm.GPIO_OType=GPIO_OType_PP;
	pwm.GPIO_PuPd=GPIO_PuPd_NOPULL;
	pwm.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&pwm);

}
void adc_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	  GPIO_InitTypeDef GPIO_InitStructure;



	  //for ADC1 on PC0 using IN10
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  ADC_InitTypeDef       ADC_InitStructure;
	  ADC_InitStructure.ADC_Resolution = ADC_Resolution_8b;
	  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	  ADC_InitStructure.ADC_NbrOfConversion = 1;
	  ADC_Init(ADC1,&ADC_InitStructure);
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_84Cycles);
	  ADC_Cmd(ADC1, ENABLE);    //The ADC is powered on by setting the ADON bit in the ADC_CR2 register.

}





int main(void)
{init_gpio();
 uart_init();
 gpio_init();
 //init_tim4();
 user(); //**
 adc_init();

  USART_ClearFlag(UART5,USART_FLAG_TXE);
  USART_ClearFlag(UART4,USART_FLAG_RXNE);
  GPIO_ResetBits(GPIOD,GPIO_Pin_13);
  a=0;
int c=0;
	while(1)
    {
		ADC_SoftwareStartConv(ADC1);
	  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	  b=ADC_GetConversionValue(ADC1);

    	USART_SendData(UART5,b);
    	while(USART_GetFlagStatus(UART5,USART_FLAG_TXE)==RESET);
   //   GPIO_ResetBits(GPIOD,GPIO_Pin_13);
   	    USART_ClearFlag(UART5,USART_FLAG_TXE);
    	while(USART_GetFlagStatus(UART4,USART_FLAG_RXNE)==RESET);
  //	GPIO_ResetBits(GPIOD,GPIO_Pin_13);

			a=USART_ReceiveData(UART4);
			if(a<=250)
			{
				GPIO_ResetBits(GPIOD,GPIO_Pin_13);
			}
			else
			{
				GPIO_SetBits(GPIOD,GPIO_Pin_13);
			}if(a<=80)
			{
				GPIO_ResetBits(GPIOD,GPIO_Pin_12);
			}
			else
			{
				GPIO_SetBits(GPIOD,GPIO_Pin_12);
			}if(a<=120)
			{
				GPIO_ResetBits(GPIOD,GPIO_Pin_14);
			}
			else
			{
				GPIO_SetBits(GPIOD,GPIO_Pin_14);
			}if(a<=175)
			{
				GPIO_ResetBits(GPIOD,GPIO_Pin_15);
			}
			else
			{
				GPIO_SetBits(GPIOD,GPIO_Pin_15);
			}

			USART_ClearFlag(UART4,USART_FLAG_RXNE);

	    	USART_ClearFlag(UART5,USART_FLAG_TXE);
			c++;

    }
}
