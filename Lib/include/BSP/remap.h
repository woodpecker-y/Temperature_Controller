
#ifndef _REMAP_H
#define _REMAP_H

#ifdef HAVE_STM8S

// ���������ض���
#define GPIO_SetBits			GPIO_WriteHigh
#define GPIO_ResetBits		        GPIO_WriteLow
#define GPIO_ReadInputDataBit	        GPIO_ReadInputPin

// ���������ض���
#define EXTI_Pin_TypeDef                
#endif

#endif