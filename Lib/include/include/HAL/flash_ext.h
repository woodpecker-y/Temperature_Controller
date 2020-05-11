#ifdef HAVE_FLASH_EXT

#ifndef _FLASH_EXT_H
#define _FLAHS_EXT_H

#include "bsp.h"
#include "bsp_flash_ext.h"

/*! \brief
*       ����FLASH���ò���
* \param cfg[IN]			- flash���ò���
*/
void flash_ext_load_config(FlashConfig *cfg);

/*! \brief
*       ��ʼ��Flash
*/
void flash_ext_init(void);

/*! \brief
*       ��Flash����ID
* \return
*		value						- ����Flash������
*		- E_FLASH_TYPE_M25PE16		- ST 2M
*		- E_FLASH_TYPE_M25PE32		- ST 4M
*		- E_FLASH_TYPE_M25PE64		- ST 8M
*		- E_FLASH_TYPE_W25Q40BV		- Winbond 512K
*		- E_FLASH_TYPE_W25Q32FV		- Winbond 4M
*		- E_FLASH_TYPE_W25Q64FV		- Winbond 8M
*		- E_FLASH_TYPE_W25Q128FV	- Winbond 16M		
*		- E_FLASH_TYPE_GD25Q16B		- GD 2M
*		- E_FLASH_TYPE_GD25Q32B		- GD 4M
*/
u32 flash_ext_read_id(void);

/*! \brief
*       ���оƬ�����ҳ��
* \return
*		pages count
*/
u32 flash_ext_get_max_phy_pages(void);

/*! \brief
*       ��Flashд���ֽ�����
* \param addr[IN]			- ��ַ��		
* \param dat[IN]			- ����
* \param len[IN]			- ���ݳ���
* \return
*		Writen Bytes Count	- ��д����ֽ���
*			>0		- д��ɹ�
*			=0		- д��ʧ��
* \notes
*		1.�ú���д��ʱ��������������Ҫ����Ա�ֹ�����
*/
u32 flash_ext_write(u32 addr, u8 *dat, u32 len);

/*! \brief
*       ��Flash��ȡ�ֽ�����
* \param addr[IN]			- ��ʼ��ַ	
* \param dat[OUT]			- ����
* \param len[IN]			- ����
* \return
*		�Ѷ�ȡ�����ݳ���	
*			>0		- ��ȡ�ɹ�
*			=0		- ��ȡʧ��
*/
u32 flash_ext_read(u32 addr, u8 *dat, u32 len);

/*! \brief
*       ��������FLASHоƬ������
* \param page[IN]		- ҳ��ַ		
*/
void flash_ext_erase_chip(void);

/*! \brief
*       ����4K����
* \param page[IN]		- ҳ��ַ		
*/
void flash_ext_erase_4k(u32 page);

/*! \brief
*       �������4K����
* \param addr[IN]		- ��ַ
* \param size[IN]		- ��С
*/
void flash_ext_erase_multi_4k(u32 addr, u32 size);

#endif

#endif
