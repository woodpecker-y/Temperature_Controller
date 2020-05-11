#ifndef _AWU_H
#define _AWU_H

#ifdef HAVE_AWU

/*! \brief
*   awu initilization
*/
void awu_init(void);

/*! \brief
*       enable awu
* \param init[IN]	- wakeup cycle
*
* \notes
*       �������ڼ���ֵ��CPUƵ���йأ����㹫ʽΪ��
*/
void awu_enable(u16 cycle);

/*! \brief
*       disable awu
*/
void awu_disable(void);

#endif

#endif