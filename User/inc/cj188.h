#ifndef _CJ188_H
#define _CJ188_H

#include "sysparams.h"

// ������ݸ��س���
#define MSG_DATA_MAX    80
// ��ʼ֡
#define CJ188_STX       0x68
// ����֡
#define CJ188_ETX       0x16
// ͨ��ʱ��������豸���Ͷ���
#define CJ188_MTYPE_THERMOSTAT         0x41
#define CJ188_MTYPE_ONOFF_ACTUATORS    0x42
// ������
#define CTRL_CODE_DEV_LOGIN         0x20    // �豸ǩ��
#define CTRL_CODE_REPORT            0x21    // ��ʱ�ϱ�
#define CTRL_CODE_FACTORY           0x22    // ��������
#define CTRL_CODE_ACK               0x26    // ȷ�Ϸ���

/* CJ188Э��֡���� */
typedef struct _CJ188Pkg{
    u8  addr[LENGTH_ADDR];      // �Ǳ��ַ
    u8  ctrl_code;              // ������
    u8  msg_data[MSG_DATA_MAX]; // ����
    u8  msg_size;               // ���ݳ���
    
    u32		sn;			//��Ʒ���к�	4�ֽ�
    u16		gn;			//��Ʒ���		2�ֽ�
//    u8		ctrl_type;		//��������		1�ֽ�
//    u8		msg_length;		//���ݳ���		1�ֽ�
}CJ188Pkg;

/* cj188��������ö�� */
typedef enum _CJ188Ret{
    CJ188_OK = 0,
    CJ188_ERR_CHECKSUM,         // У��ʹ���
    CJ188_ERR_LESS_MEMORY,      // �ڴ治��
    CJ188_ERR_LENGTH,           // ���ȴ���
    CJ188_ERR_ADDR,             // ��ַ��ƥ��
    CJ188_ERR_INVALID_PKG,      // ���ݰ�����
    CJ188_ERR_CTRL_CODE,        // ���������
}CJ188Ret;

/* ��ʱ�ϱ��������ݵ�ö�� */
typedef enum _AddtionDataIdx{
    AD_IDX_HP = 0,			// ��ů��
    AD_IDX_TEMP_SET,			// Զ���趨�¶�
    AD_IDX_TEMP_SET_LIMITS,		// �����趨��ֵ
    AD_IDX_RECHARGE,			// ��ֵ���
    AD_IDX_BALANCE_LINMITS,		// �����ֵ
    AD_IDX_DISP_CTL,                    // ��ʾ����λ
    AD_IDX_ROOM_NAME,                   // ��������
}AddtionDataIdx;

/*! \brief cj188Э���� */
u8 cj188_pack(CJ188Pkg *pkg, u8 *out_data, u8 *out_size);
/*! \brief cj188Э���� */
u8 cj188_unpack(CJ188Pkg *pkg, u8 *in_data, u8 in_size);

#endif