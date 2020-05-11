#include <stdio.h>
//#include <string.h>
#include "adf.h"
#include "board.h"
#include "delay.h"
#include "sht20.h"
#include "utili.h"

void SHT2x_Init(void)
{	
    GPIOSCL_init();
    GPIOSDA_init();
	
	//���������ø�
    SHT2x_SCL_HIGH();
    SHT2x_SDA_HIGH();

    SHT2x_Delay(80);

    SHT2x_SoftReset();
}

//I2C��ʼ
void SHT2x_I2cStartCondition(void)
{
    SHT2x_SCL_OUTPUT();
    SHT2x_SDA_OUTPUT();
    
    SHT2x_SDA_HIGH();
    SHT2x_SCL_HIGH();
	
    SHT2x_SDA_LOW();
    SHT2x_Delay(30);
	
    SHT2x_SCL_LOW();
    SHT2x_Delay(30);
}

//I2Cֹͣ
void SHT2x_I2cStopCondition(void)
{
    SHT2x_SCL_OUTPUT();
    SHT2x_SDA_OUTPUT();
    
    SHT2x_SDA_LOW();
    SHT2x_SCL_LOW();
	
    SHT2x_SCL_HIGH();
    SHT2x_Delay(30);
	
    SHT2x_SDA_HIGH();
    SHT2x_Delay(30);
}

//I2cӦ��
void SHT2x_I2cAcknowledge(void)
{
    SHT2x_SCL_OUTPUT();
    SHT2x_SDA_OUTPUT();

    SHT2x_SDA_LOW();
    
    SHT2x_SCL_HIGH();
    SHT2x_Delay(80);
	
    SHT2x_SCL_LOW();   
    SHT2x_Delay(80);
}

//I2Cû��Ӧ��
void SHT2x_I2cNoAcknowledge(void)
{
    SHT2x_SCL_OUTPUT();
    SHT2x_SDA_OUTPUT();

    SHT2x_SDA_HIGH();
    
    SHT2x_SCL_HIGH();
    SHT2x_Delay(80);
	
    SHT2x_SCL_LOW();   
    SHT2x_Delay(80);
}

//I2C��һ���ֽ�
u8 SHT2x_I2cReadByte(void)
{
    u8 i, val = 0;

    SHT2x_SCL_OUTPUT();
    SHT2x_SDA_OUTPUT();

    SHT2x_SDA_HIGH();
    
    SHT2x_SDA_INPUT();
        
    for(i = 0; i < 8; i++)
    {
        val <<= 1; 
        
        SHT2x_SCL_HIGH();   
        
        if(Bit_SET == SHT2x_SDA_STATE()) 
        {
            val |= 0x01;
        }
        
        SHT2x_SCL_LOW();    
    }

    SHT2x_SDA_OUTPUT();

    SHT2x_SDA_HIGH();
    
    return (val);
}

//I2Cдһ���ֽ�
u8 SHT2x_I2cWriteByte(u8 byte)
{
    u8 i = 0;
    u8 ack = 0;

    SHT2x_SCL_OUTPUT();
    SHT2x_SDA_OUTPUT();
    
    for(i = 0; i < 8; i++)
    {
        if(byte & 0x80) 
        {
            SHT2x_SDA_HIGH();
        }
        else 
        {
            SHT2x_SDA_LOW();
        }
        
        SHT2x_SCL_HIGH();
        SHT2x_Delay(80);
		
        SHT2x_SCL_LOW();   
        SHT2x_Delay(80);
        
        byte <<= 1;
    }

    SHT2x_SDA_INPUT();
    
    SHT2x_SCL_HIGH();
    
    if(Bit_SET == SHT2x_SDA_STATE()) 
    {
        ack = ACK_ERROR;
    }
    else
    {
        ack = ACK_OK;
    }
    
    SHT2x_SCL_LOW();  

    SHT2x_SDA_OUTPUT();

    SHT2x_SDA_HIGH();
    
    return (ack);
}

//��ѯ�����¶�
s16 SHT2x_MeasureTempPoll(void)
{
    s16 TEMP;
    u8 ack, tmp1, tmp2;
    s16 ST;
    
    //I2C��ʼ״̬ 
    SHT2x_I2cStartCondition();    
    //I2Cдһ���ֽ�  0x80
    SHT2x_I2cWriteByte(I2C_ADR_W);   
    //I2Cдһ���ֽ�  0xF3
    SHT2x_I2cWriteByte(TRIG_TEMP_MEASUREMENT_POLL);   

    do 
    {
        SHT2x_Delay(20);  //us 
        //I2C��ʼ״̬ 
        SHT2x_I2cStartCondition();  
        //I2Cдһ���ֽ�  0x81
        ack = SHT2x_I2cWriteByte(I2C_ADR_R);  
    } while(ACK_ERROR == ack);
    
    //I2C��һ���ֽ�
    tmp1 = SHT2x_I2cReadByte();   
    //I2cӦ��
    SHT2x_I2cAcknowledge();  
    //I2cӦ��
    tmp2 = SHT2x_I2cReadByte();
    //I2Cû��Ӧ��
    SHT2x_I2cNoAcknowledge();
    //I2Cֹͣ״̬
    SHT2x_I2cStopCondition();
    
    ST = (tmp1 << 8) | (tmp2 << 0);
    ST &= ~0x0003;
    
    if( ST < 0 )	
    {
        TEMP = (s16)( ( ((~ST+1) * 0.00268127) - 46.85 )*100)/10;
        TEMP |= 0X8000; 
    }
	else
        TEMP = (s16)( ( (ST * 0.00268127) - 46.85 )*100)/10;
    
    //printf("SHT20--TEMP=%d\r\n",TEMP);
    return (TEMP);	  
}

//��ѯ����ʪ��
s16 SHT2x_MeasureHumiPoll(void)
{
    s16 HUMI;
    u8 ack, tmp1, tmp2;    
    s16 SRH;
    
    SHT2x_I2cStartCondition();                               
    SHT2x_I2cWriteByte(I2C_ADR_W);
    SHT2x_I2cWriteByte(TRIG_HUMI_MEASUREMENT_POLL);
    
    do 
	{
        SHT2x_Delay(20);
        SHT2x_I2cStartCondition();
        ack = SHT2x_I2cWriteByte(I2C_ADR_R);
		
    } while(ACK_ERROR == ack);
    
    tmp1 = SHT2x_I2cReadByte();
    SHT2x_I2cAcknowledge();
    tmp2 = SHT2x_I2cReadByte();
    SHT2x_I2cNoAcknowledge();
    SHT2x_I2cStopCondition();
    
    SRH = (tmp1 << 8) | (tmp2 << 0);
    SRH &= ~0x0003;
    
    if( SRH < 0 )		 
        HUMI = (s16)(100 * ( ((~SRH+1) * 0.00190735) - 6 ) )/10;  
	else
        HUMI = (u16)(100 * ( (SRH * 0.00190735) - 6 ) )/10; 
    
    //printf("SHT20--HUMI=%d\r\n",HUMI); 
    return (HUMI);
}

//�����λ
void SHT2x_SoftReset(void)
{
    //I2C��ʼ״̬
    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_W); //  0x80
    SHT2x_I2cWriteByte(SOFT_RESET); // 0xFE
    //I2Cֹͣ״̬
    SHT2x_I2cStopCondition();
    SHT2x_Delay(80);
}

//�ɼ���ʪ��
void SHT2x_Test(s16 *temp,s16 *humi)
{    
    *temp = SHT2x_MeasureTempPoll();
    *humi = SHT2x_MeasureHumiPoll();
}

