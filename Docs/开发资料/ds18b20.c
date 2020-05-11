#include <stdio.h>
#include <string.h>
#include "adf.h"
#include "board.h"
#include "bsp_gpio.h"
#include "ds18b20.h"
#include "delay.h"

static void                           DS18B20_Rst                               ( void );
static uint8_t                        DS18B20_Presence                          ( void );
static uint8_t                        DS18B20_ReadBit                           ( void );
static uint8_t                        DS18B20_ReadByte                          ( void );
static void                           DS18B20_WriteByte                         ( uint8_t dat );
//static void                           DS18B20_SkipRom                           ( void );
//static void                           DS18B20_MatchRom                          ( void );

#define macDS18B20_DQ_1           gpio_set_high(PORTB,PIN6)
#define macDS18B20_DQ_0           gpio_set_low(PORTB,PIN6)

#define DS18B20_Mode_IPU()        gpio_init(PORTB,PIN6, GPIO_Mode_In_PU_No_IT)   //MISO为上拉输入模式
#define DS18B20_Mode_Out_PP()     gpio_init(PORTB,PIN6, GPIO_Mode_Out_PP_Low_Slow)
#define macDS18B20_DQ_IN()        gpio_read_state(PORTB,PIN6)      //读MISO的位值
#define Delay_us(a)               delay_us(a)

//DS18B20初始化函数
uint8_t DS18B20_Init(void)
{
	macDS18B20_DQ_1;
	
	DS18B20_Rst();
	
	return DS18B20_Presence ();
	
}

//主机给从机发送复位脉冲
static void DS18B20_Rst(void)
{
	DS18B20_Mode_Out_PP();  
	
	macDS18B20_DQ_0;    
	
	Delay_us(480);
	
	macDS18B20_DQ_1;   
	
	Delay_us(70);
}

//检测从机给主机返回的存在脉冲     返回1:未检测到DS18B20的存在    返回0:存在
static uint8_t DS18B20_Presence(void)
{
	uint8_t pulse_time = 0;
	
	DS18B20_Mode_IPU();
    
	while( macDS18B20_DQ_IN() && pulse_time<200 )  
	{
		pulse_time++;
		Delay_us(1);
	};
    
	if( pulse_time >=200 )
		return 1;
	else
		pulse_time = 0;
    
	while( !macDS18B20_DQ_IN() && pulse_time<240 )
	{
		pulse_time++;
		Delay_us(1);
	};
	
	if( pulse_time >=240 )
		return 1;
	else
		return 0;
}

//从DS18B20中读取一个bit
static uint8_t DS18B20_ReadBit(void)
{
	uint8_t dat;
    
	DS18B20_Mode_Out_PP();   
	macDS18B20_DQ_0;
	Delay_us(5);
	macDS18B20_DQ_1;
	DS18B20_Mode_IPU();

	if( macDS18B20_DQ_IN()==1) 
		dat = 1;
	else
		dat = 0;
	
	Delay_us(50);
	
	return dat;
}

//从DS18B20 中读取一个字节，低位先行
static uint8_t DS18B20_ReadByte(void)
{
	uint8_t i, j, dat = 0;	
	
	for(i=0; i<8; i++) 
	{
		j = DS18B20_ReadBit();		
		dat = (dat) | (j<<i);
	}
	
	return dat;
}

//写一个字节到DS18B20 低位先行
static void DS18B20_WriteByte(uint8_t dat)
{
	uint8_t i, testb;
    
	DS18B20_Mode_Out_PP();
	
	for( i=0; i<8; i++ )
	{
		testb = dat&0x01;
		dat = dat>>1;		
		if (testb)
		{			
			macDS18B20_DQ_0;
			Delay_us(8);   //8us		
			macDS18B20_DQ_1;
			Delay_us(58);    //58us
		}		
		else
		{			
			macDS18B20_DQ_0;
			Delay_us(70);   //70us		
			macDS18B20_DQ_1;			
			Delay_us(5);     //2us
		}
	}
}

//在跳过ROM情况下获取DS18B20温度值
void DS18B20_GetTemp_SkipRom (s16 *temp)
{
	u8 tpmsb = 0;
    u8 tplsb = 0;
	s16 s_tem = 0;
	u8 i = 0;
    
    DS18B20_Rst();
    if(DS18B20_Presence() == 0)
    {
        //DS18B20_Presence();
        DS18B20_WriteByte(0XCC);   //0XCC跳过ROM
        DS18B20_WriteByte(0X44);	
        
        DS18B20_Rst();
        if(DS18B20_Presence() == 0)
        {
            DS18B20_Presence(); 
            DS18B20_WriteByte(0XCC);    //0XCC跳过ROM
            DS18B20_WriteByte(0XBE);		
            
            tplsb = DS18B20_ReadByte();		 
            tpmsb = DS18B20_ReadByte(); 
            
            for(i=0; i<7; i++)
            {
            	DS18B20_ReadByte(); 
            }
            //printf("tplsb=%02X\r\n",tplsb);
            //printf("tpmsb=%02X\r\n",tpmsb);
            
            s_tem = tpmsb<<8;
            s_tem = s_tem | tplsb;
            
            if( s_tem < 0 )	
            {
                s_tem = (s16)( (~s_tem+1) * 0.625)-5;	
                s_tem = s_tem | 0X8000;
            }
            else
            {
                s_tem = (s16)(s_tem * 0.625)-5;
            }
            
            *temp = s_tem;
            
            //printf("stem=%d\r\n",s_tem);
            //s_tem = s_tem/10;
            //a = s_tem%10;
            //printf("ds18b20--temp=%d.%d\r\n",s_tem,a);
            
            return; 
        }
        else
        {
            *temp = 0;             
            return; 
        }
        
    }
    else
    {
        *temp = 0;             
        return; 
    }
    
}

