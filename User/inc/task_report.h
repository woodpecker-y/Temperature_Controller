#ifndef _TASK_REPORT_H
#define _TASK_REPORT_H

#include "sysparams.h"

// ����ĳ���
#define MAX_PACKAGE_LEN     64
// �����ճ�ʱʱ��:2s
#define MAX_RECV_TIMEOUT    (UNIT_SECOND*2)
// ������Դ���
#define MAX_RETRY_CNT       3

typedef enum _E_REPORT_STATE{
    E_REPORT_IDLE = 0,  //����״̬
    E_REPORT_READY,     //׼��״̬
    E_REPORT_PACKAGE,   //���״̬
    E_REPORT_SEND,      //����״̬
    E_REPORT_RECV,      //����״̬
    E_REPORT_DEAL,      //����״̬
    E_REPORT_SUCCESS,   //�ɹ�״̬
    E_REPORT_FINISH,    //���״̬
}E_REPORT_STATE;

typedef struct _ReportHandler{
    u8          sts;                        //״̬
    u8          cmd;                        //�ϱ��ķ�ʽѡ��
    u8          pkg_snd[MAX_PACKAGE_LEN];   //���͵�����
    u8          pkg_snd_len;                //�������ݵĳ���
    u8         *pkg_rcv;                    //���ݰ�������
    u8          pkg_rcv_len;                //���ݰ����յĳ���
    u16         timeout;                    //��ʱʱ��
    u8          retry_cnt;                  //���Դ���
    u32         report_period_timer;        //�ڹ�ů��
//    u32         report_nperiod_timer;       //���ڹ�ů��
//    u32         switch_login_timer;          //24Сʱǩ��һ��
}ReportHandler;

/* �ϱ���ʼ�� */
void task_report_init(void);
/* �ϱ������� */
void task_report_proc(void);
/* �ϱ����� */
void task_report_triggered(u8 cmd);
/* �ϱ����� */
void task_report_request(u8 cmd, u8 *pkg_snd, u8 *pkg_len);
/* ����ʱ���ѡ�� */
void task_report_schedule(void);

void task_report_request(u8 cmd, u8 *pkg_snd, u8 *pkg_len);

#endif