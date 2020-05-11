#ifndef _ERROR_H
#define _ERROR_H

#include "stm8l15x.h"

typedef enum _ErrorSet{
    FAULT_VALVE				= 0x0003,  // ���Ź���
    FAULT_COMM				= 0x0004,  // ͨѶʧ��
    FAULT_BATT			        = 0x0008,  // ��ص�ѹ����
    FAULT_RF_OUTDOOR			= 0x0010,  // �����RF����
    FAULT_RF_INDOOR		        = 0x0020,  // ���ڻ�RF����
    FAULT_TEMP_SENSOR_IN		= 0x0040,  // ��ˮ�¶ȴ���������
    FAULT_TEMP_SENSOR_OUT		= 0x0080,  // ��ˮ�¶ȴ���������
    FAULT_TEMP_SENSOR_INDOOR	        = 0x0100,  // ���ڻ��¶ȴ���������
    FAULT_BATT_SENDOR_INDOOR	        = 0x0200,  // ��ش���������
    //FAULT_VALVE_IS_ACTION               = 0x0400,  // ���Ŷ�����
    FAULT_RF                            = 0x80,  // ���߹���
    FAULT_LOW_BATT                      = 0x01,  // ��ص�ѹ����
}ErrorSet;

void error_set(u16 code);

void error_clr(u16 code);

void error_set_u8(u8 code);
void error_clr_u8(u8 code);

#endif