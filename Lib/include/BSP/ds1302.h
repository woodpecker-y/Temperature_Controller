
#ifndef __DS1302_H__
#define __DS1302_H__	

#ifdef HAVE_DS1302

#include "bsp.h"

#define AM(X)	X
#define PM(X)	(X+12)            					// ת��24Сʱ��

#define DS1302_SECOND	0x80
#define DS1302_MINUTE	0x82
#define DS1302_HOUR		0x84 
#define DS1302_WEEK		0x8A
#define DS1302_DAY		0x86
#define DS1302_MONTH	0x88
#define DS1302_YEAR		0x8C
#define DS1302_RAM(X)	(0xC0+(X)*2)   			//���ڼ��� DS1302_RAM ��ַ�ĺ� 

//-------------------------------------������---------------------------------// 
#define DS1302_SECOND_WRITE		0x80          //дʱ��оƬ�ļĴ���λ�� 
#define DS1302_MINUTE_WRITE		0x82 
#define DS1302_HOUR_WRITE		0x84  
#define DS1302_WEEK_WRITE		0x8A 
#define DS1302_DAY_WRITE		0x86 
#define DS1302_MONTH_WRITE		0x88 
#define DS1302_YEAR_WRITE		0x8C  

#define DS1302_SECOND_READ		0x81          //��ʱ��оƬ�ļĴ���λ�� 
#define DS1302_MINUTE_READ		0x83 
#define DS1302_HOUR_READ		0x85  
#define DS1302_WEEK_READ		0x8B 
#define DS1302_DAY_READ			0x87 
#define DS1302_MONTH_READ		0x89 
#define DS1302_YEAR_READ		0x8D  	

/*! \brief ʱ�ӳ�ʼ�� */
void BSP_RTC_Init(void);				

/*! \brief дʱ�� */
void BSP_RTC_Write(struct tm t);

/*! \brief ��ʱ�� */
void BSP_RTC_Read(struct tm *t);

#endif

#endif