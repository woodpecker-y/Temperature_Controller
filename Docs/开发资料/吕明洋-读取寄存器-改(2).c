#define DQ_BIT_W1				GPIO_SetBits(DS18B20_DQ_PORT,DS18B20_DQ_PIN)
#define DQ_BIT_W0				GPIO_ResetBits(DS18B20_DQ_PORT,DS18B20_DQ_PIN)
#define DQ_BIT_OutPut			GPIO_Init(DS18B20_DQ_PORT,DS18B20_DQ_PIN,GPIO_Mode_Out_PP_High_Fast);  // direction   output
#define DQ_BIT_InPut			GPIO_Init(DS18B20_DQ_PORT,DS18B20_DQ_PIN,GPIO_Mode_In_PU_No_IT);    	 // direction  input
#define DQ_BIT_Read			    (BSP_GPIO_ReadState(PORTF, PIN1))           	//  input mode,read the  DQ data


//// READ_BIT – 从MY18E20读取一位数
unsigned char read_bit(void) { 
	unsigned char res; 
	DQ_BIT_W0;          //主机拉低DQ总线
	delay_us(5);     //拉低DQ总线持续5us  
	DQ_BIT_W1;          //主机释放DQ总线，由上拉电阻拉高
        DQ_BIT_InPut;
	delay_us(2);    // 等待2us确保总线上数据稳定
	res = DQ_BIT_Read;
	delay_us(50);    //时序末尾等待
	return(res);    // 返回读取数值
}

//// WRITE_BIT – 主机写一位数据到MY18E20
void write_bit(char bitval) { 
	DQ_BIT_W0;              //主机拉低DQ总线
	delay_us(5);         //拉低DQ总线持续5us
	if(bitval==1) DQ_BIT_W1; // 如果写1，此时拉高DQ总线
	delay_us (60);       // 如果写0，则持续拉低DQ总线60us
	DQ_BIT_W1;              //释放DQ总线
	delay_us (5);        //（写0）恢复时间1us 
}

//// READ_BYTE - 从MY18E20读取一字节数据  
unsigned char read_byte(void) { 
	unsigned char i, j; 
	unsigned char value = 0; 
	for (i=0;i<8;i++) { 
	j = read_bit();		
	value = (value) | (j<<i);  //每次读进1 位(低位先行), 然后左移 
	} 
	return(value); 
} 

//// WRITE_BYTE - 主机写一字节数据到MY18E20 
void write_byte(char val) { 
	unsigned char i; 
	unsigned char temp; 
	for (i=0; i<8; i++) {  // 写字节,每次一位  
		temp = val>>i;  
		temp &= 0x01;   // 低位先行
		write_bit(temp); 
	}  
}

// 主机发送复位脉冲（大于480us低电平），并检查存在脉冲 
unsigned char ow_reset(void) { 
	unsigned char presence; 
	DQ_BIT_W0;             //主机拉低DQ总线
	delay_us(480);     // 拉低DQ总线持续480us 
	DQ_BIT_W1;            // 主机释放总线，由上拉电阻拉高
        DQ_BIT_InPut;
	delay_us(70);      // 等待80us后检查presence 
	presence = DQ_BIT_Read;     // 检查存在脉冲 
//	delay_us(15);      // 时序末尾等待 
	delay_us(410);      // 修改：Presense周期480us
        printf("presence = %d\r\n", presence);
//        printf("GPIO_ReadInputDataBit = %d\r\n", BSP_GPIO_ReadState(PORTF, PIN1));
	return(presence); 
} // 0 = MY18E20存在, 1 = MY18E20不存在


void obtain_power_reg(void) 
{ 
    u8 i;
    u8 serial[10];
      
    ow_reset(); 
	write_byte(0xcc);  //Skip ROM，或使用匹配ROM序列号（见后文）
	write_byte(0x8b); // 写入1字节
      
//      write_byte(0xcc);  //Skip ROM，或使用匹配ROM序列号（见后文）
//      write_byte(0xbe); // 写入1字节
      
    for(i=0; i<2; i++) 
    {
      serial[i] = read_byte();        // 读取
      printf("\r\n Parameter byte %u : %02x\r\n",i, serial[i]);
        //printf("? %2x",serial[i]);
    }
}


#define MY18E20_SCRPARAMETERS_SIZE		8

typedef struct
{
	uint8_t Ttrim;				
	uint8_t ana_conf;			/*D7, PD_idle设置; D7=1为Power-down模式*/	
	uint8_t adc_conf;				
	uint8_t adc_coeff[3];		
	uint8_t ana_cal[2];					
} MYT_SCRPARAMETERS;

#define MY18E20_ANA_CONFREG_PD_IDLE         0x80

MYT_BOOL MY18E20_ReadParameters_SkipRom(uint8_t *scr)
{
    int16_t i;

    if(OW_ResetPresence() == FALSE)
		{
			myom_errno = MYT_ERR_NODEVICE;
#if defined(MYT_DEBUG)		
			printf("\r\nNo Device(s).");  /* Debug */
#endif						
			return FALSE;
		}
		
    OW_WriteByte(SKIP_ROM);
    OW_WriteByte(READ_PARAMETERS);
		
		for(i=0; i<MY18E20_SCRPARAMETERS_SIZE; i++)
    {
			*scr++ = OW_ReadByte();
		}

    return TRUE;
}
