#include"stm32f4xx.h"
#include"led.h"
#include"rc.h"
#include"stdio.h"

#include"delay.h" 



u8 Reset[]={0x55,0x55,0x55,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
u8 PwmMode[]={0x55,0x56,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
u8 Speed[]={0x55,0x56,0,0,0x00,0x00,0x00,0x00,0x00,0x00};
char hander[50];

 u16 ch[15];
 u8 t,safetemp=99;
 int pwml,pwmr,pwmtemp,hander0=1350,hander1,hander2=500,hander3,hander4;


///////////////////      init        ////////////////////////////////////////////////////////////////
void InitWheel() 
{  
   for(t=0;t<11;t++)//l
			{
				USART_SendData(USART3,Reset[t]);         //向串口3发送数据
		  	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
			}
//	 delay_ms(1000);
			
	 for(t=0;t<11;t++)//r
		 {
		  	USART_SendData(UART4,Reset[t]);         //向串口4发送数据
	    	while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);//等待发送结束
		 }
		 
		 delay_ms(1000);
		 


		 
		    for(t=0;t<10;t++)//l
			{
				USART_SendData(USART3,PwmMode[t]);         //向串口3发送数据
		  	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
			}
//	 		 delay_ms(1000);
	 for(t=0;t<10;t++)//r
		 {
		  	USART_SendData(UART4,PwmMode[t]);         //向串口4发送数据
	    	while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);//等待发送结束
		 }
		 
//		  delay_ms(1000);
}
///////////////////      mode 1      ////////////////////////////////////////////////////////////////
void ManualHanderMode1()
{

while(safetemp==99)             //安全归位判断
{
if(ch[4]==352&&ch[6]==1024)safetemp=1;
}	

if((ch[0]-1024)>10||(ch[0]-1024)<-10)hander0+=(int)(((double)ch[0]-1024)/40.0);
	if(hander0>2150)hander0=2150;
	if(hander0<500)hander0=500;
if((ch[1]-1024)>3||(ch[1]-1024)<-3)hander2-=(int)(((double)ch[1]-1024)/(60.0));
	if(hander2>2150)hander2=2150;
	if(hander2<575)hander2=575;
hander1=(int)(((double)(ch[4]-352)/1344.0)*(-1600.0)+2100);
hander3=(int)(((double)(ch[6]-352)/1344.0)*(-1650.0)+2150);
hander4=(int)(((double)(ch[5]-352)/1344.0)*(680.0)+1250);

sprintf(hander,"#0 P%d #1 P%d #2 P%d #3 P%d #4 P%d \r\n",hander0,hander1,hander2,hander3,hander4);
	
   for(t=0;t<50;t++)//l
			{
				USART_SendData(USART1,hander[t]);         //向串口1发送数据
		  	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
				if(hander[t]=='n')t=50;
			}

}



void SendSpeedMode1()
{

int temppwm;
	
pwml=(int)(10000.0*(((double)ch[2]+(1024-(double)ch[3])-352)/1344.0)-5000.0);
pwmr=(int)(10000.0*(((double)ch[2]+((double)ch[3]-1024)-352)/1344.0)-5000.0);



if(pwml>5000)pwml=5000;
if(pwmr>5000)pwmr=5000;	
if(pwml<-5000)pwml=-5000;
if(pwmr<-5000)pwmr=-5000;


temppwm=pwml;	
Speed[2] = (unsigned char)((temppwm>>8)&0xff);
Speed[3] = (unsigned char)(pwml&0xff);

   for(t=0;t<10;t++)//l
			{
				USART_SendData(USART3,Speed[t]);         //向串口1发送数据
		  	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
			}
temppwm=pwmr;				
Speed[2] = (unsigned char)((temppwm>>8)&0xff);
Speed[3] = (unsigned char)(pwmr&0xff);
			
	 for(t=0;t<10;t++)//r
		 {
		  	USART_SendData(UART4,Speed[t]);         //向串口1发送数据
	    	while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);//等待发送结束
		 }
}




///////////////////      mode2       ////////////////////////////////////////////////////////////////
void SendSpeedMode2()
{

int temppwm;
	
pwml=-(int)(10000.0*((double)((((double)ch[6]-1696.0)+(1024.0-(double)ch[7]))/1344.0))+5000.0);
pwmr=-(int)(10000.0*((double)(((double)(ch[6]-1696.0)+((double)ch[7]-1024))/1344.0))+5000.0);



if(pwml>5000)pwml=5000;
if(pwmr>5000)pwmr=5000;	
if(pwml<-5000)pwml=-5000;
if(pwmr<-5000)pwmr=-5000;


temppwm=pwml;	
Speed[2] = (unsigned char)((temppwm>>8)&0xff);
Speed[3] = (unsigned char)(pwml&0xff);

   for(t=0;t<10;t++)//l
			{
				USART_SendData(USART3,Speed[t]);         //向串口1发送数据
		  	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
			}
temppwm=pwmr;				
Speed[2] = (unsigned char)((temppwm>>8)&0xff);
Speed[3] = (unsigned char)(pwmr&0xff);
			
	 for(t=0;t<10;t++)//r
		 {
		  	USART_SendData(UART4,Speed[t]);         //向串口1发送数据
	    	while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);//等待发送结束
		 }
}

void ManualHanderMode2()
{

while(safetemp==99)             //安全归位判断
{
  hander0=1350;
	hander1=2100;
	hander2=575;
	hander3=1350;
  safetemp=2;
}	

if((ch[3]-1024)>20||(ch[3]-1024)<-20)hander3+=(int)(((double)ch[3]-1024)/30.0);
	if(hander3>2150)hander3=2150;
	if(hander3<500)hander3=500;

if((ch[1]-1024)>3||(ch[1]-1024)<-3)hander2-=(int)(((double)ch[1]-1024)/(60.0));
	if(hander2>2150)hander2=2150;
	if(hander2<575)hander2=575;

if((ch[0]-1024)>20||(ch[0]-1024)<-20)hander0+=(int)(((double)ch[0]-1024)/40.0);
	if(hander0>2150)hander0=2150;
	if(hander0<500)hander0=500;

if((ch[2]-1024)>3||(ch[2]-1024)<-3)hander1+=(int)(((double)ch[2]-1024)/(60.0));
	if(hander1>2100)hander1=2100;
	if(hander1<500)hander1=500;

hander4=(int)(((double)(ch[5]-352)/1344.0)*(680.0)+1250);

sprintf(hander,"#0 P%d #1 P%d #2 P%d #3 P%d #4 P%d \r\n",hander0,hander1,hander2,hander3,hander4);
	
   for(t=0;t<50;t++)//l
			{
				USART_SendData(USART1,hander[t]);         //向串口1发送数据
		  	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
				if(hander[t]=='n')t=50;
			}

}


////////////////////     mode3       /////////////////////////////////////////////////////////////////
void ManualHanderMode3()
{

while(safetemp==99)             //安全归位判断
{
  hander0=1350;
	hander1=2100;
	hander2=575;
	hander3=1350;
  safetemp=2;
}	



if((ch[0]-1024)>20||(ch[0]-1024)<-20)hander0+=(int)(((double)ch[0]-1024)/40.0);
	if(hander0>2150)hander0=2150;
	if(hander0<500)hander0=500;

if((ch[1]-1024)>3||(ch[1]-1024)<-3)hander2-=(int)(((double)ch[1]-1024)/(60.0));
	if(hander2>2150)hander2=2150;
	if(hander2<575)hander2=575;

hander4=(int)(((double)(ch[5]-352)/1344.0)*(680.0)+1250);

sprintf(hander,"#0 P%d #1 P%d #2 P%d #3 P%d #4 P%d \r\n",hander0,hander1,hander2,hander3,hander4);
	
   for(t=0;t<50;t++)//l
			{
				USART_SendData(USART1,hander[t]);         //向串口1发送数据
		  	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
				if(hander[t]=='n')t=50;
			}

}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void led()
{
if(ch[10]==2)GPIO_ResetBits(GPIOC,GPIO_Pin_9|GPIO_Pin_7);
if(ch[10]==1)GPIO_SetBits(GPIOC,GPIO_Pin_9);
if(ch[10]==3)GPIO_SetBits(GPIOC,GPIO_Pin_9|GPIO_Pin_7);
}
int main(void)
{
  delay_init(168);
  RC_Init(); 
  delay_ms(1000);
	InitWheel();
	LED_Init(); 
	
	while(1)
{

while(ch[8]==1)   //行车模式
{
SendSpeedMode1();
ManualHanderMode1();
led();
delay_ms(10);
}	

while(ch[8]==2)   //手臂模式
{
SendSpeedMode2();
ManualHanderMode2();
if(ch[13]==1)safetemp=99;
led();
delay_ms(10);
}

while(ch[8]==3)   //行车 保持手臂
{
SendSpeedMode1();
ManualHanderMode3();
if(ch[13]==1)safetemp=99;
led();
delay_ms(10);
	
}


}


	
	 
	
	


}
