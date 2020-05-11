#include <stdio.h>
#include "task_ds18b20.h"
#include "adf.h"
#include "sysparams.h"
#include "menu.h"
#include "task_disp.h"

#define TEMP_COLLECT_TIME 10    // �¶Ȳɼ�ʱ��Ϊ10����
#define TEMP_AVE_NUM 6    // ����ƽ���¶Ȳɼ��Ĵ���

static TASK_18B20_HANDLER s_task_18b20_handler;
static s16 temp_history_data[6] = {0};
static u8 temp_offset = 0;
static u8 temp_num_flag = 0;
static u8 i = 0;
static u16 temp_total = 0;
/*! \brief
*  ds18b20����
*/
void task_18b20_proc(void)
{
    //    s_task_18b20_handler.adc_timer++;
    switch(s_task_18b20_handler.sts)
    {
    case E_TASK_18B20_IDLE:      // ����״̬
        task_18b20_schedule();
        break;
    case E_TASK_18B20_READY:    //׼���ɼ��׶�
//      printf("E_TASK_18B20_READY\r\n");
          DS18B20_Start(); 
//        adc_init(ADC_BATT);   //adc��Դ��ʼ��
//        adc_init(ADC_TEMP);   //adc�¶ȳ�ʼ��
        s_task_18b20_handler.sts = E_TASK_18B20_COLLECTION_TEMP;
        break;     
    case E_TASK_18B20_COLLECTION_TEMP:   //�ɼ��׶�
//      printf("E_TASK_18B20_COLLECTION_TEMP\r\n");
//        temp_sample();
        g_run_params.temp = DS18B20_ReadTemp();	//温度读取命令
        
        temp_history_data[temp_offset] = g_run_params.temp;
        temp_offset++;
        if (temp_offset >= TEMP_AVE_NUM)
        {
          temp_num_flag = 1;
          temp_offset = 0;
        }
        if (temp_num_flag == 1)         // ����ɼ����¶ȴ���������6�Σ��õ�ǰ���¶ȵ���ƽ���¶ȣ��������6�Σ���ô�ͼ���ƽ��ֵ
        {
          temp_total = 0;       // ��������
          for (i = 0; i < TEMP_AVE_NUM; i++)
          {
            temp_total += temp_history_data[i];
          }
          g_run_params.ave_temp_100 = (temp_total / TEMP_AVE_NUM);
        }
        else
        {
          g_run_params.ave_temp_100 = g_run_params.temp;
        }
          
//////        printf("g_run_params.temp = %d\r\n", g_run_params.temp);        // ��ʱע��
        s_task_18b20_handler.sts = E_TASK_18B20_FINISH;
        break;
    case E_TASK_18B20_FINISH:     //��ɽ׶�
//        printf("E_TASK_18B20_FINISH\r\n");
//        LCD_Temp_Display(g_run_params.temp, INPUT, WRITE);
        task_lcd_triggered(MENU_MAIN);//Ϊ������Ļʵʱˢ�£���δ���LCDˢ�µĺ���
//        adc_close(ADC_BATT);
//        adc_close(ADC_TEMP);
        ds18b20_close();
        s_task_18b20_handler.sts = E_TASK_18B20_IDLE; 
        break;
    default:
        break;
    }
    
}        

/*! \brief
*  ds18b20��������     
*/
void task_18b20_triggered(void)
{
    s_task_18b20_handler.sts = E_TASK_18B20_READY;  
}

/*! \brief
*  ds18b20��������ת������     
*/
void task_18b20_schedule(void)
{
//    printf("s_task_18b20_handler.ds18b20_singleslow_timer = %u\r\n", s_task_18b20_handler.ds18b20_singleslow_timer);
    if(g_run_params.ds18b20_keytrigger == 1)
    {
        s_task_18b20_handler.ds18b20_keytrigger_timer++;
        if(s_task_18b20_handler.ds18b20_keytrigger_timer <= TWO_MIN)
        {
            s_task_18b20_handler.ds18b20_singlefast_timer++;
            if(s_task_18b20_handler.ds18b20_singlefast_timer >= THREE_SECOND)
            {
                s_task_18b20_handler.sts = E_TASK_18B20_READY;
                s_task_18b20_handler.ds18b20_singlefast_timer = 0;
            }
        }
        else
        {
            g_run_params.ds18b20_keytrigger = 0;
            s_task_18b20_handler.ds18b20_keytrigger_timer = 0;
        }
    }
    else
    {
        s_task_18b20_handler.date_timer++;   
        if(s_task_18b20_handler.date_timer >= UNIT_MIN) // һ����ˢ����ʱ��
        {
            s_task_18b20_handler.sts = E_TASK_18B20_FINISH;     // ֻˢ����Ļ
            s_task_18b20_handler.date_timer = 0;
            
            s_task_18b20_handler.ds18b20_singleslow_timer++;
            if(s_task_18b20_handler.ds18b20_singleslow_timer >= TEMP_COLLECT_TIME)
            {
                s_task_18b20_handler.sts = E_TASK_18B20_READY;
                s_task_18b20_handler.ds18b20_singleslow_timer = 0;
            }
        }
    }
}

/*! \brief
*  ����ds18b20����ʱ�����㺯��     
*/
void task_18b20_timereset(void)
{
    s_task_18b20_handler.date_timer = 0;
    s_task_18b20_handler.ds18b20_singleslow_timer = 0;
    s_task_18b20_handler.ds18b20_keytrigger_timer = 0;
    s_task_18b20_handler.ds18b20_singlefast_timer = THREE_SECOND-1;
}

/*! \brief
*  ds18b20�ɼ���ʼ�����ϵ�ɼ��¶� 
*/
void task_18b20_init(void)
{
    s_task_18b20_handler.date_timer = UNIT_MIN - 1;
    s_task_18b20_handler.ds18b20_singleslow_timer = TEMP_COLLECT_TIME - 1;
}