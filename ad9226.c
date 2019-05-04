#include "stm32f4xx.h"
#define AD0_bit_0 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0)//MSB
#define AD0_bit_1 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3)
#define AD0_bit_2 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)
#define AD0_bit_3 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8)

#define AD0_bit_4 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7)
#define AD0_bit_5 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6)
#define AD0_bit_6 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5)
#define AD0_bit_7 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_4)

#define AD0_bit_8 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3)
#define AD0_bit_9 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2)
#define AD0_bit_10 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1)
#define AD0_bit_11 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_0)//LSB
void AD9226_GPIO_config(void);
void ADC_Clk_Init(u32 arr,u32 psc,u16 cnt);
void TIM3_Int_Init(u16 arr,u16 psc);
float Get_AD9226_value();


#include "AD_9226.h"
#include "led.h"
extern uint16_t ADC_value_A;
extern uint16_t ADC_value_B;
u16 AD0_value;
u16 AD0_byte;
float AD_tmp1;
u16 led0;
void AD9226_GPIO_config(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//Ê¹ÄÜGPIOFÊ±ÖÓ
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//Ê¹ÄÜGPIOFÊ±ÖÓ
  //GPIOF9,F10³õÊ¼»¯ÉèÖÃ
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0| GPIO_Pin_5| GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType= GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOF, &GPIO_InitStructure);//³õÊ¼»¯
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_OType= GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);//³õÊ¼»¯


}

float Get_AD9226_value()
{
	
			if(AD0_bit_0)//two's complement output,when Voltage is lower than Vref(2V),bit0 will set 1
		{
			AD_tmp1=(
			(0x00<<15)|(0x00<<14)|(0x00<<13)|(0x00<<12)
			|(AD0_bit_0<<11)|(!AD0_bit_1<<10)|(!AD0_bit_2<<9)|(!AD0_bit_3<<8)//CAUTION:"!"should be put inside the"|"operation!
			|(!AD0_bit_4<<7)|(!AD0_bit_5<<6)|(!AD0_bit_6<<5)|(!AD0_bit_7<<4)
			|(!AD0_bit_8<<3)|(!AD0_bit_9<<2)|(!AD0_bit_10<<1)|(!AD0_bit_11<<0)
		);
			AD_tmp1=5-(AD_tmp1/4095)*10;
		}
		else
		{
			AD_tmp1=(
			(0x00<<15)|(0x00<<14)|(0x00<<13)|(0x00<<12)
			|(1<<11)|(AD0_bit_1<<10)|(AD0_bit_2<<9)|(AD0_bit_3<<8)//
			|(AD0_bit_4<<7)|(AD0_bit_5<<6)|(AD0_bit_6<<5)|(AD0_bit_7<<4)
			|(AD0_bit_8<<3)|(AD0_bit_9<<2)|(AD0_bit_10<<1)|(AD0_bit_11<<0)
		
		);
			AD_tmp1=(AD_tmp1/4095)*10-5;
		}

		
		return AD_tmp1;
}
