/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
*
* \brief
*    board support package-- stm15x board gpio interface layer
* \author
*    zhou_sm(at)blackants.com.cn
* \date
*    2014-07-16
* \version
*    v1.0
* Copyright (c) 2010-2014, Blackants Energy Saving Technology co., LTD All rights reserved.
******************************************************************************/
#ifndef _BSP_GPIO_H
#define _BSP_GPIO_H

#include "remap.h"

/*! \brief GPIO Port Redefined */
typedef enum _Port{
    PORTA = 0,
    PORTB = 1,
    PORTC = 2,
    PORTD = 3,
    PORTE = 4,
    PORTF = 5,
    PORTG = 6,
}Port;

/*! \brief GPIO Pin Redefined */
typedef enum _Pin{
    PIN0 = 0,
    PIN1 = 1,
    PIN2 = 2,
    PIN3 = 3,
    PIN4 = 4,
    PIN5 = 5,
    PIN6 = 6,
    PIN7 = 7,
}Pin;

/*! \brief Port definition */
typedef struct _PortTypeDef{
    Port port;
    Pin  pin;
}PortTypeDef;

/*! \brief
*       gpio port remapping
* \param port[IN]           - gpio port index.
* \return
*       gpio port pointer
*/
GPIO_TypeDef* BSP_GPIO_Port_Remap(Port port);

/*! \brief
*       gpio pin remapping
* \param pin[IN]            - gpio pin index.
* \return
*       stm8l15x chip gpio pin index
*/
GPIO_Pin_TypeDef BSP_GPIO_Pin_Remap(Pin pin);

/*! \brief
*       Get EXTI Num by Pin Number
* \param pin[IN]        - Pin Number of Port
* \return EXTI Number
*/
EXTI_Pin_TypeDef BSP_GPIO_GetEXTIPinNum(Pin pin);

/*! \brief
*       gpio pin initilization
* \param port[IN]           - gpio port index.
* \param pin[IN]            - gpio pin index.
* \param mode[IN]           - gpio pin init mode.
*/
u8 BSP_GPIO_Init(Port port, Pin pin, u8 mode);

/*! \brief
*       set gpio pin to 1
* \param port[IN]           - gpio port index.
* \param pin[IN]            - gpio pin index.
*/
u8 BSP_GPIO_SetHigh(Port port, Pin pin);

/*! \brief
*       set gpio pin to 0
* \param port[IN]           - gpio port index.
* \param pin[IN]            - gpio pin index.
*/
u8 BSP_GPIO_SetLow(Port port, Pin pin);

/*! \brief
*       read gpio pin state
* \param port[IN]           - gpio port index.
* \param pin[IN]            - gpio pin index.
* \return
*       pin state:0-low level;1-high level
*/
u8  BSP_GPIO_ReadState(Port port, Pin pin);

#endif