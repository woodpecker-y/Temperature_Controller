#ifndef _BU97931_H
#define _BU97931_H

#ifdef HAVE_LCD_EXT

/*! \brief LCD Extern Chip Port Configure Definition */
typedef struct _LCDPortConfigExt{
    PortTypeDef csb;       /*!< \brief LCD Extern Chip Select Pin */
    PortTypeDef sck;       /*!< \brief LCD Extern Chip serial clock Pin */
    PortTypeDef sda;       /*!< \brief LCD Extern Chip serial data Pin */
}LCDPortConfigExt;

void BSP_LCD_LoadConfig(LCDPortConfigExt *handler);
/*! \brief LCD��ʼ�� */
void BSP_LCD_Init(void);
/*! \brief LCD�ر� */
void BSP_LCD_Close(void);
/*! \brief LCD�ϵ� */
void BSP_LCD_PowerOn(void);
/*! \brief LCD���� */
void BSP_LCD_PowerOff(void);
/*! \brief LCDд���� */
void BSP_LCD_WriteData(unsigned char addr, const unsigned char *data, unsigned char len);

#endif

#endif