#ifndef _BSP_H
#define _BSP_H

#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef enum _LevelEffType{
    E_LE_LOW = 0,
    E_LE_HIGH,
}LevelEffType;

#ifdef HAVE_STM8S
#include "stm8s.h"
#else
#include "stm8l15x.h"
#endif
#include "bsp_sysclk.h"
#include "bsp_gpio.h"
#include "delay.h"
//#include "remap.h"

#include "pin.h"

//////////////////// adc���� //////////////////////////////
#ifdef HAVE_ADC_BSP1
#include "adc_bsp.h"
#include "bsp_adc_bsp.h"
#endif

//////////////////// �ⲿRTC���� //////////////////////////////
#ifdef HAVE_RTC_EXT

#include "rtc_ext.h"
//#include "bsp_rtc_ext.h"

#endif

//////////////////// �ڲ�RTC���� //////////////////////////////
#ifdef HAVE_RTC_INTER
#include "RTC_inter.h"
#endif

//////////////////// DS18B20���� //////////////////////////////
#ifdef HAVE_18b20
#include "ds18b20.h"
#endif

//////////////////// LCD���� //////////////////////////////
#ifdef HAVE_LCD
#include "LCD_Driver.h"  
#endif

//////////////////// BEEP���� //////////////////////////////
#ifdef HAVE_BEEP
#include "bsp_beep.h"
#endif

//////////////////// RTC���� //////////////////////////////
#ifdef HAVE_RTC
#include "bsp_rtc.h"
#endif

//////////////////// �����ʱ������ //////////////////////////////
#ifdef HAVE_SYSTIMER
#include "bsp_systimer.h"
#endif

//////////////////// LCD���� //////////////////////////////
#if defined(HAVE_LCD_EXT)

#include "bu97931.h"

#elif defined(HAVE_LCD)

#include "bsp_lcd.h"

#endif


//////////////////// RF���� //////////////////////////////
#ifdef HAVE_RF
#include "si4432.h"
#endif

#ifdef HAVE_RF_BSP
#include "bsp_si4432.h"
#endif

//////////////////// �������� //////////////////////////////
#ifdef HAVE_MOTOR

#include "ba6289.h"

#endif

//////////////////// �������� //////////////////////////////
#ifdef HAVE_KEY

#include "bsp_key.h"

#endif

//////////////////// AD�������� ////////////////////////////
//#ifdef HAVE_ADC
//
//#include "bsp_adc.h"
//
//#endif

//////////////////// UART���� //////////////////////////////
#ifdef HAVE_COM

#include "bsp_com.h"

//#define USART1_REMAP                    // ����1��ӳ��

//extern const COM_Cfg_t com_cfg[1];      // ���ڶ���

#endif

//////////////////// UART���� //////////////////////////////
#ifdef HAVE_COM_BSP

#include "bsp_com_bsp.h"
#include "com_bsp.h"

//#define USART1_REMAP                    // ����1��ӳ��

//extern const COM_Cfg_t com_cfg[1];      // ���ڶ���

#endif

//////////////////// EXTI���� //////////////////////////////
#ifdef HAVE_EXTI

#include "bsp_exti.h"

#endif

//////////////////// AWU���� //////////////////////////////
#ifdef HAVE_AWU

#include "bsp_awu.h"

#endif

//////////////////// ALARM���� //////////////////////////////
#ifdef HAVE_ALARM

#include "bsp_alarm.h"

#endif

//////////////////// LED���� //////////////////////////////
#ifdef HAVE_LED

#include "bsp_led.h"

#endif

//////////////////// EEPROM���� //////////////////////////////
#ifdef HAVE_EEPROM

#include "bsp_eeprom.h"

#endif

//////////////////// RFID���� //////////////////////////////
#ifdef HAVE_RFID

#include "rc522.h"

#endif

//////////////////// ���Ź����� //////////////////////////////
#ifdef HAVE_WDG

#include "bsp_wdg.h"

#endif

//////////////////// ���Ź����� //////////////////////////////
#ifdef HAVE_SHT2x

#include "sht2x.h"

#endif

//////////////////// ���Ź����� //////////////////////////////
#ifdef HAVE_GPRS

#include "a6.h"

#endif

#endif