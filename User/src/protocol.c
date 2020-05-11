#include <stdio.h>
#include "adf.h"
#include "sysparams.h"
#include "cj188.h"
#include "protocol.h"

char room_name[7] = {0};

/*
��������:LittleANDBig_ModeCON2
��������:��һ��INT16U���ݽ��д�С��ģʽ�л�

*/
u16 LittleANDBig_ModeCON2(u16*Input)
{
	u16 DATAOUT =0;
	u16 DATAIN =*Input;
	DATAOUT =((DATAIN&0X00FF )<<8)|((DATAIN&0XFF00 )>>8);
	return DATAOUT;
}


/*
��������:LittleANDBig_ModeCON4
��������:��һ��INT32U���ݽ��д�С��ģʽ�л�

*/
u32 LittleANDBig_ModeCON4(u32*Input)
{
	u32 DATAOUT =0;
	u32 DATAIN =*Input;

	DATAOUT =((DATAIN&0X000000FF )<<24)|((DATAIN&0X0000FF00 )<<8)|((DATAIN&0X00FF0000 )>>8)|((DATAIN&0XFF000000 )>>24);
	return DATAOUT;
}

/*! \brief 
*      ǩ������
* \param pkg[IN]            - cj188�Ĳ��� 
* \param sys_params[IN]     - ϵͳ����
* \param run_params[IN]     - ���в���
*
* \note  
* 
*/
u8 app_login_request(CJ188Pkg *pkg, const SysParams *sys_params, RunParams run_params)
{ 
    // �Ǳ��ַ
    memcpy(pkg->addr, sys_params->addr, sizeof(pkg->addr));
    // ������
    pkg->ctrl_code = CTRL_CODE_DEV_LOGIN;    
    // �����򳤶�
    pkg->msg_size  = 0x00;
    
    return 0;
}

/*! \brief 
*      ǩ������
* \param pkg[IN]            - cj188�Ĳ��� 
* \param sys_params[IN]     - ϵͳ����
* \param run_params[IN]     - ���в���
*
* \note  
* 
*/
u8 app_login_response(CJ188Pkg *pkg, SysParams *sys_params, RunParams *run_params)
{  
////    //char room_name[7] = {0};
////    
////    // ��ַ����
////    if (memcmp(pkg->addr, sys_params->addr, sizeof(pkg->addr)) != 0)
////    {
////        return CJ188_ERR_ADDR;
////    }
////    
////    // ������
////    if (pkg->ctrl_code != (CTRL_CODE_DEV_LOGIN | 0x80))
////    {
////        return CJ188_ERR_CTRL_CODE;
////    }
////    
////#ifdef DEBUG
////    //MYLOG_DEBUG_HEXDUMP("MsgData:", pkg->msg_data, pkg->msg_size);
////#endif
////    
////    // ��ů��ʼʱ��
////    sys_params->heating_period_st[0] = pkg->msg_data[1];
////    sys_params->heating_period_st[1] = pkg->msg_data[0];
////    // ��ů����ʱ��
////    sys_params->heating_period_et[0] = pkg->msg_data[3];
////    sys_params->heating_period_et[1] = pkg->msg_data[2];
////    //    printf("g_sys_params.heating_period_st = %02x\r\n" ,g_sys_params.heating_period_st);
////    //    printf("g_sys_params.heating_period_et = %02x\r\n" ,g_sys_params.heating_period_et);
////    // �¶��趨����
////    sys_params->temp_room_uplimits   = pkg->msg_data[4];
////    // �¶��趨����
////    sys_params->temp_room_lowlimits  = pkg->msg_data[5];
////    // ��������(���㷨Ϊ�ֽڵ��𣬰Ѱ����intel�ֽ���ת������������3C 00ת��Ϊ00 3C����Ϊ1����)
////    //sys_params->cycle_sample = pkg->msg_data[7]<<8 | pkg->msg_data[6];
////    sys_params->cycle_sample = bcd_2_dec_type(&(pkg->msg_data[6]), 2, ORD_INTEL);
////    // ����ֵ
////    sys_params->balance_alarm        = pkg->msg_data[8];
////    // ��ʾ����λ   
////    sys_params->disp_ctl             = pkg->msg_data[9];
////    // ������
////    if (pkg->msg_data[12]>=0x10 && pkg->msg_data[11]>=0x10)
////    {
////        //sprintf(room_name, "%X%02X", pkg->msg_data[11], pkg->msg_data[10]);
////        room_name[0] = (pkg->msg_data[11]>>4)+'0';
////        room_name[1] = (pkg->msg_data[11]%0x0f)+'0';
////        room_name[2] = (pkg->msg_data[10]>>4)+'0';
////        room_name[3] = (pkg->msg_data[10]%0x0f)+'0';
////        memcpy(sys_params->room_name, room_name, sizeof(sys_params->room_name));        
////    }
////    else
////    {
////        //sprintf(room_name, "%X-%X%02X", pkg->msg_data[12], pkg->msg_data[11], pkg->msg_data[10]);
////        room_name[0] = (pkg->msg_data[12]%0x0f)+'0';
////        room_name[1] = '-';
////        if ((pkg->msg_data[11]>>4) > 0)
////        {
////            room_name[2] = (pkg->msg_data[11]>>4)+'0';
////            room_name[3] = (pkg->msg_data[11]%0x0f)+'0'; 
////            room_name[4] = (pkg->msg_data[10]>>4)+'0';
////            room_name[5] = (pkg->msg_data[10]%0x0f)+'0';            
////        }
////        else
////        {
////            room_name[2] = (pkg->msg_data[11]%0x0f)+'0';    
////            room_name[3] = (pkg->msg_data[10]>>4)+'0';
////            room_name[4] = (pkg->msg_data[10]%0x0f)+'0';  
////            room_name[5] = '\0';
////        }
////        
////        memcpy(sys_params->room_name, room_name, sizeof(sys_params->room_name));         
////    }
////    
////    //    printf("g_sys_params.temp_room_uplimits = %d\r\n" ,g_sys_params.temp_room_uplimits);
////    //    printf("g_sys_params.temp_room_lowlimits = %d\r\n" ,g_sys_params.temp_room_lowlimits);
////    // �¶������޸ı����Ҫ���¼��㵵λ
////    if (sys_params->temp_set > sys_params->temp_room_uplimits*10)
////    {
////        sys_params->temp_set = sys_params->temp_room_uplimits*10;
////        run_params->temp_return = sys_params->temp_set;
////    }
////    else if (sys_params->temp_set < sys_params->temp_room_lowlimits*10)
////    {
////        sys_params->temp_set = sys_params->temp_room_lowlimits*10;
////        run_params->temp_return = sys_params->temp_set;
////    }   
////    
////    //printf("Heating Period:%02X-%02X/%02X-%02X\r\n", sys_params->heating_period_st[0], sys_params->heating_period_st[1], sys_params->heating_period_et[0], sys_params->heating_period_et[1]);
////    //printf("RoomName:%s\r\n", sys_params->room_name);
////    //printf("DispCtrl:%02X/%02X\r\n", pkg->msg_data[9], sys_params->disp_ctl);
////    
////    //MYLOG_DEBUG("cycle_sample:%u\r\n", sys_params->cycle_sample);
    return 0;
}

 /*! \brief 
*      ��������
* \param pkg[IN]            - cj188�Ĳ��� 
* \param sys_params[IN]     - ϵͳ����
* \param run_params[IN]     - ���в���
*
* \note  
* 
*/
u8 app_factory_request(CJ188Pkg *pkg, /*const*/ SysParams *sys_params, RunParams run_params)
{
    u8 offset = 0;
    u32 sn_data = 0;
    u16 gn_data = 0;
    
    /* -------------------û����Щ�̶��ĳ���------------------- */
    /* SN */
    sn_data = LittleANDBig_ModeCON4(&(sys_params->Device_SN));
    memcpy(&(pkg->sn), &(sn_data), sizeof(pkg->sn));
    /* GN */
    gn_data = LittleANDBig_ModeCON2(&(sys_params->Device_GN));
    memcpy(&(pkg->gn), &(gn_data), sizeof(pkg->gn));
    /* �������� */
    pkg->ctrl_code = 1;
    /* ������ */
    offset = 0;
    /* SN */
    memcpy(pkg->msg_data+offset, &(sn_data), sizeof(pkg->sn));
    offset += 4;
    /* GN */
    memcpy(pkg->msg_data+offset, &(gn_data), sizeof(pkg->gn));
    offset += 2;
    /* Ӳ���汾 */
    sys_params->hardware_persion = 0x00;
    pkg->msg_data[offset] = sys_params->hardware_persion;
    offset += 1;
    /* ����汾 */
    sys_params->soft_persion = 0x60;
    pkg->msg_data[offset] = sys_params->soft_persion;
    offset += 1;
    /* ִ�б�־ */
    pkg->msg_data[offset] = 0xAA;
    offset += 1;
    /* ���ݸ��س��� */
    pkg->msg_size = offset;
    return 0;
}

/*! \brief 
*      ��ʱ�ϱ�����
* \param pkg[IN]            - cj188�Ĳ��� 
* \param sys_params[IN]     - ϵͳ����
* \param run_params[IN]     - ���в���
*
* \note  
* 
*/
u8 app_report_request(CJ188Pkg *pkg, /*const*/ SysParams *sys_params, RunParams *run_params)
{
    u8 offset = 0;
    u32 sn_data = 0;
    u16 gn_data = 0;
    u16 data_first = 0xAAAA;
    u16 temp_set = 0;
    u16 temp = 0;
    s16 ave_temp_100 = 0;
    u32 com_ok = 0;
    u32 com_total = 0;
    
    /* -------------------û����Щ�̶��ĳ���------------------- */
    /* SN */
    sn_data = LittleANDBig_ModeCON4(&(sys_params->Device_SN));
    memcpy(&(pkg->sn), &(sn_data), sizeof(pkg->sn));
    /* GN */
    gn_data = LittleANDBig_ModeCON2(&(sys_params->Device_GN));
    memcpy(&(pkg->gn), &(gn_data), sizeof(pkg->gn));
    /* �������� */
    pkg->ctrl_code = 200;
    /* ������ */
    offset = 0;
    memcpy(pkg->msg_data+offset, &data_first, sizeof(data_first));
    offset += sizeof(data_first);
    /* �¶����ñ�־λ */
    pkg->msg_data[offset] = sys_params->sys_set_temp_flg;
    offset += 1;
    /* �趨�¶� */
    temp_set = sys_params->temp_set;  
    temp_set = LittleANDBig_ModeCON2(&(temp_set));
    memcpy(pkg->msg_data+offset, &(temp_set), sizeof(sys_params->temp_set));
    offset += sizeof(sys_params->temp_set);
    /* ��ǰ�����¶� */
    temp = run_params->temp;       
    temp = LittleANDBig_ModeCON2(&(temp));
    memcpy(pkg->msg_data+offset, &(temp), sizeof(run_params->temp));
    offset += sizeof(run_params->temp);
    /* ����ƽ���¶� */
    ave_temp_100 = LittleANDBig_ModeCON2(&(run_params->ave_temp_100));
    memcpy(pkg->msg_data+offset, &(ave_temp_100), sizeof(run_params->ave_temp_100));
    offset += sizeof(run_params->ave_temp_100);
    /* ���״̬ */
    pkg->msg_data[offset] = run_params->face_state;
    offset += 1;
    /* ͨѶ�ɹ����� */      
    com_ok = LittleANDBig_ModeCON4(&(sys_params->com_ok));
    memcpy(pkg->msg_data+offset, &(com_ok), sizeof(sys_params->com_ok));
    offset += sizeof(sys_params->com_ok);
    /* ͨѶ�ܴ��� */      
    com_total = LittleANDBig_ModeCON4(&(sys_params->com_total));
    memcpy(pkg->msg_data+offset, &(com_total), sizeof(sys_params->com_total));
    offset += sizeof(sys_params->com_total);
    /* ���������־ */
    if (sys_params->temp_set >= run_params->temp)
    {
      run_params->actionflag = 0x0A;
      run_params->valve_position = 0x0A;
    }
    else
    {
      run_params->actionflag = 0xA0;
      run_params->valve_position = 0xA0;
    }
    pkg->msg_data[offset] = run_params->actionflag;
    offset += 1;
    /* ���ݸ��س��� */
    pkg->msg_size = offset;
    return 0;
    
    
//////    //    int i = 0;
//////    // �Ǳ��ַ
//////    memcpy(pkg->addr, sys_params->addr, sizeof(pkg->addr));
//////    
//////    //    for(i=0; i<5; i++)
//////    //    {
//////    //        printf("pkg->addr1111111 = %x\r\n" ,sys_params->addr[i]);
//////    //    }
//////    
//////    // ������
//////    pkg->ctrl_code = CTRL_CODE_REPORT;
//////    // ���ݸ���
//////    offset = 0;
//////    // �����¶�
//////    ////#if 0
//////    ////    dec_2_bcd_type(pkg->msg_data+offset, 2, 235, ORD_INTEL);
//////    ////#else
//////    dec_2_bcd_type(pkg->msg_data+offset, 2, run_params.temp, ORD_INTEL);
//////    ////#endif
//////    offset += 2;
//////    // �趨�¶�
//////    //dec_2_bcd_type(pkg->msg_data+offset, 2, run_params.temp_return, ORD_INTEL);
//////    //printf("run_params.temp_return = %d\r\n" ,run_params.temp_return);
//////    //dec_2_bcd_type(pkg->msg_data+offset, 2, run_params.temp_return, ORD_INTEL);
//////    dec_2_bcd_type(pkg->msg_data+offset, 2, sys_params->temp_set, ORD_INTEL);
//////    //printf("pkg->msg_data+offset = %d\r\n" ,dec_2_bcd_type(pkg->msg_data+offset, 2, run_params.temp_return, ORD_INTEL));
//////    offset += 2;
//////    // ����ģʽ
//////    pkg->msg_data[offset] = 0;
//////    offset += 1;
//////    // ��ص�ѹ
//////    //printf("run_params.batt_lvl = %d\r\n" ,run_params.batt_lvl);
//////    dec_2_bcd_type(pkg->msg_data+offset, 2, run_params.batt_lvl, ORD_INTEL);
//////    offset += 2;
//////    // ������
//////    pkg->msg_data[offset] = 0;
//////    offset += 1;
//////    // ST
//////    dec_2_hex_type(pkg->msg_data+offset, 2, run_params.st, ORD_INTEL);
//////    offset += 2;
//////    // ���ݸ��س���
//////    pkg->msg_size = offset;
//////
//////    
//////    return 0;
}

/*! \brief 
*      ����ǰ���÷���ID����
* \param pkg[IN]            - cj188�Ĳ��� 
* \param sys_params[IN]     - ϵͳ����
* \param run_params[IN]     - ���в���
* \param ack[IN]            - �������ݱ�־
*
* \note  
* 
*/
u8 app_factory_report_response(CJ188Pkg *pkg, SysParams *sys_params, RunParams *run_params, u8 *ack)
{  	
//    char factory_sn[4] = {0xAA, 0xAA, 0xAA, 0xAA};
    char factory_gn[2] = {0x00, 0x00};
    
    // SN���
//    printf("pkg->sn = %lu\r\n", pkg->sn);
//    if (memcmp(&pkg->sn, factory_sn, sizeof(pkg->sn)) != 0)
//    {
//        return CJ188_ERR_ADDR;
//    }
    
    // GN���
    if (memcmp(&pkg->gn, factory_gn, sizeof(pkg->gn)) != 0)
    {
        return CJ188_ERR_ADDR;
    }
    
    //    int i = 0;
    //    for(i=0; i<5; i++)
    //    {
    //        printf("pkg->addr = %x\r\n" ,g_sys_params.addr[i]);
    //    }
    
    // ������
    if (pkg->ctrl_code != 0)
    {
        return CJ188_ERR_CTRL_CODE;
    }
    
    return app_factory_response(pkg, sys_params, run_params, ack);
}

/*! \brief 
*      ����ǰ���÷���ID����
* \param pkg[IN]           - ����������ݱ���
* \param sys_params[OUT]   - ϵͳ����
* \param run_params[OUT]   - ���в���
* 
* \return  
* \note  
*      �ú�������鱨�ĺϷ��ԣ�����֮ǰ��Ҫ��鱨�ĺϷ���
* 
*/
u8 app_factory_response(CJ188Pkg *pkg, SysParams *sys_params, RunParams *run_params, u8 *ack)
{
    u8 offset = 0;
    
    u32 Device_SN = 0;
    u16 Device_GN = 0;
    
    if (pkg->msg_size < 8)
        return CJ188_ERR_LENGTH;
    
    //printf("Resport Success\r\n");
    
    offset = 0;
    /* �豸��SN,���д洢 */
    memcpy(&Device_SN, pkg->msg_data+offset, sizeof(sys_params->Device_SN)); 
    Device_SN = LittleANDBig_ModeCON4(&Device_SN);
    memcpy(&sys_params->Device_SN, &Device_SN, sizeof(sys_params->Device_SN)); 
    offset += 4;
    /* �豸��GN,���д洢 */
    memcpy(&Device_GN, pkg->msg_data+offset, sizeof(sys_params->Device_GN)); 
    Device_GN = LittleANDBig_ModeCON2(&Device_GN);
    memcpy(&sys_params->Device_GN, &Device_GN, sizeof(sys_params->Device_GN)); 
    offset += 2;
    /* Ӳ���汾 */
    sys_params->hardware_persion = pkg->msg_data[offset];
    offset += 1;
    /* ����汾 */
    sys_params->soft_persion = pkg->msg_data[offset];
    
    return 0;
}

/*! \brief 
*      ��ʱ�ϱ�����
* \param pkg[IN]            - cj188�Ĳ��� 
* \param sys_params[IN]     - ϵͳ����
* \param run_params[IN]     - ���в���
* \param ack[IN]            - �������ݱ�־
*
* \note  
* 
*/
u8 app_report_response(CJ188Pkg *pkg, SysParams *sys_params, RunParams *run_params, u8 *ack)
{  	
  
    // GN���
    if (memcmp(&pkg->sn, &sys_params->Device_SN, sizeof(pkg->gn)) != 0)
    {
        return CJ188_ERR_ADDR;
    }
    
    //    int i = 0;
    //    for(i=0; i<5; i++)
    //    {
    //        printf("pkg->addr = %x\r\n" ,g_sys_params.addr[i]);
    //    }
    
    // ������
    if (pkg->ctrl_code != 201)
    {
        return CJ188_ERR_CTRL_CODE;
    }
    
    return app_normal_response(pkg, sys_params, run_params, ack);
    
//////    // ��ַ����
//////    if (memcmp(pkg->addr, sys_params->addr, sizeof(pkg->addr)) != 0)
//////    {
//////        return CJ188_ERR_ADDR;
//////    }
//////    
//////    //    int i = 0;
//////    //    for(i=0; i<5; i++)
//////    //    {
//////    //        printf("pkg->addr = %x\r\n" ,g_sys_params.addr[i]);
//////    //    }
//////    
//////    // ������
//////    if (pkg->ctrl_code != (CTRL_CODE_REPORT | 0x80))
//////    {
//////        return CJ188_ERR_CTRL_CODE;
//////    }
//////    
//////    return app_normal_response(pkg, sys_params, run_params, ack);
}

/*! \brief 
*      ���淴��
* \param pkg[IN]           - ����������ݱ���
* \param sys_params[OUT]   - ϵͳ����
* \param run_params[OUT]   - ���в���
* 
* \return  
* \note  
*      �ú�������鱨�ĺϷ��ԣ�����֮ǰ��Ҫ��鱨�ĺϷ���
* 
*/
u8 app_normal_response(CJ188Pkg *pkg, SysParams *sys_params, RunParams *run_params, u8 *ack)
{
//////    u8 i = 0;
//////    u8 tmp[8] = {0};
//////    u8 offset = 0;
//////    u8 flag = 0;
//////    s32 balance = 0;
//////    g_sys_params.sn_recharge = 0;
//////    //char room_name[7] = {0};
    u8 offset = 0;
    u32 heating_time = 0;
    u32 heating_quantity = 0;
    u16 year = 0;
    u16 temp_set = 0;
    u16 limte_te_value = 0;
    struct tm t;
    
    if (pkg->msg_size < 27)
        return CJ188_ERR_LENGTH;
    
    //printf("Resport Success\r\n");
    
    
    offset = 0;
    /* ���ط�����λ�� */
    run_params->valve_position = pkg->msg_data[offset];
    offset += 1;
    /* ���ط�����״̬ */
    run_params->valve_state = pkg->msg_data[offset];
    offset += 1;
    /* ���Ŷ�ת״̬ */
    run_params->valve_lockstate = pkg->msg_data[offset];
    offset += 1;
    /* �ۼƿ���ʱ�� */
    memcpy(&heating_time, pkg->msg_data+offset, sizeof(sys_params->heating_time)); 
    heating_time = LittleANDBig_ModeCON4(&heating_time);//�ۼƿ���ʱ��
    memcpy(&sys_params->heating_time, &heating_time, sizeof(sys_params->heating_time)); 
    offset += 4;
    /* �ۼ����� */
    memcpy(&heating_quantity, pkg->msg_data+offset, sizeof(sys_params->heating_quantity)); 
    heating_quantity = LittleANDBig_ModeCON4(&heating_quantity);
    memcpy(&sys_params->heating_quantity, &heating_quantity, sizeof(sys_params->heating_quantity)); 
    offset += 4;
    /* ����-�� */
    memcpy(&year, pkg->msg_data+offset, sizeof(run_params->year)); 
    year = LittleANDBig_ModeCON2(&year);
    memcpy(&run_params->year, &year, sizeof(run_params->year));
    offset += 2;
    /* ����-�� */
    run_params->month = pkg->msg_data[offset];
    offset += 1;
    /* ����-�� */
    run_params->day = pkg->msg_data[offset];
    offset += 1;
    /* ����-ʱ */
    run_params->hour = pkg->msg_data[offset];
    offset += 1;
    /* ����-�� */
    run_params->minute = pkg->msg_data[offset];
    offset += 1;
    /* ����-�� */
    run_params->second = pkg->msg_data[offset];
    offset += 1;
    /* ����-�� */
    run_params->week = pkg->msg_data[offset];
    offset += 1;
    t.tm_year = run_params->year-2000;
    t.tm_mon  = run_params->month;
    t.tm_mday = run_params->day;
    t.tm_hour = run_params->hour;
    t.tm_min  = run_params->minute;
    t.tm_sec  = run_params->second;
    t.tm_week = run_params->week;
    rtc_write(t);   //��ʱ��д��ȥ
    /* �Ƿ��ڹ�ů�� */
    sys_params->workflg = pkg->msg_data[offset];
    offset += 1;
    /* ϵͳ�����¶���Ч��־λ */
    sys_params->sys_set_temp_flg = pkg->msg_data[offset];
    offset += 1;
    /* �趨�¶� */
    if (sys_params->sys_set_temp_flg == 0xAA)
    {
      memcpy(&temp_set, pkg->msg_data+offset, sizeof(sys_params->temp_set)); 
      temp_set = LittleANDBig_ModeCON2(&temp_set);
      temp_set *= 10;
      memcpy(&sys_params->temp_set, &temp_set, sizeof(sys_params->temp_set));
    }
    offset += 2;
    /* Ƿ�ѱ�־ */
    run_params->arrears_state = pkg->msg_data[offset];
    offset += 1;
    /* �����¶����ñ�־ */
    sys_params->limte_te_flag = pkg->msg_data[offset];
    offset += 1;
    if (sys_params->limte_te_flag == 0xAA)      
    {
      /* �����¶Ⱦ����趨���µ����� */
      memcpy(&limte_te_value, pkg->msg_data+offset, sizeof(limte_te_value));       // 2���ֽ�
      limte_te_value = LittleANDBig_ModeCON2(&limte_te_value);
      limte_te_value = limte_te_value / 100;
      memcpy(&sys_params->temp_room_uplimits, &limte_te_value+1, sizeof(sys_params->temp_room_uplimits));   // 1���ֽ�,ȡ���ֽ�
    }
    
    return 0;
    
//////    offset = 0;
//////    
//////    // ���ۼ�����
//////    memcpy(tmp, pkg->msg_data+offset, 4); //memcpy������ǰ��λ�ǵ�ַ
//////    sys_params->heating_quantity = bcd_2_dec_type(tmp, 4, ORD_INTEL); //sys_params�ǵ�ַָ��ṹ����ĳ�Ա
//////    offset += 4; //offsetΪ��ַƫ����,Ϊ�ð���ĵ�ַ�ı�
//////    
//////    // ���ۼ�������λ
//////    sys_params->heating_quantity_unit = pkg->msg_data[offset];
//////    offset += 1;
//////    
//////    // ���ۼ��ȷ�
//////    memcpy(tmp, pkg->msg_data+offset, 4);
//////    sys_params->heating_cost_total = bcd_2_dec_type(tmp, 4, ORD_INTEL);
//////    offset += 4;
//////    
//////    // ���ۼ�ʱ��
//////    memcpy(tmp, pkg->msg_data+offset, 3);
//////    sys_params->heating_time = bcd_2_dec_type(tmp, 3, ORD_INTEL);
//////    offset += 3;
//////    
//////    // ���ۼ�����
//////    memcpy(tmp, pkg->msg_data+offset, 4);
//////    sys_params->heating_quantity_day = bcd_2_dec_type(tmp, 4, ORD_INTEL);
//////    offset += 4;
//////    
//////    // ���ۼ�������λ
//////    sys_params->heating_quantity_day_unit = pkg->msg_data[offset];
//////    offset += 1;
//////    
//////    // ���ۼ��ȷ�
//////    memcpy(tmp, pkg->msg_data+offset, 4);
//////    sys_params->heating_cost_day = bcd_2_dec_type(tmp, 4, ORD_INTEL);
//////    offset += 4;
//////    
//////    // ���ۼ�ʱ��
//////    memcpy(tmp, pkg->msg_data+offset, 3);
//////    sys_params->heating_time_day = bcd_2_dec_type(tmp, 3, ORD_INTEL);
//////    offset += 3;
//////    
//////    // ���
//////    memcpy(tmp, pkg->msg_data+offset, 4);
//////    if ((tmp[3]&0x80) == 0)
//////    {
//////        // ��ֵ���
//////        balance = (long)bcd_2_dec_type(tmp, 4, ORD_INTEL);
//////        //printf("[2]balance:%ld\r\n", balance);
//////        
//////        sys_params->balance = balance;
//////    }
//////    else
//////    {
//////        // ��ֵ���
//////        tmp[3] &= ~0x80;
//////        balance = (long)bcd_2_dec_type(tmp, 4, ORD_INTEL);
//////        balance *= -1;
//////        
//////        sys_params->balance = balance;
//////    }
//////    offset += 4;
//////    
//////    // ��λ
//////    if (pkg->msg_data[offset]==UNIT_KWH || pkg->msg_data[offset]==UNIT_GJ)
//////    {
//////        sys_params->balance_unit = pkg->msg_data[offset];
//////    }
//////    else
//////    {
//////        sys_params->balance_unit = UNIT_KWH;        
//////    }
//////    offset += 1;    
//////    
//////    // ϵͳʱ��
//////    memcpy(tmp, pkg->msg_data+offset, 7);
//////    bytes_reverse(tmp, 7);//����rtc_write_bcd����ҪBCD�룬���Բ���Ҫת��
//////    //run_params->date[0] = bcd_2_dec_type(tmp, 7, ORD_INTEL);
//////    
//////    // ͬ��ʱ�� 
//////    rtc_write_bcd(tmp, 7);
//////    //rtc_write_bcd(run_params->date, 7);
//////    offset += 7;
//////    
//////    // ״̬ST
//////    memcpy(tmp, pkg->msg_data+offset, 2);    
//////    run_params->st = bcd_2_dec_type(tmp, 2, ORD_INTEL);
//////    offset += 2;
//////    
//////    //printf("ST:%04X\r\n", run_params->st);
//////    
//////    // �������ݱ�־λ
//////    flag = pkg->msg_data[offset];
//////    offset += 1;
//////#ifdef TASK_PRINTF    
//////    MYLOG_DEBUG("FLAG:%02x\r\n", flag);
//////#endif
//////    // ��Ҫ����
//////    if (flag != 0)
//////    {
//////        *ack = 1;
//////        //printf("ack22222222222222222222222222222222222:%d\r\n", *ack);
//////    }
//////    
//////    //MYLOG_DEBUG("FLAG:%02X\r\n", flag);    
//////    
//////    for (i=0; i<8; ++i)
//////    {
//////        if (flag&0x01)  //��flagһֱ����ʲôʱ��Ϊ0ʱ֤�����λΪ1�ˣ��ƶ���λ����Ϊi�Ĵ�С
//////        {
//////            switch(i)
//////            {
//////            case AD_IDX_HP:
//////                // ��ů��ʼʱ��
//////                sys_params->heating_period_st[1] = pkg->msg_data[offset++];
//////                sys_params->heating_period_st[0] = pkg->msg_data[offset++];
//////                // ��ů����ʱ��
//////                sys_params->heating_period_et[1] = pkg->msg_data[offset++];
//////                sys_params->heating_period_et[0] = pkg->msg_data[offset++];
//////                
//////                //printf("g_sys_params.heating_period_st = %d\r\n" ,g_sys_params.heating_period_st);
//////                //printf("g_sys_params.heating_period_et = %d\r\n" ,g_sys_params.heating_period_et);
//////                //printf("HP[%02X-%02X/%02X-%02X]\r\n", sys_params->heating_period_st[0], sys_params->heating_period_st[1], sys_params->heating_period_et[0], sys_params->heating_period_et[1]);
//////                break;
//////            case AD_IDX_TEMP_SET:
//////                //printf("TEMP_SET[%X%02X]\r\n", pkg->msg_data[offset+1], pkg->msg_data[offset]);
//////                sys_params->temp_set = bcd_2_dec_type(pkg->msg_data+offset, 2, ORD_INTEL);
//////                offset += 2;
//////                
//////                
//////                //                printf("g_sys_params.temp_room_uplimits = %d\r\n" ,g_sys_params.temp_room_uplimits);
//////                //                printf("g_sys_params.temp_room_lowlimits = %d\r\n" ,g_sys_params.temp_room_lowlimits);
//////                if (sys_params->temp_set > sys_params->temp_room_uplimits*10)
//////                {
//////                    sys_params->temp_set = sys_params->temp_room_uplimits*10;
//////                }
//////                else if (sys_params->temp_set < sys_params->temp_room_lowlimits*10)
//////                {
//////                    sys_params->temp_set = sys_params->temp_room_lowlimits*10;
//////                }
//////                
//////                //printf("TEMP_SET[%u]\r\n", sys_params->temp_set);
//////                
//////                break;
//////            case AD_IDX_TEMP_SET_LIMITS:
//////                // �¶��趨����
//////                sys_params->temp_room_uplimits   = pkg->msg_data[offset++];
//////                // �¶��趨����
//////                sys_params->temp_room_lowlimits  = pkg->msg_data[offset++];
////////                printf("2222222222222222222222222222222222222222222");
////////                printf("sys_params->temp_set = %d\r\n", sys_params->temp_set);
////////                printf("sys_params->temp_room_uplimits = %d\r\n", sys_params->temp_room_uplimits);
//////                //�¶������޸ı����Ҫ���¼��㵵λ
//////                if (sys_params->temp_set > sys_params->temp_room_uplimits*10)
//////                {
//////                    //sys_params->temp_set = sys_params->temp_room_uplimits*10;
//////                    //printf("1111111111111111111111111111111111111");
//////                    sys_params->temp_set = sys_params->temp_room_uplimits*10;
//////                    run_params->temp_return = sys_params->temp_set;
//////                    //printf("run_params->temp_return = %u\r\n" ,run_params->temp_return);
//////                }
//////                else if (sys_params->temp_set < sys_params->temp_room_lowlimits*10)
//////                {
//////                    sys_params->temp_set = sys_params->temp_room_lowlimits*10;
//////                    run_params->temp_return = sys_params->temp_set;
//////                }
//////                
//////                //printf("TEMP_SET_LIMITS[%u, %u]\r\n", sys_params->temp_room_uplimits, sys_params->temp_room_lowlimits);
//////                break;
//////            case AD_IDX_RECHARGE:              
//////                sys_params->sn_recharge = bcd_2_dec_type(pkg->msg_data+offset, 4, ORD_INTEL);
//////                offset += 4;
//////                
//////                //printf("RECHARGE[%u]\r\n", sys_params->sn_recharge);
//////                break;
//////            case AD_IDX_BALANCE_LINMITS:
//////                sys_params->balance_alarm = pkg->msg_data[offset++];
//////                
//////                //printf("BALANCE_LINMITS[%u]\r\n", sys_params->balance_alarm);
//////                break;
//////            case AD_IDX_DISP_CTL:
//////                sys_params->disp_ctl = pkg->msg_data[offset++];
//////                
//////                //printf("DISPLAY_CTRL[%02X]\r\n", sys_params->disp_ctl);
//////                break;
//////            case AD_IDX_ROOM_NAME:
//////                //sprintf(room_name, "%X-%X%02X", pkg->msg_data[offset+2], pkg->msg_data[offset+1], pkg->msg_data[offset]);
//////                room_name[0] = (pkg->msg_data[offset+2]%0x0f)+'0';
//////                room_name[1] = '-';
//////                if ((pkg->msg_data[offset+1]>>4) > 0)
//////                {
//////                    room_name[2] = (pkg->msg_data[offset+1]>>4)+'0';
//////                    room_name[3] = (pkg->msg_data[offset+1]%0x0f)+'0'; 
//////                    room_name[4] = (pkg->msg_data[offset+0]>>4)+'0';
//////                    room_name[5] = (pkg->msg_data[offset+0]%0x0f)+'0';            
//////                }
//////                else
//////                {
//////                    room_name[2] = (pkg->msg_data[offset+1]%0x0f)+'0';    
//////                    room_name[3] = (pkg->msg_data[offset+0]>>4)+'0';
//////                    room_name[4] = (pkg->msg_data[offset+0]%0x0f)+'0';  
//////                    room_name[5] = '\0';
//////                }                
//////                
//////                memcpy(sys_params->room_name, room_name, sizeof(sys_params->room_name));
//////                offset += 3;
//////                
//////                //printf("ROOM_NAME[%s]\r\n", sys_params->room_name);
//////                break;
//////            default:
//////                break;
//////            }
//////        }
//////        
//////        flag >>= 1;
//////    }
//////    
//////    return 0;
}

/*! \brief 
*      ȷ�Ϸ���
* \param pkg[IN]           - ����������ݱ���
* \param sys_params[OUT]   - ϵͳ����
* \param run_params[OUT]   - ���в���
* 
* \return  
* \note  
*      
* 
*/
u8 app_ack_request(CJ188Pkg *pkg, const SysParams *sys_params, RunParams run_params)
{
    // �Ǳ��ַ
    memcpy(pkg->addr, sys_params->addr, sizeof(pkg->addr));
    // ������
    pkg->ctrl_code = CTRL_CODE_ACK;
    // �����򳤶�
    pkg->msg_size  = 0x00;
    
    return 0;
}