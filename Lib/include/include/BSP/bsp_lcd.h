

#ifndef _BSP_LCD_H
#define _BSP_LCD_H

#ifdef HAVE_LCD

typedef enum _E_PWR_Type{
    E_PWR_INT = 0,
    E_PWR_EXT,
}E_PWR_Type;

/*! \brief LCD Port Configure Definition */
typedef struct _LCDPortConfig{   
    u8 pwr_type;
    u8 seg[6];              /*!< \brief ����seg����ʹ�� */
}LCDPortConfig;

/*! \brief
*       lcd power on
*/
void BSP_LCD_PowerOn(void);

/*! \brief
*       lcd power off
*/
void BSP_LCD_PowerOff(void);

void BSP_LCD_LoadConfig(LCDPortConfig *handler);

/*! \brief
*       lcd initilization
*/
void BSP_LCD_Init(void);

/*! \brief
*       lcd close
*/
void BSP_LCD_Close(void);

/*! \brief
*       write display byte data to lcd
* \param addr[IN]	lcd display address
* \param dat[IN]	display data
* \param len[IN]	length of data
*/
void BSP_LCD_WriteData(u8 addr, const u8 *dat, u8 len);

#endif

#endif