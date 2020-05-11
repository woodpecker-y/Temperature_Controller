#ifndef _TASK_POWER_H
#define _TASK_POWER_H

#include "sysparams.h"
  
#define TEMP_MEAS_R         5090 

typedef enum {
    E_TASK_ADC_IDLE = 0,    //����״̬
    E_TASK_ADC_READY,       //׼��״̬
    E_TASK_ADC_COLLECTION_BATTERY,
    E_TASK_ADC_COLLECTION_TEMP,  //�ɼ�״̬
    E_TASK_ADC_FINISH,      //���״̬
}TASK_ADC_STATE;

typedef struct _TASK_ADC_HANDLER{
    u8  sts;        //״̬
    u32 adc_singleslow_timer;   //�ɼ�ʱ����
    u32 adc_singlefast_timer;   //�ɼ�ʱ���
    u32 adc_keytrigger_timer;   //������������ˢ�µ�ʱ��
        
}TASK_ADC_HANDLER;

/* adc���� */
void task_adc_proc(void);
/* ��������¶ȵ�ֵ */
u16 task_sample_result_temp(u16 adc_temp);
/* �¶Ȳɼ� */
void temp_sample(void);
/* �����ɼ� */
void batter_sample(void);
/* adc�ϵ�ɼ� */
void task_adc_init(void);
/* adc�������� */
void task_adc_triggered(void);
/* adc��������ת������ */
void task_adc_schedule(void);
/* ����adc�����������㺯�� */
void task_adc_timereset(void);
/* �¶Ȳ������� */
void Temperature_Compensation(void);

#endif