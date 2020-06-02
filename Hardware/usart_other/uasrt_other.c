#include "all.h"

void USART3_Init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //使能USART3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能GPIOB时钟

	//USART3_TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//USART3_RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //PB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

	//USART3 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART3, &USART_InitStructure); //初始化串口3
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART3, ENABLE);                    //使能串口3

}

void USART3_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	static u8 Rec_flag=0;
	static u8 Rec_Buf[4]={1,1,1,1};
	static u8 count=0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART3);	//读取接收到的数据	 		 
    USART_SendData(USART1,Res);
		
		if(Res==')')Rec_flag=0,count=0;
		
		if(Rec_flag==1)
		{
		  Rec_Buf[count++]=Res;
			
			if(count==4)                //接收完一帧数据
			{
			  if((Rec_Buf[0]=='1')&&(Rec_Buf[1]=='1')&&(Rec_Buf[2]=='1')&&(Rec_Buf[3]=='1'))
				{Flag_Left=0,Flag_Right=0,Flag_Front=0,Flag_Back=0,Flag_Stop=1;}
				if((Rec_Buf[0]=='0')&&(Rec_Buf[1]=='1')&&(Rec_Buf[2]=='1')&&(Rec_Buf[3]=='1'))
				{Flag_Left=0,Flag_Right=0,Flag_Front=1,Flag_Back=0,Flag_Stop=0;}
				if((Rec_Buf[0]=='1')&&(Rec_Buf[1]=='0')&&(Rec_Buf[2]=='1')&&(Rec_Buf[3]=='1'))
				{Flag_Left=0,Flag_Right=0,Flag_Front=0,Flag_Back=1,Flag_Stop=0;}
				if((Rec_Buf[0]=='1')&&(Rec_Buf[1]=='1')&&(Rec_Buf[2]=='0')&&(Rec_Buf[3]=='1'))
				{Flag_Left=1,Flag_Right=0,Flag_Front=0,Flag_Back=0,Flag_Stop=0;}
				if((Rec_Buf[0]=='1')&&(Rec_Buf[1]=='1')&&(Rec_Buf[2]=='1')&&(Rec_Buf[3]=='0'))
				{Flag_Left=0,Flag_Right=1,Flag_Front=0,Flag_Back=0,Flag_Stop=0;}
			}
		}
		
		if(Res=='(')Rec_flag=1;
  } 
} 


