#include "sys.h"
#include "usart.h"	
uint16_t res_data[5];
uint16_t temp_data;
int res_flag;
void usart_Init(int baud)
{
	GPIO_InitTypeDef GPIO_Initstructure;
	USART_InitTypeDef USART1_Initstructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);

	
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_Initstructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Initstructure.GPIO_OType = GPIO_OType_PP;
	
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	//��������
	
	
	USART1_Initstructure.USART_BaudRate = baud;
	USART1_Initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART1_Initstructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART1_Initstructure.USART_Parity = USART_Parity_No;
	USART1_Initstructure.USART_StopBits = USART_StopBits_1;
	USART1_Initstructure.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1,&USART1_Initstructure);
	
	/*
	
	 中断配置
	*/
	//开启相关中断
		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_Init(&NVIC_InitStructure);
	
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(USART1,ENABLE);






}
//中断服务函数
void USART_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		temp_data=USART_ReceiveData(USART1);
		res_data[res_flag]=temp_data;
		res_flag++;
	}
	if(res_flag==5)
	{
		res_flag=0;
	}
}