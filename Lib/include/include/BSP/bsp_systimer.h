#ifndef _BSP_SYSTIMER_H
#define _BSP_SYSTIMER_H

#include "stm8l15x.h"

/*! \brief support max timer counter */
#define MAX_TIMER_CNT	17

/*! \brief ��ʱ�������� */
typedef enum _SysTimerRet{
	E_SYSTIMER_OK = 0,
	E_SYSTIMER_ERR_IMPOSSIBLE_VALUE,
}SysTimerRet;

/*! \brief ��ʱ�������״̬ */
typedef enum _SysTimerSts{
	E_TIMER_IDLE		= 0,		/*!< \brief ���� */
	E_TIMER_BUSY		= 1,		/*!< \brief ��æ */
	E_TIMER_OVF		= 2,		/*!< \brief ���� */
}SysTimerSts;

/*! \brief �����ʱ��ID */
typedef enum _TimerIDX{
	TIMER_T0		= 0,			/*!< \brief ��ʱ��0 UART0_TIMER */
	TIMER_T1		= 1,			/*!< \brief ��ʱ��1 UART1_TIMER */
	TIMER_T2		= 2,			/*!< \brief ��ʱ��2 MEAS_TIMER */
	TIMER_T3		= 3,			/*!< \brief ��ʱ��3 LCD_REFRESH_TIMER*/
	TIMER_T4		= 4,			/*!< \brief ��ʱ��4 LCD_IDLE_TIMER*/
	TIMER_T5		= 5,			/*!< \brief ��ʱ��5 LCD_CFG_TIMER*/
	TIMER_T6		= 6,			/*!< \brief ��ʱ��6 */
	TIMER_T7		= 7,			/*!< \brief ��ʱ��7 */
	TIMER_T8		= 8,			/*!< \brief ��ʱ��8 */
	TIMER_T9		= 9,			/*!< \brief ��ʱ��9 */
	TIMER_T10		= 10,			/*!< \brief ��ʱ��10 */
	TIMER_T11		= 11,			/*!< \brief ��ʱ��11 */
	TIMER_T12		= 12,			/*!< \brief ��ʱ��12 */
	TIMER_T13		= 13,			/*!< \brief ��ʱ��13 */
	TIMER_T14		= 14,			/*!< \brief ��ʱ��14 */
	TIMER_T15		= 15,			/*!< \brief ��ʱ��15 */
	TIMER_SYSTIMER	= 16,			/*!< \brief ϵͳ��ʱ�� */
}TimerIDX;

/*! \brief
*       �����ʱ����Ƶϵ������
*/
void BSP_SysTimer_ConfigClkDiv(u8 pre);

/*! \brief
*       ��ʱ����ʼ��
*/
u8 BSP_SysTimer_Init(void);

/*! \brief
*       ���ö�ʱ����ʼֵ
* \param[IN]id				- ��ʱ��������	
* \param[IN]val				- ��ʱ���趨�ο�ֵ			
*/
void BSP_SysTimer_Config(unsigned char id, unsigned long val);

/*! \brief
*       ��ȡ��ʱ��״̬����״̬ΪE_TIMER_OVF������ʱ�����
* \param[IN]id				- ��ʱ��������	
* \param[IN]val				- ��ʱ���趨�ο�ֵ			
*/
u8 BSP_SysTimer_GetOverFlag(unsigned char id);

/*! \brief
*       �����ʱ�������־
* \param[IN]id				- ��ʱ��������				
*/
void BSP_SysTimer_ClrOverFlag(unsigned char id);

void BSP_SysTimer_ISR(void);

#endif

