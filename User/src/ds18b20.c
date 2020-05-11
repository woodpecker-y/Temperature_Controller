#include <stdio.h>
#define _DS18B20_C_
#include"DS18B20.h"
#include "bsp.h"
#include "sysparams.h"

//u8  ReadSlot (void)
//{
//	u8 i;
//
//	DQ_BIT_W0;
//	DQ_BIT_InPut;
//
//	i=DQ_BIT_Read;
////	Delay_5us(60/5);
//        delay_us(60);
//	DQ_BIT_OutPut;
//	DQ_BIT_W1;
//	return i;
//}
u8  ReadSlot (void)
{
  	u8 i;

	DQ_BIT_W0;
    DQ_BIT_InPut;

    delay_us(5);

    i = DQ_BIT_Read;
    delay_us(60);
	DQ_BIT_OutPut;
	DQ_BIT_W1;
	return i;
}



u8 Read_One_Byte(void)       //读取一个字节的数据read a byte date
{
	u8 i,j=0x01,byte=0;
	for(i=0;i<8;i++)
	{
		if(ReadSlot()) byte=byte | j;
		j=j<<1;
	}
	return byte;
}

void WriteSlot (u8 i)
{

	DQ_BIT_W0;
	if(i)
	{
		DQ_BIT_W1;
	}
//	Delay_5us(60/5);
        delay_us(60);
	DQ_BIT_W1;
}


void Write_One_Byte(u8 byte) //写入一个字节的数据write a byte date
{
	u8 i;
	for(i=0;i<8;i++)
	{
		if(byte & 0x01)
		{
			WriteSlot(1);
		}
		else
		{
			WriteSlot(0);
		}
		byte=byte>>1;
	}
}

u8 DS18B20_Init(void)     //DS18B20初始化send reset and initialization command
{
	u8 i;
	s8 tryTimes;
	u8 backs =0x00;

	/* 拉低总线复位 */
	DQ_BIT_OutPut;
	DQ_BIT_W0;
//	Delay_5us(720/5);
        delay_us(720);

	/* 释放总线 */
	DQ_BIT_InPut;

    /* 检测480微秒内有无低电平，判断18B20是否存在 */
    tryTimes = 24;
    backs =0x00;
    while(tryTimes--)
    {
		i = DQ_BIT_Read;
		if(i == 0)
		{
			backs =0x01;
			break;
		}
//		Delay_5us(15/5);	//精确延时20us
                delay_us(15);
    }

	/* 检测480微秒内有无低电平，判断18B20是否存在 */
    tryTimes = 24;
    while(tryTimes--)
    {
		i = DQ_BIT_Read;
		if(i == 1)
		{
			break;
		}
//		Delay_5us(15/5);//精确延时20us
                delay_us(15);
    }
	DQ_BIT_OutPut;
	DQ_BIT_W1;
	return backs;

}



void DS18B20_Start(void)
{

//	disableInterrupts();						//总中断控制

	DS_18B20Controler.DS18b20Flag =DS18B20_Init();	//初始化温度传感器
//        printf("DS_18B20Controler.DS18b20Flag = %d\r\n", DS_18B20Controler.DS18b20Flag);
	Write_One_Byte(0XCC);					//忽略ROM指令
	Write_One_Byte(0x44);					//温度转换指令
//	enableInterrupts();						//总中断控制

}




s16 DS18B20_ReadTemp(void)
{
	s16 Temp;
	s32 TempBuffer =0;
	u8 a =0,b =0;
	s16 TempOutPut =0;
        int i = 0;
        char data[9] = {0};

//	disableInterrupts();					//总中断控制	
	DS18B20_Init();
	Write_One_Byte(0XCC);          		//忽略ROM指令
	Write_One_Byte(0XBE);          		//读暂存器指令

        for (i = 0; i < 9; i++)
        {
          data[i] = Read_One_Byte();
        }
        a = data[0];
        b = data[1];
//	a = Read_One_Byte();           		//读取到的该字节为温度LSB
//	b = Read_One_Byte();           		//读取到的该字节为温度MSB

	Temp = b<<8;               		//先把高八位有效数据赋于temp
	Temp = Temp|a;          			//两字节合成一个整型变量测量精度为1/16  即把实际温度扩大为16倍

	TempBuffer =Temp*100l/16l;			//得到真实精确到0.01度  温度传感器最低有效位是0.0625(1/16)


	TempOutPut =(s16)TempBuffer;

    if(TempOutPut<0)
        TempOutPut = 0;

	return TempOutPut;

}




void DS18B20_GetTemp_Server(void)//温度获取服务函数
{
    s16 Temp_Buffer =0;


    DS18B20_Start(); 					//传感器配置命令
    // ������Ҫ�ж��³�ʼ���Ƿ�ɹ�
        Temp_Buffer =DS18B20_ReadTemp();	//温度读取命令
//        LCD_Temp_Display(Temp_Buffer, INPUT, WRITE);    // ��ʱ
        printf("Temp_Buffer:%d\r\n", Temp_Buffer);
        if((Temp_Buffer<0)||(Temp_Buffer>=10000))
        {
                Temp_Buffer= 0;
        }

        g_run_params.temp = Temp_Buffer;




}

/*
	函数功能:DS18B20 功能服务 模块上初始化 包含对数据库的连接与配置
	@Para	ScanPara:扫描周期(间隔)
	@Para	*Clock:    时基地址
*/

void DS18B20_PowerON_Init(void)
{
    s16 Temp_Buffer =0;
    Temp_Buffer =Temp_Buffer;
    DS18B20_Start();
    Temp_Buffer =DS18B20_ReadTemp();
    printf("Temp_Buffer_main = %d\r\n", Temp_Buffer);
    DS_18B20Controler.Sys_Temp =0;
}

/*

	平均温度记录点输入函数，将所得到的当前温度进行存储

	服务变量 AVE_TempData

*/
void AVETemp_PointInput(s16* Temp)
{
	AVE_TempData.Buffer[AVE_TempData.Count]=*Temp;
	AVE_TempData.Count +=1;
	if(AVE_TempData.Count >=AVEtemp_BufferSize)
	{
		AVE_TempData.Count =0;
		AVE_TempData.StackFull =0X01;
	}
}


/*
	求平均温度
	参数:系统最近一次获取的温度值指针

*/
s16 AVETemp_Calculate(s16* Temp)
{
	s16 Ave_Value =0;
	u8 loop =0;
	AVE_TempData.Temp_Add =0;
	AVE_TempData.Buffer[AVE_TempData.Count]=*Temp;
	AVE_TempData.Count +=1;

	if(AVE_TempData.StackFull ==0X01)	//堆栈区满
	{
		for(loop=0;loop<AVEtemp_BufferSize;loop++ )
		{
			AVE_TempData.Temp_Add +=AVE_TempData.Buffer[loop];
		}
		Ave_Value=AVE_TempData.Temp_Add/AVEtemp_BufferSize;
	}
	else
	{
		if(AVE_TempData.Count ==0)
		{
			Ave_Value =*Temp;
		}
		else
		{
			for(loop=0;loop<AVE_TempData.Count;loop++ )
			{
				AVE_TempData.Temp_Add +=AVE_TempData.Buffer[loop];
			}
			Ave_Value=AVE_TempData.Temp_Add/AVE_TempData.Count;
		}
	}
	return Ave_Value;
}

void ds18b20_close(void)
{
  GPIO_Init(DS18B20_DQ_PORT,DS18B20_DQ_PIN,GPIO_Mode_Out_OD_Low_Slow);       // �͹��Ĳ���
}

// �������͸�λ���壨����480us�͵�ƽ����������������
unsigned char ow_reset(void) {
	unsigned char presence;
	DQ_BIT_W0;             //��������DQ����
	delay_us(480);     // ����DQ���߳���480us
	DQ_BIT_W1;            // �����ͷ����ߣ���������������
        DQ_BIT_InPut;
	delay_us(80);      // �ȴ�80us����presence
	presence = DQ_BIT_Read;     // ����������
	delay_us(15);      // ʱ��ĩβ�ȴ�
        printf("presence = %d\r\n", presence);
        printf("GPIO_ReadInputDataBit = %d\r\n", BSP_GPIO_ReadState(PORTF, PIN1));
	return(presence);
} // 0 = MY18E20����, 1 = MY18E20������

//// READ_BIT �C ��MY18E20��ȡһλ��
unsigned char read_bit(void) {
	unsigned char res;
	DQ_BIT_W0;          //��������DQ����
	delay_us(5);     //����DQ���߳���5us
	DQ_BIT_W1;          //�����ͷ�DQ���ߣ���������������
        DQ_BIT_InPut;
	delay_us(2);    // �ȴ�2usȷ�������������ȶ�
	res = DQ_BIT_Read;
	delay_us(50);    //ʱ��ĩβ�ȴ�
	return(res);    // ���ض�ȡ��ֵ
}

//// WRITE_BIT �C ����дһλ���ݵ�MY18E20
void write_bit(char bitval) {
	DQ_BIT_W0;              //��������DQ����
	delay_us(5);         //����DQ���߳���5us
	if(bitval==1) DQ_BIT_W1; // ���д1����ʱ����DQ����
	delay_us (60);       // ���д0�����������DQ����60us
	DQ_BIT_W1;              //�ͷ�DQ����
	delay_us (5);        //��д0���ָ�ʱ��1us
}

//// READ_BYTE - ��MY18E20��ȡһ�ֽ�����
unsigned char read_byte(void) {
	unsigned char i, j;
	unsigned char value = 0;
	for (i=0;i<8;i++) {
	j = read_bit();
	value = (value) | (j<<i);  //ÿ�ζ���1 λ(��λ����), Ȼ������
	}
	return(value);
}

//// WRITE_BYTE - ����дһ�ֽ����ݵ�MY18E20
void write_byte(char val) {
	unsigned char i;
	unsigned char temp;
	for (i=0; i<8; i++) {  // д�ֽ�,ÿ��һλ
		temp = val>>i;
		temp &= 0x01;   // ��λ����
		write_bit(temp);
	}
}

//
void sample_temp(void)
{
	unsigned char get[10];
	unsigned char tpmsb, tplsb, i;
 	short s_tem;
 	float f_tem;

	ow_reset();
	write_byte(0xCC);  //Skip ROM����ʹ��ƥ��ROM���кţ������ģ�
	write_byte(0x44);  // ת���¶�
	delay_ms (500);
        // �¶�ת��ʱ�䣬���п���ģʽΪ15ms������ģʽΪ500ms

	ow_reset();
	write_byte(0xCC); // Skip ROM����ʹ��ƥ��ROM���кţ������ģ�
	write_byte(0xBE); // ��ȡScratch Pad����ֵ

	for (i=0;i<9;i++){
		get[i]=read_byte();
	}

	tpmsb = get[1];   // �¶ȸ��ֽ�
	tplsb = get[0];   // �¶ȵ��ֽ�
        printf("tpmsb = %0x, tplsb = %0x", tpmsb, tplsb);
	s_tem = tpmsb<<8;
 	s_tem = s_tem | tplsb;
 	s_tem = s_tem & 4095;

 	if( (s_tem & 2048) == 2048 )	{
 		s_tem = (s_tem^4095) & 4095;
 		f_tem = -1*(s_tem+1) * 0.0625;  //�¶�Ϊ��ֵ
 	}
 	else f_tem = s_tem * 0.0625;
//	printf( "\nTempF= %f degrees C\n", f_tem); //��ӡ�����¶�
//        printf("temp = %f\r\n", f_tem);
//        printf("temp = %d\r\n", f_tem);
}








