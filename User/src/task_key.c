#include "adf.h"
#include "sysparams.h"
#include "board.h"
#include "task_key.h"
#include "key.h"
#include "menu.h"
#include "task_disp.h"
#include "task_report.h"
#include "cj188.h"
#include "task_adc.h"
#include "delay.h"
#include "disp.h"


//u16 t = 250;
//u8 p = 1;

/* key status */
static KeyHandler s_key_handler; //������һ���ṹ�����

/*! \brief
*  ��������
*/
void task_key_proc(void)
{

    //printf("g_sys_params.temp_set2222222=%d\r\n",g_sys_params.temp_set);
    switch(s_key_handler.sts)
    {
    case KEY_STS_IDLE:
        break;
    case KEY_STS_PUSH:
        // �ж��Ƿ�Ϊ�Ϸ�����
        if (TRUE == key_check_valid(s_key_handler.key_val))
        {
            g_run_params.key_long = 1;  //�а������´˱�־Ϊ1�������ͷŴ˱�־Ϊ0
            s_key_handler.sts = KEY_STS_VALID;
            g_run_params.ds18b20_keytrigger = 0;//��adc�ɼ��������ı�־���㣬����ֻҪ�а������£�����Ҫ6s֮��ˢ����Ļ
            g_run_params.adc_keytrigger = 0;
            task_adc_timereset();
        }
        else
        {
            s_key_handler.sts = KEY_STS_IDLE;
        }
        break;
    case KEY_STS_VALID:
        // ��ⰴ���ͷ�
        delay_ms(10);
        if (TRUE == key_release(s_key_handler.key_val))
        {
            s_key_handler.timer_long = 0;
            g_run_params.key_long = 0;
            s_key_handler.sts = KEY_STS_DEAL;
        }

        if(g_run_params.key_long == 1)  // ����������£�����Ҳ�ܽ�����һ��״̬��
        {
            if (FALSE == key_release(s_key_handler.key_val))    //����û���ͷ�
            {
                s_key_handler.timer_long++;
                if(s_key_handler.timer_long >= TWO_SECOND)      // ����2s�����л���һ����Ļ
                {
                    s_key_handler.timer_long = 0;
                    s_key_handler.sts = KEY_STS_DEAL;
                }
            }
        }
        break;
    case KEY_STS_DEAL:
        if(g_run_params.set_id == 1)    //��Ϊ����IDʱ�����а������µ�һ��ʱ�������������¶Ƚ���
        {
            g_run_params.set_id = 0;
            //g_run_params.ds18b20_keytrigger = 1;
            s_key_handler.timer = 1;
            s_key_handler.sts = KEY_STC_FINISH;
            break;
        }
        g_run_params.set_id = 0;    //�����������¶�ģʽ��ʱҲҪ�ѱ�־���㣬������һ���ܷ��ص�������
        //printf("s_key_handler.key_val:%d\r\n",s_key_handler.key_val);
        //printf("key_code:%d\r\n",key_code);
        s_key_handler.timer = THREE_SECOND;
        /* '1'Ϊ��; '2'Ϊ�˵�; '3'Ϊ��; 'a'Ϊ�ӺͲ˵�ͬʱ���� */
        switch(s_key_handler.key_val)
        {
        case '1':
            key_action_add();
            break;
        case '2':
            key_action_view();
            break;
        case '3':
            key_action_sub();
            break;
        case 'b':
            key_action_setid();
            break;
        default:
            break;
        }
        //        if(s_key_handler.key_val == 49)
        //        {
        //            key_action_view();
        //        }
        //
        //        if(s_key_handler.key_val == 50)
        //        {
        //            key_action_sub();
        //        }
        //
        //        if(s_key_handler.key_val == 51)
        //        {
        //            key_action_add();
        //        }


        task_lcd_triggered(g_run_params.menu_id);       // ����Һ������ʾ��debug

        // ������û�ж����ԣ����ܾ��ǳ�����������
        if(g_run_params.key_long == 1)  //����������û���ͷ�ʱ�������������ٴλص������ͷŽ��̽��м�⣬ֱ�������ͷ������־
        {
            s_key_handler.sts = KEY_STS_VALID;
            break;
        }

        eeprom_write_sys(14, &g_sys_params.temp_set, 2);        //ֻд���趨�¶ȣ����ûд
        s_key_handler.sts = KEY_STC_FINISH;
        break;
    case KEY_STC_FINISH:
        //printf("s_key_handler.timer = %lu\r\n", s_key_handler.timer);
        if(g_run_params.set_id != 1)    // ���趨id������²���6s�ص�������
        {
            s_key_handler.timer--;
        }
        if(s_key_handler.timer <= 0)//Ϊ����û�а�����������Զ��л�������Ļ��ˢ�����£�������һֱ�ȴ�adc�ɼ���ʱ�䵽�˲�ˢ�³�����Ļ
        {
            //printf("11111111111111\r\n");
            g_run_params.view_idx = MENU_VIEW_IDX_TEMP_SET-1;
            g_run_params.ds18b20_keytrigger = 1;
            g_run_params.adc_keytrigger = 1;
            task_report_triggered(CTRL_CODE_REPORT);//û�а������º�6S�����ϱ���adc�ɼ�

            //task_adc_triggered();


            //            g_run_params.menu_id = MENU_MAIN;
            //            task_lcd_triggered(g_run_params.menu_id);

            //            printf("write[1]\r\n");
            //            eeprom_init();
            //            eeprom_write(24, (u8*)&(g_sys_params.temp_set), sizeof(g_sys_params.temp_set));//ֻд���趨�¶ȣ����ûд
            //            //printf("write sucess\r\n");
            //            eeprom_close();
            //            printf("write sucess\r\n");


//            if(g_run_params.key_long == 0)
//            {
                s_key_handler.sts = KEY_STS_IDLE;
//            }
//            else
//            {
//                s_key_handler.sts = KEY_STS_VALID;
//            }
        }

        break;
    default:
        break;
    }
}

/*! \brief
*  ������������
*/
void task_key_triggered(u8 key_code)
{
    s_key_handler.key_val = key_code;
    s_key_handler.sts = KEY_STS_PUSH;
#if TASK_PRINTF
    printf("key_code:%c\r\n", key_code);
#endif
}

/*! \brief
*  ���ϼ�����
*/
void key_action_add(void)
{
    //printf("g_sys_params.temp_set1111111=%d\r\n",g_sys_params.temp_set);
    //eeprom_read(0, (u8*)&g_sys_params, sizeof(g_sys_params));
    //printf("g_sys_params.temp_set=%d\r\n",g_sys_params.temp_set);
    if(g_sys_params.temp_set < (g_sys_params.temp_room_uplimits * 100))
    {
        g_sys_params.temp_set = g_sys_params.temp_set+50;
    }
    else
    {
        g_sys_params.temp_set = (g_sys_params.temp_room_uplimits * 100);
    }
    g_run_params.temp_return = g_sys_params.temp_set;
    //    eeprom_init();
    //    eeprom_write(0, (u8*)&g_sys_params, sizeof(g_sys_params));
    //    //printf("write sucess\r\n");
    //    eeprom_close();
    g_run_params.menu_id = MENU_SET_TEMP;
    g_sys_params.sys_set_temp_flg = 0x00;
    eeprom_write_sys(13, &g_sys_params.sys_set_temp_flg, 1);
}

/*! \brief
*  ���¼�����
*/
void key_action_sub(void)
{
    //eeprom_read(0, (u8*)&g_sys_params, sizeof(g_sys_params));

    if(g_sys_params.temp_set > (g_sys_params.temp_room_lowlimits*100))
    {
        g_sys_params.temp_set = g_sys_params.temp_set-50;
    }
    else
    {
        g_sys_params.temp_set = (g_sys_params.temp_room_lowlimits*100);
    }
    g_run_params.temp_return = g_sys_params.temp_set;
    //    eeprom_init();
    //    eeprom_write(0, (u8*)&g_sys_params, sizeof(g_sys_params));
    //    //printf("write sucess\r\n");
    //    eeprom_close();

    g_run_params.menu_id = MENU_SET_TEMP;
    g_sys_params.sys_set_temp_flg = 0x00;
    eeprom_write_sys(13, &g_sys_params.sys_set_temp_flg, 1);
}

/*! \brief
*  ��ѯ������
*/
void key_action_view(void)
{
//    printf("g_run_params.view_idx = %d\r\n" ,g_run_params.view_idx);
    g_run_params.view_idx ++;
//    printf("g_run_params.view_idx = %d\r\n" ,g_run_params.view_idx);
    if(g_run_params.view_idx >= 5)
    {
        g_run_params.view_idx = MENU_VIEW_IDX_TEMP_SET;//ѭ�����趨�¶�
    }

    /* ����Ĵ����������ʾ����λ�����򲻻��õ� */
    //printf("g_sys_params.disp_ctl = %x\r\n" ,g_sys_params.disp_ctl);
    /* ���������ʣ�����������ǲ�����ʾ�����������ۼ����� �������8λ���ĸ�Ϊ1��ʾ���ȫ��FF����ʾ��00������ʾ*/
    if (g_run_params.view_idx==MENU_VIEW_IDX_TEMP_SET && !(g_sys_params.disp_ctl&DISP_CTL_BALANCE))
    {
        g_run_params.view_idx = MENU_VIEW_IDX_HEATING_QUANTITY_TOTAL;
    }

    /* ����������ۼ����������ǲ�����ʾ��������������ʱ�� */
    if (g_run_params.view_idx==MENU_VIEW_IDX_HEATING_QUANTITY_TOTAL && !(g_sys_params.disp_ctl&DISP_CTL_HEAT_QUANTITY_TOTAL))
    {
        g_run_params.view_idx = MENU_VIEW_IDX_HEATING_TIME_TOTAL;
    }
    /* �������������ʱ�䣬���ǲ�����ʾ������������� */
    if (g_run_params.view_idx==MENU_VIEW_IDX_HEATING_TIME_TOTAL && !(g_sys_params.disp_ctl&DISP_CTL_HEAT_TIME_TOTAL))
    {
        g_run_params.view_idx = MENU_VIEW_IDX_FAULT;
    }
    /* ��������ǹ��ϣ����ǲ�����ʾ���������뷿��� */
    if (g_run_params.view_idx==MENU_VIEW_IDX_FAULT && !(g_sys_params.disp_ctl&DISP_CTL_FAULT))
    {
        g_run_params.view_idx = MENU_VIEW_IDX_ID_LEFT;
    }
//    /* ��������Ƿ���ţ����ǲ�����ʾ�������������� */
//    if (g_run_params.view_idx==MENU_VIEW_IDX_ROOM_ID && !(g_sys_params.disp_ctl&DISP_CTL_ROOM_NAME))
//    {
//        g_run_params.view_idx = MENU_VIEW_IDX_ID_LEFT;
//    }


    g_run_params.menu_id  = MENU_VIEW;

}

void key_action_setid(void)
{
    int rv;
    if (g_sys_params.factory_flag == 0)
    {
        rf_power_on();
        rv = rf_init(RF_FRE_420_5M, RF_DATA_RATE_1200, TXPOW_20dBm, DOWNLOAD_ID_CHANNEL);
        if(rv == 0)
        {
            g_run_params.menu_id  = MENU_ID;
            //printf("set id\r\n");
            g_run_params.set_id = 1;
            rf_rcv_init();
        }

    }
}