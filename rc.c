 #include<stdint.h>
 #include"stm32f4xx.h"
 #include"rc.h"
 
//		 uint8_t ch0_h:8; //!< Byte 0

//		 uint8_t ch0_l:3; //!< Byte 1
//		 uint8_t ch1_h:5;

//		 uint8_t ch1_l:6; //!< Byte 2
//		 uint8_t ch2_h:2;

//		 uint8_t ch2_m:8; //!< Byte 3

//		 uint8_t ch2_l:1; //!< Byte 4
//		 uint8_t ch3_h:7;

//		 uint8_t ch3_l:4; //!< Byte 5
//		 uint8_t ch4_h:4;
//			 
//		 uint8_t ch4_l:7; //!< Byte 6
//		 uint8_t ch5_h:1;
//			
//		 uint8_t ch5_m:8; //!< Byte 7
//			 
//		 uint8_t ch5_l:2; //!< Byte 8
//		 uint8_t ch6_h:6;	 
//			 
//		 uint8_t ch6_l:5; //!< Byte 9
//		 uint8_t ch7_h:3;
//		 
//		 uint8_t ch7_l:8; //!< Byte 10
//		 
//		 uint8_t ch8_h:8; //!< Byte 11
//		 
//		 uint8_t ch8_l:3; //!< Byte 12
//		 uint8_t ch9_h:5;
//		 
//		 uint8_t ch9_l:6; //!< Byte 13
//		 uint8_t ch10_h:2;
//		 
//		 uint8_t ch10_m:8; //!< Byte 14
//		 
//		 uint8_t ch10_l:1; //!< Byte 15
//		 uint8_t ch11_h:7;
//		 
//		 uint8_t ch11_l:4; //!< Byte 16
//		 uint8_t ch12_h:4;
//		 
//		 uint8_t ch12_l:7; //!< Byte 17
//		 uint8_t ch13_h:1;
//		 
//		 uint8_t ch13_m:8; //!< Byte 18
//		 
//		 uint8_t ch13_l:2; //!< Byte 19
//		 uint8_t ch14_h:6;
//		 
//		 uint8_t ch14_l:5; //!< Byte 20
//		 uint8_t ch15_h:3;
//		 
//		 uint8_t ch15_l:8; //!< Byte 21

/* ----------------------- RC Channel Definition---------------------------- */
#define RC_CH_VALUE_MIN ((uint16_t)364 )
#define RC_CH_VALUE_OFFSET ((uint16_t)1024)
#define RC_CH_VALUE_MAX ((uint16_t)1684)
/* ----------------------- RC Switch Definition----------------------------- */
#define RC_SW_UP ((uint16_t)1)
#define RC_SW_MID ((uint16_t)3)
#define RC_SW_DOWN ((uint16_t)2)
/* ----------------------- PC Key Definition-------------------------------- */
#define KEY_PRESSED_OFFSET_W ((uint16_t)0x01<<0)
#define KEY_PRESSED_OFFSET_S ((uint16_t)0x01<<1)
#define KEY_PRESSED_OFFSET_A ((uint16_t)0x01<<2)
#define KEY_PRESSED_OFFSET_D ((uint16_t)0x01<<3)
#define KEY_PRESSED_OFFSET_Q ((uint16_t)0x01<<4)
#define KEY_PRESSED_OFFSET_E ((uint16_t)0x01<<5)
#define KEY_PRESSED_OFFSET_SHIFT ((uint16_t)0x01<<6)
#define KEY_PRESSED_OFFSET_CTRL ((uint16_t)0x01<<7)
/* ----------------------- Data Struct ------------------------------------- */


/* ----------------------- Internal Data ----------------------------------- */
volatile unsigned char sbus_rx_buffer[25];
extern u16 ch[15];


//static RC_Ctl_t RC_Ctl;
/* ------------------------------------------------------------------------- */

/* ----------------------- Function Implements ---------------------------- */
/******************************************************************************
* @fn RC_Init
*
* @brief configure stm32 usart2 port
* - USART Parameters
* - 100Kbps
* - 8-N-1
* - DMA Mode
*
* @return None.
*
* @note This code is fully tested on STM32F405RGT6 Platform, You can port it
* to the other platform.
*/
//u8 t;
//u8 Speed[]={0x55,0x56,0,0,0x00,0x00,0x00,0x00,0x00,0x00};
//		
//int pwml,pwmr,temppwm;
//	
//void SendSpeed()
//{


//	
//pwml=(int)(10000.0*(((double)ch[2]+(1024-(double)ch[3])-352)/1344.0)-5000.0);
//pwmr=(int)(10000.0*(((double)ch[2]+((double)ch[3]-1024)-352)/1344.0)-5000.0);



//if(pwml>5000)pwml=5000;
//if(pwmr>5000)pwmr=5000;	
//if(pwml<-5000)pwml=-5000;
//if(pwmr<-5000)pwmr=-5000;


//temppwm=pwml;	
//Speed[2] = (unsigned char)((temppwm>>8)&0xff);
//Speed[3] = (unsigned char)(pwml&0xff);

//   for(t=0;t<10;t++)//l
//			{
//				USART_SendData(USART3,Speed[t]);         //向串口1发送数据
//		  	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
//			}
//temppwm=pwmr;				
//Speed[2] = (unsigned char)((temppwm>>8)&0xff);
//Speed[3] = (unsigned char)(pwmr&0xff);
//			
//	 for(t=0;t<10;t++)//r
//		 {
//		  	USART_SendData(UART4,Speed[t]);         //向串口1发送数据
//	    	while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);//等待发送结束
//		 }

//}

void RC_Init(void)
{
/* -------------- Enable Module Clock Source ----------------------------*/
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_DMA1, ENABLE);//串口2 a3 接收机
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
GPIO_PinAFConfig(GPIOA,GPIO_PinSource3, GPIO_AF_USART2);
	
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//串口3 b10 左轮
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
GPIO_PinAFConfig(GPIOB,GPIO_PinSource10, GPIO_AF_USART3);
	
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//串口4 c10 右轮
RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
GPIO_PinAFConfig(GPIOC,GPIO_PinSource10, GPIO_AF_UART4);
	
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//串口1 a9 舵机
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
GPIO_PinAFConfig(GPIOA,GPIO_PinSource9, GPIO_AF_USART1);
/* -------------- Configure GPIO ---------------------------------------*/
{

	
GPIO_InitTypeDef gpio;                                        //u2
USART_InitTypeDef usart2;
	
gpio.GPIO_Pin = GPIO_Pin_3 ;
gpio.GPIO_Mode = GPIO_Mode_AF;
gpio.GPIO_OType = GPIO_OType_PP;
gpio.GPIO_Speed = GPIO_Speed_100MHz;
gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOA, &gpio);
	
USART_DeInit(USART2);
usart2.USART_BaudRate = 100000;
usart2.USART_WordLength = USART_WordLength_8b;
usart2.USART_StopBits = USART_StopBits_2;
usart2.USART_Parity = USART_Parity_Even;
usart2.USART_Mode = USART_Mode_Rx;
usart2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	



USART_Init(USART2,&usart2);
USART_Cmd(USART2,ENABLE);
USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);


}

{
GPIO_InitTypeDef gpio1;                                       // u3 B10
USART_InitTypeDef usart3;
	
gpio1.GPIO_Pin = GPIO_Pin_10 ;
gpio1.GPIO_Mode = GPIO_Mode_AF;
gpio1.GPIO_OType = GPIO_OType_PP;
gpio1.GPIO_Speed = GPIO_Speed_100MHz;
gpio1.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOB, &gpio1);
	
USART_DeInit(USART3);
usart3.USART_BaudRate = 115200;
usart3.USART_WordLength = USART_WordLength_8b;
usart3.USART_StopBits = USART_StopBits_1;
usart3.USART_Parity = USART_Parity_No;
usart3.USART_Mode = USART_Mode_Tx;
usart3.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

USART_Init(USART3,&usart3);
USART_Cmd(USART3,ENABLE);
USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
}

{
GPIO_InitTypeDef gpio2;                                       // u4 c10
USART_InitTypeDef uart4;
	
gpio2.GPIO_Pin = GPIO_Pin_10 ;
gpio2.GPIO_Mode = GPIO_Mode_AF;
gpio2.GPIO_OType = GPIO_OType_PP;
gpio2.GPIO_Speed = GPIO_Speed_100MHz;
gpio2.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(GPIOC, &gpio2);
	
USART_DeInit(UART4);
uart4.USART_BaudRate = 115200;
uart4.USART_WordLength = USART_WordLength_8b;
uart4.USART_StopBits = USART_StopBits_1;
uart4.USART_Parity = USART_Parity_No;
uart4.USART_Mode = USART_Mode_Tx;
uart4.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

USART_Init(UART4,&uart4);
USART_Cmd(UART4,ENABLE);
USART_DMACmd(UART4,USART_DMAReq_Tx,ENABLE);
}

{
GPIO_InitTypeDef gpio3;                                       // u1 a9
USART_InitTypeDef uart1;
	
gpio3.GPIO_Pin = GPIO_Pin_9 ;
gpio3.GPIO_Mode = GPIO_Mode_AF;
gpio3.GPIO_OType = GPIO_OType_PP;
gpio3.GPIO_Speed = GPIO_Speed_100MHz;
gpio3.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(GPIOA, &gpio3);
	
USART_DeInit(USART1);
uart1.USART_BaudRate = 115200;
uart1.USART_WordLength = USART_WordLength_8b;
uart1.USART_StopBits = USART_StopBits_1;
uart1.USART_Parity = USART_Parity_No;
uart1.USART_Mode = USART_Mode_Tx;
uart1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

USART_Init(USART1,&uart1);
USART_Cmd(USART1,ENABLE);
USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
}
/* -------------- Configure NVIC ---------------------------------------*/
{
NVIC_InitTypeDef nvic;
nvic.NVIC_IRQChannel = DMA1_Stream5_IRQn;
nvic.NVIC_IRQChannelPreemptionPriority = 1;
nvic.NVIC_IRQChannelSubPriority = 1;
nvic.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&nvic);
}
/* -------------- Configure DMA -----------------------------------------*/
{
DMA_InitTypeDef dma;
DMA_DeInit(DMA1_Stream5);
dma.DMA_Channel = DMA_Channel_4;
dma.DMA_PeripheralBaseAddr = (uint32_t)&(USART2->DR);
dma.DMA_Memory0BaseAddr = (uint32_t)sbus_rx_buffer;
dma.DMA_DIR = DMA_DIR_PeripheralToMemory;
dma.DMA_BufferSize = 25
	
	
	
	
	
	 ;
dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
dma.DMA_Mode = DMA_Mode_Circular;
dma.DMA_Priority = DMA_Priority_VeryHigh;
dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
dma.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
dma.DMA_MemoryBurst = DMA_Mode_Normal;
dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
DMA_Init(DMA1_Stream5,&dma);
DMA_ITConfig(DMA1_Stream5,DMA_IT_TC,ENABLE);
DMA_Cmd(DMA1_Stream5,ENABLE);
}
}
/******************************************************************************
* @fn DMA1_Stream5_IRQHandler
*
* @brief USART2 DMA ISR
*
* @return None.
*
* @note This code is fully tested on STM32F405RGT6 Platform, You can port it
* to the other platform.
*/
void DMA1_Stream5_IRQHandler(void)
{
if(DMA_GetITStatus(DMA1_Stream5, DMA_IT_TCIF5))
{
DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF5);
DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF5);
ch[0] = (sbus_rx_buffer[1]| (sbus_rx_buffer[2] << 8)) & 0x07ff; 
ch[1] = ((sbus_rx_buffer[2] >> 3) | (sbus_rx_buffer[3] << 5)) & 0x07ff; 
ch[2] = ((sbus_rx_buffer[3] >> 6) | (sbus_rx_buffer[4] << 2) |(sbus_rx_buffer[5] << 10)) & 0x07ff; 
ch[3] = ((sbus_rx_buffer[5] >> 1) | (sbus_rx_buffer[6] << 7)) & 0x07ff; 
ch[4] = ((sbus_rx_buffer[6] >> 4) | (sbus_rx_buffer[7] << 4)) & 0x07ff; 
ch[5] = ((sbus_rx_buffer[7] >> 7) | (sbus_rx_buffer[8] << 1) |(sbus_rx_buffer[9] << 9)) & 0x07ff;
ch[6] = ((sbus_rx_buffer[9] >> 2) | (sbus_rx_buffer[10] << 6)) & 0x07ff; 
ch[7] = ((sbus_rx_buffer[10] >> 5) | (sbus_rx_buffer[11] << 3)) & 0x07ff;
ch[12]= sbus_rx_buffer[23] & 1;
ch[13]= sbus_rx_buffer[23] >> 1;
	
if(sbus_rx_buffer[13]==1)ch[8]=1;
if(sbus_rx_buffer[13]==4)ch[8]=2;
if(sbus_rx_buffer[13]==6)ch[8]=3;

if(sbus_rx_buffer[14]==11)ch[9]=1;
if(sbus_rx_buffer[14]==32)ch[9]=2;
if(sbus_rx_buffer[14]==53)ch[9]=3;	
	
if(sbus_rx_buffer[15]==88)ch[10]=1;
if(sbus_rx_buffer[15]==0)ch[10]=2;
if(sbus_rx_buffer[15]==168)ch[10]=3;

if(sbus_rx_buffer[17]==2)ch[11]=1;
if(sbus_rx_buffer[17]==8)ch[11]=2;
if(sbus_rx_buffer[17]==13)ch[11]=3;



}
}
