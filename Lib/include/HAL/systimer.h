#ifndef _SYSTIMER_H
#define _SYSTIMER_H

/*! \brief
*       ��ʱ����ʼ��
*/
u8  systimer_init(void);

/*! \brief
*       ���ö�ʱ����ʼֵ
* \param[IN]id				- ��ʱ��������	
* \param[IN]val				- ��ʱ���趨�ο�ֵ			
*/
void systimer_config(unsigned char id, unsigned long val);

/*! \brief
*       ��ȡ��ʱ��״̬����״̬ΪE_TIMER_OVF������ʱ�����
* \param[IN]id				- ��ʱ��������	
* \param[IN]val				- ��ʱ���趨�ο�ֵ			
*/
u8  systimer_get_over_flag(unsigned char id);

/*! \brief
*       �����ʱ�������־
* \param[IN]id				- ��ʱ��������				
*/
void  systimer_clr_over_flag(unsigned char id);

#endif
