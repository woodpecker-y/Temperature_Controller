/*    ��������:
*       |-->wdg_init()
*           |-->wdg_reset()
*           |-->wdg_reset()
*           |-->wdg_reset()
******************************************************************************/

#ifndef _WDG_H
#define _WDG_H

#ifdef HAVE_WDG

/*! \brief
*       �ڲ����Ź���ʼ��
* \param _1s[IN]			- ���Ź����ʱ��
*/
void wdg_init(u32 _1ms);

/*! \brief
*       �ڲ����Ź�ι��
*/
void wdg_reset(void);

#endif

#endif
