/*    ��������:
*       |-->rf_load_config()
*           |-->rf_power_on()
*               |-->rf_init()
*               |-->rf_reinit()
*                   |-->rf_snd_data()
*                   |-->rf_rcv_init()
*                   |-->rf_rcv_data()
*               |-->rf_close()
*           |-->rf_power_off()
*       �˴�Ϊ�ⲿ�жϣ�����ѡ����һ���ⲿ�жϺ�����ܽ��йأ�һ��PIN5���ⲿ�жϼ�ΪEXTI5��PIN4���ⲿ�жϼ�ΪEXTI4
*       |-->INTERRUPT_HANDLER(EXTI5_IRQHandler,13)
*           |-->rf_isr()
******************************************************************************/

#ifndef _RF_H
#define _RF_H

#ifdef HAVE_RF

#include "bsp.h"

/*! \brief
*       rf module load config
* \param rf_cfg[IN]        - rf config poninter
* \return
*       none
*/
void rf_load_config(RFConfig *rf_cfg);

/*! \brief
*       rf module power on
* \return
*       none
*/
void rf_power_on(void);

/*! \brief
*       rf module init
* \param fre[IN]           - rf communication frequency
* \param rate[IN]          - rf communication rate
* \param rf_pow[IN]        - rf power
* \param ch[IN]            - rf communication channel
* \return
*       E_RF_OK         - successful
*       others          - failed
*/
void rf_power_off(void);

/*! \brief
*       rf module init
* \param fre[IN]           - rf communication frequency
* \param rate[IN]          - rf communication rate
* \param rf_pow[IN]        - rf power
* \param ch[IN]            - rf communication channel
* \return
*       E_RF_OK         - successful
*       others          - failed
*/
u8   rf_init(RF_FRE fre, RF_DATA_RATE rate, RF_TXPOW rf_pow, u8 ch);

/*! \brief
*       rf module close
* \return
*       none
*/
void rf_close(void);

/*! \brief
*       rf module reinit
* \param fre[IN]           - rf communication frequency
* \param rate[IN]          - rf communication rate
* \param rf_pow[IN]        - rf power
* \param ch[IN]            - rf communication channel
* \return
*       E_RF_OK         - successful
*       others          - failed
*/
u8   rf_reinit(RF_FRE fre, RF_DATA_RATE rate, RF_TXPOW rf_pow, u8 ch);

/*! \brief
*       rf get rssi
* \return
*       E_RF_OK         - successful
*       others          - failed
* \note
*       not use.
*/
u8   rf_get_rssi(void);

/*! \brief
*       rf module send data
* \param dat[IN]           - rf send data 
* \param len[IN]           - the length of rf send data
* \return
*       E_RF_OK         - successful
*/
u8   rf_snd_data(u8 *dat, u8  len);

/*! \brief
*       rf module recv init
* \return
*       none
*/
void rf_rcv_init(void);

/*! \brief
*       rf module recv data
* \param dat[OUT]           - rf recv data
* \param len[OUT]           - the length of rf recv data
* \return
*       E_RF_OK         - successful
* \note
*       �˴�datΪ����ָ�룬����Ҫ�����ڴ棬�����÷���
*           uint8_t *rcv_ptr = NULL;
*	    uint16_t rcv_len = 0;
*			
*	    rf_rcv_data(&rcv_ptr, &rcv_len);         
*/
u8   rf_rcv_data(u8 **dat, u8 *len);

/*! \brief
*       rf module set rf frequency
* \param fre[IN]           - rf communication frequency
* \return
*       none         
*/
void rf_set_channel(u8 ch);

/*! \brief
*       rf module set rf frequency
* \param fre[IN]           - rf communication frequency
* \return
*       none         
*/
void rf_set_fre(u8 fre);

/*! \brief
*       rf module enter into rx mode
* \return
*       none         
*/
void rf_set_rxmode(void);

/*! \brief
*       rf module get state
* \return
*       E_RF_MODE_IDLE  - ����״̬
*       E_RF_MODE_SEND  - ����״̬
*       E_RF_MODE_RECV  - ����״̬
*/
u8   rf_get_state(void);

/*! \brief
*       rf module interrupt service routines
* \return
*       E_RF_MODE_IDLE  - ����״̬
*       E_RF_MODE_SEND  - ����״̬
*       E_RF_MODE_RECV  - ����״̬
*/
void rf_isr(void);

/*! \brief
*       rf module query recv state
* \return
*       E_RF_RX_FLAG_IDLE           - ����״̬
*       E_RF_RX_FLAG_RECVING        - ���ڽ���
*       E_RF_RX_FLAG_RECV_COMPLETE  - �������
*       E_RF_RX_FLAG_PROCESSING     - ���ڴ���    
*/
u8   rf_get_recv_flag(void);

#endif

#endif