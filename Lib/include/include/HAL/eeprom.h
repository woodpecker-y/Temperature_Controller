/*    ��������:
*       дEEPROM�����ʼ��
*       |-->eeprom_init()
*           |-->eeprom_write_byte()
*           |-->eeprom_write()
*       |-->eeprom_close()
*       ��EEPROM����ֱ�Ӷ�
*       |-->eeprom_read_byte()
*       |-->eeprom_read()
******************************************************************************/
#ifndef _EEPROM_H
#define _EEPROM_H

#ifdef HAVE_EEPROM

#include "bsp.h"


/*! \brief
*       eeprom initilization
*/
void eeprom_init(void);

/*! \brief
*       eeprom write one byte
* \param addr[IN]       - dest address to be written
* \param dat[IN]        - data to be written
*/
void eeprom_write_byte(u32 addr, u8 byte);

/*! \brief
*       eeprom read one byte
* \param addr[IN]       - dest address to be read
* \return
*       readed data
*/
u8   eeprom_read_byte(u32 addr);

/*! \brief
*       eeprom write multiply bytes
* \param addr[IN]       - dest address to be written
* \param dat[IN]        - data to be written
* \param len[IN]        - length of data
*/
void eeprom_write(u32 addr, u8 *dat, u8 len);

/*! \brief
*       eeprom read multiply bytes
* \param addr[IN]       - dest address to be written
* \param dat[OUT]       - data buffer
* \param len[IN]        - length will be readed.
*/
void eeprom_read(u32 addr, u8 *dat, u8 len);

/*! \brief
*       eeprom close
* \note
*       it will be used when the function 'eeprom_write' or 'eeprom_write_byte' is used.
*/
void eeprom_close(void);

#endif

#endif
