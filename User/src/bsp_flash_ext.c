#ifdef HAVE_FLASH_EXT

#include <stdio.h>
#include <string.h>
#include "bsp.h"
#include "bsp_flash_ext.h"
#include "bsp_gpio.h"

static FlashConfig *s_flash_cfg_handler		= NULL;
static u32   s_flash_max_phy_pages	= 0;

/*! \brief  SPI�ܽų�ʼ�� */
static void BSP_FLASH_EXT_SPI_PortInit(void);
/*! \brief ����ģ��SPI��NSS���� */
static void BSP_FLASH_EXT_SPI_NssSet(u8 val);
/*! \brief ����ģ��SPI��Sck���� */
static void BSP_FLASH_EXT_SPI_SckSet(u8 val);
/*! \brief ����ģ��SPI��MOSI���� */
static void BSP_FLASH_EXT_SPI_MosiSet(u8 val);
/*! \brief ��ģ��SPI��miso�������� */
static u8 BSP_FLASH_EXT_SPI_MisoRead(void);
/*! \brief ͨ��ģ��SPI��д���� */
static void BSP_FLASH_EXT_SPI_WriteData(unsigned char uData);
/*! \brief ͨ��ģ��SPI�ڶ����� */
static unsigned char BSP_FLASH_EXT_SPI_ReadData(void);
/*! \brief flash������ʱ */
static void BSP_FLASH_EXT_Delay(void);
/*! \brief flashоƬд����ʹ�� */
static void BSP_FLASH_EXT_WriteEnable(void);
/*! \brief flashоƬд������ֹ */
static void BSP_FLASH_EXT_WriteDisable(void);
/*! \brief flash��״̬�Ĵ��� */
static u8  BSP_FLASH_EXT_ReadRegStatus(void);
/*! \brief flash�ȴ�д������� */
static void BSP_FLASH_EXT_WaitWriteComplete(void);

/*! \brief
*       ����FLASH���ò���
* \param cfg[IN]			- flash���ò���
*/
void BSP_FLASH_EXT_LoadConfig(FlashConfig *cfg)
{
    s_flash_cfg_handler = cfg;
}

/*! \brief
*       ��ʼ��Flash
*/
void BSP_FLASH_EXT_Init(void)
{
    BSP_FLASH_EXT_SPI_PortInit();
    // ��ʱ�ȴ�
    //BSP_FLASH_EXT_Delay();
}

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
u32 BSP_FLASH_EXT_ReadID(void)
{
    u32 flash_id = 0;
    
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(0);
    // ��ʱ�ȴ�
    BSP_FLASH_EXT_Delay();
    // д����
    BSP_FLASH_EXT_SPI_WriteData(FLASH_INS_READ_ID);
    // ������
    flash_id = BSP_FLASH_EXT_SPI_ReadData();
    flash_id = (flash_id<<8) + BSP_FLASH_EXT_SPI_ReadData();
    flash_id = (flash_id<<8) + BSP_FLASH_EXT_SPI_ReadData();
    // ��ʱ�ȴ�
    BSP_FLASH_EXT_Delay();
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(1);
    
//    if (E_FLASH_TYPE_M25PE16 == flash_id)
//    {
//        s_flash_max_phy_pages = 8192;
//    }
//    else if (E_FLASH_TYPE_M25PE32 == flash_id)
//    {
//        s_flash_max_phy_pages = 8192*2;
//    }
//    else if (E_FLASH_TYPE_M25PE64 == flash_id)
//    {
//        s_flash_max_phy_pages = 32768;
//    }
//    else if (E_FLASH_TYPE_W25Q40BV == flash_id)
//    {
//        s_flash_max_phy_pages = 2048;
//    }
//    else if (E_FLASH_TYPE_W25Q32FV == flash_id)
//    {
//        s_flash_max_phy_pages = 8192*2;
//    }
//    else if (E_FLASH_TYPE_W25Q64FV == flash_id)
//    {
//        s_flash_max_phy_pages = 32768;
//    }
//    else if (E_FLASH_TYPE_W25Q128FV == flash_id)
//    {
//        s_flash_max_phy_pages = 65536;
//    }   
//    else if (E_FLASH_TYPE_W25Q128FV == flash_id)
//    {
//        s_flash_max_phy_pages = 8192;
//    }  
//    else if (E_FLASH_TYPE_GD25Q16B == flash_id)
//    {
//        s_flash_max_phy_pages = 8192*2;
//    }  
//    else
//    {
//        s_flash_max_phy_pages = 0;
//    }      
    
    switch(flash_id)
    {
    case E_FLASH_TYPE_M25PE16:
        s_flash_max_phy_pages = 8192;
        break;
    case E_FLASH_TYPE_M25PE32:
        s_flash_max_phy_pages = 8192*2;
        break;
    case E_FLASH_TYPE_M25PE64:
        s_flash_max_phy_pages = 32768;
        break;
    case E_FLASH_TYPE_W25Q40BV:
        s_flash_max_phy_pages = 2048;
        break;
    case E_FLASH_TYPE_W25Q32FV:
        s_flash_max_phy_pages = 8192*2;
        break;
    case E_FLASH_TYPE_W25Q64FV:
        s_flash_max_phy_pages = 32768;
        break;
    case E_FLASH_TYPE_W25Q128FV:
        s_flash_max_phy_pages = 65536;
        break;
    case E_FLASH_TYPE_GD25Q16B:
        s_flash_max_phy_pages = 8192;
        break;
    case E_FLASH_TYPE_GD25Q32B:
        s_flash_max_phy_pages = 8192*2;
        break;
    default:
        s_flash_max_phy_pages = 0;
        break;
    }
    
    return flash_id;
}

/*! \brief
*       ���оƬ�����ҳ��
* \return
*		pages count
*/
u32 BSP_FLASH_EXT_GetMaxPhyPages(void)
{
    return s_flash_max_phy_pages;
}

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
u32 BSP_FLASH_EXT_WriteBytes(u32 addr, u8 *dat, u32 len)
{
    u32 i = 0;
    u8  tmp[256] = {0};
    u32 size = 0;
    
    // д���ݲ��ܳ���256�ֽ��Ҳ��ܿ�ҳ
    if ((len > 256) || (256-addr%256 < len) || (len==0))
    {
        return 0;
    }
    
    // ʹ��д����
    BSP_FLASH_EXT_WriteEnable();
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(0);
    // ��ʱ�ȴ�
    BSP_FLASH_EXT_Delay();
    // д����
    BSP_FLASH_EXT_SPI_WriteData(FLASH_INS_PAGE_PROGRAM);	
    // д��ַ
    BSP_FLASH_EXT_SPI_WriteData((addr>>16)&0xff);
    BSP_FLASH_EXT_SPI_WriteData((addr>>8)&0xff);
    BSP_FLASH_EXT_SPI_WriteData((addr&0xff));
    // д����
    for (i=0; i<len; ++i)
    {
        BSP_FLASH_EXT_SPI_WriteData(dat[i]);
    }
    
    // ��ʱ�ȴ�
    BSP_FLASH_EXT_Delay();
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(1);
    // ��ʱ�ȴ�
    BSP_FLASH_EXT_WaitWriteComplete();
    // ��ֹд����
    BSP_FLASH_EXT_WriteDisable();
    
    // ��֤д�������
    size = BSP_FLASH_EXT_ReadBytes(addr, tmp, len);
    if (len != size)
        return 0;
    
    // ��֤д��������Ƿ���ȷ
    if (memcmp(tmp, dat, len) != 0)
        return 0;
    
    return len;
}

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
uint32_t BSP_FLASH_EXT_Write_MultiPages_Data(u32 page_start, u32 pages, u8 *dat, u32 len)
{
    u32 i = 0;
    u32 rv = 0;
    u32 addr = 0;
    
    // �ж����ݻ�������С�Ƿ��㹻
    if (len < pages*FLASH_EXT_PAGE_SIZE)
    {
        return 0;
    }
    
    addr = page_start * FLASH_EXT_PAGE_SIZE;
    
    for (i=0; i<pages; ++i)
    {
        rv = BSP_FLASH_EXT_WriteBytes(addr+i*FLASH_EXT_PAGE_SIZE, dat+i*FLASH_EXT_PAGE_SIZE, FLASH_EXT_PAGE_SIZE);
        if (rv != FLASH_EXT_PAGE_SIZE)
        {
            break;
        }
    }
    
    return pages;
}

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
u32 BSP_FLASH_EXT_ReadBytes(u32 addr, u8 *dat, u32 len)
{
    u32 i = 0;
    
    // д���ݲ��ܳ���256�ֽ��Ҳ��ܿ�ҳ
    if ((len > 256) || (256-addr%256 < len) || (len==0))
    {
        return 0;
    }
    
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(0);
    // ��ʱ�ȴ�
    BSP_FLASH_EXT_Delay();
    // д����
    BSP_FLASH_EXT_SPI_WriteData(FLASH_INS_READ_DATA);	
    // д��ַ
    BSP_FLASH_EXT_SPI_WriteData((addr>>16)&0xff);
    BSP_FLASH_EXT_SPI_WriteData((addr>>8)&0xff);
    BSP_FLASH_EXT_SPI_WriteData((addr&0xff));
    // ������
    for (i=0; i<len; ++i)
    {
        dat[i] = BSP_FLASH_EXT_SPI_ReadData();
    }
    
    // ��ʱ�ȴ�
    BSP_FLASH_EXT_Delay();
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(1);
    
    return i;
}

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
u32 BSP_FLASH_EXT_Read_MultiPages_Data(u32 page_start, u32 pages, u8 *dat, u32 len)
{
    u32 i = 0;
    u32 rv = 0;
    u32 addr = 0;
    
    // �ж����ݻ�������С�Ƿ��㹻
    if (len < pages*FLASH_EXT_PAGE_SIZE)
    {
        return 0;
    }
    
    addr = page_start * FLASH_EXT_PAGE_SIZE;
    
    for (i=0; i<pages; ++i)
    {
        rv = BSP_FLASH_EXT_ReadBytes(addr+i*FLASH_EXT_PAGE_SIZE, dat+i*FLASH_EXT_PAGE_SIZE, FLASH_EXT_PAGE_SIZE);
        if (rv != FLASH_EXT_PAGE_SIZE)
        {
            break;
        }
    }
    
    return pages;
}

/*! \brief
*       ����4K����
* \param page[IN]		- ҳ��ַ		
*/
void BSP_FLASH_EXT_Erase4K(u32 page)
{
    u32 addr = 0;
    
    // ����FLASH������ַ
    addr = page * FLASH_EXT_PAGE_SIZE;
    
    // ʹ��д����
    BSP_FLASH_EXT_WriteEnable();
    
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(0);
    // ��ʱ�ȴ�
    BSP_FLASH_EXT_Delay();
    // д����
    BSP_FLASH_EXT_SPI_WriteData(FLASH_INS_BLOCK_ERASE_4K);	
    // д��ַ
    BSP_FLASH_EXT_SPI_WriteData((addr>>16)&0xff);
    BSP_FLASH_EXT_SPI_WriteData((addr>>8)&0xff);
    BSP_FLASH_EXT_SPI_WriteData((addr&0xff));
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(1);
    // ��ʱ�ȴ�
    BSP_FLASH_EXT_Delay();
    // �ȴ�ִ�н���
    BSP_FLASH_EXT_WaitWriteComplete();
    // ��ֹд����
    BSP_FLASH_EXT_WriteDisable();
    
    return;
}

/*! \brief
*       ��������FLASHоƬ	
*/
void BSP_FLASH_EXT_EraseChip(void)
{
    // ʹ��д����
    BSP_FLASH_EXT_WriteEnable();
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(0);
    // ��ʱ�ȴ�
    BSP_FLASH_EXT_Delay();
    // д����
    BSP_FLASH_EXT_SPI_WriteData(FLASH_INS_CHIP_ERASE);	
    
    // ��ʱ�ȴ�
    BSP_FLASH_EXT_Delay();
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(1);
    // �ȴ��������
    BSP_FLASH_EXT_WaitWriteComplete();
    // ��ֹд����
    BSP_FLASH_EXT_WriteDisable();
}

/*! \brief
*      SPI�ܽų�ʼ��
*/
static void BSP_FLASH_EXT_SPI_PortInit(void)
{
    assert_param(s_flash_cfg_handler != NULL);
    
    BSP_GPIO_Init(s_flash_cfg_handler->nss.port,	s_flash_cfg_handler->nss.pin,	GPIO_Mode_Out_PP_Low_Fast);
    BSP_GPIO_Init(s_flash_cfg_handler->sck.port,	s_flash_cfg_handler->sck.pin,	GPIO_Mode_Out_PP_Low_Fast);
    BSP_GPIO_Init(s_flash_cfg_handler->mosi.port,	s_flash_cfg_handler->mosi.pin,	GPIO_Mode_Out_PP_Low_Fast);
    BSP_GPIO_Init(s_flash_cfg_handler->miso.port,	s_flash_cfg_handler->miso.pin,	GPIO_Mode_In_PU_No_IT);
}

/*! \brief
*      SPI NSS��������
* \param[IN]val			- ����ֵ
*		0		- �õ�
*		1		- �ø�
*/
static void BSP_FLASH_EXT_SPI_NssSet(u8 val)
{
    if (val)
    {
        BSP_GPIO_SetHigh(s_flash_cfg_handler->nss.port,	s_flash_cfg_handler->nss.pin);
    }
    else
    {
        BSP_GPIO_SetLow(s_flash_cfg_handler->nss.port,	s_flash_cfg_handler->nss.pin);
    }
}

/*! \brief
*      SPI Sck��������
* \param[IN]val			- ����ֵ
*		0		- �õ�
*		1		- �ø�
*/
static void BSP_FLASH_EXT_SPI_SckSet(u8 val)
{
    if (val)
    {
        BSP_GPIO_SetHigh(s_flash_cfg_handler->sck.port, s_flash_cfg_handler->sck.pin);
    }
    else
    {
        BSP_GPIO_SetLow(s_flash_cfg_handler->sck.port, s_flash_cfg_handler->sck.pin);
    }
}

/*! \brief
*      SPI MOSI��������
* \param[IN]val			- ����ֵ
*		0		- �õ�
*		1		- �ø�
*/
static void BSP_FLASH_EXT_SPI_MosiSet(u8 val)
{
    if (val)
    {
        BSP_GPIO_SetHigh(s_flash_cfg_handler->mosi.port, s_flash_cfg_handler->mosi.pin);
    }
    else
    {
        BSP_GPIO_SetLow(s_flash_cfg_handler->mosi.port,	s_flash_cfg_handler->mosi.pin);
    }
}

/*! \brief
*      SPI miso���Ŷ�����
* \return
*		value		- SPI���豸���ص�����
*/
static u8 BSP_FLASH_EXT_SPI_MisoRead(void)
{
    return BSP_GPIO_ReadState(s_flash_cfg_handler->miso.port, s_flash_cfg_handler->miso.pin);
}

/*! \brief
*       ͨ��ģ��SPI��д����
* \param uData[IN]      - data
*/
static void BSP_FLASH_EXT_SPI_WriteData(unsigned char uData)
{
    u8	u8Index = 0;
    
    // д�Ĵ�����ַ
    for(u8Index = 0; u8Index < 8; u8Index++)
    {
        if((uData << u8Index) & 0x80)
        {
            BSP_FLASH_EXT_SPI_MosiSet(1);
        }
        else
        {
            BSP_FLASH_EXT_SPI_MosiSet(0);
        }
        
        BSP_FLASH_EXT_SPI_SckSet(0);
        BSP_FLASH_EXT_SPI_SckSet(1);	
    }
}

/*! \brief
*       ͨ��ģ��SPI�ڶ�����
* \return
*       register value
*/
static unsigned char BSP_FLASH_EXT_SPI_ReadData(void)
{
    u8	u8Index = 0;
    u8 	u8Value = 0;
    
    u8Value = 0;
    for(u8Index = 0; u8Index < 8; u8Index++)
    {
        BSP_FLASH_EXT_SPI_SckSet(1);
        BSP_FLASH_EXT_SPI_SckSet(0);
        
        u8Value = u8Value << 1;
        if(1 == BSP_FLASH_EXT_SPI_MisoRead())
        {
            u8Value |= 0x01;		
        }
    }
    
    return u8Value;
}

/*! \brief
*       flash������ʱ
*/
static void BSP_FLASH_EXT_Delay(void) 
{
    u8 i = 50;
    while(i--);
    //delay_us(50);
    /* �ĳɿ���־ */
}

/*! \brief
*       flashоƬд����ʹ��
*/
static void BSP_FLASH_EXT_WriteEnable(void)
{
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(0);
    // ��ʱ�ȴ�
    BSP_FLASH_EXT_Delay();
    // ����FLASHдʹ��
    BSP_FLASH_EXT_SPI_WriteData(FLASH_INS_WRITE_ENABLE);		// write instruction
    // ��ʱ�ȴ�
    BSP_FLASH_EXT_Delay();
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(1);
}

/*! \brief
*       flashоƬд������ֹ
*/
static void BSP_FLASH_EXT_WriteDisable(void)
{
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(0);
    // ����FLASHдʹ��
    BSP_FLASH_EXT_SPI_WriteData(FLASH_INS_WRITE_DISABLE);		// write instruction
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(1);
    // ��ʱ�ȴ�
    BSP_FLASH_EXT_Delay();
}

/*! \brief
*       flash��״̬�Ĵ���
*/
static u8  BSP_FLASH_EXT_ReadRegStatus(void)
{
    unsigned char state;
    
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(0);
    // д����
    BSP_FLASH_EXT_SPI_WriteData(FLASH_INS_READ_STATUS_REG);		
    // ��״̬
    state = BSP_FLASH_EXT_SPI_ReadData();
    // Ƭѡ����
    BSP_FLASH_EXT_SPI_NssSet(1);
    
    return state;
}

/*! \brief
*       flash�ȴ�д�������
*/
static void BSP_FLASH_EXT_WaitWriteComplete(void)
{
    do {
    }while (BSP_FLASH_EXT_ReadRegStatus() & 0x01);
}

#endif





