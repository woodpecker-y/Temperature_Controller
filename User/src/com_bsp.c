/*    ��������:
*       |-->com_load_config()
*           |-->com_init()
*               |-->com_send_char()
*               |-->com_send_data()
*               |-->com_send_str()
*               |-->com_recv_init()
*               |-->com_recv_data()
*           |-->com_close()
*       |-->INTERRUPT_HANDLER(USART1_RX_TIM5_CC_IRQHandler,28)
*           |-->com_isr()
******************************************************************************/
#include "bsp.h"
#include "com_bsp.h"
#ifdef HAVE_COM_BSP
/*! \brief
*       com confirure handler
* \param com_cfg[IN]        - �������ýṹ��
* \param com_cfg_cnt[IN]	- ������������		
*/
void com_load_config(COMConfig *com_cfg, uint8_t cnt)
{
    BSP_COM_LoadConfig(com_cfg, cnt);
}

void com_set_rx_pin_mode(u8 mode)
{
    BSP_COM_SetRxPinMode(mode);
}

/*! \brief
*       ���ڳ�ʼ��
* \param com[IN]					- ���ں�
* \param baudrate[IN]				- ������
* \param wordlength[IN]				- ����λ
* \param stopbits[IN]				- ֹͣλ
* \param mode[IN]					- ����ģʽ
* \param rx_interrupt_state[IN]		- �����ж�״̬
* \param rx_interrupt_prority[IN]	- �����ж����ȼ�
* \return
*		E_COM_OK						- �ɹ�
*		E_COM_ERR_NOT_DEFINED_COM_ID	- δ����Ĵ���
*		E_COM_ERR_NOT_SUPPORT_COM		- ��֧�ֵĴ���
*/
uint8_t com_init(COM com, uint32_t baudrate, uint16_t wordlength, uint16_t stopbits, uint16_t parity, uint16_t mode, uint8_t rx_interrupt_state,	uint8_t  rx_interrupt_prority)
{
    return BSP_COM_Init(com, baudrate, wordlength, stopbits, parity, mode, rx_interrupt_state, rx_interrupt_prority);
}

/*! \brief
*       ���ڹر�
* \param com[IN]					- ���ں�
* \return
*		E_COM_OK			        - �ɹ�
*		E_COM_ERR_NOT_DEFINED_COM_ID	        - δ����Ĵ���
*		E_COM_ERR_NOT_SUPPORT_COM		- ��֧�ֵĴ���
*/
uint8_t com_close(COM com)
{
    return BSP_COM_Close(com);
}

/*! \brief
*       ���ڳ�ʼ��
* \param com[IN]					- ���ں�
* \param ch[IN]						- һ���ֽ�
* \return
*		E_COM_OK						- �ɹ�
*		E_COM_ERR_NOT_DEFINED_COM_ID	- δ����Ĵ���
*		E_COM_ERR_NOT_SUPPORT_COM		- ��֧�ֵĴ���
*/
uint8_t com_send_char(COM com, uint8_t ch)
{
    return BSP_COM_SendChar(com, ch);
}

/*! \brief
*       uart get recv flag
* \param com[IN]            uart com no.
* \return
*       SET         - ˵��������
*       RSET        - ˵�����ջ�����Ϊ��
*/
FlagStatus com_get_rxflag(COM com)
{
    return BSP_COM_GetRxFlag(com);
}

/*! \brief
*       ���ڽ���һ���ֽ�����
* \param com[IN]					- ���ں�
* \return
*   һ���ֽ�����
* \notes
*   ʹ��ǰ�����ȵ���com_get_rxflag,��ֻ���䷵��ֵΪSETֵ���ſ��Ե��ñ�����
*/
eCOMRet com_recv_char(COM com, uint16_t *dat)
{
    return BSP_COM_RecvChar(com, dat);
}

/*! \brief
*       ���ڳ�ʼ��
* \param com[IN]					- ���ں�
* \param dat[IN]					- �ֽ�����
* \param len[IN]					- �ֽ����ݳ���
* \return
*		E_COM_OK						- �ɹ�
*		E_COM_ERR_NOT_DEFINED_COM_ID	- δ����Ĵ���
*		E_COM_ERR_NOT_SUPPORT_COM		- ��֧�ֵĴ���
*/
uint8_t com_send_data(COM com, uint8_t *dat, uint16_t len)
{
    return BSP_COM_SendData(com, dat, len);
}

/*! \brief
*       ���ڳ�ʼ��
* \param com[IN]					- ���ں�
* \param str[IN]					- �ַ���
* \return
*		E_COM_OK						- �ɹ�
*		E_COM_ERR_NOT_DEFINED_COM_ID	- δ����Ĵ���
*		E_COM_ERR_NOT_SUPPORT_COM		- ��֧�ֵĴ���
*/
uint8_t com_send_str(COM com, char *str)
{
    return BSP_COM_SendStr(com, str);
}

/*! \brief
*       ���ڽ��ճ�ʼ��
* \param com[IN]					- ���ں�
* \return
*		E_COM_OK						- �ɹ�
*		E_COM_ERR_NOT_DEFINED_COM_ID	- δ����Ĵ���
*/
uint8_t com_recv_init(COM com)
{
    return BSP_COM_RecvInit(com);
}

/*! \brief
*       ���ڽ�������
* \param com[IN]						- ���ں�
* \param dat[OUT]						- ���ݽ���ָ��
* \param len[OUT]						- ���ݵĳ���
* \return
*		E_COM_OK						- �ɹ�
*		E_COM_ERR_NOT_DEFINED_COM_ID	- δ����Ĵ���
* \note
*		����ptr��һ������ָ�룬��ʹ��ʱ����ҪΪptr�����ڴ�ռ䣬����һ����ָ�뼴�ɣ����ʱ����������������ݻ��������׵�ַ��
*		ʹ�ð�����
*			uint8_t *rcv_ptr = NULL;
*			uint16_t rcv_len = 0;
*			
*			com_recv_data(COM1, &rcv_ptr, &rcv_len);
*/
uint8_t com_recv_data(COM com, uint8_t **dat, uint16_t *len)
{
    return BSP_COM_RecvData(com, dat, len);
}

/*! \brief
*       uart read data from recv data buffer.
* \param com[IN]            uart com no.
* \param pval[OUT]          data ptr point to recv data buffer.
* \param len[OUT]           length of recved data.
* \return
*       >0          read data successfully.
*       =0          no data
*/
u8   com_recv_data_stream(COM com, u8 **pval, u16 *len)
{
    return BSP_COM_RecvDataStream(com, pval, len);
}

/*! \brief
*	com interrupt service runtine
* \param com[IN]            - com no.
*/
void com_isr(COM com)
{
    BSP_COM_ISR(com);
}

/**  @brief   com read data in lower power mode
  *  @param   rcv_buf [OUT]     - ?����??o��?
  *  @param   rcv_len [OUT]     - ?����?��y?Y3��?��
  *
  *  @retval  none
  */
u8 uart_lpr_rcv(COM com, u8 **rcv_buf, u16 *rcv_len)
{
   return BSP_COM_LprRecvData(com, rcv_buf, rcv_len);
}

#endif



