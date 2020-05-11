#include "lcd.h"
#include "disp.h"
#include "dbg.h"
#include "utili.h"
#include <string.h>
#include <stdio.h>

unsigned char disp_buf[14] = {0};

/*! \brief
*       display initilization��Ļ��ʼ��
*/
void disp_init(void)
{
    /* lcd initilization */
    lcd_init();

    /* display raw buffer initilization */
    memset(disp_buf, 0, sizeof(disp_buf));
    lcd_update_screen(disp_buf, sizeof(disp_buf));
}

/*! \brief
*       display close�ر���Ļ
*/
void disp_close(void)
{
    /* display raw buffer initilization */
    memset(disp_buf, 0, sizeof(disp_buf));
    lcd_update_screen(disp_buf, sizeof(disp_buf));

    /* lcd close */
    lcd_close();
}

/*! \brief
*       display all segementȫ����ʾ
*/
void disp_all(void)
{
    memset(disp_buf, 0xFF, sizeof(disp_buf));
    lcd_update_screen(disp_buf, sizeof(disp_buf));
}


/*! \brief
*       display clear��Ļ���
*/
void disp_clr(void)
{
    memset(disp_buf, 0x00, sizeof(disp_buf));
    lcd_update_screen(disp_buf, sizeof(disp_buf));
}

/*! \brief
*       display updateˢ����Ļ
*/
void disp_update(void)
{
    //MYLOG_DEBUG_HEXDUMP("Display Buffer:", disp_buf, sizeof(disp_buf));
    lcd_update_screen(disp_buf, sizeof(disp_buf));
}

/*! \brief
*      ��ʾ��������
* \param pos[IN]				- �ڼ��������
* \param val[IN]				- Ҫ��ʾ������
* \param sts[IN]				- ��ʾ����ʾ 0-����ʾ��1-��ʾ
*
* \return
*                           - �޷���ֵ
* \note
*		disp_digit(DIGIT1,1,1);��ʾ��һ������ܣ���ʾ����1����ʾ
*/
void disp_digit(u8 pos, u8 val, u8 sts)
{
    /* digit segmented table: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, b, c, d, E, F, S, T, -, P, r, ''*/
    const static u8 table_digit[] = {0x5F, 0x50, 0x3B, 0x79, 0x74, 0x6D, 0x6F, 0x58, 0x7F, 0x7D,0x7E, 0x67, 0x23, 0x73, 0x2F, 0x2E, 0x6D, 0x0E, 0x20, 0x3E, 0x22, 0x00};  //����Һ�����Ķ���˳��ʵ�֣����иߵ�˳����Ҫע��
    const static u8 table_position[] = {DIGIT6, DIGIT5, DIGIT4, DIGIT3, DIGIT2,DIGIT1};

    assert_param(pos<=5);
    assert_param(val<=sizeof(table_digit));

    /* position remapping */
    pos = table_position[pos];

    /* update screen buffer */
    if (sts == DISPLAY_ON)
    {
        /* ����Ĳ������ǰ����������ݲ�����ֻ���Լ�com���ϵĶ�����ֵ�ı䣬��ʱ��һˢ�¾Ϳ����� */

        /* COM1 */
        //        printf("pos:%d/%d\r\n", (0+6+pos*2)/8, (0+6+pos*2)%8);
        disp_buf[(0+6+pos*2)/8]  = disp_buf[(0+6+pos*2)/8] & (~(1<<((0+6+pos*2)%8)));   // /8��Ϊ��֪���ǵڼ����ֽڣ�%8��Ϊ��֪���ǵڼ�λ
        disp_buf[(0+6+pos*2)/8] |= ((table_digit[val]&0x01)>>0)<<(((0+6+pos*2)%8));

        /* COM2 */
        //        printf("pos:%d/%d\r\n", (28+6+pos*2)/8, (28+6+pos*2)%8);
        disp_buf[(28+6+pos*2)/8]  = disp_buf[(28+6+pos*2)/8] & (~(1<<((28+6+pos*2)%8) | 1<<((28+6+pos*2+1)%8)));
        disp_buf[(28+6+pos*2)/8] |= ((table_digit[val]&0x02)>>1)<<((28+6+pos*2)%8);
        disp_buf[(28+6+pos*2)/8] |= ((table_digit[val]&0x40)>>6)<<((28+6+pos*2+1)%8);

        /* COM3 */
        //        printf("pos:%d/%d\r\n", (56+6+pos*2)/8, (56+6+pos*2)%8);
        disp_buf[(56+6+pos*2)/8]  = disp_buf[(56+6+pos*2)/8] & (~(1<<((56+6+pos*2)%8) | 1<<((56+6+pos*2+1)%8)));
        disp_buf[(56+6+pos*2)/8] |= ((table_digit[val]&0x04)>>2)<<((56+6+pos*2)%8);
        disp_buf[(56+6+pos*2)/8] |= ((table_digit[val]&0x20)>>5)<<((56+6+pos*2+1)%8);

        /* COM4 */
        //        printf("pos:%d/%d\r\n", (84+6+pos*2)/8, (84+6+pos*2)%8);
        disp_buf[(84+6+pos*2)/8]  = disp_buf[(84+6+pos*2)/8] & (~(1<<((84+6+pos*2)%8) | 1<<((84+6+pos*2+1)%8)));
        disp_buf[(84+6+pos*2)/8] |= ((table_digit[val]&0x08)>>3)<<((84+6+pos*2)%8);
        disp_buf[(84+6+pos*2)/8] |= ((table_digit[val]&0x10)>>4)<<((84+6+pos*2+1)%8);
    }
    else
    {
        /* COM1 */
        disp_buf[(0+6+pos*2)/8]  = disp_buf[(0+6+pos*2)/8] & (~(1<<((0+6+pos*2)%8)));
        /* COM2 */
        disp_buf[(28+6+pos*2)/8]  = disp_buf[(28+6+pos*2)/8] & (~(1<<((28+6+pos*2)%8) | 1<<((28+6+pos*2+1)%8)));
        /* COM3 */
        disp_buf[(56+6+pos*2)/8]  = disp_buf[(56+6+pos*2)/8] & (~(1<<((56+6+pos*2)%8) | 1<<((56+6+pos*2+1)%8)));
        /* COM4 */
        disp_buf[(84+6+pos*2)/8]  = disp_buf[(84+6+pos*2)/8] & (~(1<<((84+6+pos*2)%8) | 1<<((84+6+pos*2+1)%8)));
    }
}

/*! \brief
*      ��ʾ�ַ�
* \param start[IN]				- �ڼ��������
* \param ch[IN]				        - Ҫ��ʾ���ַ�
*
* \return
*                           - �޷���ֵ
* \note
*		disp_char(0, '1');��ʾ��һ������ܣ���ʾ�ַ�'1'
*/
void disp_char(u8 start, u8 ch)
{
    u8 val = 0;
    //    unsigned char pos[9] = {IDX_DIGIT_3, IDX_DIGIT_2, IDX_DIGIT_1, IDX_DIGIT_9, IDX_DIGIT_8, IDX_DIGIT_7, IDX_DIGIT_6, IDX_DIGIT_5, IDX_DIGIT_4};
    assert_param(start < 6);

    switch(ch)
    {
    case '0':
        val = 0;
        break;
    case '1':
        val = 1;
        break;
    case '2':
        val = 2;
        break;
    case '3':
        val = 3;
        break;
    case '4':
        val = 4;
        break;
    case '5':
        val = 5;
        break;
    case '6':
        val = 6;
        break;
    case '7':
        val = 7;
        break;
    case '8':
        val = 8;
        break;
    case '9':
        val = 9;
        break;
    case 'A':
        val = 10;
        break;
    case 'b':
        val = 11;
        break;
    case 'c':
        val = 12;
        break;
    case 'd':
        val = 13;
        break;
    case 'E':
        val = 14;
        break;
    case 'F':
        val = 15;
        break;
    case 'S':
        val = 16;
        break;
    case 'T':
        val = 17;
        break;
    case '-':
        val = 18;
        break;
    case 'P':
        val = 19;
        break;
    case ' ':
        val = 20;
        break;
    default:
        val = 20;
        break;
    }

    disp_digit(start, val, DISPLAY_ON);
}

/*! \brief
*      ��ʾ��������
* \param start[IN]				- ��ʼ�������
* \param end[IN]				- �����������
* \param val[IN]				- ��ʾ�Ķ�λ����
*
* \return
*                           - �޷���ֵ
* \note
*		disp_number(2 ,4 ,789);��ʾ�ӵڶ�������ܵ����ĸ��������ʾ789�������
*               ��Ļ�ϵ�����ܴ�����Ϊ0~5
*/
void disp_number(u8 start, u8 end, u32 val)
{
    //u8 pos[] = {DIGIT1, DIGIT2, DIGIT3, DIGIT4, DIGIT5};
    u8 i=0, j=0, len=0;
    u8 num[9] = {0};
    u32 fator = 1;

    assert_param(/*start>=0 && */end<=5 && start<=end);

    // MYLOG_DEBUG_HEXDUMP("[0]Display Buffer:", disp_buf, sizeof(disp_buf));

    for (i=0; i<end-start+1; ++i)
    {
        disp_digit(start+i, 0, DISPLAY_OFF);
    }

    for (i=0; i<(end-start+1); ++i)
    {
        fator = 1;
        for (j=0; j<end-start-i; ++j)
        {
            fator *= 10;
        }

        num[i] = val / fator;
        val %= fator;
    }

    for (i=0; i<end-start+1; ++i)
    {
        if (num[i] != 0)
            break;
    }

    len = end-start+1-i;

    for (i=0; i<len; ++i)
    {
        disp_digit(end-i, num[end-start-i], DISPLAY_ON);
    }

    //MYLOG_DEBUG_HEXDUMP("[1]Display Buffer:", disp_buf, sizeof(disp_buf));
}

/*! \brief
*      ��ʾ�ַ���
* \param start[IN]				- ��ʼ�������
* \param end[IN]				- �����������
* \param str[IN]				- ��ʾ���ַ���
*
* \return
*                           - �޷���ֵ
* \note
*		disp_str(2, 4, "bcd");��ʾ�ӵڶ�������ܵ����ĸ��������ʾ"bcd"�������
*               ��Ļ�ϵ�����ܴ�����Ϊ0~5
*/
void disp_str(u8 start, u8 end, const char *str)
{
    //u8 pos[] = {DIGIT1, DIGIT2, DIGIT3, DIGIT4, DIGIT5};
    u8 i=0;

    assert_param(/*start>=0 && */end<=5 && start<=end);

    for (i=0; i<end-start+1; ++i)
    {
        if (str[i]>='0' && str[i]<='9')
        {
            disp_digit(start+i, str[i]-'0', DISPLAY_ON);
        }
        else
        {
            disp_char(start+i, str[i]);
        }
    }
}

/*! \brief
*      ��ʾ�ָ���
* \param disp_sts[IN]
*
* \note
*
*/
void disp_line(u8 disp_sts)
{
    lcd_write_seg(disp_buf, SEG_L, DISPLAY_OFF);
    //    lcd_write_seg(disp_buf, SEG_LINE_2, DISPLAY_OFF);
    //    lcd_write_seg(disp_buf, SEG_LINE_3, DISPLAY_OFF);

    /* ��ʾ */
    if (disp_sts == DISPLAY_ON)
    {
        lcd_write_seg(disp_buf, SEG_L, DISPLAY_ON);
        //lcd_write_seg(disp_buf, SEG_LINE_2, DISPLAY_ON);
        //lcd_write_seg(disp_buf, SEG_LINE_3, DISPLAY_ON);
    }

    //lcd_update_screen(disp_buf, sizeof(disp_buf));
}

/*! \brief
*      ��ʾ��ص���
* \param disp_sts[IN]      - �Ƿ���ʾ 0-�رգ�1-��ʾ
* \param lv[IN]            - ��ص��� 0~3
*
* \note
*
*/
void disp_batt(u8 disp_sts, u8 lv)
{
    assert_param(lv==BATT_LVL_3 || lv==BATT_LVL_2 || lv==BATT_LVL_1 || lv==BATT_LVL_0);

    lcd_write_seg(disp_buf, SEG_B1, DISPLAY_OFF);//��ر߿�
    lcd_write_seg(disp_buf, SEG_B2, DISPLAY_OFF);//����Ϊһ��
    lcd_write_seg(disp_buf, SEG_B3, DISPLAY_OFF);//����Ϊ����
    lcd_write_seg(disp_buf, SEG_B4, DISPLAY_OFF);//����Ϊ����

    if (disp_sts == DISPLAY_ON)
    {
        switch(lv)
        {
        case BATT_LVL_3:
            lcd_write_seg(disp_buf, SEG_B4, DISPLAY_ON);
            lcd_write_seg(disp_buf, SEG_B3, DISPLAY_ON);
            lcd_write_seg(disp_buf, SEG_B2, DISPLAY_ON);
            lcd_write_seg(disp_buf, SEG_B1, DISPLAY_ON);
        case BATT_LVL_2:
            lcd_write_seg(disp_buf, SEG_B3, DISPLAY_ON);
            lcd_write_seg(disp_buf, SEG_B4, DISPLAY_ON);
            lcd_write_seg(disp_buf, SEG_B1, DISPLAY_ON);
        case BATT_LVL_1:
            lcd_write_seg(disp_buf, SEG_B4, DISPLAY_ON);
            lcd_write_seg(disp_buf, SEG_B1, DISPLAY_ON);
        case BATT_LVL_0:
            lcd_write_seg(disp_buf, SEG_B1, DISPLAY_ON);
            break;
        default:
            break;
        }
    }

    //lcd_update_screen(disp_buf, sizeof(disp_buf));
}

/*! \brief
*      ��ʾ�ź�ֵ
* \param disp_sts[IN]      - �Ƿ���ʾ 0-�رգ�1-��ʾ
* \param sts[IN]           - ��û���ź� 0-û��;1-��
*
* \note
*
*/
void disp_ant(u8 disp_sts, u8 sts)
{
    assert_param(sts==DISPLAY_ON || sts==DISPLAY_OFF);

//    lcd_write_seg(disp_buf, SEG_T1, DISPLAY_OFF);
//    lcd_write_seg(disp_buf, SEG_T2, DISPLAY_OFF);
//    lcd_write_seg(disp_buf, SEG_T3, DISPLAY_OFF);
//    lcd_write_seg(disp_buf, SEG_T4, DISPLAY_OFF);

    LCD_MARK_WriteChar("N", CLEAR);
    //MYLOG_DEBUG("Ant Sts:%u\r\n", sts);

    /* ��ʾ�ź� */
    if (disp_sts == DISPLAY_ON)
    {
        /* ���ź� */
        if (sts == DISPLAY_ON)
        {
//            lcd_write_seg(disp_buf, SEG_T1, DISPLAY_ON);
//            lcd_write_seg(disp_buf, SEG_T2, DISPLAY_ON);
//            lcd_write_seg(disp_buf, SEG_T3, DISPLAY_ON);
//            lcd_write_seg(disp_buf, SEG_T4, DISPLAY_ON);

            LCD_MARK_WriteChar("N", WRITE);
        }
    }

    //    assert_param(lv==RF_LVL_3 || lv==RF_LVL_2 || lv==RF_LVL_1 || lv==RF_LVL_0);
    //
    //    lcd_write_seg(disp_buf, SEG_T1, DISPLAY_OFF);
    //    lcd_write_seg(disp_buf, SEG_T2, DISPLAY_OFF);
    //    lcd_write_seg(disp_buf, SEG_T3, DISPLAY_OFF);
    //    lcd_write_seg(disp_buf, SEG_T4, DISPLAY_OFF);
    //
    //    if (disp_sts == DISPLAY_ON)
    //    {
    //        switch(lv)
    //        {
    //        case BATT_LVL_3:
    //            lcd_write_seg(disp_buf, SEG_T4, DISPLAY_ON);
    //        case BATT_LVL_2:
    //            lcd_write_seg(disp_buf, SEG_T3, DISPLAY_ON);
    //        case BATT_LVL_1:
    //            lcd_write_seg(disp_buf, SEG_T2, DISPLAY_ON);
    //        case BATT_LVL_0:
    //            lcd_write_seg(disp_buf, SEG_T1, DISPLAY_ON);
    //            break;
    //        default:
    //            break;
    //        }
    //    }

    //    lcd_update_screen(disp_buf, sizeof(disp_buf));
}

/*! \brief
*      ��ʾ�ź�״̬(�״�Ѷ��)
* \param disp_sts[IN]      - �Ƿ���ʾ 0-�رգ�1-��ʾ
*
* \note
*
*/
void disp_rf_state(u8 disp_sts)
{
    assert_param(disp_sts==DISPLAY_ON || disp_sts==DISPLAY_OFF);

//    lcd_write_seg(disp_buf, SEG_XH, DISPLAY_OFF);
    LCD_MARK_WriteChar("Z", CLEAR);

    //MYLOG_DEBUG("Ant Sts:%u\r\n", sts);

    /* ��ʾ�״��ź� */
    if (disp_sts == DISPLAY_ON)
    {
//        lcd_write_seg(disp_buf, SEG_XH, DISPLAY_ON);
        LCD_MARK_WriteChar("Z", WRITE);

    }

    //lcd_update_screen(disp_buf, sizeof(disp_buf));
}

/*! \brief
*      ��ʾ�����ʶ
* \param disp_sts[IN]      - �Ƿ���ʾ 0-�رգ�1-��ʾ
*
* \note
*
*/
void disp_warning(u8 disp_sts)
{
    //disp_clr_region();
    lcd_write_seg(disp_buf, SEG_KL, DISPLAY_OFF);

    // ��ʾ
    if (disp_sts == DISPLAY_ON)
    {
        lcd_write_seg(disp_buf, SEG_KL, DISPLAY_ON);
    }

    //lcd_update_screen(disp_buf, sizeof(disp_buf));
}

/*! \brief
*      ��ʾǷ��
* \param disp_sts[IN]      - �Ƿ���ʾ 0-�رգ�1-��ʾ
*
* \note
*
*/
void disp_owed(u8 disp_sts)
{
    lcd_write_seg(disp_buf, SEG_QF, DISPLAY_OFF);

    // ��ʾ
    if (disp_sts == DISPLAY_ON)
    {
        lcd_write_seg(disp_buf, SEG_QF, DISPLAY_ON);
    }

    //lcd_update_screen(disp_buf, sizeof(disp_buf));
}




///*! \brief
//*      ��ʾ���ۼ�ʱ��
//* \param heat_time[IN]         - ���ۼ�ʱ��
//*
//* \note
//*
//*/
//void disp_heat_time_total(u32 heat_time)
//{
//    disp_clr_region();
//
//    lcd_write_seg(disp_buf, SEG_UNIT_HOUR, DISPLAY_ON);
//    disp_heat_time(heat_time);
//    lcd_update_screen(disp_buf, sizeof(disp_buf));
//
//}
//
//
//
/*! \brief
*      ��ʾϵͳʱ��������
* \param year[IN]      - ��
* \param month[IN]     - ��
* \param day[IN]       - ��
* \note
*
*/
void disp_sys_time_ymd(u8 year, u8 month, u8 day)
{
    disp_clr_region();

    lcd_write_seg(disp_buf, SEG_SJ, DISPLAY_ON);
    //lcd_write_seg(disp_buf, SEG_S3, DISPLAY_ON);
    //lcd_write_seg(disp_buf, SEG_S2, DISPLAY_ON);

    disp_digit(5, 6, year);
    disp_digit(3, 4, month);
    disp_digit(1, 2, day);
}

/*! \brief
*      ��ʾϵͳʱ��ʱ����
* \param hour[IN]      - Сʱ
* \param min[IN]       - ����
* \param second[IN]    - ��
* \note
*
*/
void disp_sys_time_hms(u8 hour, u8 min, u8 second)
{
    disp_clr_region();

    lcd_write_seg(disp_buf, SEG_SJ, DISPLAY_ON);
    lcd_write_seg(disp_buf, SEG_S3, DISPLAY_ON);
    lcd_write_seg(disp_buf, SEG_S2, DISPLAY_ON);

    disp_digit(5, 6, hour);
    disp_digit(3, 4, min);
    disp_digit(1, 2, second);
}

/*! \brief
*      ��ʾ�����¶�
* \param temp_room[IN]     - �����¶�
*
* \note
*
*/
void disp_temp_room(s16 temp_room)
{
    disp_clr_region();
    char buf_temp_room[8] = {0};

    lcd_write_seg(disp_buf, SEG_SW, DISPLAY_ON);//����??
    lcd_write_seg(disp_buf, SEG_DF, DISPLAY_ON);
    lcd_write_seg(disp_buf, SEG_S2, DISPLAY_ON);

    //printf("temp_room=%d\r\n",temp_room);
    if (temp_room >= 10)
    {
        disp_number(2, 4, temp_room); //��?disp_number������?��??��?��2?��?��a??3����?��?��?
    }
    else if(temp_room>=0 && temp_room<10)
    {
        sprintf(buf_temp_room, "%02d", temp_room);
        disp_str(3, 4, buf_temp_room);
    }
    else if(temp_room<0)
    {
        if (temp_room < -100)
        {
            temp_room = -99;
        }
//	if(temp_room>=(-10) && temp_room<0)
//        {
            sprintf(buf_temp_room, "%03d", temp_room);
//        }
//        else
//        {
//            sprintf(buf_temp_room, "%02d", temp_room);
//        }
        disp_str(2, 4, buf_temp_room);
    }

}

/*! \brief
*      ��ʾ�趨�¶�
* \param temp_set[IN]      - �趨�¶�
*
* \note
*
*/
void disp_temp_set(u16 temp_set)
{
    disp_clr_region();
    char buf_temp_set[8] = {0};

    lcd_write_seg(disp_buf, SEG_SD, DISPLAY_ON);//�趨�¶�
    lcd_write_seg(disp_buf, SEG_DF, DISPLAY_ON);
    lcd_write_seg(disp_buf, SEG_S2, DISPLAY_ON);
    //printf("temp_set = %d\r\n", temp_set);
    if (temp_set >= 10)
    {
        disp_number(2, 4, temp_set);     // �趨�¶� ��λ��0.1��
    }
    else
    {
        sprintf(buf_temp_set, "%02d", temp_set);
        disp_str(3, 4, buf_temp_set);
    }
}

/*! \brief
*      ���ű�ʶ
* \param sts[IN]      - �Ƿ���ʾ 0-�رգ�1-��ʾ
*
* \note
*
*/
void disp_valve_sts(u8 sts)
{
    //assert_param(sts==VALVE_STS_OPEN || sts==VALVE_STS_CLOSE);

    lcd_write_seg(disp_buf, SEG_FM, DISPLAY_OFF);
    assert_param(sts==DISPLAY_ON || sts==DISPLAY_OFF);
    if (sts == DISPLAY_ON)
    {
        lcd_write_seg(disp_buf, SEG_FM, DISPLAY_ON); //���ű�ʶ
    }

    //lcd_update_screen(disp_buf, sizeof(disp_buf));
}

/*! \brief
*      ID���
* \param id[IN]      - �����Ԫ��
* \param len[IN]     - ����ĳ���
*
* \note
*
*/
void disp_id(const unsigned char *id, u8 len)
{
    //char buf[13] = {0};

    //    assert_param(id != NULL);
    //    assert_param(len<=6);
    //
    //    disp_clr_region();
    //
    //    lcd_write_seg(disp_buf, SEG_BH, DISPLAY_ON);
    //
    //    //bytes_2_ascii(buf, sizeof(buf), id, len);
    //    //disp_str(3, 2+strlen(buf), buf);
    //    //printf("strlen(id)=%d\r\n" ,strlen(id));
    //    if (strlen(id) > 1 && strlen(id)<=6)
    //    {
    //        disp_str(0, strlen(id)-2, id);//strlen(id)��ֵΪ6�����Լ�һ
    //    }
    //    else
    //    {
    //        disp_str(1, 5, "0-000");
    //    }

    disp_clr_region();
    char buf[11] = {0};

    assert_param(id != NULL);
    assert_param(len<=6);

    //printf("id=%x\r\n",id);
    //printf("idsizeof=%d\r\n",len);
    //disp_clr_region();

    lcd_write_seg(disp_buf, SEG_BH, DISPLAY_ON);
    /*���ݳ��ȱ�Ϊ����,��ת�����ַ���ʽ���������ÿ�����������һ����λ
    ����u8 addr[5] = {0x90,0x05,0x00,0x01,0x01};ת��ΪBUF[0]='9',BUF[1]='0'.... */
    bytes_2_ascii(buf, sizeof(buf), id, len);

#ifdef TASK_PRINTF
    printf("BUF[0]=%c\r\n",buf[0]);
    printf("BUF[1]=%c\r\n",buf[1]);
    printf("BUF[2]=%c\r\n",buf[2]);
    printf("BUF[3]=%c\r\n",buf[3]);
    printf("BUF[4]=%c\r\n",buf[4]);
    printf("BUF[5]=%c\r\n",buf[5]);
    printf("BUFsizeof=%d\r\n",sizeof(buf));
#endif
    disp_str(0, len*2-1, buf);
    //disp_str(0, 5, buf);
}

/*! \brief
*      ������
* \param id[IN]      - �ַ���������
* \param len[IN]     - �ַ����ĳ���
*
* \note
*
*/
void disp_room_id(const char *id, u8 len)
{
    //char buf[13] = {0};

    assert_param(id != NULL);
    assert_param(len<=6);

    disp_clr_region();

    lcd_write_seg(disp_buf, SEG_FJ, DISPLAY_ON);
    //printf("id44444444444444444444 = %s\r\n" ,id); //idΪ������׵�ַ����ӡ����Ϊ1-204
    //printf("strlen(id)=%d\r\n",strlen(id));
    if (strlen(id) > 1 && strlen(id)<=6)
    {
        disp_str(0, strlen(id)-1, id);//strlen(id)��ֵΪ6�����Լ�һ
    }
    else
    {
        disp_str(1, 5, "0-000");
    }
}

/*! \brief
*      ����
* \param code[IN]      - ״̬st
*
* \note
*
*/
void disp_fault(u16 code)
{
    //printf("code=%04x",code);
    char buf[8] = {0};  //��Ҫת���ַ�������disp_str����ʾ
    //u8 len = 0;

    disp_clr_region();

    //    sprintf(buf, "F-%04X", code);//��ΪbalanceΪlong�ͣ����Դ�ӡΪ%ld
    //            len = strlen(buf);
    //            disp_str(0+6-len, 5, buf);

    lcd_write_seg(disp_buf, SEG_GZ, DISPLAY_ON);
    sprintf(buf, "F-%04x", code);//04X������4λ16����������ʾ ע��%04x��xΪСд�ķ���b,c,d�޷���ʾ
    disp_str(0, 5, buf);
    return;
}

/*! \brief
*      ��ʾʣ������
* \param balance[IN]       - ����ֵ ��λ:0.01kwh
* \param unit[IN]          - ��� ��λ:0.01kwh
* ��ֵ���ǷŴ�100��
*
* \note
*
*/
void disp_surplus_heat(long balance, u8 unit)
{
    char buf[8] = {0};
    u8 len = 0;

    assert_param(unit==UNIT_KWH || unit==UNIT_GJ);

    disp_clr_region();

    lcd_write_seg(disp_buf, SEG_S6, DISPLAY_ON);
    lcd_write_seg(disp_buf, SEG_S2, DISPLAY_ON);

    //printf("Balance:%ld\r\n", balance);

    // ������ʾ��ȵ�ֵ�Ĵ���
    if (unit == UNIT_KWH)
    {
        // ת����λΪGJ
        if (balance>999999 || balance<-99999)
        {
            balance = balance*36/10000;
            unit = UNIT_GJ;
        }
    }

    if (unit == UNIT_GJ)
    {
        // ��λΪ�������ʾ���ֵ
        if (balance > 999999)
        {
            balance = 999999;
        }
        // ��λΪ�������ʾ���ֵ
        if (balance < -99999)
        {
            balance = -99999;
        }
    }
    if (unit == UNIT_KWH)
    {
        lcd_write_seg(disp_buf, SEG_KWH, DISPLAY_ON);
    }
    else
    {
        lcd_write_seg(disp_buf, SEG_GJ, DISPLAY_ON);
    }

    if (balance >= 0)
    {
        if (balance >= 100)
        {
            sprintf(buf, "%ld", balance);//��ΪbalanceΪlong�ͣ����Դ�ӡΪ%ld
            len = strlen(buf);           //Ϊ��ʵ���Ҷ���ż����
            disp_str(0+6-len, 5, buf);   //Ϊ��ʵ���Ҷ���
            //disp_str(3+3-strlen(buf), 5, buf);
        }
        else
        {
            sprintf(buf, "%03ld", balance);//��λ��Ϊ��λʱ%03ldҪ��ʾ��λ��������ǰ����һλ����
            len = strlen(buf);             //����Ϊ3
            disp_str(0+6-len, 5, buf);
            //disp_digit(3, 5, balance);
        }
    }
    else
    {

        //        sprintf(buf, "-%ld", balance);
        //
        //        len = strlen(buf);
        //
        //        disp_str(0+6-len-1, 5, buf);
        //disp_digit(3+3-len+1, 5, balance*(-1));
        sprintf(buf, "%ld", balance);

        len = strlen(buf);//�ַ���ʽ��ʱ������ҲҪռһλ

        disp_str(0+6-len, 0+6-len, "-");
        disp_number(0+6-len+1, 5, balance*(-1));
    }
}

/*! \brief
*      ��ʾ�ۼ�����
* \param heat_quantity[IN]         - ����
* \param heat_quantity_uint[IN]    - ������λ:0.01kwh
*
* \note
*
*/
void disp_heat_quantity(u32 heat_quantity, u8 heat_quantity_uint)
{
    disp_clr_region();
    //    char buf[8] = {0};
    char buf[8] = {0};
    u8 len = 0;
    //printf("heat_quantity_uint=%x\r\n",heat_quantity_uint);
    assert_param(heat_quantity_uint==UNIT_KWH || heat_quantity_uint == UNIT_GJ);

    lcd_write_seg(disp_buf, SEG_S5, DISPLAY_ON);
    lcd_write_seg(disp_buf, SEG_S2, DISPLAY_ON);

    if (heat_quantity_uint == UNIT_GJ && heat_quantity >= 999999)
    {
        heat_quantity = 999999;
        heat_quantity_uint = UNIT_GJ;
    }
    else if (heat_quantity_uint == UNIT_KWH && heat_quantity >= 999999)
    {
        heat_quantity = heat_quantity*36/10000;
        heat_quantity_uint = UNIT_GJ;
    }

    if (heat_quantity >= 100)
    {
        sprintf(buf, "%ld", heat_quantity);//��ΪbalanceΪlong�ͣ����Դ�ӡΪ%ld
        len = strlen(buf);
        disp_str(0+6-len, 5, buf);
        //        sprintf(buf, "%lu", heat_quantity);
        //        disp_str(3+3-strlen(buf), 5, buf);
    }
    else
    {
        sprintf(buf, "%03ld", heat_quantity);//��λ��Ϊ��λʱ%03ldҪ��ʾ��λ��������ǰ����һλ����
        len = strlen(buf);
        disp_str(0+6-len, 5, buf);
        //disp_digit(3,5 , heat_quantity);
    }

    if (heat_quantity_uint == UNIT_KWH)
    {
        lcd_write_seg(disp_buf, SEG_KWH, DISPLAY_ON);
    }
    else
    {
        lcd_write_seg(disp_buf, SEG_GJ, DISPLAY_ON);
    }

    //lcd_update_screen(disp_buf, sizeof(disp_buf));
}

/*! \brief
*      ��ʾ����ʱ��
* \param heat_time[IN]         - �ۼ�ʱ��
*
* \note
*
*/
void disp_heat_time(u32 heat_time)
{
    disp_clr_region();
    char buf[8] = {0};

    lcd_write_seg(disp_buf, SEG_S4, DISPLAY_ON);
    lcd_write_seg(disp_buf, SEG_S1, DISPLAY_ON);

    if (heat_time >= 1000000)
    {
        heat_time = 999999;
    }

    sprintf(buf, "%lu", heat_time);
    disp_str(0+6-strlen(buf), 5, buf);
    //    lcd_update_screen(disp_buf, sizeof(disp_buf));
}

/*! \brief
*      �ص�����Ĳ���
*
* \note
*
*/
void disp_clr_region(void)
{
    disp_digit(DIGIT1, 0, DISPLAY_OFF);
    disp_digit(DIGIT2, 0, DISPLAY_OFF);
    disp_digit(DIGIT3, 0, DISPLAY_OFF);
    disp_digit(DIGIT4, 0, DISPLAY_OFF);
    disp_digit(DIGIT5, 0, DISPLAY_OFF);
    disp_digit(DIGIT6, 0, DISPLAY_OFF);

    lcd_write_seg(disp_buf, SEG_SW, DISPLAY_OFF);
    lcd_write_seg(disp_buf, SEG_SD, DISPLAY_OFF);
    lcd_write_seg(disp_buf, SEG_S6, DISPLAY_OFF);
    lcd_write_seg(disp_buf, SEG_S5, DISPLAY_OFF);
    lcd_write_seg(disp_buf, SEG_SJ, DISPLAY_OFF);
    lcd_write_seg(disp_buf, SEG_S4, DISPLAY_OFF);

    lcd_write_seg(disp_buf, SEG_BH, DISPLAY_OFF);
    lcd_write_seg(disp_buf, SEG_FJ, DISPLAY_OFF);
    lcd_write_seg(disp_buf, SEG_GZ, DISPLAY_OFF);

    lcd_write_seg(disp_buf, SEG_GJ, DISPLAY_OFF);
    lcd_write_seg(disp_buf, SEG_S1, DISPLAY_OFF);
    lcd_write_seg(disp_buf, SEG_KWH, DISPLAY_OFF);
    lcd_write_seg(disp_buf, SEG_DF,DISPLAY_OFF);

    lcd_write_seg(disp_buf, SEG_S3, DISPLAY_OFF);
    lcd_write_seg(disp_buf, SEG_S2, DISPLAY_OFF);
}

/*! \brief
*      ��ʾϵͳʱ��
* \param hour[IN]      - Сʱ
* \param min[IN]       - ����
*
* \note
*
*/
void disp_sys_time(u8 hour, u8 min)
{
    disp_clr_region();
    char buf_hour[8] = {0};
    //u8 len_hour = 0;
    char buf_min[8] = {0};
    //u8 len_min = 0;

    lcd_write_seg(disp_buf, SEG_SJ, DISPLAY_ON);
    lcd_write_seg(disp_buf, SEG_S3, DISPLAY_ON);
    lcd_write_seg(disp_buf, SEG_S2, DISPLAY_ON);

    sprintf(buf_hour, "%02d", hour);//��ΪbalanceΪlong�ͣ����Դ�ӡΪ%ld
    //len_hour = strlen(buf_hour);
    disp_str(2, 3, buf_hour);   //Ϊ��ʵ���Ҷ���

    sprintf(buf_min, "%02d", min);//��ΪbalanceΪlong�ͣ����Դ�ӡΪ%ld
    //len_hour = strlen(buf_hour);
    disp_str(4, 5, buf_min);   //Ϊ��ʵ���Ҷ���

    //    disp_number(2, 3, hour);
    //    disp_number(4, 5, min);
}

/*! \brief
*      ��ʾ���ò���
*
* \note
*
*/
void disp_set_id(void)
{
//    disp_clr_region();
//      disp_str(1, 5, "SET-P");
    LCD_NUM_WriteChar(0x00, LCD_TEMP_D_POSITION, WRITE);    // LCD_TEMP_D_POSITION   �¶�ʮλ  ������ʾ����ID��ͨ����
    LCD_NUM_WriteChar(DOWNLOAD_ID_CHANNEL/10, LCD_TEMP_U_POSITION, WRITE);	// LCD_TEMP_U_POSITION   �¶ȸ�λ  ������ʾ����ID��ͨ����
}







