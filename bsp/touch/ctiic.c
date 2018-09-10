#include "ctiic.h"
#include "delay.h"	 
#include "lcd.h"
#include "FreeRTOS.h"
#include "task.h"

//����I2C�ٶȵ���ʱ
void CT_Delay(void)
{
	opt_delay(3);//about 2us
} 
//���ݴ���оƬIIC�ӿڳ�ʼ��
void CT_IIC_Init(void)
{			
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_SET);
  
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}
//����IIC��ʼ�ź�
void CT_IIC_Start(void)
{
  taskENTER_CRITICAL();
	CT_SDA_OUT();     //sda�����
	CT_IIC_SDA=1;	  	  
	CT_IIC_SCL=1;
	opt_delay(41);//about 30us
 	CT_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	CT_Delay();
	CT_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
  taskEXIT_CRITICAL();
}	  
//����IICֹͣ�ź�
void CT_IIC_Stop(void)
{
  taskENTER_CRITICAL();
	CT_SDA_OUT();//sda�����
	CT_IIC_SCL=1;
	opt_delay(41);//about 30us
	CT_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
	CT_Delay();
	CT_IIC_SDA=1;//����I2C���߽����ź�
  taskEXIT_CRITICAL();  
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 CT_IIC_Wait_Ack(void)
{
  taskENTER_CRITICAL();
	u8 ucErrTime=0;
	CT_SDA_IN();      //SDA����Ϊ����  
	CT_IIC_SDA=1;	   
	CT_IIC_SCL=1;
	CT_Delay();
	while(CT_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			CT_IIC_Stop();
			return 1;
		} 
		CT_Delay();
	}
	CT_IIC_SCL=0;//ʱ�����0 	
  taskEXIT_CRITICAL();   
	return 0;  
} 
//����ACKӦ��
void CT_IIC_Ack(void)
{
  taskENTER_CRITICAL();
	CT_IIC_SCL=0;
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA=0;
	CT_Delay();
	CT_IIC_SCL=1;
	CT_Delay();
	CT_IIC_SCL=0;
  taskEXIT_CRITICAL();  
}
//������ACKӦ��		    
void CT_IIC_NAck(void)
{
  taskENTER_CRITICAL();
	CT_IIC_SCL=0;
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA=1;
	CT_Delay();
	CT_IIC_SCL=1;
	CT_Delay();
	CT_IIC_SCL=0;
  taskEXIT_CRITICAL();  
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void CT_IIC_Send_Byte(u8 txd)
{                        
  u8 t;  
  taskENTER_CRITICAL();  
  CT_SDA_OUT(); 	    
  CT_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
  CT_Delay();
	for(t=0;t<8;t++)
  {              
    CT_IIC_SDA=(txd&0x80)>>7;
    txd<<=1; 	      
    CT_IIC_SCL=1; 
    CT_Delay();
    CT_IIC_SCL=0;	
    CT_Delay();
  }	
  taskEXIT_CRITICAL();     
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 CT_IIC_Read_Byte(unsigned char ack)
{
	u8 i,receive=0;
  taskENTER_CRITICAL();  
 	CT_SDA_IN();//SDA����Ϊ����
	opt_delay(41);//about 30us
	for(i=0;i<8;i++ )
	{ 
		CT_IIC_SCL=0; 	    	   
		CT_Delay();
		CT_IIC_SCL=1;	 
		receive<<=1;
		if(CT_READ_SDA)receive++;   
	}	  				 
	if (!ack)CT_IIC_NAck();//����nACK
	else CT_IIC_Ack(); //����ACK 
  taskEXIT_CRITICAL();   
 	return receive;
}

