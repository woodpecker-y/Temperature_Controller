#include <stdio.h>
#include "adf.h"
#include "board.h"
#include "sysparams.h"
#include "verify.h"
#include "awu.h"
#include "motor.h"
#include "BSP_SysTimer.h"
#include "stm8l15x_tim1.h"
#include "flash_ext.h"
#include "disp.h"
#include "menu.h"
#include "task_report.h"
#include "task_key.h"
#include "task_config.h"
#include "task_adc.h"
#include "task_disp.h"
#include "task_disp.h"
#include "task_ds18b20.h"
#include "task_main.h"

#define TEST_WDG 0
#define TEST_COM 1
#define TEST_SOFT_TIMER 0
#define TEST_DELAY_MS 0
#define TEST_DELAY_US 0

void hardware_init(void)
{
//    int adc = 0;
//    int adc_ext = 0;
//    uint8_t test_data[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
//    uint8_t test_data[11] = "start-test";
//    u8 rv = 0;
//    u8 *rcv_dat = NULL;
//    u16 rcv_len = 0;
//    u8 rcv_rflen = 0;
//
//    u16 set_temp = 2800;

    //int rv;
    /* PORT��ʼ�� */
    GPIO_Init(GPIOA, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow );
    GPIO_Init(GPIOB, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow );
    GPIO_Init(GPIOC, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow );
    GPIO_Init(GPIOD, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow );
    GPIO_Init(GPIOE, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow );
    GPIO_Init(GPIOF, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow );
    GPIO_Init(GPIOG, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow );

    /* ----------------�ر�ds18b20---------------- */
    ds18b20_close();

    /* ���ô������� */
    //gpio_init(PORTA, PIN2, GPIO_Mode_Out_PP_High_Fast);//TX
    //gpio_init(PORTA, PIN3, GPIO_Mode_In_PU_No_IT);//RX

    /* ----------------system clock init---------------- */
    sysclk_init_hsi(CLK_SYSCLKDiv_2);   //����Ƶ

//    /* ----------------ʵʱʱ�ӳ�ʼ��,ʹ���ڲ���38MHz----------------  */
//    /* ��ʱʹ�ã�����ʹ���ⲿ��32.768KHz����ʱ�ӷ�ƵҪ���� */
//    STM8RTC_Initialiazation();

    /* ----------------debug,��ʱ�ر���Ϊû���ⲿ����---------------- */
    rtc_init();

    /* ----------------�Զ�����ʱ�ӳ�ʼ��---------------- */
    awu_init();
    awu_enable(CYCLE_AWU);

#if 1
    struct tm t;

    t.tm_year = 19;
    t.tm_mon  = 8;
    t.tm_mday = 19;
    t.tm_week = 1;
    t.tm_hour = 8;
    t.tm_min  = 0;
    t.tm_sec  = 0;

    rtc_write(t);   //��ʱ��д��ȥ
#endif

      /* ----------------������������ʱ��ͻ---------------- */
      /* com load configuration & init */
    com_load_config(com_cfg, sizeof(com_cfg)/sizeof(com_cfg[0]));
    com_init(COM1, 2400, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, (uint8_t)0x0C, ENABLE, 0);
//    com_init(COM3, 9600, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, USART_Mode_All, ENABLE, 0);
    com_recv_init(COM1);
    //com_recv_init(COM2);

    /* ----------------LCD��ʼ��---------------- */
    LCD_Config();
    LCD_Whole_Clear();   //���������Ļ��Ϣ

    /* ��ʾ����汾��0x56 */
    LCD_NUM_WriteChar(0x06, LCD_TEMP_D_POSITION, WRITE);    // LCD_TEMP_D_POSITION   �¶�ʮλ  ������ʾ�汾��
    LCD_NUM_WriteChar(0x00, LCD_TEMP_U_POSITION, WRITE);	// LCD_TEMP_U_POSITION   �¶ȸ�λ  ������ʾ�汾��

    delay_ms(2000);
    LCD_Whole_Clear();   //���������Ļ��Ϣ
//    LCD_Whole_Display();
//    delay_ms(10000);

    /* ���Ҹ��Ĳɼ��¶ȳ�����ԣ�δ�ɹ� */
//    while (1)
//    {
////    sample_temp();
//      DS18B20_GetTemp_Server();
//      delay_ms(2000);
//    }
    /* �ɼ��¶Ⱥ���Ļ��ʾ���� */
//    while(1)
//    {
//      /* ��ʾ�¶� */
//      DS18B20_GetTemp_Server();
//      /* ��ʾʱ�� */
////      rtc_read(&t);
////      printf("t.tm_year = %d\r\n", t.tm_year);
////      LCD_Date_Display(t.tm_year, t.tm_mon, t.tm_mday, t.tm_week, WRITE);	//	Display DATE
////      LCD_Time_Display( t.tm_hour, t.tm_min,WRITE);			//	Display  TIME
//
//      lcd_temp_data_disp(g_run_params.temp);
//      delay_ms(2000);
//      lcd_clr_region();
////      lcd_temp_data_disp();
//
//      delay_ms(2000);
//
//    }


      /* ��ʱû�õ� */
//    /* adc config & init */
//    BSP_ADC_LoadConfig1(adc_cfg, sizeof(adc_cfg)/sizeof(adc_cfg[0]));
//    adc_close(ADC_TEMP);
//    adc_close(ADC_BATT);
//    //    adc_init(ADC_TEMP);
//    //    adc_init(ADC_BATT);

    /* �ⲿ��adc���� */
//    BSP_ADC_LoadConfig1(adc_cfg, sizeof(adc_cfg)/sizeof(adc_cfg[0]));
//    adc_close1(ADC_BATT);
//    adc_power_on1(ADC_BATT);
//    adc_init1(ADC_BATT);
//    delay_ms(50);
//    while (1) {
//      adc_ext = adc_sample1(ADC_BATT);
//      printf("adc_ext = %u\r\n", adc_ext);
//      delay_ms(2000);
//    }

    /* �ڲ���adc���� */
    adc_close_vrefint1();
//    adc_init_vrefint1();
//    delay_ms(2000);
//    adc = adc_sample_vrefint1();
//    while (1) {
//      adc = adc_sample_vrefint1();
//        printf("adc = %d\r\n", adc);
//        delay_ms(2000);
//    }

    /* ----------------load key configure & init---------------- */
    key_load_config(key_config, sizeof(key_config)/sizeof(key_config[0]));
    key_init();

    /* ----------------rf������Ҫʹ�ò�����ʱʹ��---------------- */
    enableInterrupts();           //ʼ���ն˺���
    /* ʹ������һ��Ҫ���жϲ��Ҷ���Ҫ�����жϺ��� */
    /* ----------------rf config & init---------------- */
    rf_load_config(&rf_cfg);
    rf_close();
    rf_power_off();

      /* si4432���߽��в��� */
//    rf_power_on();
//    rv = rf_init(RF_FRE_470_5M, RF_DATA_RATE_1200, TXPOW_20dBm, 0);
//    if (rv != E_RF_OK)
//    {
//      delay_ms(1);
//    }
//
//    rf_rcv_init();
//
//    while(1)
//    {
//      /* ���� */
//      rv = rf_rcv_data(&rcv_dat, &rcv_rflen);
//      if(rv == 0)
//      {
////        lcd_temp_data_disp(g_run_params.temp);
////        MYLOG_DEBUG_HEXDUMP("RF Config Recv:", rcv_dat, rcv_len);
////        disp_temp_room(330);
////        disp_update();
//          printf("rcv_dat = %s\r\n", rcv_dat);
//          rv = memcmp(rcv_dat, "start-test", 10);
//          if (rv == 0)
//          {
//            /* ���� */
//            rf_snd_data(test_data, 6);
//          }
//
//
//          rf_rcv_init();
//      }
//
//
////      /* ���� */
////      rf_snd_data(test_data, 11);
////      delay_ms(3000);
//    }

    /* ----------------��ʱû�õ�---------------- */
    /* lcd config & init */
    /*lcd_load_config(&lcd_config);
    lcd_power_on();
    lcd_init();
    disp_temp_room(250);
    disp_update();
    exti_load_config(pwr_check_cfg, 1);
    exti_init();

    th_sht2x_load_config(&sht20_cfg);
    th_sht2x_power_on();
    th_sht2x_init();
    SHT2x_Init();

    flash_ext_load_config(&flash_config);
    flash_ext_init();

    // RFID load config
    rfid_load_config(&rfid_config);
    rv = rfid_init(&ctrl_reg, &ver_reg);
    if (rv != 0)
    {
      printf("rfid init error\r\n");
    }
    //printf("ctrl_reg:%02X, ver_reg:%02X\r\n", ctrl_reg, ver_reg);
    rfid_close();
    rfid_power_off(); */

    return;
}

void software_init(void)
{
//    u16 gn = 0x4002;    // debug
//    u32 sn = 0x19014002;        //debug
//    u8 rf_fre = 0;
//    u8 rf_channel = 0;

//    printf("sizeof(g_sys_params) = %d\r\n", sizeof(g_sys_params));
    memset(&g_sys_params, 0, sizeof(g_sys_params));
    memset(&g_run_params, 0, sizeof(g_run_params));
    eeprom_read(0, (u8*)&g_sys_params, sizeof(g_sys_params));

    // ������ debug
//    eeprom_write_sys(2, &gn, 2);
//    eeprom_write_sys(4, &sn, 4);


    /* һ����û��ID�����ʹ�ã�������Ϊ25�� */
    if (g_sys_params.temp_set == 0) //�趨һ���¶�
    {
        g_sys_params.temp_set = 1800;
    }

    /* �������� */
    g_sys_params.rf_fre = (g_sys_params.Device_SN & 0x0000FFFF)>>12;
//    printf("g_sys_params.rf_fre = %d\r\n", g_sys_params.rf_fre);
    if ((g_sys_params.rf_fre != RF_FRE_470_5M) && (g_sys_params.rf_fre != RF_FRE_480_5M) && (g_sys_params.rf_fre != RF_FRE_490_5M))        // ������߲��ǹ涨��Ƶ�ʣ���ô��Ĭ������470_5MHz
        g_sys_params.rf_fre = RF_FRE_410_5M;    // Ĭ��Ϊ410.5M

    // RFͨ����
    g_sys_params.rf_channel = (((g_sys_params.Device_SN & 0x00000FFF)>>8)*100) + (((g_sys_params.Device_SN & 0x000000FF)>>4)*10) + (g_sys_params.Device_SN & 0x0000000F);
//    printf("g_sys_params.rf_channel = %d\r\n", g_sys_params.rf_channel);
    if(g_sys_params.rf_channel > 200)
        g_sys_params.rf_channel = 200;  // Ĭ��ͨ����Ϊ200

    // RF����
    g_sys_params.rf_power = TXPOW_20dBm;

    /* ������ʼ�� */
//    g_sys_params.heating_quantity = 12345678;   // ���Ϊ99999999�����к�����λֱ��ȥ����Ӧ���ǲ�ҪС������     // debug
//    g_sys_params.heating_time = 4442400;   // �������ģ�4442400/60/60 = 1234Сʱ                              // debug
    /* �����¶ȵ����޳�ʼ�� */
    if (g_sys_params.temp_room_uplimits == 0)
    {
      g_sys_params.temp_room_uplimits = 32;
    }
    /* �����¶ȵ����޳�ʼ�� */
    g_sys_params.temp_room_lowlimits = 0;

    g_sys_params.disp_ctl = 255;        // ��ʾ����λ
//    g_sys_params.workflg = 0xAA;        // Ĭ���ڹ�ů��     // debug
    g_run_params.valve_position = Valve_Open;       // Ĭ��Ϊ����
    g_run_params.arrears_state = 1;      // Ĭ��Ƿ��
    g_run_params.batt_lvl = 3300;       // Ĭ�ϵ�ص�����
    g_run_params.face_state = 0x00;       // Ĭ��û������
    g_run_params.sts_login = 1;

    task_18b20_init();
    task_adc_init();    // �ϵ�ɼ���ص���
    task_report_init();
}

void system_print(void)
{
    u8 gn_arry[2] = {0};
    u8 sn_arry[4] = {0};

    memcpy(gn_arry, &g_sys_params.Device_GN, 2);
    memcpy(sn_arry, &g_sys_params.Device_SN, 4);
    printf("\f");
    printf("productmodel:%s\r\n", product_model);
    printf("Hardware Ver:%s\r\n", hw_ver);
    printf("Software Ver:%s\r\n", sw_ver);
    printf("Product GN :%02X%02X\r\n", gn_arry[0], gn_arry[1]);
    printf("Product SN :%02X%02X %02X%02X\r\n", sn_arry[0], sn_arry[1], sn_arry[2], sn_arry[3]);

    printf("Factory Mode:%d\r\n", g_sys_params.factory_flag);
    printf("Heating Period: %02X\r\n" ,g_sys_params.workflg);
    printf("Temp Set: %d\r\n" ,g_sys_params.temp_set);
    printf("Rf Fre: %u\r\n", g_sys_params.rf_fre);
    printf("Rf Channel: %u\r\n",g_sys_params.rf_channel);
    printf("Com Ok: %lu\r\n", g_sys_params.com_ok);
    printf("Com Total: %lu\r\n", g_sys_params.com_total);
    printf("Temp Uplimits: %u\r\n", g_sys_params.temp_room_uplimits);
}

void main(void)
{
    hardware_init();
    software_init();
    factory_check();
    system_print();


    wdg_init(1500);//���Ź������������������1.5s����ô����������
    /* ʹ���ж� */
    enableInterrupts();
    PWR_UltraLowPowerCmd(ENABLE);   //�ⲿ��ѹ
    if (g_sys_params.factory_flag == 1)
    {
      com_close(COM1);
    }
    while (1)
    {
        if ((g_sys_params.factory_flag == 0) || (g_run_params.batt_collect_flag == 1)/*&& g_run_params.set_id==1*/)     // ע���ڲ��ɼ�adc��ʱ�������wfiģʽ
        {
            wfi();
        }
        else
        {
            halt();
        }
    }
}

#ifdef  USE_FULL_ASSERT

/**
* @brief  Reports the name of the source file and the source line number
*   where the assert_param error has occurred.
* @param  file: pointer to the source file name
* @param  line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    //printf("Wrong parameters value: file %s on line %lu\r\n", file, line);

    /* Infinite loop */
    while (1)
    {
    }
}
#endif