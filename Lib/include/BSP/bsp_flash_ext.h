#ifndef _BSP_FLASH_EXT_H
#define _BSP_FLASH_EXT_H

#ifdef HAVE_FLASH_EXT

#include "bsp_gpio.h"

/*! \brief �ⲿFLASHһҳ���ֽ��� */
#define FLASH_EXT_PAGE_SIZE			256

/*! \brief �ⲿFLASH�����붨�� */
#define FLASH_INS_WRITE_ENABLE     	    	0x06
#define FLASH_INS_WRITE_DISABLE     	    0x04
#define FLASH_INS_READ_ID		     	    0x9f
#define FLASH_INS_READ_STATUS_REG     	    0x05
#define FLASH_INS_WRITE_STATUS_REG     	    0x01
#define FLASH_INS_READ_DATA		     	    0x03
#define FLASH_INS_PAGE_PROGRAM       	    0x02
#define FLASH_INS_BLOCK_ERASE_4K      	    0x20
#define FLASH_INS_CHIP_ERASE				0xC7
#define FLASH_INS_POWER_DOWN	       	    0xB9
#define FLASH_INS_RELEASE_POWER_DOWN   	    0xAB

/*! \brief Flash���ýṹ�� */
typedef struct _eFlashConfig{
	PortTypeDef		nss;					/*!< \brief NSS */
	PortTypeDef		sck;					/*!< \brief SCK */
	PortTypeDef		mosi;					/*!< \brief MOSI */
	PortTypeDef		miso;					/*!< \brief MISO */
}FlashConfig;

/*! \brief Flash���Ͷ��� */
typedef enum _eFlashType{
	E_FLASH_TYPE_M25PE16	= 0x208015,		/*!< \brief ST 2M */
	E_FLASH_TYPE_M25PE32	= 0x202016,		/*!< \brief ST 4M */
	E_FLASH_TYPE_M25PE64	= 0x202017,		/*!< \brief ST 8M */
	E_FLASH_TYPE_W25Q40BV	= 0xEF4015,		/*!< \brief Winbond 512k */
	E_FLASH_TYPE_W25Q32FV	= 0xEF4016,		/*!< \brief Winbond 4M */
	E_FLASH_TYPE_W25Q64FV	= 0xEF4017,		/*!< \brief Winbond 8M */
	E_FLASH_TYPE_W25Q128FV	= 0xEF4018,		/*!< \brief Winbond 16M */
	E_FLASH_TYPE_GD25Q16B	= 0xC84015,		/*!< \brief Winbond 2M */
	E_FLASH_TYPE_GD25Q32B	= 0xC84016,		/*!< \brief Winbond 4M */
}eFlashType;

/*! \brief
*       ����FLASH���ò���
* \param cfg[IN]			- flash���ò���
*/
void BSP_FLASH_EXT_LoadConfig(FlashConfig *cfg);

/*! \brief
*       ��ʼ��Flash
*/
void BSP_FLASH_EXT_Init(void);

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
u32 BSP_FLASH_EXT_ReadID(void);

/*! \brief
*       ���оƬ�����ҳ��
* \return
*		pages count
*/
u32 BSP_FLASH_EXT_GetMaxPhyPages(void);

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
*		1.�ú������֧��д1ҳ���ݣ���256�ֽڣ�
*		2.�ú�����֧�ֿ�ҳд���ݣ�������м俪ʼд�Ļ������ݳ�����Ҫʹ��256-Addr%256�����ܹ�д��ĳ��ȣ������д��ʧ�ܣ�����0.
*/
u32 BSP_FLASH_EXT_WriteBytes(u32 addr, u8 *dat, u32 len);

/*! \brief
*       ��Flashд���ֽ�����
* \param page_start[IN]		- ��ʼҳ		
* \param pages[IN]			- д���ҳ��
* \param dat[IN]			- ����
* \param len[IN]			- ����
* \return
*		Writen Pages Count	- ��д�����ݵ�ҳ��
* \notes
*		1.һҳ���ݵĳ�����256�ֽڣ����Ҫд������ݳ��ȱ�����pages*256��С��
*/
uint32_t BSP_FLASH_EXT_Write_MultiPages_Data(u32 page_start, u32 pages, u8 *dat, u32 len);

/*! \brief
*       ��Flash��ȡ�ֽ�����
* \param addr[IN]			- ��ʼ��ַ	
* \param dat[OUT]			- ����
* \param len[IN]			- ����
* \return
*		�Ѷ�ȡ�����ݳ���	
*			>0		- ��ȡ�ɹ�
*			=0		- ��ȡʧ��
* \notes
*		1.�ú������֧�ֶ�1ҳ���ݣ���256�ֽڣ�
*		2.�ú�����֧�ֿ�ҳ�����ݣ�������м俪ʼд�Ļ������ݳ�����Ҫʹ��256-Addr%256�����ܹ���ȡ�ĳ��ȣ�������ȡʧ�ܣ�����0.
*/
u32 BSP_FLASH_EXT_ReadBytes(u32 addr, u8 *dat, u32 len);

/*! \brief
*       ��Flash��ȡ�ֽ�����
* \param page_start[IN]		- ��ʼҳ	
* \param pages[OUT]			- ҳ��
* \param dat[IN]			- ����
* \param len[IN]			- ����
* \return
*		�Ѷ�ȡ������ҳ��	
* \notes
*		1.һҳ���ݵĳ�����256�ֽڣ����Ҫ��ȡ�����ݳ��ȱ�����pages*256��С�����ݻ��������붨��ô�С
*/
u32 BSP_FLASH_EXT_Read_MultiPages_Data(u32 page_start, u32 pages, u8 *dat, u32 len);

/*! \brief
*       ����4K����
* \param page[IN]		- ҳ��ַ		
*/
void BSP_FLASH_EXT_Erase4K(u32 page);

/*! \brief
*       ��������FLASHоƬ	
*/
void BSP_FLASH_EXT_EraseChip(void);

#endif

#endif

