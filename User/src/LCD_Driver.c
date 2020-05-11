

#define  _LCD_DRIVER_C_
#include "LCD_Driver.h"  
//#include "ds18b20.h"
//#include "Sys_Data.h"
//#include "VALVE.h"
//#include "COM.h"
//#include "main.h"
#include "bsp.h"
#include "sysparams.h"

static struct tm t;

/**
  * @brief  Configure LCD
  * @param  
  * @retval 
  */
void LCD_Config(void)
{

  CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE);        //  Enables LCD peripheral clock  
  LCD_Init(LCD_Prescaler_1, LCD_Divider_16, LCD_Duty_1_4, LCD_Bias_1_3, LCD_VoltageSource_External);    //  RTC 38000 / 4  = 9500,   LCD = 9500 / 2 =  4750,  4750 / (1 * 16) = 296,  296 / 
  LCD_PortMaskConfig(LCD_PortMaskRegister_0, 0xFF);       		//  Configures the LCD Port Mask.  0--7 SEG
  LCD_PortMaskConfig(LCD_PortMaskRegister_1, 0xFF);       		//  8 --- 15 SEG
  LCD_PortMaskConfig(LCD_PortMaskRegister_2, 0xFF);       		//  16--- 23  SEG
  LCD_PortMaskConfig(LCD_PortMaskRegister_3, 0xFF);       		//  24--- 31 SEG
	
  LCD_ContrastConfig(LCD_Contrast_Level_5);                  	//   The contrast can be adjusted using two different methods:
  LCD_DeadTimeConfig(LCD_DeadTime_0);     					//LCD_DeadTimeConfig(LCD_DeadTime_1);           // LCD_DeadTimeConfig(LCD_DeadTime_6);      //  6������ʱ�� ������
  LCD_PulseOnDurationConfig(LCD_PulseOnDuration_5);
  LCD_Cmd(ENABLE);                 						//  Enables the LCD Controller
  
}



/**
  * @brief  Converts an ascii char to the a LCD digit (previous coding).
  * @param  c: a char to display.
  * @param  point: a point to add in front of char
  *         This parameter can be: POINT_OFF or POINT_ON
  * @param  apostrophe: flag indicating if a apostrophe has to be add in front
  *         of displayed character.
  *         This parameter can be: APOSTROPHE_OFF or APOSTROPHE_ON.
  * @retval None
  */
static void Convert(uint8_t* c)
{
  uint16_t 	ch = 0 , tmp = 0;
  uint8_t	 i;
  /* The character c is a number*/
  if ((*c < 0x3A)&(*c > 0x2F))
  {
    ch = NumberMap[*c-0x30];
  }
  for (i = 0;i < 4; i++)
  {
    tmp = ch & mask[i];
    digit[i] = (uint8_t)(tmp >> (uint8_t)shift[i]);
  }
}



/**
  * @brief  This function writes a NUM in the LCD frame buffer.
  * @param  ch: the numnber to dispaly.0 ~ 9
  * @param  position: �ڼ���8�֡�1-8��
  * @param  flag: �����־�� ��CLEAR �����Write д��
  * @retval None
  * @par    Required preconditions: The LCD should be cleared before to start the
  *         write operation.
  */
void LCD_NUM_WriteChar(uint8_t ch, uint8_t position, LCD_CLEAR_FLAG flag)
{
	uint8_t* c;
	switch (ch)
  	{   
		case 0:
			c = "0";
		break;		
		case 1:
			c = "1";
		break;
		case 2:
			c = "2";
		break;
		case 3:
			c = "3";
		break;
		case 4:
			c = "4";
		break;
		case 5:
			c = "5";
		break;
		case 6:
			c = "6";
		break;		
		case 7:
			c = "7";
		break;
		case 8:
			c = "8";
		break;
		case 9:
			c = "9";
		break;			
	}	
			
  	Convert(c);                    //  Converts an ascii char to the a LCD digit[i]
  	switch (position)
  	{   
  		case 1:                                                      //  ��һλ8��
		  	LCD->RAM[LCD_RAMRegister_0] &=  Clear1;      					// COM0--SEG
		    LCD->RAM[LCD_RAMRegister_0] &=  Clear2; 
			LCD->RAM[LCD_RAMRegister_3] &=  Clear5;      					// COM1--SEG
		    LCD->RAM[LCD_RAMRegister_3] &=  Clear6; 
		    LCD->RAM[LCD_RAMRegister_7] &=  Clear1;      					// COM2--SEG
		    LCD->RAM[LCD_RAMRegister_7] &=  Clear2;		
		    LCD->RAM[LCD_RAMRegister_10] &=  Clear6;		 				// COM3--SEG
	    	if( CLEAR != flag)
	    	{
		    	LCD->RAM[LCD_RAMRegister_0] |=  PUTS1_S2(digit[0]);         // COM0--SEG
		      	LCD->RAM[LCD_RAMRegister_3] |=  PUTS5_S6(digit[1]);         // COM1--SEG
			    LCD->RAM[LCD_RAMRegister_7] |=  PUTS1_S2(digit[2]);         // COM2--SEG
			    LCD->RAM[LCD_RAMRegister_10] |=  PUTS5_S6(digit[3]);        // COM3--SEG
			}
   		break;
   		case 2:                                                             //  ��2λ8��
			LCD->RAM[LCD_RAMRegister_0] &=  Clear3;     					// COM0--SEG
			LCD->RAM[LCD_RAMRegister_0] &=  Clear4; 
			LCD->RAM[LCD_RAMRegister_3] &=  Clear7;     					// COM1--SEG
			LCD->RAM[LCD_RAMRegister_4] &=  Clear0;
			LCD->RAM[LCD_RAMRegister_7] &=  Clear3;     					// COM2--SEG
			LCD->RAM[LCD_RAMRegister_7] &=  Clear4;		
			LCD->RAM[LCD_RAMRegister_11] &=  Clear0;						// COM3--SEG
			if( CLEAR != flag)
	    	{
				LCD->RAM[LCD_RAMRegister_0] |=  PUTS3_S4(digit[0]);   		// COM0--SEG
				LCD->RAM[LCD_RAMRegister_3] |=  PUTS7(digit[1]);      		// COM1--SEG
				LCD->RAM[LCD_RAMRegister_4] |=  PUTS0(digit[1]);
				LCD->RAM[LCD_RAMRegister_7] |=  PUTS3_S4(digit[2]);     	// COM2--SEG
				LCD->RAM[LCD_RAMRegister_11] |=  PUTS0(digit[3]);       	// COM3--SEG			
	    	}
    	break;
    
	 	case 3:                                                             //  ��3λ8��
		    LCD->RAM[LCD_RAMRegister_0] &=  Clear5;     					// COM0--SEG
		    LCD->RAM[LCD_RAMRegister_0] &=  Clear6; 
		    LCD->RAM[LCD_RAMRegister_4] &=  Clear1;     					// COM1--SEG
		    LCD->RAM[LCD_RAMRegister_4] &=  Clear2;		
		    LCD->RAM[LCD_RAMRegister_7] &=  Clear5;     					// COM2--SEG
		    LCD->RAM[LCD_RAMRegister_7] &=  Clear6;		
		    LCD->RAM[LCD_RAMRegister_11] &=  Clear2;						// COM3--SEG
	    	if( CLEAR != flag)
	    	{    
				LCD->RAM[LCD_RAMRegister_0] |=  PUTS5_S6(digit[0]);       	// COM0--SEG
				LCD->RAM[LCD_RAMRegister_4] |=  PUTS1_S2(digit[1]);			// COM1--SEG
				LCD->RAM[LCD_RAMRegister_7] |=  PUTS5_S6(digit[2]);			// COM2--SEG
				LCD->RAM[LCD_RAMRegister_11] |=  PUTS1_S2(digit[3]);		// COM3--SEG
			}      
    	break;
    
   		case 4:                                                             //  ��4λ8��
		    LCD->RAM[LCD_RAMRegister_0] &=  Clear7;      					// COM0--SEG
		    LCD->RAM[LCD_RAMRegister_1] &=  Clear0;      
		    LCD->RAM[LCD_RAMRegister_4] &=  Clear3;      					// COM1--SEG
		    LCD->RAM[LCD_RAMRegister_4] &=  Clear4;		
		    LCD->RAM[LCD_RAMRegister_7] &=  Clear7;      					// COM2--SEG
		    LCD->RAM[LCD_RAMRegister_8] &=  Clear0;		
		    LCD->RAM[LCD_RAMRegister_11] &=  Clear4;		 				// COM3--SEG
		    if( CLEAR != flag)
		    {    
				LCD->RAM[LCD_RAMRegister_0] |=  PUTS7(digit[0]);         	// COM0--SEG
				LCD->RAM[LCD_RAMRegister_1] |=  PUTS0(digit[0]); 
				LCD->RAM[LCD_RAMRegister_4] |=  PUTS3_S4(digit[1]);	     	// COM1--SEG
				LCD->RAM[LCD_RAMRegister_7] |=  PUTS7(digit[2]);         	// COM2--SEG
				LCD->RAM[LCD_RAMRegister_8] |=  PUTS0(digit[2]);			
				LCD->RAM[LCD_RAMRegister_11] |=  PUTS3_S4(digit[3]);		// COM3--SEG			
		    }
    	break;    
    
   		case 5:                                                             //  ��5λ8��
			LCD->RAM[LCD_RAMRegister_1] &=  Clear1;           				// COM0--SEG
			LCD->RAM[LCD_RAMRegister_1] &=  Clear2; 
			LCD->RAM[LCD_RAMRegister_4] &=  Clear5;           				// COM1--SEG
			LCD->RAM[LCD_RAMRegister_4] &=  Clear6;		
			LCD->RAM[LCD_RAMRegister_8] &=  Clear1;           				// COM2--SEG
			LCD->RAM[LCD_RAMRegister_8] &=  Clear2;		
			LCD->RAM[LCD_RAMRegister_11] &=  Clear6;		     			// COM3--SEG	
			if( CLEAR != flag)
			{    
				LCD->RAM[LCD_RAMRegister_1] |=  PUTS1_S2(digit[0]);     	// COM0--SEG
				LCD->RAM[LCD_RAMRegister_4] |=  PUTS5_S6(digit[1]);			// COM1--SEG
				LCD->RAM[LCD_RAMRegister_8] |=  PUTS1_S2(digit[2]);			// COM2--SEG
				LCD->RAM[LCD_RAMRegister_11] |=  PUTS5_S6(digit[3]);		// COM3--SEG	
			}  
    	break;    
   		case 6:                                                             //  ��6λ8��
			LCD->RAM[LCD_RAMRegister_1] &=  Clear3;     					// COM0--SEG
			LCD->RAM[LCD_RAMRegister_1] &=  Clear4; 
			LCD->RAM[LCD_RAMRegister_4] &=  Clear7;     					// COM1--SEG
			LCD->RAM[LCD_RAMRegister_5] &=  Clear0;		
			LCD->RAM[LCD_RAMRegister_8] &=  Clear3;     					// COM2--SEG
			LCD->RAM[LCD_RAMRegister_8] &=  Clear4;		
			LCD->RAM[LCD_RAMRegister_12] &=  Clear0;		 				// COM3--SEG	
			if( CLEAR != flag)
			{    
				LCD->RAM[LCD_RAMRegister_1] |=  PUTS3_S4(digit[0]);    		// COM0--SEG
				LCD->RAM[LCD_RAMRegister_4] |=  PUTS7(digit[1]);       		// COM1--SEG
				LCD->RAM[LCD_RAMRegister_5] |=  PUTS0(digit[1]);			
				LCD->RAM[LCD_RAMRegister_8] |=  PUTS3_S4(digit[2]);			// COM2--SEG
				LCD->RAM[LCD_RAMRegister_12] |=  PUTS0(digit[3]);			// COM3--SEG				
			}  
    	break;
    
   		case 7:                                                             //  ��7λ8��
			LCD->RAM[LCD_RAMRegister_1] &=  Clear5;      					// COM0--SEG
			LCD->RAM[LCD_RAMRegister_1] &=  Clear6; 
			LCD->RAM[LCD_RAMRegister_5] &=  Clear1;      					// COM1--SEG
			LCD->RAM[LCD_RAMRegister_5] &=  Clear2; 		
			LCD->RAM[LCD_RAMRegister_8] &=  Clear5;       					// COM2--SEG
			LCD->RAM[LCD_RAMRegister_8] &=  Clear6;		
			LCD->RAM[LCD_RAMRegister_12] &=  Clear2;		   				// COM3--SEG

			if( CLEAR != flag)
			{    
				LCD->RAM[LCD_RAMRegister_1] |=  PUTS5_S6(digit[0]);      	// COM0--SEG
				LCD->RAM[LCD_RAMRegister_5] |=  PUTS1_S2(digit[1]);			// COM1--SEG
				LCD->RAM[LCD_RAMRegister_8] |=  PUTS5_S6(digit[2]);			// COM2--SEG
				LCD->RAM[LCD_RAMRegister_12] |=  PUTS1_S2(digit[3]);		// COM3--SEG			
			}
    	break;    
        
   		case 8:                                                             //  ��8λ8��
			LCD->RAM[LCD_RAMRegister_1] &=  Clear7;       					// COM0--SEG
			LCD->RAM[LCD_RAMRegister_2] &=  Clear0; 
			LCD->RAM[LCD_RAMRegister_5] &=  Clear3;       					// COM1--SEG
			LCD->RAM[LCD_RAMRegister_5] &=  Clear4;		
			LCD->RAM[LCD_RAMRegister_8] &=  Clear7;       					// COM2--SEG
			LCD->RAM[LCD_RAMRegister_9] &=  Clear0;		
			LCD->RAM[LCD_RAMRegister_12] &=  Clear4;		 				// COM3--SEG
			if( CLEAR != flag)
			{
				LCD->RAM[LCD_RAMRegister_1] |=  PUTS7(digit[0]);       		// COM0--SEG
				LCD->RAM[LCD_RAMRegister_2] |=  PUTS0(digit[0]); 
				LCD->RAM[LCD_RAMRegister_5] |=  PUTS3_S4(digit[1]);			// COM1--SEG
				LCD->RAM[LCD_RAMRegister_8] |=  PUTS7(digit[2]);       		// COM2--SEG
				LCD->RAM[LCD_RAMRegister_9] |=  PUTS0(digit[2]);			
				LCD->RAM[LCD_RAMRegister_12] |=  PUTS3_S4(digit[3]);		// COM3--SEG		
			}
    	break;

   		case 9:                                                             //  ��9λ8��
			LCD->RAM[LCD_RAMRegister_2] &=  Clear1;       					// COM0--SEG
			LCD->RAM[LCD_RAMRegister_2] &=  Clear2; 
			LCD->RAM[LCD_RAMRegister_5] &=  Clear5;       					// COM1--SEG
			LCD->RAM[LCD_RAMRegister_5] &=  Clear6;		
			LCD->RAM[LCD_RAMRegister_9] &=  Clear1;      					// COM2--SEG
			LCD->RAM[LCD_RAMRegister_9] &=  Clear2;		
			LCD->RAM[LCD_RAMRegister_12] &=  Clear6;		 				// COM3--SEG
			if( CLEAR != flag)
			{
				LCD->RAM[LCD_RAMRegister_2] |=  PUTS1_S2(digit[0]);       	// COM0--SEG
				LCD->RAM[LCD_RAMRegister_5] |=  PUTS5_S6(digit[1]);			// COM1--SEG
				LCD->RAM[LCD_RAMRegister_9] |=  PUTS1_S2(digit[2]);      	// COM2--SEG
				LCD->RAM[LCD_RAMRegister_12] |=  PUTS5_S6(digit[3]);		// COM3--SEG		
			}
    	break;		
		
   		case 10:                                                            //  ��10λ8��
			LCD->RAM[LCD_RAMRegister_2] &=  Clear3;     					// COM0--SEG
			LCD->RAM[LCD_RAMRegister_2] &=  Clear4; 
			LCD->RAM[LCD_RAMRegister_5] &=  Clear7;     					// COM1--SEG
			LCD->RAM[LCD_RAMRegister_6] &=  Clear0;		
			LCD->RAM[LCD_RAMRegister_9] &=  Clear3;     					// COM2--SEG
			LCD->RAM[LCD_RAMRegister_9] &=  Clear4;		
			LCD->RAM[LCD_RAMRegister_13] &=  Clear0;		 				// COM3--SEG	
			if( CLEAR != flag)
			{    
				LCD->RAM[LCD_RAMRegister_2] |=  PUTS3_S4(digit[0]);    		// COM0--SEG
				LCD->RAM[LCD_RAMRegister_5] |=  PUTS7(digit[1]);       		// COM1--SEG
				LCD->RAM[LCD_RAMRegister_6] |=  PUTS0(digit[1]);			
				LCD->RAM[LCD_RAMRegister_9] |=  PUTS3_S4(digit[2]);			// COM2--SEG
				LCD->RAM[LCD_RAMRegister_13] |=  PUTS0(digit[3]);			// COM3--SEG				
			}  
    	break;		
		
   		case 11:                                                            //  ��11λ8��
			LCD->RAM[LCD_RAMRegister_2] &=  Clear5;      					// COM0--SEG
			LCD->RAM[LCD_RAMRegister_2] &=  Clear6; 
			LCD->RAM[LCD_RAMRegister_6] &=  Clear1;      					// COM1--SEG
			LCD->RAM[LCD_RAMRegister_6] &=  Clear2; 		
			LCD->RAM[LCD_RAMRegister_9] &=  Clear5;       					// COM2--SEG
			LCD->RAM[LCD_RAMRegister_9] &=  Clear6;		
			LCD->RAM[LCD_RAMRegister_13] &=  Clear2;		   				// COM3--SEG

			if( CLEAR != flag)
			{    
				LCD->RAM[LCD_RAMRegister_2] |=  PUTS5_S6(digit[0]);      	// COM0--SEG
				LCD->RAM[LCD_RAMRegister_6] |=  PUTS1_S2(digit[1]);			// COM1--SEG
				LCD->RAM[LCD_RAMRegister_9] |=  PUTS5_S6(digit[2]);			// COM2--SEG
				LCD->RAM[LCD_RAMRegister_13] |=  PUTS1_S2(digit[3]);		// COM3--SEG			
			}
    	break;		
		
   		case 12:                                                            //  ��12λ8��
			LCD->RAM[LCD_RAMRegister_2] &=  Clear7;       					// COM0--SEG
			LCD->RAM[LCD_RAMRegister_3] &=  Clear0; 
			LCD->RAM[LCD_RAMRegister_6] &=  Clear3;       					// COM1--SEG
			LCD->RAM[LCD_RAMRegister_6] &=  Clear4;		
			LCD->RAM[LCD_RAMRegister_9] &=  Clear7;       					// COM2--SEG
			LCD->RAM[LCD_RAMRegister_10] &=  Clear0;		
			LCD->RAM[LCD_RAMRegister_13] &=  Clear4;		 				// COM3--SEG
			if( CLEAR != flag)
			{
				LCD->RAM[LCD_RAMRegister_2] |=  PUTS7(digit[0]);      		// COM0--SEG
				LCD->RAM[LCD_RAMRegister_3] |=  PUTS0(digit[0]); 
				LCD->RAM[LCD_RAMRegister_6] |=  PUTS3_S4(digit[1]);			// COM1--SEG
				LCD->RAM[LCD_RAMRegister_9] |=  PUTS7(digit[2]);       		// COM2--SEG
				LCD->RAM[LCD_RAMRegister_10] |=  PUTS0(digit[2]);			
				LCD->RAM[LCD_RAMRegister_13] |=  PUTS3_S4(digit[3]);		// COM3--SEG		
			}
    	break;		
		
   		case 13:                                                            //  ��13λ8��
			LCD->RAM[LCD_RAMRegister_3] &=  Clear1;       					// COM0--SEG
			LCD->RAM[LCD_RAMRegister_3] &=  Clear2; 
			LCD->RAM[LCD_RAMRegister_6] &=  Clear5;       					// COM1--SEG
			LCD->RAM[LCD_RAMRegister_6] &=  Clear6;		
			LCD->RAM[LCD_RAMRegister_10] &=  Clear1;      					// COM2--SEG
			LCD->RAM[LCD_RAMRegister_10] &=  Clear2;		
			LCD->RAM[LCD_RAMRegister_13] &=  Clear6;		 				// COM3--SEG
			if( CLEAR != flag)
			{
				LCD->RAM[LCD_RAMRegister_3] |=  PUTS1_S2(digit[0]);       	// COM0--SEG
				LCD->RAM[LCD_RAMRegister_6] |=  PUTS5_S6(digit[1]);			// COM1--SEG
				LCD->RAM[LCD_RAMRegister_10] |=  PUTS1_S2(digit[2]);      	// COM2--SEG
				LCD->RAM[LCD_RAMRegister_13] |=  PUTS5_S6(digit[3]);		// COM3--SEG		
			}
    	break;		
		
   		case 14:                                                            //  ��14λ8��
			LCD->RAM[LCD_RAMRegister_3] &=  Clear3;     					// COM0--SEG
			LCD->RAM[LCD_RAMRegister_14] &=  Clear0; 
			LCD->RAM[LCD_RAMRegister_6] &=  Clear7;     					// COM1--SEG
			LCD->RAM[LCD_RAMRegister_16] &=  Clear0;		
			LCD->RAM[LCD_RAMRegister_10] &=  Clear3;     					// COM2--SEG
			LCD->RAM[LCD_RAMRegister_18] &=  Clear0;
			LCD->RAM[LCD_RAMRegister_20] &=  Clear0;		 				// COM3--SEG	
			if( CLEAR != flag)
			{    
				LCD->RAM[LCD_RAMRegister_3] |= ( PUTS3_0(digit[0]) & 0x0F); // COM0--SEG
				LCD->RAM[LCD_RAMRegister_14] |= ( PUTS0(digit[0]) & 0X01);
				LCD->RAM[LCD_RAMRegister_6] |=  PUTS7_0(digit[1]);          // COM1--SEG
				LCD->RAM[LCD_RAMRegister_16] |=  (PUTS0(digit[1]) & 0X01);			
				LCD->RAM[LCD_RAMRegister_10] |=  (PUTS3_0(digit[2]) & 0x0F);// COM2--SEG
				LCD->RAM[LCD_RAMRegister_18] |=  (PUTS0(digit[2]) & 0X01);
				LCD->RAM[LCD_RAMRegister_20] |=  ( PUTS0(digit[3]) & 0X01);	// COM3--SEG				
			}  
    	break;
		
   		case 15:                                                            //  ��15λ8��
			LCD->RAM[LCD_RAMRegister_14] &=  Clear1;    					// COM0--SEG
			LCD->RAM[LCD_RAMRegister_14] &=  Clear2;  
			LCD->RAM[LCD_RAMRegister_16] &=  Clear1;      					// COM1--SEG
			LCD->RAM[LCD_RAMRegister_16] &=  Clear2; 		
			LCD->RAM[LCD_RAMRegister_18] &=  Clear1;      					// COM2--SEG
			LCD->RAM[LCD_RAMRegister_18] &=  Clear2;
			LCD->RAM[LCD_RAMRegister_20] &=  Clear2;		 				// COM3--SEG	
			if( CLEAR != flag)
			{    
				LCD->RAM[LCD_RAMRegister_14] |=  PUTS1_S2(digit[0]);    	// COM0--SEG
				LCD->RAM[LCD_RAMRegister_16] |=  PUTS1_S2(digit[1]);        // COM1--SEG
				LCD->RAM[LCD_RAMRegister_18] |=  PUTS1_S2(digit[2]);    	// COM2--SEG
				LCD->RAM[LCD_RAMRegister_20] |=  PUTS1_S2(digit[3]);		// COM3--SEG				
			}  
    	break;
    	default:
    	break;
  }
}



/**

  * @brief  This function writes a MARK in the LCD frame buffer.
  * @param  ch: the MARK to dispaly.
              O ���� OPEN  ��MARK:����
              C ���� close  ��MARK:���� 
              F ���� fault  ��MARK:���ϣ�Ȧ�棩
              S ���� Set  ��MARK:�趨�¶�
              T ���� time  ��MARK:20(2088��20)���ꡢ�¡��ա�����
              I ���� Input  ��MARK:  �����¶�
              E ���� export  ��MARK:�����¶�
              D ���� Drop��MARK:13,14 �е������㣨ʱ�ӵ������㣩
              H ���� heat��MARK:�ۼ�����
              M ���� coMmunication��MARK:ͨѶ
              P ���� temPerature��MARK: ��c
              K ���� kW.H��MARK: kW.h
              A ���� û�С��¡�����ĸ��MARK: 1���µ�ʮλ��
              U ���� hoUr��MARK: h 
              N ���� sigNal��MARK: �ź�ǿ��(|||)
              W ���� toWer��MARK: �ź���
              Z ���� Zero signal ��MARK: ���źţ�x�� 
              B ���� Battery ��MARK: ��ط��� 
              R ���� aRrearage ��MARK: Ƿ�� 
              G ���� ,  ��MARK:8p
              Q ����  ��MARK: 14p 

  * @param  flag: �����־�� ��CLEAR �����Write д��
  * @retval None
  * @par    Required preconditions: The LCD should be cleared before to start the
  *         write operation.
  */
void LCD_MARK_WriteChar(uint8_t* ch, LCD_CLEAR_FLAG flag)
{
  switch (*ch)
  {   
    case 'O':                                                                //  O ���� OPEN  ��MARK:����
    case 'o':
    LCD->RAM[LCD_RAMRegister_14] &=  Clear3;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_14] |=  bit(3);
    }
    break;
    
    case 'C':                                                                //  C ���� close  ��MARK:����
    case 'c':
    LCD->RAM[LCD_RAMRegister_16] &=  Clear3;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_16] |=  bit(3);
    }
    break; 
    
    case 'F':                                                                //  F ���� fault  ��MARK:���ϣ�Ȧ�棩
    case 'f':
    LCD->RAM[LCD_RAMRegister_13] &=  Clear3;

    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_13] |=  bit(3);
    }
    break;
    
    case 'S':                                                                //  S ���� Set  ��MARK:�趨�¶�
    case 's':
    LCD->RAM[LCD_RAMRegister_7] &=   Clear0;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_7] |=  bit(0);
    }
    break;    
    
    case 'T':                                                                //  T ���� time  ��MARK:20(2088��20)���ꡢ�¡��ա�����
    case 't':
    LCD->RAM[LCD_RAMRegister_10] &=   Clear5;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_10] |=  bit(5);
    }
    break; 
    
    case 'I':                                                                //  I ���� Input  ��MARK:  �����¶�
    case 'i':
    LCD->RAM[LCD_RAMRegister_3] &=   Clear4;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_3] |=  bit(4);
      LCD->RAM[LCD_RAMRegister_10] &=   Clear4;
    }
    break;    
        
    case 'E':                                                                //  E ���� export  ��MARK:�����¶�
    case 'e':
    LCD->RAM[LCD_RAMRegister_10] &=   Clear4;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_10] |=  bit(4);
    }
    break; 
   
    case 'D':                                                                //  D ���� Drop��MARK:13,14 �е������㣨ʱ�ӵ������㣩
    case 'd':
    LCD->RAM[LCD_RAMRegister_0] &=   Clear0;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_0] |=  bit(0);
    }
    break;    
    
    case 'H':                                                                //  H ���� heat��MARK:�ۼ�����
    case 'h':
    LCD->RAM[LCD_RAMRegister_18] &=   Clear3;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_18] |=  bit(3);
    }
    break;    
    
    case 'M':                                                                //  M ���� coMmunication��MARK:ͨѶ
    case 'm':
    LCD->RAM[LCD_RAMRegister_20] &=   Clear3;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_20] |=  bit(3);
    }
    break;    
    
    case 'P':                                                                //  P ���� temPerature��MARK: ��c
    case 'p':
    LCD->RAM[LCD_RAMRegister_12] &=   Clear5;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_12] |=  bit(5);
    }
    break;    
    
    case 'K':                                                                //  K ���� kW.H��MARK: kW.h
    case 'k':
    LCD->RAM[LCD_RAMRegister_20] &=   Clear1;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_20] |=  bit(1);
    }
    break;    
    
    case 'A':                                                                //  A ���� û�С��¡�����ĸ��MARK: 1���µ�ʮλ��
    case 'a':
    LCD->RAM[LCD_RAMRegister_11] &=   Clear1;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_11] |=  bit(1);
    }
    break;    

    case 'U':                                                                //  U ���� hoUr��MARK: h 
    case 'u':
    LCD->RAM[LCD_RAMRegister_13] &=   Clear5;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_13] |=  bit(5);
    }
    break; 

    case 'N':                                                                //  N ���� sigNal��MARK: �ź�����ح 
    case 'n':
    LCD->RAM[LCD_RAMRegister_11] &=   Clear7;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_11] |=  bit(7);
    }
    break;
    
    case 'W':                                                                //  W ���� toWer��MARK: �ź���
    case 'w':
    LCD->RAM[LCD_RAMRegister_11] &=   Clear5;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_11] |=  bit(5);
    }
    break;    

    case 'Z':                                                                //  Z ���� Zero signal ��MARK: ���źţ�x�� 
    case 'z':
    LCD->RAM[LCD_RAMRegister_11] &=   Clear3;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_11] |=  bit(3);
    }
    break;

    case 'B':                                                                //  B ���� Battery ��MARK: ��ط��� 
    case 'b':
    LCD->RAM[LCD_RAMRegister_13] &=   Clear1;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_13] |=  bit(1);
    }
    break;    
    
    case 'R':                                                                //  R ���� aRrearage ��MARK: Ƿ�� 
    case 'r':
    LCD->RAM[LCD_RAMRegister_12] &=   Clear7;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_12] |=  bit(7);
    }
    break;    

    
    case 'G':                                                                //  G ���� ,  ��MARK:8p
    case 'g':
    LCD->RAM[LCD_RAMRegister_12] &=   Clear3;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_12] |=  bit(3);
    }
    break;         
    
    case 'Q':                                                                //  Q ����  ��MARK: 14p 
    case 'q':
    LCD->RAM[LCD_RAMRegister_13] &=   Clear7;
    if( CLEAR != flag)
    {
      LCD->RAM[LCD_RAMRegister_13] |=  bit(7);
    }
    break;   
    
    default:
      break;
  }
  
}



/**
  * @brief  This function Write the whole LCD RAM.
  * @param  None
  * @retval None
  */
void LCD_Whole_Display(void)
{
  uint8_t counter = 0;
  for (counter = 0;counter < 0x16; counter++)
  {
    LCD->RAM[counter] =  0xFF;
  }
}



/**
  * @brief  This function Clear the whole LCD RAM.
  * @param  None
  * @retval None
  */
void LCD_Whole_Clear(void)
{
  uint8_t counter = 0;
  for (counter = 0;counter < 0x16; counter++)
  {
    LCD->RAM[counter] =  LCD_RAM_RESET_VALUE;
  }
}


/**
  * @brief  This function Display DATE  on LCD
  * @param  year  --  the year whitch lcd to display  
            month  --  the month whitch lcd to display
            day  --  the day whitch lcd to display
            flag  --  �����־�� ��CLEAR �����Write д��
 * @retval None
       year display 88, parameter year > 99
       month display 88, parameter month > 12
       day display 88, parameter day > 31
       week display 9, parameter week > 7
       uint8_t  > 0
 */ 
void LCD_Date_Display(uint16_t year, uint8_t month, uint8_t day, uint8_t week, LCD_CLEAR_FLAG flag)
{ 
	uint8_t yearH,yearL;
	uint8_t monthH, monthL;
	uint8_t dayH, dayL;
		
	bool year_parameter_symbol = TRUE;
	bool month_parameter_symbol = TRUE;
	bool day_parameter_symbol = TRUE; 
	bool week_parameter_symbol = TRUE;	
//	year = year - 2000;
	 if(week == 0)
 	{
		week = 7;
	}
	yearH = (uint8_t)(year / 10) ;
	yearL = (uint8_t)(year % 10) ;
	monthH = (uint8_t)(month / 10) ;
	monthL = (uint8_t)(month % 10) ;
	dayH = (uint8_t)(day / 10) ;
	dayL = (uint8_t)(day % 10) ;
	                                   // parameter check
//        printf("year = %d, yearH = %d, yearL = %d\r\n", year, yearH, yearL);
	if(year > (uint8_t)99)               							//  year display 88, parameter year > 99
	{
		year_parameter_symbol = FALSE;
		LCD_NUM_WriteChar(8, LCD_YEAR_H_POSITION, flag);		    // YEAR_H_POSITION,
    	LCD_NUM_WriteChar(8, LCD_YEAR_L_POSITION, flag);            // YEAR_L_POSITION,
	}
	
	if(month > (uint8_t)12)               							//  month display 88, parameter month > 12
	{
		month_parameter_symbol = FALSE;
		LCD_MARK_WriteChar("A", flag);           					//  A ���� û�С��¡�����ĸ��MARK: 1���µ�ʮλ��
    	LCD_NUM_WriteChar(8, LCD_MONTH_L_POSITION, flag);           // MONTH_L_POSITION,
	}
	
	if(day > (uint8_t)31)               							//  day display 88, parameter day > 31
	{
		day_parameter_symbol = FALSE;
		LCD_NUM_WriteChar(8, LCD_DAY_H_POSITION, flag);		        //   DAY_H_POSITION,
    	LCD_NUM_WriteChar(8, LCD_DAY_L_POSITION, flag);             //   DAY_L_POSITION,
	}
	
	if(week > (uint8_t)7)               							//  week display 9, parameter week > 7
	{
		week_parameter_symbol = FALSE;
		LCD_NUM_WriteChar(9, LCD_WEEK_POSITION, flag);		        //   DAY_H_POSITION,
	}
		 
	
  	LCD_MARK_WriteChar("T", CLEAR);    								//  T ���� time  ��MARK:20(2088��20)���ꡢ�¡��ա�����
  	if( CLEAR != flag)
	{
		LCD_MARK_WriteChar("T", flag);    							//  T ���� time  ��MARK:20(2088��20)���ꡢ�¡��ա�����
	}


	if(year_parameter_symbol == TRUE)       //  year
	{  
    	LCD_NUM_WriteChar(yearH, LCD_YEAR_H_POSITION, flag);		// YEAR_HOUR_H_POSITION,
    	LCD_NUM_WriteChar(yearL, LCD_YEAR_L_POSITION, flag);        //  YEAR_HOUR_L_POSITION,
	}  
	
	if(month_parameter_symbol == TRUE)      // month      
	{  
		if(monthH >= 1)
		{
			LCD_MARK_WriteChar("A", flag);           				//  A ���� û�С��¡�����ĸ��MARK: 1���µ�ʮλ��
		}
		else
		{
			LCD_MARK_WriteChar("A", CLEAR);           				//  A ���� û�С��¡�����ĸ��MARK: 1���µ�ʮλ��
		}
    	LCD_NUM_WriteChar(monthL, LCD_MONTH_L_POSITION, flag);	    // MONTH_L_POSITION,
	} 

	if(day_parameter_symbol == TRUE)       //  day 
	{  
		if(dayH == 0)
		{
            LCD_NUM_WriteChar(dayH, LCD_DAY_H_POSITION, CLEAR);		//   DAY_H_POSITION,
			LCD_NUM_WriteChar(dayL, LCD_DAY_L_POSITION, flag);	    //   DAY_L_POSITION,
		}
		else
		{
		    LCD_NUM_WriteChar(dayH, LCD_DAY_H_POSITION, flag);		//   DAY_H_POSITION,
		    LCD_NUM_WriteChar(dayL, LCD_DAY_L_POSITION, flag);	    //   DAY_L_POSITION,
	    }
	} 
	
  	if(week_parameter_symbol == TRUE)       //  week 
	{	
		if(week == 0)
		{
			LCD_NUM_WriteChar(8, LCD_WEEK_POSITION, flag);		    //   WEEK_POSITION,
		} 
		else
		{
    		LCD_NUM_WriteChar(week, LCD_WEEK_POSITION, flag);		//   WEEK_POSITION,
		}
		
	}
   
}




/**
  * @brief  This function Display  TIME on LCD
  * @param  hour  --  the hour whitch lcd to display
            minute  --  the minute whitch lcd to display
            second  --  the second whitch lcd to display
            flag  --  �����־�� ��CLEAR �����Write д��
 * @retval None
           hour display 88, parameter hour > 23
           minute display 88, parameter minute > 59
           second display 88, parameter second > 59
        uint8_t  > 0
 */ 
void LCD_Time_Display(uint8_t hour, uint8_t minute, LCD_CLEAR_FLAG flag)
{ 
	uint8_t hourH, hourL;
	uint8_t minuteH, minuteL;
//	uint8_t Timeflag;

	bool hour_parameter_symbol = TRUE;
	bool minute_parameter_symbol = TRUE;

	hourH = (uint8_t)(hour / 10);
	hourL = (uint8_t)(hour % 10);
	minuteH = (uint8_t)(minute / 10);
	minuteL = (uint8_t)(minute % 10);
	                                                                     
		                                    // parameter check
	if(hour > (uint8_t)23)               	//  hour display 88, parameter hour > 23
	{
		hour_parameter_symbol = FALSE;
		LCD_NUM_WriteChar(8, LCD_HOUR_H_POSITION, flag);		        //   HOUR_H_POSITION,
		LCD_NUM_WriteChar(8, LCD_HOUR_L_POSITION, flag);             	//   HOUR_L_POSITION,
	}		

	if(minute > (uint8_t)59)               	//  minute display 88, parameter minute > 59
	{
		minute_parameter_symbol = FALSE;
		LCD_NUM_WriteChar(8, LCD_MINUTE_H_POSITION, flag);		        //   MINUTE_H_POSITION,
		LCD_NUM_WriteChar(8, LCD_MINUTE_L_POSITION, flag);            	//   MINUTE_L_POSITION,
	}

	
	if(hour_parameter_symbol == TRUE)      	// hour 
	{  
		LCD_NUM_WriteChar(hourH, LCD_HOUR_H_POSITION, flag);		     // YEAR_HOUR_H_POSITION,
		LCD_NUM_WriteChar(hourL, LCD_HOUR_L_POSITION, flag);             //  YEAR_HOUR_L_POSITION,
	} 
 	
  	LCD_MARK_WriteChar("D", CLEAR);    									//  D ���� Drop��MARK:13,14 �е������㣨ʱ�ӵ������㣩
    if( CLEAR != flag)
	{
		LCD_MARK_WriteChar("D", flag);    								//  D ���� Drop��MARK:13,14 �е������㣨ʱ�ӵ������㣩
	}
	
	if(minute_parameter_symbol == TRUE)      // minute
	{  
		LCD_NUM_WriteChar(minuteH, LCD_MINUTE_H_POSITION, flag);		  // MONTH_MINUTE_H_POSITION,
		LCD_NUM_WriteChar(minuteL, LCD_MINUTE_L_POSITION, flag);	      // MONTH_MINUTE_L_POSITION,
	} 
   
   
}



/**
  * @brief  This function Display  TEMPERATURE on LCD
  * @param  PT_Temp_100  --  the TEMPERATURE 100times whitch lcd to display
                      flag  --  �����־�� ��CLEAR �����Write д��
 * @retval None
           display 88.8, parameter Temp > 99��
           display 00.0, parameter Temp < 0��
           uint16_t  > 0
*/
void LCD_Temp_Display(u16 DS18B20_Temp_100, LCD_PT_TEMP_TYPE PT_Temp_type, LCD_CLEAR_FLAG flag)
{ 
    LCD_MARK_WriteChar("I", CLEAR);             //����趨�¶ȱ�־
	if(PT_Temp_type == INPUT)
	{
		LCD_MARK_WriteChar("I", flag);          // I ���� Input  ��MARK:  �����¶� 
        LCD_MARK_WriteChar("S", CLEAR); 
	}	
	else                  
	{	
		LCD_MARK_WriteChar("E", flag);          // E ���� export  ��MARK:�����¶� 
        LCD_MARK_WriteChar("S", CLEAR);
	}
		
	LCD_MARK_WriteChar("P", flag);            	// P ���� temPerature��MARK: ��c

	bool DS18B20_Temp_100_symbol = TRUE;
	if(DS18B20_Temp_100 > (u16)9900)         //  hour display 88, parameter hour > 23
	{
		DS18B20_Temp_100_symbol = FALSE;
		LCD_NUM_WriteChar(8, LCD_TEMP_D_POSITION, flag);		     // LCD_TEMP_D_POSITION    �¶�ʮλ
		LCD_NUM_WriteChar(8, LCD_TEMP_U_POSITION, flag);             //  LCD_TEMP_U_POSITION    �¶ȸ�λ	
		LCD_NUM_WriteChar(8, LCD_TEMP_P_POSITION, flag);             //  LCD_TEMP_P_POSITION    �¶ȵ�һ��С����λ
	}	
	if(DS18B20_Temp_100_symbol != FALSE )       // �¶���ʾ            
	{	
		DS18B20_Temp_100 += (u16)5;        	// DS18B20_Temp_100 ��������
		u8	DS18B20_Temp_100_K = 0;         //  ǧλ
		u8	DS18B20_Temp_100_H = 0;		    // ��λ
		u8	DS18B20_Temp_100_D = 0;		    // ʮλ
			
		DS18B20_Temp_100_K = (uint8_t)(DS18B20_Temp_100 / (uint16_t)1000);        					//  ǧλ
		DS18B20_Temp_100_H = (uint8_t)((DS18B20_Temp_100 % (uint16_t)1000) / (uint16_t)100);       // ��λ
		DS18B20_Temp_100_D =	(uint8_t)(((DS18B20_Temp_100 % (uint16_t)1000) % (uint16_t)100) / (uint16_t)10);  // ʮλ				

		LCD_NUM_WriteChar(DS18B20_Temp_100_K, LCD_TEMP_D_POSITION, flag);		      // LCD_TEMP_D_POSITION    �¶�ʮλ
		LCD_NUM_WriteChar(DS18B20_Temp_100_H, LCD_TEMP_U_POSITION, flag);             //  LCD_TEMP_U_POSITION    �¶ȸ�λ	 
		LCD_MARK_WriteChar("G", flag);          // G ���� ,  ��MARK:8p  
		LCD_NUM_WriteChar(DS18B20_Temp_100_D, LCD_TEMP_P_POSITION, flag);             //  LCD_TEMP_P_POSITION    �¶ȵ�һ��С����λ
	}
        // debug
//	if(DS_18B20Controler.Sys_Temp==8880)
//	{
//		LCD_MARK_WriteChar("P", CLEAR); 		// P ���� temPerature��MARK: ��c
//	}
}

/**
  * @brief  This function set  TEMPERATURE on LCD
  * @param  Set_Temp_100  --  the TEMPERATURE 100times whitch lcd to set
            flag  --  �����־�� ��CLEAR �����Write д��
 * @retval None
           ����趨���¶� �� SET_HIGH_100����ʾ SET_HIGH_100
           ����趨���¶� �� SET_LOW_100����ʾ SET_LOW_100
           uint16_t  > 0
*/
void LCD_Temp_Set(uint16_t Set_Temp_100, LCD_PT_TEMP_TYPE PT_Temp_type, LCD_CLEAR_FLAG flag)
{ 
	
	if(PT_Temp_type == T_SET)
	{
		uint8_t	Set_Temp_100_K = 0;          	//  ǧλ
		uint8_t	Set_Temp_100_H = 0;		       	// ��λ
		uint8_t	Set_Temp_100_D = 0;		       	// ʮλ
		
		LCD_MARK_WriteChar("I", CLEAR);			//              Clear ,  MARK:  �����¶�
		LCD_MARK_WriteChar("E", CLEAR);			//              Clear ,  MARK:  �����¶�
		LCD_MARK_WriteChar("S", flag);          // S ���� Set  ��MARK:�趨�¶�
		LCD_MARK_WriteChar("P", flag);          // P ���� temPerature��MARK:     ��c

		Set_Temp_100_K = (uint8_t)(Set_Temp_100 / (uint16_t)1000);      					//  ǧλ
		Set_Temp_100_H = (uint8_t)((Set_Temp_100 % (uint16_t)1000) / (uint16_t)100);       // ��λ
		Set_Temp_100_D = (uint8_t)(((Set_Temp_100 % (uint16_t)1000) % (uint16_t)100) / (uint16_t)10);  // ʮλ				
	
		LCD_NUM_WriteChar(Set_Temp_100_K, LCD_TEMP_D_POSITION, flag);		          	// LCD_TEMP_D_POSITION    �¶�ʮλ
		LCD_NUM_WriteChar(Set_Temp_100_H, LCD_TEMP_U_POSITION, flag);             		//  LCD_TEMP_U_POSITION    �¶ȸ�λ	 
		LCD_MARK_WriteChar("G", flag);          // G ���� ,  ��MARK:8p  
		LCD_NUM_WriteChar(Set_Temp_100_D, LCD_TEMP_P_POSITION, flag);            		//  LCD_TEMP_P_POSITION    �¶ȵ�һ��С����λ
	}
}



/**
  * @brief  This function display PowerOn  screen
  * @param  None
  * @retval None
  */
void LCD_PowerOn_Display(void)
{
    
    
}

/**
  * @brief  This function display the LCD HEAT value
  * @param  None
  * @retval None
  */
void  LCD_HEAT_Display(u32 Heat_Value, LCD_CLEAR_FLAG flag)
{
	uint8_t	Heat_Value_HT = 0;                    	//   ���� ʮ��λ     hundred   thoUsand
	uint8_t	Heat_Value_TT = 0;                    	//   ����  ��λ TEN  THOUSAND
	uint8_t	Heat_Value_U = 0;                    	//   ����  ǧλ   thoUsand
	uint8_t	Heat_Value_H = 0;		       			// ����   ��λ  hundred
	uint8_t	Heat_Value_T = 0;		       			//  ����  ʮλ TEN
	uint8_t	Heat_Value_O = 0;		       			//  ����  ��λ  ONE

	LCD_MARK_WriteChar("H",flag);		     		//  H ���� heat��MARK:�ۼ�����
	LCD_MARK_WriteChar("K",flag);		    	 	//   K ���� kW.H��MARK: kW.h
	 
    bool Heat_Value_symbol = TRUE; 
	if(Heat_Value  > (u32)99999999) 				//  hour display 88, parameter hour > 23
	{
		Heat_Value_symbol = FALSE;
		LCD_NUM_WriteChar(8, Heat_Value_HT_POSITION, flag);		          	//   ���� ʮ��λ     
		LCD_NUM_WriteChar(8, Heat_Value_TT_POSITION, flag);              	//   ����  ��λ 
		LCD_NUM_WriteChar(8, Heat_Value_U_POSITION, flag);             		//   ����  ǧλ 
		LCD_NUM_WriteChar(8, Heat_Value_H_POSITION, flag);		         	// ����   ��λ  
		LCD_NUM_WriteChar(8, Heat_Value_T_POSITION, flag);              	//  ����  ʮλ 
		LCD_NUM_WriteChar(8, Heat_Value_O_POSITION, flag);             		//  ����  ��λ  
	}			

	if(Heat_Value_symbol != FALSE )       // �¶���ʾ            
	{		
		Heat_Value_HT  =  (uint8_t)(Heat_Value /(u32)10000000 );          //     ʮ��λ   
		Heat_Value_TT  =  (uint8_t)((Heat_Value % (u32)10000000 )  /  (u32)1000000);           //  ��λ 
		Heat_Value_U  =  (uint8_t)(((Heat_Value % (u32)10000000 )  %  (u32)1000000)    /  (u32)100000);            //  ǧλ  
		Heat_Value_H  =  (uint8_t)((((Heat_Value % (u32)10000000 )  %  (u32)1000000)    %  (u32)100000)  /  (u32)10000);         // ��λ
		Heat_Value_T  =  (uint8_t)(((((Heat_Value % (u32)10000000 )  %  (u32)1000000)    %  (u32)100000)  %  (u32)10000)  /  (u32)1000);          // ʮλ
		Heat_Value_O  =  (uint8_t)((((((Heat_Value % (u32)10000000 )  %  (u32)1000000)    %  (u32)100000)  %  (u32)10000)  %   (u32)1000) / (u32)100);           // ��λ
  
		LCD_NUM_WriteChar(Heat_Value_HT, Heat_Value_HT_POSITION, flag);		          	//   ���� ʮ��λ     
		LCD_NUM_WriteChar(Heat_Value_TT, Heat_Value_TT_POSITION, flag);              	//   ����  ��λ D
		LCD_NUM_WriteChar(Heat_Value_U, Heat_Value_U_POSITION, flag);             		//   ����  ǧλ 
		LCD_NUM_WriteChar(Heat_Value_H, Heat_Value_H_POSITION, flag);		         	// ����   ��λ  
		LCD_NUM_WriteChar(Heat_Value_T, Heat_Value_T_POSITION, flag);             	 	//  ����  ʮλ 
		LCD_NUM_WriteChar(Heat_Value_O, Heat_Value_O_POSITION, flag);             		//  ����  ��λ  
	}	

}




/**
  *  brief  This function display the LCD HEAT time
  * @param  Total_OpTim	--	�ۼƿ���ʱ��
  * @flag  --  �����־�� ��CLEAR �����Write д��
  * retval None
  */
void  LCD_HEAT_Time_Display(u32 Total_OpTim, LCD_CLEAR_FLAG flag)
{
	uint8_t	Heat_Time_U = 0;             	//   ����ʱ��  ǧλ   thoUsand
	uint8_t	Heat_Time_H = 0;		       	//   ����ʱ��   ��λ  hundred
	uint8_t	Heat_Time_T = 0;		       	//  ����ʱ��  ʮλ TEN
	uint8_t	Heat_Time_O = 0;		       	//  ����ʱ��  ��λ  ONE

	LCD_MARK_WriteChar("H",flag);		    //  H ���� heat��MARK:�ۼ�����
	LCD_MARK_WriteChar("U",flag);		    //  U ���� hoUr��MARK: h 
	 
    bool Heat_Time_symbol = TRUE;

	if(Total_OpTim  > (u32)9999*3600)                 //  hour display 88, parameter hour > 23
	{
		Heat_Time_symbol = FALSE;
		LCD_NUM_WriteChar(8, Heat_Time_U_POSITION, flag);		      //   ����ʱ�� ǧλ     
		LCD_NUM_WriteChar(8, Heat_Time_H_POSITION, flag);             //   ����ʱ��  ��λ 
		LCD_NUM_WriteChar(8, Heat_Time_T_POSITION, flag);             //   ����ʱ��  ʮλ 
		LCD_NUM_WriteChar(8, Heat_Time_O_POSITION, flag);		      //    ����ʱ��  ��λ  
	}			

	if(Heat_Time_symbol != FALSE )       // �¶���ʾ            
	{	
		
		Heat_Time_U  =  (uint8_t)((Total_OpTim /  (u32)3600) /  (u32)1000);            //  ǧλ  
		Heat_Time_H  =  (uint8_t)(((Total_OpTim /  (u32)3600) %  (u32)1000) / (u32)100);         // ��λ
		Heat_Time_T  =  (uint8_t)((((Total_OpTim /  (u32)3600) %  (u32)1000) % (u32)100) / 10);         // ʮλ
		Heat_Time_O  =  (uint8_t)((((Total_OpTim /  (u32)3600) %  (u32)1000) % (u32)100) % 10);          // ��λ
         
		LCD_NUM_WriteChar(Heat_Time_U, Heat_Time_U_POSITION, flag);             //   ����ʱ��  ǧλ 
		LCD_NUM_WriteChar(Heat_Time_H, Heat_Time_H_POSITION, flag);		       	// ����ʱ��   ��λ  
		LCD_NUM_WriteChar(Heat_Time_T, Heat_Time_T_POSITION, flag);             //  ����ʱ��  ʮλ 
		LCD_NUM_WriteChar(Heat_Time_O, Heat_Time_O_POSITION, flag);             //  ����ʱ��  ��λ  
	}	
}
   
   

/**
  * @brief  This function display the LCD MARK
  * @param  None
  * @retval None
  */
void LCD_MARK_Display(void)
{
  //debug
//	if(DevPara_DATA.ValvePosition == Valve_Open)      	//  ����  
//	{
//		LCD_MARK_WriteChar("O", WRITE);   				//   O ���� OPEN  ��MARK:���� ,д
//		LCD_MARK_WriteChar("C", CLEAR);
//	} 	
//
//	if(DevPara_DATA.ValvePosition == Valve_Close)   	//  ���� 
//	{
//		LCD_MARK_WriteChar("C", WRITE);    				//  C ���� close  ��MARK:���� , д
//		LCD_MARK_WriteChar("O", CLEAR);		
//	} 
//
//	if((DevPara_DATA.ValvePosition == Valve_Middle)||(DevPara_DATA.ValvePosition == Valve_Execute))//���ڿ�����ط� 
//	{
//		LCD_MARK_WriteChar("C", CLEAR);
//		LCD_MARK_WriteChar("O", CLEAR);
//	}
//
// 	if(DevPara_DATA.ArrearFlg == 0xAA)         			//  Ƿ��   
//	{
//		LCD_MARK_WriteChar("R", WRITE);         		//   R ���� aRrearage ��MARK: Ƿ�� ,     д
//	} 
//	else
//	{
//		 LCD_MARK_WriteChar("R", CLEAR);        		// R ���� aRrearage ��MARK: Ƿ�� �� ��
//	} 


}



/*
 DevWorkState_DispCtrl
 �豸����״̬��ʾ������
 */
void DevWorkState_DispCtrl(void)
{
  // debug
//	if(LCD_Blink.BlinkFlg == Flag_True) 
//	{
//		LCD_MARK_WriteChar("Z", CLEAR);						// ͨ��ʧ��   Z ���� Zero signal ��MARK: ���źţ�x�� 
//		if(LCD_Blink.BlinkNum < LCD_MARK_BLINK_NUM * 2)  //
//		{
//			
//			if(SystemTick_ms - LCD_Blink.BlinkTimeRcrd >= 250)  	// ��˸Ƶ��  0.25s
//			{
//				if(LCD_Blink.BlinkNum % 2 == 0)
//				{
//					LCD_MARK_WriteChar("N", CLEAR);			//N ���� sigNal��MARK: �źű�־(|||)			
//				}	
//				if(LCD_Blink.BlinkNum % 2 == 1)
//				{
//					LCD_MARK_WriteChar("N", WRITE); 
//				}
//                LCD_Blink.BlinkTimeRcrd = SystemTick_ms;
//                LCD_Blink.BlinkNum += 1;	
//			}
//		}	
//		else
//		{
//			LowPower_Ctrler.LowPow_LCD_Flg =Flag_True;
//			LCD_Blink.BlinkNum = 0;
//            LCD_Blink.BlinkFlg = Flag_False;
//            LCD_MARK_WriteChar("N", WRITE); 
//		}
//	}
//
//
//	if(DeviceState_DATA.Battery_Level == Flag_False)			//�����ص�������
//	{
//		LCD_MARK_WriteChar("B", CLEAR); 
//	}
//	else if(DeviceState_DATA.Battery_Level == Flag_True)	  //  B ���� Battery ��MARK: ��ط���  //�����ص������ľ�
//	{
//		LCD_MARK_WriteChar("B", WRITE); 
//
//	}
//
//	//ͨ�Ź����ж�
//	if(ComCheck.ComFailRecord >= COM_FAIL_TOTAL_NUM)	
//	{
//		
//		DeviceState_DATA.COM_Fault=Flag_True;
//	}
//	else
//	{
//		
//		DeviceState_DATA.COM_Fault=Flag_False;
//	}
//	
//	//ͨ�Ź��ϼ�¼����
//	if(DevPara_DATA.COM_Fault !=DeviceState_DATA.COM_Fault)
//	{
//		DevPara_DATA.COM_Fault=DeviceState_DATA.COM_Fault;
//		DevPara_DATA_Save();
//	}
//	if((DevPara_DATA.COM_Fault !=Flag_False)||(DevPara_DATA.Valve_State !=Flag_False))
//	{
//		LCD_MARK_WriteChar("F", WRITE); 
//	}
//	else
//	{
//		LCD_MARK_WriteChar("F", CLEAR); 
//
//	}
//
//
//
//	//ͨ��ģ���Լ�ͨ������ָʾ
//	if(SI4432Falt_Flag ==Flag_False)					//˵��ģ���ʼ���ɹ�
//	{
//		LCD_MARK_WriteChar("W", WRITE);			//�ź�����ʾ
//
//		if(ComCheck.ComFailFlg==Flag_True)			//��ͨ��ʧ�ܱ�־
//		{
//			LCD_MARK_WriteChar("Z", WRITE);		// ͨ��ʧ��   Z ���� Zero signal ��MARK: ���źţ�x�� 
//			LCD_MARK_WriteChar("N", CLEAR);		//N ���� sigNal��MARK: �ź�����(|||)
//			LowPower_Ctrler.LowPow_LCD_Flg =Flag_True;	//��Ļ��˸���Ʒ���ʧ�ܺ󲻽��еȴ���˸��������͹���ģʽ
//		}
//		if(ComCheck.ComSendOverFlg ==Flag_True)		//�÷�����ɱ�־
//		{
//			LCD_MARK_WriteChar("N", CLEAR);		//N ���� sigNal��MARK: �ź�����ح 
//		}
//	}
//	else//ͨ��ģ���ʼ��ʧ��
//	{
//		LCD_MARK_WriteChar("Z", WRITE);			//���ţ�x�� ��ʾ
//		LCD_MARK_WriteChar("W", CLEAR);			//�ź�������
//		LCD_MARK_WriteChar("N", CLEAR);			//N ���� sigNal��MARK: �ź�����(|||)
//	}

	




}


/**
  * @brief  This function Display  Communication/ device group number 
  * @param  Device_GN  --  device group number
            flag  --  �����־�� ��CLEAR �����Write д��
 * @retval None           
*/

void LCD_COM_Display(u16 Device_GN, LCD_CLEAR_FLAG flag)
{ 
	LCD_MARK_WriteChar("M", flag);			//	    M ���� coMmunication��MARK:ͨѶ
	uint8_t	Device_GN_K = 0;        	  	//  ǧλ
	uint8_t	Device_GN_H = 0;		       	// ��λ
	uint8_t	Device_GN_T = 0;		       	// ʮλ
	uint8_t	Device_GN_O = 0;		       	// ��λ

	Device_GN_K = (uint8_t)(Device_GN >> 12) & 0x0F;        //  ǧλ
	Device_GN_H = (uint8_t)(Device_GN >> 8) & 0x0F;       	// ��λ
	Device_GN_T = (uint8_t)(Device_GN >> 4) & 0x0F;  		// ʮλ	
	Device_GN_O = (uint8_t)(Device_GN >> 0) & 0x0F;  		// ��λ


	LCD_NUM_WriteChar(Device_GN_K, LCD_COM_K_POSITION, flag);		          
	LCD_NUM_WriteChar(Device_GN_H, LCD_COM_H_POSITION, flag);             	 
	LCD_NUM_WriteChar(Device_GN_T, LCD_COM_T_POSITION, flag);             
	LCD_NUM_WriteChar(Device_GN_O, LCD_COM_O_POSITION, flag);             
}


/******************************************************
  function����ʾ������  ����
            ʱ�� �¶�  
  ****************************************************/
void  LCD_1_Screen_Display(void)
{ 	
//	LCD_Date_Display(SoftTime.Year, SoftTime.Month, SoftTime.Day, SoftTime.Week, WRITE);				//	Display DATE  
//	LCD_Time_Display( SoftTime.Hour,SoftTime.Minute,WRITE);										//	Display  TIME
//	LCD_Temp_Display(DS_18B20Controler.Sys_Temp, INPUT, WRITE);									//	 Display  TEMPERATURE
}

/******************************************************
  function����ʾ������  ����
            ʱ�� �¶�  
  ****************************************************/
void  lcd_temp_data_disp(s16 temp)
{       
      rtc_read(&t);
      
      LCD_Date_Display(t.tm_year, t.tm_mon, t.tm_mday, t.tm_week, WRITE);			//	Display DATE  
      LCD_Time_Display(t.tm_hour, t.tm_min, WRITE);						//	Display  TIME
      LCD_Temp_Display(temp, INPUT, WRITE);				        //	 Display  TEMPERATURE
}

/************************************
function����ʾ�����¶�
*************************************/
void lcd_temp_disp(void)
{ 
        LCD_Temp_Display(g_run_params.temp, INPUT, WRITE);		
}

/************************************
function����ʾ�趨�¶�
*************************************/
void  lcd_set_temp_disp(void)
{ 
        LCD_Temp_Set(g_sys_params.temp_set, T_SET, WRITE);	
}


/**********************************************
function�� ��ʾ�յ���ʹ��������ֵ
**********************************************/
void  lcd_heating_quantity_disp(void)
{ 
//	LCD_HEAT_Display(DevPara_DATA.Total_Heat,WRITE);                //  HEAT value	
    LCD_HEAT_Display(g_sys_params.heating_quantity,WRITE);                //  HEAT value	
}

/*********************************************
brief:��ʾ�յ��ۼƿ���ʱ��

*********************************************/
void  lcd_heating_time_disp(void)
{ 
//	LCD_HEAT_Time_Display(DeviceState_DATA.Total_OpTim,WRITE);		//  �ۼƿ���ʱ��	
  LCD_HEAT_Time_Display(g_sys_params.heating_time,WRITE);		//  �ۼƿ���ʱ��
}

/*********************************************
function�� ��ʾ�������
*********************************************/
void  lcd_device_gn_disp(void)
{
	LCD_COM_Display((g_sys_params.Device_SN&0x0000FFFF), WRITE);
}
////////////////////////////////////////////////���///////////////////////////////////////////////////////////////
/*******************************************
function�����  ������ʱ����  
               �¶���ʾ����
*******************************************/
void  LCD_1_Screen_Clear(void)
{ 	
	/* �������Ļ��ʱ������� */
	LCD_Date_Display(t.tm_year, t.tm_mon, t.tm_mday, t.tm_week, CLEAR);	//	Display DATE  
	LCD_Time_Display(t.tm_hour, t.tm_min, CLEAR);				//	Display  TIME
        LCD_Temp_Display(g_run_params.temp, INPUT, CLEAR);
}

/*******************************************
function������������򣬳���״̬��־
*******************************************/
void lcd_clr_region(void)
{ 	
        LCD_Date_Display(t.tm_year, t.tm_mon, t.tm_mday, t.tm_week, CLEAR);	// �������  
	LCD_Time_Display(t.tm_hour, t.tm_min, CLEAR);				// ���ʱ��
        LCD_Temp_Display(g_run_params.temp, INPUT, CLEAR);                      // �������
        LCD_Temp_Set(g_sys_params.temp_set, T_SET, CLEAR);                      // ����趨�¶�
        LCD_HEAT_Display(g_sys_params.heating_quantity,CLEAR);                  // ����ۼ�����	
        LCD_HEAT_Time_Display(g_sys_params.heating_time,CLEAR);		        // ����ۼƿ���ʱ��
        LCD_COM_Display(1234, CLEAR);	                                        // ���ͨѶ
        
//        LCD_1_Screen_Clear();
//        LCD_2_Screen_Clear();
//        LCD_3_Screen_Clear();
//        LCD_4_Screen_Clear();
//        LCD_5_Screen_Clear();
//        LCD_Temp_Set(g_sys_params.temp_set, T_SET, CLEAR);
}



/***************************************************
function�� 
****************************************************/
void  LCD_2_Screen_Clear(void)
{ 	
			
}

/***************************************************
function�� 
****************************************************/
void  LCD_3_Screen_Clear(void)
{ 

//	LCD_HEAT_Display(DevPara_DATA.Total_Heat,CLEAR);                //  HEAT value		
}



/***************************************************
function�� 
****************************************************/
void  LCD_4_Screen_Clear(void)
{ 
         
//	LCD_HEAT_Time_Display(DeviceState_DATA.Total_OpTim,CLEAR);		//  �ۼƿ���ʱ��
}



/***************************************************
function�� 
****************************************************/
void  LCD_5_Screen_Clear(void)
{ 
       
//	LCD_COM_Display(FactPara_DATA.Device_GN, CLEAR);	
}

/**
  * @brief  This function display the Key1   screen
  * @param  None
  * @retval None
  */
void  LCD_Key1_Screen_Display(void)
{

	switch(lcd_key.KEY1_BACKUP_RA)
	{
 				
      case 0:
		LCD_1_Screen_Clear();		
      break;
      
      case 1:
		LCD_1_Screen_Clear();
      break;

      case 2:
		LCD_2_Screen_Clear();
      break;
      
      case 3:
		LCD_3_Screen_Clear();
      break;

      case 4:
		LCD_4_Screen_Clear();      
      break;

      case 5:
		LCD_5_Screen_Clear();
      break;

      default :  
      break;  

               
	}
        //debug
//	LCD_Temp_Set(DeviceState_DATA.Set_Temp_100, T_SET, WRITE);
	
}



/**
  * @brief  This function display the Key2   screen
  * @param  None
  * @retval None
  */
void  LCD_Key3_Screen_Display(void)
{ 
	switch(lcd_key.KEY3_BACKUP_RA)
	{
      case 0:
		LCD_1_Screen_Clear();
      break;
      
      case 1:
		LCD_1_Screen_Clear();
      break;

      case 2:
      	LCD_2_Screen_Clear();
   		   
      break;
      
      case 3:
		LCD_3_Screen_Clear();
      break;

      case 4:
		LCD_4_Screen_Clear();      
      break;

      case 5:
		LCD_5_Screen_Clear();
      break;

      default :  
      break;                
	}
	// debug
//	LCD_Temp_Set(DeviceState_DATA.Set_Temp_100, T_SET, WRITE);	
}




