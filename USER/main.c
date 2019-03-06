#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
 
extern u8  TIM2CH3_CAPTURE_STA;	//���벶��״̬		    				
extern u16	TIM2CH3_CAPTURE_VAL;	//���벶��ֵ

int main(void)
{		
    u32 temp=0; 
    u16 led0pwmval=0;
    u16 outputCounter = 0;
    u16 inputCounter = 0;
	u8 dir=1;	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ�� PC13
 	//TIM3_PWM_Init(899,0);	 //����Ƶ��PWMƵ��=72000000/900=80Khz
    
    TIM2_Cap_Init(0XFFFF,72-1);	//��1Mhz��Ƶ�ʼ��� 
    while(1)
	{
 		delay_ms(10);   
        if(TIM2CH3_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
            temp=TIM2CH3_CAPTURE_STA&0X3F;
			temp*=65536;//���ʱ���ܺ�
			temp+=TIM2CH3_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
            printf("%d \n",temp); 
            TIM2CH3_CAPTURE_STA = 0;        
        }
	}	    
 }

