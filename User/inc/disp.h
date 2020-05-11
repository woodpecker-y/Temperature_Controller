#ifndef _DISP_H
#define _DISP_H

#include "sysparams.h"
#include "bsp.h"
#include "lcd.h"

#define DISPLAY_ON          1       /*!< \brief ��ʾ�� */
#define DISPLAY_OFF         0       /*!< \brief ��ʾ�� */


/*! \brief ��λ���� */
typedef enum _LcdSeg{
    /* COM1 */
    SEG_BH = 1,     //���
    SEG_L = 2,      //����
    SEG_KL = 4,     //����
    SEG_T1 = 5,     //�����źŵ�һ��СԲ�㣩
    SEG_6D = 6,     //�����6D
    SEG_S6 = 7,     //ʣ������
    SEG_5D = 8,     //�����5D
    SEG_S5 = 9,     //�ۼ�����
    SEG_4D = 10,    //�����4D
    SEG_S4 = 11,    //����ʱ��
    SEG_3D = 12,    //�����3D
    SEG_S3 = 13,    //���S3
    SEG_2D = 14,    //�����2D
    SEG_S2 = 15,    //���S2
    SEG_1D = 16,    //�����1D
    SEG_S1 = 17,    //��λ��ʱ
    /* COM2 */
    SEG_QF = 28,    //Ƿ��
    SEG_GJ = 29,    //��λ��GJ
    SEG_SJ = 30,    //ʱ��
    SEG_B4 = 31,    //��ص���������
    SEG_XH = 32,    //�״��ʶ
    SEG_T2 = 33,    //�����źŵڶ���
    SEG_6E = 34,    //�����6E
    SEG_6C = 35,    //�����6C
    SEG_5E = 36,    //�����5E
    SEG_5C = 37,    //�����5C
    SEG_4E = 38,    //�����4E
    SEG_4C = 39,    //�����4C
    SEG_3E = 40,    //�����3E
    SEG_3C = 41,    //�����3C
    SEG_2E = 42,    //�����2E
    SEG_2C = 43,    //�����2C
    SEG_1E = 44,    //�����1E
    SEG_1C = 45,    //�����1C
    /* COM3 */
    SEG_FJ = 56,    //�����
    SEG_KWH = 57,   //��λ;KWh
    SEG_GZ = 58,    //����
    SEG_B3 = 59,    //��ص����ڶ���
    SEG_FM = 60,    //���ű�ʶ
    SEG_T3 = 61,    //�����źŵ�����
    SEG_6F = 62,    //�����6F
    SEG_6G = 63,    //�����6G
    SEG_5F = 64,    //�����5F
    SEG_5G = 65,    //�����5G
    SEG_4F = 66,    //�����4F
    SEG_4G = 67,    //�����4G
    SEG_3F = 68,    //�����3F
    SEG_3G = 69,    //�����3G
    SEG_2F = 70,    //�����2F
    SEG_2G = 71,    //�����2G
    SEG_1F = 72,    //�����1F
    SEG_1G = 73,    //�����1G
    /* COM4 */
    SEG_SD = 84,    //�趨
    SEG_DF = 85,    //��λ����
    SEG_SW = 86,    //����
    SEG_B2 = 87,    //��ص�����һ��
    SEG_B1 = 88,    //��ص����߿�
    SEG_T4 = 89,    //�����źŵ��ĸ�
    SEG_6A = 90,    //�����6A
    SEG_6B = 91,    //�����6B 
    SEG_5A = 92,    //�����5A
    SEG_5B = 93,    //�����5B 
    SEG_4A = 94,    //�����4A
    SEG_4B = 95,    //�����4B 
    SEG_3A = 96,    //�����3A
    SEG_3B = 97,    //�����3B 
    SEG_2A = 98,    //�����2A
    SEG_2B = 99,    //�����2B 
    SEG_1A = 100,   //�����1A
    SEG_1B = 101,   //�����1B 
}LcdSeg;

/*! \brief digit display position */
typedef enum _DigitPos{
    DIGIT6 = 0, //�����6����
    DIGIT5,     //�����5����
    DIGIT4,     //�����4����
    DIGIT3,     //�����3����
    DIGIT2,     //�����2����
    DIGIT1,     //�����1����
}DigitPos;

/*! \brief ������ö�� */
typedef enum _BattLel{
    BATT_LVL_0 = 0, //0�����
    BATT_LVL_1,     //1�����
    BATT_LVL_2,     //2�����
    BATT_LVL_3,     //3�����
}BattLel;

/*! \brief ���ſ���״̬ */
typedef enum _Valve_Sts{
    VALVE_STS_CLOSE = 0x00, //���Źر�״̬
    VALVE_STS_OPEN  = 0x01, //���Ŵ�״̬
}_Valve_Sts;


/*! \brief
*       display a digit ��ʾһ������
* \param pos[IN]    - segment digit display index
*       DIGIT1      - the left digist position
*       DIGIT2      - the second digit position
*       DIGIT3      - the third digit position
*       DIGIT4      - the fourth digit position
*       DIGIT5      - the fifth digit position
* \param val[IN]    - display value index:0~9,A~F,S,T,-,P,r,' '
* \param sts[IN]    - display state
*       DISPLAY_ON  - display on
*       DISPLAY_OFF - display off
* \note
*       1)stm8l152?????????????????????????????????????????????????????????????
*               SEG1    SEG2    SEG3    SEG4
*       COM1    *       *       *       *
*       COM2    -       -       -       -
*       COM3    -       -       -       -
*       COM4    -       -       -       -
*           *       ?????????????
*           -       ?????????????
*       stm8l152??��??????????COM1????????COM2\COM3\COM4??????????????????LCD????��
*   ????????????????��????????????????????��??????????SEG??????????STM8L152?????COM??????????
*       2)?????????????????????��?????????bit��???????????????????��????
*   ?????????????????????????????��????????��???��????????
*/
void disp_digit(u8 pos, u8 val, u8 sts);

/*! \brief
*       display a digit
* \param pos[IN]    - segment char display index
*       DIGIT1      - the left digist position
*       DIGIT2      - the second digit position
*       DIGIT3      - the third digit position
*       DIGIT4      - the fourth digit position
*       DIGIT5      - the fifth digit position
* \param ch[IN]     - display character
*/
void disp_char(u8 start, u8 ch);
/*! \brief ��ʾ�ַ��� */
void disp_str(u8 start, u8 end, const char *str);
/*! \brief ��ʾ�������� */
void disp_number(u8 start, u8 end, u32 val);
/*! \brief Һ����ʼ�� */
void disp_init(void);
/*! \brief Һ���ر� */
void disp_close(void);
/*! \brief ��ʾҺ�� */
void disp_update(void);
/*! \brief Һ��ȫ�� */
void disp_all(void);
/*! \brief Һ������ */
void disp_clr(void);
/*! \brief ��ʾ�ָ��� */
void disp_line(u8 disp_sts);
/*! \brief ��ʾ��ص��� */
void disp_batt(u8 disp_sts, u8 lv);
/*! \brief ��ʾ�����ź� */
void disp_ant(u8 disp_sts, u8 sts);
/*! \brief ��ʾ�źţ��״��źţ� */
void disp_rf_state(u8 disp_sts);
/*! \brief ��ʾ���� */
void disp_warning(u8 disp_sts);
/*! \brief ��ʾǷ�� */
void disp_owed(u8 disp_sts);
/*! \brief ��ʾ����ʱ�� */
void disp_heat_time(u32 heat_time);
/*! \brief ��ʾϵͳʱ�������� */
void disp_sys_time_ymd(u8 year, u8 month, u8 day);
/*! \brief ��ʾϵͳʱ��ʱ���� */
void disp_sys_time_hms(u8 hour, u8 min, u8 second);
/*! \brief ��ʾ�����¶� */
void disp_temp_room(s16 temp_room);
/*! \brief ��ʾ�趨�¶� */
void disp_temp_set(u16 temp_set);
/*! \brief ��ʾ����״̬ */
void disp_valve_sts(u8 sts);
/*! \brief ��ʾ����� */
void disp_room_id(const char *id, u8 len);
/*! \brief ��ʾID����ע��ID����һ����ʾ��ȫ����Ҫ�������Σ��ֱ���ʾ��4λ�͵�6λ�� */
void disp_id(const unsigned char *id, u8 len);
/*! \brief ��ʾ���� */
void disp_fault(u16 code);
/*! \brief ��ʾ�ۼ����� */
void disp_heat_quantity(u32 heat_quantity, u8 heat_quantity_uint);
/*! \brief ��ʾʣ������ */
void disp_surplus_heat(long balance, u8 unit);
/*! \brief �������Ҫ����ʾ */
void disp_clr_region(void);
/*! \brief ��ʾСʱ�ͷ��� */
void disp_sys_time(u8 hour, u8 min);

void disp_set_id(void);

#endif