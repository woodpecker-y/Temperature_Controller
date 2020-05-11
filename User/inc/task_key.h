#ifndef _TASK_KEY_H
#define _TASK_KEY_H

/*! \brief key status definition */
typedef enum _KeySts{
    KEY_STS_IDLE = 0,               // ����״̬
    KEY_STS_PUSH,                   // ��������
    KEY_STS_VALID,                  // �����ͷ�
    KEY_STS_DEAL,                   // ��������
    KEY_STC_FINISH,                  //�������
}KeySts;

/*! \brief ������� */
typedef struct _KeyHandler{
    u8  sts;                    // ����״̬
    u8  key_val;                // ������ֵ	
    u32 timer;                  // ������ʾ��ʧ��ʱ��
    u32 timer_long;             // ��������ʱ��
}KeyHandler;

/* �������� */
void task_key_proc(void);
/* �ϼ����� */
void key_action_add(void);
/* �¼����� */
void key_action_sub(void);
/* ��ѯ������ */
void key_action_view(void);
/* ����ID���� */
void key_action_setid(void);
/* �������� */
void task_key_triggered(u8 key_code);

#endif