#ifndef _BSP_AWU_H
#define _BSP_AWU_H

#ifdef HAVE_AWU

/*! \brief
*   awu initilization
*/
void BSP_AWU_TimerInit(void);

/*! \brief
*       enable awu
* \param init[IN]	- wakeup cycle
*
* \notes
*       �������ڼ���ֵ��CPUƵ���йأ����㹫ʽΪ��
*/
void BSP_AWU_TimerEnable(u16 init);

/*! \brief
*       disable awu
*/
void BSP_AWU_TimerDisable(void);

#endif

#endif