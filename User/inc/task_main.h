#ifndef _TASK_MAIN_H
#define _TASK_MAIN_H

#include "adf.h"

/* ������ */
typedef struct TaskItem{
    u8   priority;
    void (*func)(void);
}TaskItem_t;

/* ���������̵����� */
void task_main(void);

#endif