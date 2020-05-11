#include "bsp.h"
#include "bsp_lcd.h"
#include "bsp_flash_ext.h"
//////////////////////////////��Ʒ����////////////////////////////////////
const char *product_model = "FY";
const char *hw_ver = "1.0.1";
const char *sw_ver = "1.0.0.190819";
//const char *sw_ver = "1.1.0";

//////////////////////////////��������////////////////////////////////////
uint8_t com_global_buffer[512] = {0};

///*! \brief Com Configure Definition */
//typedef struct _ComConfig{
//    COM          com;           /*!< \brief COM Object */
//    PortTypeDef  tx;            /*!< \brief COM Tx Pin */
//    PortTypeDef  rx;            /*!< \brief COM Rx Pin */
//    PortTypeDef  ctrl;          /*!< \brief COM Ctrl Pin, Only used with RS485 */
//    uint8_t*	 rcv_ptr;         /*!< \brief COM recv buffer poniter */
//    uint16_t	 max_rcv_size;    /*!< \brief COM recv buffer max size */
//}COMConfig;   //������Ľ��պͷ����Ƿ��ŵ�
COMConfig com_cfg[1] = {
    {COM1, {PORTA, PIN2}, {PORTA, PIN3}, {(Port)0, (Pin)0}, com_global_buffer+0, 256},
    //{COM3, {PORTG, PIN1}, {PORTG, PIN0}, {(Port)0, (Pin)0}, com_global_buffer+256, 256}
};

//////////////////// LCD���� //////////////////////////////
LCDPortConfig lcd_config = {
    E_PWR_EXT,
    {0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00}//���ݽӿڱ��ҳ�
};
//////////////////// ADC���� //////////////////////////////
//typedef struct _ADCConfig{
//    ADC_TypeDef*    adc;
//    PortTypeDef     ctrl;
//    PortTypeDef     ai;
//    u8              pwr_le;
//}ADCConfig;
//
//typedef struct _ADCConfig{
//    ADC_TypeDef*    adc;
//    PortTypeDef     ctrl;
//    PortTypeDef     ai;
//    u16             ch;
//    u8              pwr_le;
//}ADCConfig;
//ADCConfig adc_cfg[2] = {
//    {ADC1,{PORTC, PIN0},{PORTC, PIN7}, ADC_Channel_3, E_LE_LOW}, 
//    {ADC1,{PORTC, PIN0},{PORTF, PIN0}, ADC_Channel_24, E_LE_LOW}
//};
ADCConfig1 adc_cfg = {ADC1, {PORTC, PIN1}, {PORTF, PIN0}, E_LE_LOW};

//////////////////////////////470MHz RF////////////////////////////////////
uint8_t rf_global_buffer[80] = {0};

//typedef struct _RFConfig{
//    PortTypeDef pwr;            /*!< \brief rfid power control pin */
//    PortTypeDef mosi; (master output slave input)          /*!< \brief rfid mosi pin */
//    PortTypeDef miso;           /*!< \brief rfid miso pin */ 
//    PortTypeDef sck;            /*!< \brief rfid serial clock */        
//    PortTypeDef nss;            /*!< \brief rfid chip select */
//    PortTypeDef sdn;            /*!< \brief rfid sdn pin */
//    PortTypeDef nirq;  (????????)         /*!< \brief rfid nirq pin */
//    u8*         rcv_ptr;        /*!< \brief rfid recv data pointer */
//    u16         max_rcv_size;   /*!< \brief rfid max recv data buffer size */ 
//}RFConfig;
RFConfig rf_cfg = {
//    {(Port)0, (Pin)0},{PORTG, PIN6},{PORTG, PIN7},{PORTG, PIN5},{PORTC, PIN6},{PORTF, PIN4},{PORTC, PIN5},rf_global_buffer+0, 80      // �ϰ���
//      {PORTC, PIN0},{PORTG, PIN6},{PORTG, PIN7},{PORTG, PIN5},{PORTG, PIN4},{PORTA, PIN0},{PORTF, PIN4},rf_global_buffer+0, 80          // �°���
      {PORTC, PIN0},{PORTG, PIN6},{PORTG, PIN7},{PORTG, PIN5},{PORTG, PIN4},{PORTC, PIN1},{PORTF, PIN4},rf_global_buffer+0, 80          // �°���V0.1
};
////////////////////// KEY���� //////////////////////////////
PortTypeDef key_config[3] = {
//    {PORTC, PIN2},
//    {PORTE, PIN6},
//    {PORTE, PIN7},   
    {PORTF, PIN7},
    {PORTF, PIN6},
    {PORTF, PIN5}, 
};

//SHT2xConfig sht20_cfg = {
//    {PORTF, PIN4},
//    {PORTF, PIN1},
//};

/*! \brief alarm confirgure Definition */
/*! \note 
*     �������õ�������������Ч������������������Ϊ0ʱ��������Ч��
RTC_AlarmMask_None
RTC_AlarmMask_Seconds
RTC_AlarmMask_Minutes
RTC_AlarmMask_Hours
RTC_AlarmMask_DateWeekDay
RTC_AlarmMask_All
*/
//AlarmConfig alarm_cfg = {
//    RTC_AlarmDateWeekDaySel_Date,       /*!< \brief ���ڻ�����ѡ��ֵ��Ч */
//    1,                                  /*!< \brief ���ڻ�����ֵ��  ֵ��Ч */ 
//    0,                                  /*!< \brief ������Ч��Сʱ��ֵ��Ч */  
//    0,                                  /*!< \brief ������Ч�ķ��� */   
//    0,                                  /*!< \brief ������Ч������ */   
//    RTC_AlarmMask_DateWeekDay | RTC_AlarmMask_Hours
//};