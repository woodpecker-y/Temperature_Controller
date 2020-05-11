#include "adf.h"
#include "modbus.h"

/*! \brief 
*      MODBUSЭ�����
* \param package[OUT]          - ���������ݰ�
* \param size[OUT]				- ���������ݰ�����
* \param addr[IN]				- ��ַ��
* \param cmd[IN]				- ������
* \param dat[IN]				- ����������
* \param dat[IN]				- ���������ݳ���
* 
* \return  
*      0                   - �ɹ�
* \note  
*		size��Ϊ����Ϊ�������������Ϊ�����������Ϊ�������ʱָ��package��������С
* 
*/
u8 modbus_pack(u8 *package, u8 *size, u8 addr, u8 cmd, u8 *dat, u8 dat_len)
{
    u8 i = 0;
    u8 offset = 0;
    u16 crc = 0;
    
    // ��ַ��
    package[offset++] = addr;
    // ������
    package[offset++] = cmd;
    // ������
    for (i=0; i<dat_len; ++i)
    {
        package[offset++] = dat[i];
    }
    
    // CRC-16 Modbus
    crc = crc_16_modbus(package, offset);
    package[offset++] = crc&0xFF;
    package[offset++] = (crc>>8)&0xFF;
    
    *size = offset;
    
    return 0;
}

/*! \brief 
*      MODBUSЭ����
* \param package[IN]			- ԭʼ����
* \param size[IN]				- ԭʼ���ĳ���
* \param addr[OUT]				- ��ַ��
* \param cmd[OUT]				- ������
* \param dat[OUT]				- ����������
* \param dat[OUT]				- ���������ݳ���
* 
* \return  
*      0                   - �ɹ�
* \note  
*		size��Ϊ����Ϊ�������������Ϊ�����������Ϊ�������ʱָ��package��������С
* 
*/
u8 modbus_unpack(u8 *package, u8 size, u8 *addr, u8 *cmd, u8 **dat, u8 *len)
{
    u8  offset = 0;
    u16 crc = 0;
    
    crc = crc_16_modbus(package, size-2);
    if ((crc&0xFF)!=package[size-2] || ((crc>>8)&0xFF)!=package[size-1])
        return MODBUS_ERR_CRC16;
    
    // ��ַ��
    *addr = package[offset];
    offset += 1;
    
    // ������
    if (package[offset]!=MODBUS_CMD_READ_MULTI && package[offset]!=MODBUS_CMD_WRITE_SINGLE && package[offset]!=MODBUS_CMD_WRITE_MULTI)
        return MODBUS_ERR_INVALID_CMD;
    
    *cmd = package[offset];
    offset += 1;
    
    // ������
    *len = size-4;
    *dat = package + offset;
    
    return 0;
}

u8 modbus_read_multi_request_unpack(u8 *data_field, u8 data_field_len, u16 *reg_val, u16 *reg_cnt)
{
    if (data_field_len != 4)
        return MODBUS_ERR_LENGTH;
    
    *reg_val = (data_field[0]<<8) | data_field[1];
    *reg_cnt = (data_field[2]<<8) | data_field[3];
    
    return 0;
}

u8 modbus_read_multi_response_pack(u8 *data_field, u8 data_field_len, u16 *reg_addr, u16 *reg_cnt)
{
    if (data_field_len != 4)
        return MODBUS_ERR_LENGTH;
    
    *reg_addr = (data_field[0]<<8) | data_field[1];
    *reg_cnt  = (data_field[2]<<8) | data_field[3];
    
    return 0;
}

u8 modbus_write_single_request_unpack(u8 *data_field, u8 data_field_len, u16 *reg_addr, u16 *reg_val)
{
    if (data_field_len != 4)
        return MODBUS_ERR_LENGTH;
    
    *reg_addr = (data_field[0]<<8) | data_field[1];
    *reg_val  = (data_field[2]<<8) | data_field[3];
    
    return 0;	
}

u8 modbus_write_multi_request_unpack(u8 *data_field, u8 data_field_len, u16 *reg_addr_st, u8 *reg_val, u8 *reg_cnt)
{
    u8 i = 0;
    u8 offset = 0;
    
    // �������ܳ����ж�
    if (data_field_len != data_field[4]+4)
        return MODBUS_ERR_LENGTH;
    
    // �Ĵ�����ʼ��ַ
    *reg_addr_st = (data_field[0]<<8) | data_field[1];
    // �Ĵ�������
    *reg_cnt     = (data_field[2]<<8) | data_field[3];
    
    // �Ĵ���ֵ�����ж�
    if (*reg_cnt*2 != data_field[4])
        return MODBUS_ERR_LENGTH;
    
    offset = 5;
    
    // �Ĵ���ֵ
    for (i=0; i<data_field[4]; ++i)
    {
        reg_val[i] = data_field[offset];
        offset++;
    }
    
    return 0;	
}