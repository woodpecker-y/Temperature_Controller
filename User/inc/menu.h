#ifndef _MENU_H
#define _MENU_H

/*! \brief �˵����� */
typedef enum _Menu{
    MENU_MAIN = 0,  //��ʾ������
    MENU_SET_TEMP,  //�趨�¶�
    MENU_VIEW,      //�˵�
    MENU_ID,        //����ID
}Menu;

/*! \brief ��Ϣ�鿴���� */
typedef enum _MenuViewIdx{
    MENU_VIEW_IDX_TEMP=0,                       // ����
    MENU_VIEW_IDX_TEMP_SET,                     // �趨�¶�
//    MENU_VIEW_IDX_BALANCE,                      // ʣ������   
    MENU_VIEW_IDX_HEATING_QUANTITY_TOTAL,       // �ۼ�����
    MENU_VIEW_IDX_HEATING_TIME_TOTAL,           // ����ʱ��
    MENU_VIEW_IDX_FAULT,                        // ���� 
    MENU_VIEW_IDX_ROOM_ID,			// �����	
    MENU_VIEW_IDX_ID_LEFT,                      // ID LEFT 
    MENU_VIEW_IDX_ID_RIGHT,		        // ID Right	
    MENU_VIEW_IDX_TIME,                         // ʱ��
}MenuViewIdx;

/* �����¶� */
void menu_set_temp(void);
/* һֱ�����ʾ */
void menu_common(void);
/* ����Ļ��ʾ�¶� */
void menu_main(void);
/* ����ID */
void menu_ID(void);
/* ��ʾѡ�� */
void menu_disp(u8 menu_id);
/* �˵� */
void menu_view(void);
/* ��ص�����ѡ�� */
void batter_value(void);

#endif