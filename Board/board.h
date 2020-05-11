#ifndef _BOARD_H
#define _BOARD_H

#include "bsp.h"
//////////////////////////////��Ʒ����////////////////////////////////////
extern const char *hw_ver;
extern const char *sw_ver;
extern const char *product_model;

//////////////////////////////��������////////////////////////////////////
extern uint8_t com_global_buffer[512];

extern COMConfig com_cfg[1];

extern uint8_t rf_global_buffer[80];     // debug

//////////////////////////////ADC����/////////////////////////////////////
typedef struct _TEMP_TABLE{
    s16  temp;  // �¶� 
    u32  r;     // ���� 
}TEMP_TABLE;

typedef enum _AdcIdx{
    ADC_BATT = 0,
    ADC_TEMP = 1,
}AdcIdx;
extern ADCConfig1 adc_cfg[1];
//////////////////////////////led����/////////////////////////////////////
typedef enum _LedDef{
    LED_FAULT = 0,
    LED_CARD = 1,
    LED_COMM = 2,
    LED_VALVE = 3,
    LED_PWR = 4,    
}LedDef;
extern PortTypeDef led_config[5];
//////////////////////////////lcd����/////////////////////////////////////
extern LCDPortConfig lcd_config;
//////////////////////////////key����/////////////////////////////////////
extern PortTypeDef key_config[3];
//////////////////////////////��������////////////////////////////////////
extern RFConfig rf_cfg;
//
extern PortTypeDef beep_config;

//extern FlashConfig flash_config;

extern PortTypeDef pwr_cfg;
//
extern EXTIConfig pwr_check_cfg[1];
//

//extern SHT2xConfig sht20_cfg;

#endif