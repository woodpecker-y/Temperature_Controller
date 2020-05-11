#ifndef _TASK_RF_H
#define _TASK_RF_H

/*! \brief key status definition */
typedef enum _TASK_RFSts{
    TASK_RF_STS_IDLE = 0,               // ����״̬
    TASK_RF_STS_refresh,                // ���߱�ʶˢ��
}TASK_RFSts;

/*! \brief ���߾�� */
typedef struct _TASK_RF_HANDLER{
    u8  sts;                    // ����״̬
    u32 timer;                   //���߱�־��תʱ��
}TASK_RF_HANDLER;

/* ���߱�ʶ��˸�������� */
void task_rf_proc(void);
/* ���߱�ʶ�������� */
void task_rf_triggered(u8 ant_sts_triggered);



#endif