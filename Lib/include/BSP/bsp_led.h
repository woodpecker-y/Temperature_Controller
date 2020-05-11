
#ifndef _BSP_LED_H
#define _BSP_LED_H

#ifdef HAVE_LED

/*! \brief
*      Load LED Port Configure
* \param handler[IN]        - board configure handler
* \param cnt[IN]            - LED Count
* \note
*      ex.
*           const PortTypeDef led_handler[] = {
*               {PORTA, PIN0},      // LED 1
*               {PORTA, PIN1},      // LED 2
*               {PORTA, PIN2},      // LED 3
*            };
*/
void BSP_LED_LoadConfig(const PortTypeDef *handler, u8 cnt);

/*! \brief
*      Load LED Port Init
*/
void BSP_LED_Init(void);

/*! \brief
*      set led on
* \param led_idx[IN]        - led index of led configure array
*/
void BSP_LED_On(u8 led_idx);

/*! \brief
*      set led off
* \param led_idx[IN]        - led index of led configure array
*/
void BSP_LED_Off(u8 led_idx);

#endif

#endif