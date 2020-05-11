
#ifndef _SYSCLK_H
#define _SYSCLK_H

/*! \brief
*       system clock initilization
* \note
*       default system clock is HSI, and its frequency is 8MHz.
*/
void sysclk_init(void);

/*! \brief
*       system clock initilization(HSI)
* \param div[IN]                - Frequency division coefficient
*           CLK_SYSCLKDiv_1     - 1 points frequency
*           CLK_SYSCLKDiv_2     - 2 points frequency
*           CLK_SYSCLKDiv_4     - 4 points frequency
*           CLK_SYSCLKDiv_8     - 8 points frequency
*           CLK_SYSCLKDiv_16    - 16 points frequency
*           CLK_SYSCLKDiv_64    - 64 points frequency
*           CLK_SYSCLKDiv_128   - 128 points frequency
*/
void sysclk_init_hsi(u8 div);

/*! \brief
*       system clock initilization(HSE)
* \param div[IN]                - Frequency division coefficient
*           CLK_SYSCLKDiv_1     - 1 points frequency
*           CLK_SYSCLKDiv_2     - 2 points frequency
*           CLK_SYSCLKDiv_4     - 4 points frequency
*           CLK_SYSCLKDiv_8     - 8 points frequency
*           CLK_SYSCLKDiv_16    - 16 points frequency
*           CLK_SYSCLKDiv_64    - 64 points frequency
*           CLK_SYSCLKDiv_128   - 128 points frequency
*/
void sysclk_init_hse(u8 div);

/*! \brief
*       system clock initilization(LSI)
* \param div[IN]                - Frequency division coefficient
*           CLK_SYSCLKDiv_1     - 1 points frequency
*           CLK_SYSCLKDiv_2     - 2 points frequency
*           CLK_SYSCLKDiv_4     - 4 points frequency
*           CLK_SYSCLKDiv_8     - 8 points frequency
*           CLK_SYSCLKDiv_16    - 16 points frequency
*           CLK_SYSCLKDiv_64    - 64 points frequency
*           CLK_SYSCLKDiv_128   - 128 points frequency
*/
void sysclk_init_lsi(u8 div);

#endif
