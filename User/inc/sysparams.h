#ifndef _SYS_PARAMS_H
#define _SYS_PARAMS_H

#include "adf.h"
/* ʱ�� */
#define CYCLE_AWU                       101UL         // ʹ���ⲿ��32.768kHz����ʹ��
//#define CYCLE_AWU                       29UL            // ʹ���ڲ���38kHz����ʹ�ã����ƺ�����ʱ�䣬���������
#define UNIT_SECOND	                    20UL
#define HALF_SECOND                     10UL
#define FIVE_SECOND                     (5*UNIT_SECOND)
#define SIX_SECOND                      (6*UNIT_SECOND)
#define THREE_SECOND                    (3*UNIT_SECOND)
#define TWO_SECOND                      (2*UNIT_SECOND)
#define TEN_SECOND                      (10*UNIT_SECOND)
#define UNIT_MIN		                (60*UNIT_SECOND)
#define TWO_MIN                         (2*60*UNIT_SECOND)
#define FIVE_MIN                        (5*60*UNIT_SECOND)
#define FIFTEEN_SECOND		            (15*UNIT_SECOND)
#define THIRTY_SECOND		            (30*UNIT_SECOND)
#define QUARTER_HOUR                    (15*60*UNIT_SECOND)
#define HALF_HOUR                       (30*60*UNIT_SECOND)
#define UNIT_HOUR                       (60*60*UNIT_SECOND)
#define UNIT_DAY                        (24UL*60UL*60UL*UNIT_SECOND)

#define UNIT_KWH                        0x05    /*!< \brief KWH */
#define UNIT_GJ                         0x11    /*!< \brief GJ */

#define AWU_TIMER                       15                 // ~50ms

/*      ��ʽ�������������ID���̷�Ϊ���飬����ͨ���Ų�ͬ���֡�
    ʹ����������ID����Ƶ�� ��Ϊ 420.5M -- ͨ��40  ͨ��50   ͨ��60*/
#define DOWNLOAD_ID_CHANNEL    40
//#define DOWNLOAD_ID_CHANNEL    50
//#define DOWNLOAD_ID_CHANNEL    60



//typedef enum _DevType{
//    E_DEV_TYPE_ELEC_VALVE = 0x01,
//    E_DEV_TYPE_IC_HP_LOCKING_VALVE,
//}DevType;
//
//typedef enum _eValveCtrl{
//    E_VALVE_MODE_OPEN  = 0x55,
//    E_VALVE_MODE_CLOSE = 0x99,
//    E_VALVE_MODE_AUTO  = 0x59,
//}eValveCtrl;
//
//typedef enum _ValveState{
//    E_VALVE_STATE_OPENED = 0x00,
//    E_VALVE_STATE_CLOSED = 0x01,
//    E_VALVE_STATE_ABNORMAL = 0x03,
//}ValveState;
//
//typedef enum _HPState{
//    E_HP_IN = 0,
//    E_HP_OUT,
//}HPState;
//
//typedef struct _RechargeInfoHP{
//    u16     recharge_sn;
//    u8      hp_st[4];
//    u8      hp_et[4];
//}RechargeInfoHP;
//
//typedef union _RechargeInfo{
//    RechargeInfoHP  hp_info;
//}RechargeInfo;

#define LENGTH_ADDR 8   //add�ĳ���

// ��ʾ����λ
typedef enum _DISP_CTL_BIT{
    DISP_CTL_HEAT_TIME_DAY = 0x01,
    DISP_CTL_HEAT_TIME_TOTAL = 0x02,
    DISP_CTL_HEAT_QUANTITY_DAY = 0x04,
    DISP_CTL_HEAT_QUANTITY_TOTAL = 0x08,
    DISP_CTL_BALANCE = 0x10,
    DISP_CTL_FAULT = 0x20,
    DISP_CTL_ROOM_NAME = 0x40,
    DISP_CTL_OWE = 0x80,
}DISP_CTL_BIT;

// ϵͳ��������Ҫ�洢��EEPROM��
typedef struct _SysParams{
    //ǩ��
    u8      factory_flag;		/*!< \brief ������ʶ */                   // 0
    u8      padding1;                                                             // 1
    u16     Device_GN;			//��Ʒ���		2�ֽ�             // 2
    u32	    Device_SN;			//��Ʒ���к�	4�ֽ�                     // 4
    u8	    soft_persion;		//����汾		1�ֽ�             // 8
    u8	    hardware_persion;	        //Ӳ���汾		1�ֽ�             // 9
    u8	    limte_te_flag;		//�����¶����ñ�־                        // 10
    u8	    limte_te_value;		//�����¶�����ֵ                          // 11
    u8	    workflg;			//�Ƿ��ڹ�ů��                            // 12
    u8	    sys_set_temp_flg;		//ϵͳ�����¶���Ч��־                    // 13
    u16     temp_set;                   /*!< \brief �¶����� */                   // 14
    u32     heating_quantity;		/*!< \brief �ۼ�����  */                  // 16
    u32     heating_time;		/*!< \brief ����ʱ�� ��λ��h */           // 20
    u32	    com_ok;			//���ͨ�ųɹ�����                        // 24
    u32	    com_total;		        //���ͨ���ܼƴ���                        // 28

//    u8      factory_flag;			/*!< \brief ������ʶ */
//    u8      padding1;
    u8      addr[LENGTH_ADDR];                  /*!< \brief �豸��ַ */           // 32
    u8      heating_period_st[2];		/*!< \brief ��ů�ڿ�ʼʱ�� MMDD */// 40
    u8      heating_period_et[2];		/*!< \brief ��ů�ڽ���ʱ�� MMDD */// 42
//    u8      padding3;
    u8      temp_room_uplimits;		        /*!< \brief �����趨���� ��λ���� */// 44
//    u8      padding4;
    u8      temp_room_lowlimits;	        /*!< \brief �����趨���� ��λ���� */// 45
//    u8      padding5;
    u8      rf_fre;                             /*!< \brief RF����Ƶ�� */           // 46
//    u8      padding6;
    u8      rf_channel;                         /*!< \brief RFͨ���� */            // 47
//    u8      padding7;
    u8      rf_power;                           /*!< \brief RF���� */             // 48
//    u8      padding8;
    u8      disp_ctl;                           /*!< \brief ��ʾ����λ */            // 49



    //��ʱ�ϴ�
////    u16     temp_set;                           /*!< \brief �¶����� */  // ***
    u8      room_name[6];                       /*!< \brief ��������  */            // 50
//    u16     cycle_sample;			/*!< \brief �������� ��λ��Min */
//    u16     sn_recharge;		        /*!< \brief ��ֵ���к� */
////    u32     heating_quantity;		        /*!< \brief �ۼ�����  */            // ***
//    u8	    heating_quantity_unit;	        /*!< \brief �ۼ�������λ ��λ�����188Э�� */
//    u8	    balance_unit;		        /*!< \brief ����������λ �����188Э�� */
//    u8      balance_alarm;			/*!< \brief ����ֵ ��λ��KWH */
//    long    balance;			        /*!< \brief ������� ��λ��0.01,����Ϊ��ֵ */
////    u32     heating_time;		        /*!< \brief ����ʱ�� ��λ��h */                // ***
//    u32     heating_cost_total;		        /*!< \brief ���ۼƷ�̯�ȷ� ��λ��0.01Ԫ */
//    u32     heating_time_day;		        /*!< \brief ���ۼƿ���ʱ�� ��λ��h */
//    u32     heating_cost_day;		        /*!< \brief ���ۼƷ�̯�ȷ� ��λ��0.01Ԫ */
//    u32     heating_quantity_day;		/*!< \brief ���ۼƷ�̯���� */
//    u8	    heating_quantity_day_unit;	        /*!< \brief ���ۼƷ�̯������λ ��λ�����188Э�� */

    // ��Դ��
//    u32		com_ok;			    //���ͨ�ųɹ�����
//    u32		com_total;		    //���ͨ���ܼƴ���
    // ͷ����

//    u32		Device_SN;			//��Ʒ���к�	4�ֽ�
//    u16		Device_DESN;			//�����ֽ�		1�ֽ�
//    u16		Device_GN;			//��Ʒ���		2�ֽ�
//    u8		soft_persion;			//����汾		1�ֽ�
//    u8		hardware_persion;	        //Ӳ���汾		1�ֽ�

//    u8		workflg;			//�Ƿ��ڹ�ů��
//    u8		sys_set_temp_flg;		//ϵͳ�����¶���Ч��־
//    u8		limte_te_flag;		//�����¶����ñ�־
//    u8		limte_te_value;		//�����¶�����ֵ

}SysParams;

// ���в��������������ڴ���
typedef struct _RunParams{
    u8      adc_keytrigger;                     /*!< \brief ��������adc���ٲ�����־ */
    u8      ds18b20_keytrigger;                 /*!< \brief ��������ds18b20���ٲ�����־ */
    u8      menu_id;                            /*!< \brief �˵���� */
    u8      view_idx;                           /*!< \brief ��ѯ��� */
    u8      date[7];                            /*!< \brief ���� */
    //����
    s16     temp;                               /*!< \brief �¶� */                       // ***
    s16     temp_last;                           /*!< \brief ��һ�ε��¶� */
    u8      ant_flash;			        /*!< \brief ͨѶʧ��ʱ��������˸��ʶ */
    int     batt_lvl;                           /*!< \brief ��ؼ��� */
    u8      low_power;                           /*!< \brief �͵��� */
    u8      ant_sts;                            /*!< \brief ����״̬:0-���źţ�1-���źţ�2-���źţ�������... */
    u16     st;                                 /*!< \brief ״̬ST �����ж��Ƿ���ϡ����桢���ſ���״̬ */

    u8      valve_state;                        /*!< \brief ���ŵ�״̬ */            // ***
    u8      arrears_state;                      /*!< \brief Ƿ��״̬ */             // ***
    //Э��
    u8      sts_login;                          /*!< \brief ��½״̬ */
    u16     temp_return;                        /*!< \brief �趨�¶ȵ����в��� */
    u8      set_id;                             /*!< \brief �趨id */
    u8      key_long;                           /* �������´˱�־Ϊ1���ͷ�Ϊ0 */

    // ��Դ��
    s16	    ave_temp_100;			//ƽ���¶ȣ�����100��
    u8	    face_state;				//��������״̬
    u8	    actionflag;			        //������־;0X00 ��Ч  0X55  ����  0XAA�ط�
    u8	    valve_position;	                //���ط�����λ��
    u8	    valve_lockstate;                    //���Ŷ�ת״̬

    u16		year;				//��
    u8		month;			//��
    u8		day;				//��
    u8		hour;				//ʱ
    u8		minute;			//��
    u8		second;			//��
    u8		week;			//��
    u8		batt_collect_flag;			//��
}RunParams;


// �ź�״̬
typedef enum _AntSts{
    ANT_NO_SIGNAL = 0,
    ANT_CONNECTRED,
    ANT_CONNECTING,
}AntSts;

typedef enum
{
    State_OK = (u8)0x00,
    State_Error= (u8)0xAA
} State_TypeDef;

typedef struct
{
    u8   	Second;
    u8   	Minute;
    u8  	Hour;
    u8   	Week;
    u8   	Day;
    u8  	Month;
    u16  	Year;
    u16  	Msec;
}RealClock_Str;

typedef enum
{
    Force_NOR = (u8)0X00,		//��ǿ��״̬    (û��Ƿ��)
    Force_Close	= (u8)0XAA,		//ǿ�ƹط�     	(Ƿ��)
    Force_Open = (u8)0X55,		//ǿ�ƿ���
    Valve_NOR = (u8)0X00,		//�����޶�������
    Valve_Open = (u8)0X0A,		//����״̬
    Valve_Middle = (u8)0X55,		//�м�״̬
    Valve_Execute = (u8)0XAA,		//����ִ��
    Valve_Close	= (u8)0XA0,		//�ط�״̬
    Valve_Lock = (u8)0XEE,		//��ת״̬
    Valve_Break	= (u8)0XFF,		//����״̬

}Valve_Type;

extern SysParams g_sys_params;   //g_sys_params�ṹ�����
extern RunParams g_run_params;

void eeprom_write_sys(u8 offset, void* sys_params, u8 length);

#endif