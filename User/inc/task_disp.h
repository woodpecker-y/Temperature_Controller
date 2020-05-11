#ifndef _TASK_DISP_H
#define _TASK_DISP_H

#include "sysparams.h"

typedef enum {
    E_TASK_DISP_IDLE = 0,   //����״̬
    E_TASK_DISP_REFRESH,    //ˢ��״̬
}TASK_DISP_STATE;

typedef struct _TASK_DISP_HANDLER{
    u8  sts;    //״̬
    u32 menu;   //�˵�
}TASK_DISP_HANDLER;

/* ��ʾ�������� */
void task_disp_proc();
/* ��ʾ�Ĵ������� */
void task_lcd_triggered(u8 menu_id);

#endif