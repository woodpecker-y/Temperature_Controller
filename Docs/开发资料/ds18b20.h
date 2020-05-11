#ifndef _DS18B20_H
#define _DS18B20_H

uint8_t                  DS18B20_Init                      ( void );
void                     DS18B20_ReadId                    ( uint8_t * ds18b20_id );
//float                    DS18B20_GetTemp_SkipRom           ( void );
float                    DS18B20_GetTemp_MatchRom          ( uint8_t * ds18b20_id );
void                    DS18B20_GetTemp_SkipRom            (s16 *temp);

//void DS_out_0();
//void DS_out_1();
//void DS_Write_Byte(unsigned char);
//unsigned char DS_Read_Byte(void);
//void DS_Init (void);
//void DS_Skip(void);
//void DS_Convert (void);
//void DS_ReadDo (void);
//unsigned int DS_ReadTemp(void);

#endif