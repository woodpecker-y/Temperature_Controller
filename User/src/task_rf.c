#include "adf.h"
#include "sysparams.h"
#include "board.h"
#include "task_rf.h"
#include "task_report.h"
#include "menu.h"
#include "task_disp.h"
#include "disp.h"
#include "error.h"

static TASK_RF_HANDLER s_rf_handler; //������һ���ṹ�����

/*! \brief
*  ���߱�ʶ��˸������
*/
void task_rf_proc(void)
{
    switch(s_rf_handler.sts)
    {
    case TASK_RF_STS_IDLE:
        break;
    case TASK_RF_STS_refresh:   
        if (g_run_params.ant_sts <= ANT_CONNECTRED)//����ź����ӻ�û����
        {
            disp_ant(DISPLAY_ON, g_run_params.ant_sts);//Ϊ���ߵĸ�����ʾ
            /* ����Ϊ�״��źŵ���ʾ */
            if (g_run_params.ant_sts == 0)//����ֵ��ö�ٱ�ʾ����Ϊ�����ź�״̬
            {
//////                disp_rf_state(DISPLAY_OFF);
                disp_rf_state(DISPLAY_ON);
////                error_set(FAULT_COMM);
                error_set_u8(FAULT_RF);
            }
            else
            {
//////                disp_rf_state(DISPLAY_ON);
                disp_rf_state(DISPLAY_OFF);
////                error_clr(FAULT_COMM);
                error_clr_u8(FAULT_RF);
            }
            s_rf_handler.sts = TASK_RF_STS_IDLE;
        }
        else
        {
            s_rf_handler.timer++;
            if(s_rf_handler.timer == HALF_SECOND)
            {
                s_rf_handler.timer = 0;
                g_run_params.ant_flash ^= 0x01;
                //printf("g_run_params.ant_flash=%x" ,g_run_params.ant_flash);
                disp_ant(DISPLAY_ON, g_run_params.ant_flash);
            }
        }
//////        disp_update();//ˢ����Ļ
        
        break;
    }
}

/*! \brief
*  ���߱�ʶ����Ĵ�������
*/
void task_rf_triggered(u8 ant_sts_triggered)
{
    g_run_params.ant_sts = ant_sts_triggered;
    s_rf_handler.sts = TASK_RF_STS_refresh;  
}


