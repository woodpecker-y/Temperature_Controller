#ifndef _TASK_DS18B20_H
#define _TASK_DS18B20_H

#include "sysparams.h"

typedef enum {
    E_TASK_18B20_IDLE = 0,    //����״̬
    E_TASK_18B20_READY,       //׼��״̬
    E_TASK_18B20_COLLECTION_TEMP,  //�ɼ�״̬
    E_TASK_18B20_FINISH,      //���״̬
}TASK_18B20_STATE;

typedef struct _TASK_18B20_HANDLER{
    u8  sts;        //״̬
    u32 date_timer;   //ʱ��ˢ��ʱ��
    u32 ds18b20_singleslow_timer;   //�ɼ�ʱ����
    u32 ds18b20_singlefast_timer;   //�ɼ�ʱ���
    u32 ds18b20_keytrigger_timer;   //������������ˢ�µ�ʱ��
}TASK_18B20_HANDLER;

/* ds18b20���� */
void task_18b20_proc(void);
/* ds18b20�������� */
void task_18b20_triggered(void);
/* ds18b20��������ת������ */    
void task_18b20_schedule(void);
/* ����ds18b20����ʱ�����㺯�� */  
void task_18b20_timereset(void);
/* ds18b20�ɼ���ʼ�����ϵ�ɼ��¶� */
void task_18b20_init(void);


#endif