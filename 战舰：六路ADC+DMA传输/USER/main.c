#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "adc.h"
#include "dma.h"
 
/************************************************
 ALIENTEK ս��STM32F103������ʵ��17
 ��·ADC+DMA���� ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
#define ADC1_DR_Address    ((uint32_t)0x4001244C)
u16 AD_Value[6];    
float volta[6];
u8 i;

 
int main(void)
{
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ115200
	MYDMA_Config(DMA1_Channel1,(u32)ADC1_DR_Address,(u32)&AD_Value,6);//cndtr��Ӧ�����ŵ�����
	Adc_Init();
	DMA_Cmd(DMA1_Channel1, ENABLE);      //����DMAͨ��
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	  //ʹ��ָ����ADC1�����ת����������
	while(1)
	{
		for(i=0;i<6;i++)			//ѭ��6��ת��ADֵ
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

