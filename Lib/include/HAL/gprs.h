/*    A6ģ��ʹ��ָ��
*       1.�ڵ���gprs_init�ӿ�֮ǰ�����ȵ���com_load_config()�������ض�Ӧ���ڵ�����;
*       2.gprs_get_rssi()������gprs_check_is_ready���ú�gprs_close����ǰ������ʹ�ã�
*       3.�����Ҫ�������ն�����ݣ��������ݽ���ǰ����gprs_recv_init()����������ջ��������ڷ��ͱ��ĺ������һ������Ҫ���ã�
*       4.�������̣�
*       |-->gprs_load_config()
*           |-->gprs_power_on()
*               |-->gprs_init()
*                   |-->gprs_check_is_ready()
*                   |-->gprs_get_rssi()
*                       |-->gprs_ip_connect()   
*                           |-->gprs_send_data() 
*                           |-->gprs_recv_data() 
*                           |-->gprs_recv_init() 
*                           |-->gprs_recv_data() 
*                           |-->......
*                       |-->gprs_ip_close() 
*               |-->gprs_close()
*           |-->gprs_power_off()
******************************************************************************/
#ifndef _GPRS_H
#define _GPRS_H

#ifdef HAVE_GPRS

/*! \brief
*       ����A6ģ������
* \param handler[IN]        - gprs config handler
*/
void gprs_load_config(GPRSConfig *handler);

/*! \brief
*       ��A6ģ���ϵ�
*/
void gprs_power_on(void);

/*! \brief
*       ��A6ģ��ϵ�
*/
void gprs_power_off(void);

/*! \brief
*       A6ģ�����ó�ʼ��
* \param baudrate[IN]       - A6ģ�鴮�ڲ�����
* \param wordlength[IN]     - A6ģ�鴮������λ
* \param stopbits[IN]       - A6ģ�鴮��ֹͣλ
* \param parity[IN]         - A6ģ�鴮��У��λ
*
* \return
*       E_GPRS_OK     - �ɹ�
*       Others          - ʧ��
*/
u8 gprs_init(u32 baudrate, u8 wordlength, u8 stopbits, u8 parity);

/*! \brief
*       �ͷ�A6ģ��
*/
void gprs_close(void);

/*! \brief
*       GPRSģ�����ݽ��ճ�ʼ��
*/
void gprs_recv_init(void);

/*! \brief
*       ���GPRSģ���Ƿ���׼��������
* \return
*       E_GPRS_OK               - �ɹ�
*       E_GPRS_PROCESSING       - ������
*       E_GPRS_ERR_NO_SIM       - ��SIM��
*       E_GPRS_ERR_CONFIG_PDP   - ����PDP����ʧ��
*       E_GPRS_ERR_ACTIVE_PDP   - ����PDP����ʧ��
*       E_GPRS_ERR_ATTACHED_NETWORK - ��������ʧ��
*/
u8 gprs_check_is_ready(void);

/*! \brief
*       GPRS����Զ�̷�����
* \param server[IN]           - ��������֧��������IP
* \param port[IN]             - �˿�
*
* \return
*       E_GPRS_OK           - �ɹ�
*       E_GPRS_PROCESSING   - ������
*       E_GPRS_ERR_OTHERS   - ����
*/
u8 gprs_ip_connect(char* server, int port);

/*! \brief
*       GPRS�ر�����
* \return
*       E_GPRS_OK           - �ɹ�
*       E_GPRS_PROCESSING   - ������
*       E_GPRS_ERR_OTHERS   - ����
*/
u8 gprs_ip_close(void);

/*! \brief
*       ��ȡ�ź�ֵ
* \param rssi[OUT]           - �ź�ֵ
*
* \return
*       E_GPRS_OK           - �ɹ�
*       E_GPRS_PROCESSING   - ������
*       E_GPRS_ERR_OTHERS   - ����
*/
u8 gprs_get_rssi(u8 *rssi);

/*! \brief
*       �������ݵ�������
* \param dat[IN]           - ����
* \param len[IN]           - ���ݳ���
*
* \return
*       E_GPRS_OK           - �ɹ�
*       E_GPRS_PROCESSING   - ������
*       E_GPRS_ERR_OTHERS   - ����
*/
u8 gprs_send_data(u8* dat, u16 len);

/*! \brief
*       ���մӷ������·�������
* \param msg[OUT]           - ��Ϣָ��
* \param size[OUT]          - ���ݳ���
*
* \return
*       E_GPRS_OK           - �ɹ�
*       E_GPRS_ERR_NO_DATA  - ��������
*       E_GPRS_ERR_OTHERS   - ����
* \notes
*       msgΪ����ָ�룬����ҪΪ�������ڴ滺�壬��ֱ��ָ�򴮿ڽ��ջ��������ڵ���gprs_recv_init()��gprs_send_data()����֮ǰ��һֱ���á�
*/
u8 gprs_recv_data(u8** msg, u16 *size);

#endif
#endif