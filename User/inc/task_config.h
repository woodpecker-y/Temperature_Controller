#ifndef _TASK_CONFIG_H
#define _TASK_CONFIG_H

/* ���õ������� */
void task_config_proc(void);
void task_config_proc_test(void);
/* ������� */
void factory_check(void);
/* MODBUSЭ�鴦�� */
u8 params_service(u8 *snd_buf, u8 *snd_len, u8 *rcv_buf, u8 rcv_len);

#endif