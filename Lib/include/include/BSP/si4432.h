#ifndef _SI4432_H
#define _SI4432_H

#ifdef HAVE_RF

#include "stm8l15x.h"
#include "bsp_gpio.h"

///*! \brief RF�˿� */
//#define RF_PORT_PWR         GPIOB           /*!< \brief ��Դ */
//#define RF_PORT_GPIO2       GPIOA           /*!< \brief GPIO2 */
//#define RF_PORT_SPI         GPIOB           /*!< \brief SPI */
//#define RF_PORT_NIRQ        GPIOA           /*!< \brief NIRQ */
//#define RF_PORT_SDN         GPIOA           /*!< \brief SDN */
//
///*! \brief RF�ܽ� */
//#define RF_PIN_PWR          GPIO_Pin_0      /*!< \brief ��Դ */
//#define RF_PIN_GPIO2        GPIO_Pin_6      /*!< \brief GPIO2 */
//#define RF_PIN_SPI_MISO     GPIO_Pin_7      /*!< \brief SPI */
//#define RF_PIN_SPI_MOSI     GPIO_Pin_6      /*!< \brief SPI */
//#define RF_PIN_SPI_SCK      GPIO_Pin_5      /*!< \brief SPI */
//#define RF_PIN_SPI_NSS      GPIO_Pin_4      /*!< \brief SPI */
//#define RF_PIN_NIRQ         GPIO_Pin_5      /*!< \brief NIRQ */
//#define RF_PIN_SDN          GPIO_Pin_4      /*!< \brief SDN */

//#define EXTI_PIN_NIRQ       EXTI_Pin_5      // �жϹܽ�

//#define Si4432_MISO_READ		(GPIO_ReadInputDataBit(RF_PORT_SPI, RF_PIN_SPI_MISO))
//#define Si4432_MOSI_H			(GPIO_SetBits(RF_PORT_SPI, RF_PIN_SPI_MOSI))    
//#define Si4432_MOSI_L			(GPIO_ResetBits(RF_PORT_SPI, RF_PIN_SPI_MOSI))    
//#define Si4432_SCK_H			(GPIO_SetBits(RF_PORT_SPI, RF_PIN_SPI_SCK))    
//#define Si4432_SCK_L			(GPIO_ResetBits(RF_PORT_SPI, RF_PIN_SPI_SCK))    
//#define Si4432_CS_H				(GPIO_SetBits(RF_PORT_SPI, RF_PIN_SPI_NSS))    
//#define Si4432_CS_L				(GPIO_ResetBits(RF_PORT_SPI, RF_PIN_SPI_NSS))    
//
//#define Si4432_SDN_H			(GPIO_SetBits(RF_PORT_SDN, RF_PIN_SDN))    
//#define Si4432_SDN_L			(GPIO_ResetBits(RF_PORT_SDN, RF_PIN_SDN)) 
//#define RF_PWR_H				(GPIO_SetBits(RF_PORT_PWR, RF_PIN_PWR))    
//#define RF_PWR_L				(GPIO_ResetBits(RF_PORT_PWR, RF_PIN_PWR)) 
//#define RF_NIRQ_Read()			(GPIO_ReadInputDataBit(RF_PORT_NIRQ, RF_PIN_NIRQ))

#define RF_FRE_STEP         5       // ͨ��Ƶ��50kHZ

// �����������
typedef enum _RF_TXPOW{
    TXPOW__1dBm	= 0x00,
    TXPOW_02dBm	= 0x01,
    TXPOW_05dBm	= 0x02,
    TXPOW_08dBm	= 0x03,
    TXPOW_11dBm	= 0x04,
    TXPOW_14dBm = 0x05,
    TXPOW_17dBm = 0x06,
    TXPOW_20dBm = 0x07,
}RF_TXPOW;

// Ƶ������
typedef enum _RF_FRE{
    RF_FRE_410_5M = 0,
    RF_FRE_420_5M = 1,     
    RF_FRE_430_5M = 2,     
    RF_FRE_440_5M = 3,     
    RF_FRE_470_5M = 4,     
    RF_FRE_480_5M = 5,     
    RF_FRE_490_5M = 6,     
    RF_FRE_500_5M = 7,     
    RF_FRE_510_5M = 8,   
    RF_FRE_520_5M = 9,         
}RF_FRE;

//����������
typedef enum _RF_DATA_RATE{
    RF_DATA_RATE_1200,  //1.2kbps
    RF_DATA_RATE_2400,  //2.4kbps
    RF_DATA_RATE_4800,  //4.8kbps
    RF_DATA_RATE_9600,  //9.6kbps
    RF_DATA_RATE_19200, //19.2kbps
    RF_DATA_RATE_38400, //38.4kbps
    RF_DATA_RATE_76800, //76.8kbps
    RF_DATA_RATE_128000,  //128kbps
    RF_DATA_RATE_256000   //256kbps
}RF_DATA_RATE;

typedef enum _RFSts{
    E_RF_OK = 0,
    E_RF_ERR_INIT,
    E_RF_ERR_NO_DATA,
}RFSts;

#define RF_STS_IDLE		0
#define RF_STS_SEND		1
#define RF_STS_RECV		2

typedef enum _RFMode{
    E_RF_MODE_IDLE = 0,
    E_RF_MODE_SEND,
    E_RF_MODE_RECV,
}RFMode;

/*! \brief UART Recv FLags Definition */
typedef enum _RFRxFlags{
    E_RF_RX_FLAG_IDLE = 0,
    E_RF_RX_FLAG_RECVING = 1,
    E_RF_RX_FLAG_RECV_COMPLETE = 2,
    E_RF_RX_FLAG_PROCESSING = 3,
}RFRxFlags;

typedef struct _RFConfig{
    PortTypeDef pwr;            /*!< \brief rfid power control pin */
    PortTypeDef mosi;           /*!< \brief rfid mosi pin */
    PortTypeDef miso;           /*!< \brief rfid miso pin */ 
    PortTypeDef sck;            /*!< \brief rfid serial clock */        
    PortTypeDef nss;            /*!< \brief rfid chip select */
    PortTypeDef sdn;            /*!< \brief rfid sdn pin */
    PortTypeDef nirq;           /*!< \brief rfid nirq pin */
    u8*         rcv_ptr;        /*!< \brief rfid recv data pointer */
    u16         max_rcv_size;   /*!< \brief rfid max recv data buffer size */ 
}RFConfig;

/*! \brief 
*      RF Configuartion Init
* 
* \param rf_cfg[IN]           - rf config pointer.
* \note  
* 
*/
void BSP_RF_LoadConfig(RFConfig *rf_cfg);
/*! \brief ���߳�ʼ */
u8   BSP_RF_Init(RF_FRE rf_fre, RF_DATA_RATE date_rate, RF_TXPOW rf_pow, u8 ch);
/*! \brief ���߹ر� */
void BSP_RF_Close(void);
/*! \brief �������³�ʼ�� */
u8 BSP_RF_ReInit(RF_FRE rf_fre, RF_DATA_RATE date_rate, RF_TXPOW rf_pow, u8 ch);
/*! \brief �ر�IO�˿� */
void BSP_RF_PortClose(void);
/*! \brief ���߹ر� */
void BSP_RF_PowerOn(void);
/*! \brief ���߹ر� */
void BSP_RF_PowerOff(void);
/*! \brief ���߷������� */
void BSP_RF_SendData(u8 *dat, u8  len);
/*! \brief ���߽��ճ�ʼ�� */
void BSP_RF_RecvInit(void);
/*! \brief ���߽������� */
u8   BSP_RF_RecvData(u8 **dat, u8 *len);
/*! \brief �����жϷ��� */
void BSP_RF_ISR(void);
/*! \brief ����������� */
void BSP_RF_SetTxpow(RF_TXPOW txpow);
/*! \brief ����Ƶ�� */
void BSP_RF_SetFre(RF_FRE fre);
/*! \brief ����ͨ�� */    
void BSP_RF_SetFreChannel(u8 ch);
/*! \brief ���ò����� */
void BSP_RF_SetDataRate(RF_DATA_RATE datarate);
/*! \brief ��������Ϊ����ģʽ */
void BSP_RF_SetRxMode(void);
/*! \brief ��������Ϊ����ģʽ */
void BSP_RF_SetTxMode(void);
/*! \brief ��������Ϊ����ģʽ */
void BSP_RF_SetIdleMode(void);
/*! \brief ����ź�ǿ�� */
u8   BSP_RF_GetRssi(void);
/*! \brief ���ܻ��渴λ */
void BSP_RF_ResetRxFIFO(void);
/*! \brief ���ͻ��渴λ */
void BSP_RF_ResetTxFIFO(void);
/*! \brief ��ȡ�豸״̬ */
u8   BSP_RF_GetDevStatus(void);
///*! \brief ��ȡ�����ж�״̬1 */
//u8   BSP_RF_GetITStatus1(void);
///*! \brief ��ȡ�����ж�״̬2 */
//u8   BSP_RF_GetITStatus2(void);
u8   BSP_RF_GetRecvFlag(void);
/*! \brief ��ȡ����״̬�����У����ͣ����� */
u8   BSP_RF_GetState(void);

#endif

#endif