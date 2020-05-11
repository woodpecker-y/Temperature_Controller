#ifndef _MODBUS_H
#define _MODBUS_H

// MODBUS������
#define MODBUS_CMD_READ_MULTI		0x03	// ������Ĵ���
#define MODBUS_CMD_WRITE_SINGLE		0x06	// д�����Ĵ���
#define MODBUS_CMD_WRITE_MULTI		0x10	// д����Ĵ���

// MODBUS��ַ��
#define MODBUS_ADDR	0xFF

typedef enum _ModbusRet{
    MODBUS_OK = 0,
    MODBUS_ERR_INVALID_CMD,		 // δ֪������
    MODBUS_ERR_CRC16,			 // У��ʹ���
    MODBUS_ERR_LESS_MEMORY,              // �ڴ治��
    MODBUS_ERR_ADDR,                     // ��ַ��ƥ��
    MODBUS_ERR_LENGTH			 // ���ȴ���
}ModbusRet;

u8 modbus_pack(u8 *package, u8 *size, u8 addr, u8 cmd, u8 *dat, u8 len);
u8 modbus_unpack(u8 *package, u8 size, u8 *addr, u8 *cmd, u8 **dat, u8 *len);

#endif