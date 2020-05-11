#ifdef HAVE_FLASH

#ifndef _FLASH_H
#define _FLASH_H

/*! \brief
*       доƬ�ڲ�FLASH
* \param addr[IN]			- д�׵�ַ
* \param dat[IN]			- ����
* \param len[IN]			- ���ݳ���
* \return
*		E_FLASH_OK						- �ɹ�
*		E_FLASH_ERR_INCORRECT_LENGTH	- ���Ȳ���ȷ
*		E_FLASH_ERR_WRITE_UNCOMPLETE	- д��ʧ��
* \notes
*		��flashд�����С����Ϊ2Bytes����˳��ȱ�����2����������
*/
u8 flash_write(u32 addr, u8* dat, u32 len);

/*! \brief
*       ��оƬ�ڲ�FLASH
* \param addr[IN]			- ���׵�ַ
* \param dat[IN]			- ����
* \param len[IN]			- ���ݳ���
* \return
*		E_FLASH_OK						- �ɹ�
*/
u8 flash_read(u32 addr, u8* dat, u32 len);

/*! \brief
*       ����FLASH
* \param addr[IN]			- д�׵�ַ
* \param count[IN]			- ����
* \return
*		E_FLASH_OK					- �ɹ�
*		E_FLASH_ERR_ERASE_FAILED	- ����ʧ��
*/
u8 flash_erase_sector(u32 addr, u32 count);

#endif

#endif
