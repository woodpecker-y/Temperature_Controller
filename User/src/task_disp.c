#include "disp.h"
#include "task_disp.h"
#include "adf.h"
#include "sysparams.h"
#include "board.h"
#include "task_key.h"
#include "menu.h"
#include "delay.h"

static TASK_DISP_HANDLER s_task_disp_handler;

/*! \brief 
*   ��ʾ������
* 
* \note  
*   
*/
void task_disp_proc(void)
{
    //menu_disp(MENU_MAIN);
    switch(s_task_disp_handler.sts)
    {
    case E_TASK_DISP_IDLE:      // ����״̬ 
        break;
    case E_TASK_DISP_REFRESH:   //ˢ��
        menu_disp(s_task_disp_handler.menu);
        s_task_disp_handler.sts = E_TASK_DISP_IDLE;
        break;
    default:
        break;
    }
    
}

/*! \brief 
*   �˵�ѡ��
* \param menu_id[IN]       - �˵���ID 
* 
* \note  
*   
*/
void task_lcd_triggered(u8 menu_id)
{
    s_task_disp_handler.menu = menu_id;
    s_task_disp_handler.sts = E_TASK_DISP_REFRESH;
    //printf("key_code:%c\r\n", key_code);
}