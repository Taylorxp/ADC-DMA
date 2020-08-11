#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "adc.h"
#include "dma.h"
 
/************************************************
 ALIENTEK 战舰STM32F103开发板实验17
 六路ADC+DMA传输 实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
#define ADC1_DR_Address    ((uint32_t)0x4001244C)
u16 AD_Value[6];    
float volta[6];
u8 i;

 
int main(void)
{
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为115200
	MYDMA_Config(DMA1_Channel1,(u32)ADC1_DR_Address,(u32)&AD_Value,6);//cndtr对应所开信道个数
	Adc_Init();
	DMA_Cmd(DMA1_Channel1, ENABLE);      //启动DMA通道
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	  //使能指定的ADC1的软件转换启动功能
	while(1)
	{
		for(i=0;i<6;i++)			//循环6次转换AD值
		{
		   volta[i] =(float) AD_Value[i]/4095*3.3;
		}
		printf("AD1=%d\n",AD_Value[0]);	printf("\r\n volta1 = %f V \r\n",volta[0]);
		printf("AD2=%d\n",AD_Value[1]);	printf("\r\n volta2 = %f V \r\n",volta[1]);
		printf("AD3=%d\n",AD_Value[2]);	printf("\r\n volta3 = %f V \r\n",volta[2]);
		printf("AD4=%d\n",AD_Value[3]);	printf("\r\n volta4 = %f V \r\n",volta[3]);
		printf("AD5=%d\n",AD_Value[4]);	printf("\r\n volta5 = %f V \r\n",volta[4]);
		printf("AD6=%d\n",AD_Value[5]);	printf("\r\n volta6 = %f V \r\n",volta[5]);
		delay_ms(1000);
	}
}

