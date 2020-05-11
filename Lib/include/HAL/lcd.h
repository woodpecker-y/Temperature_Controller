#ifndef _LCD_H
#define _LCD_H

#ifdef HAVE_LCD_ST7565R

// �ַ��������
#define E_TYPE_IDX_CHAR	0
#define E_TYPE_IDX_WORD	1

typedef struct _FontAttr{
	u8		type;
	u8		width;
	u8		height;
	u8		size;
}FontAttr;

/*! \brief
*       ����LCD���ò���
* \param type[IN]		- Һ������
* \param cfg[IN]		- ���þ��
*/
void lcd_load_config(void *cfg);

/*! \brief
*       LCD��ʼ��
*/
void lcd_init(void);

/*! \brief
*       �ر�LCD��ʾ
* \param type[IN]		- Һ������
* \param cfg[IN]		- ���þ��
*/
void lcd_close(void);

/*! \brief
*       ����LCD����
* \param sts[IN]		- ����
*		LCD_BACKLIGHT_OFF-�أ�
*		LCD_BACKLIGHT_ON-��
*/
void lcd_set_backlight(u8 sts);

/*! \brief
 *       ������ʾ����
 * \param char_type[IN]		- ASCII������
 * \param word_type[IN]		- ��������
 * \notes
 * \	�������ڵ���Һ��
 */
void lcd_set_font(u8 char_type, u8 word_type);

/*! \brief
 *       ������ʾģʽ
 * \param mode[IN]		- ������ʾģʽ
 * \notes
 * \	�������ڵ���Һ��
 */
void lcd_set_mode(u8 mode);

/*! \brief
 *       ��ʾһ���ַ�
 * \param x[IN]		- X����
 * \param y[IN]		- Y����
 * \param ch[IN]		- ��С
 * \notes
 * \	�������ڵ���Һ��
 */
void lcd_disp_char(unsigned int x, unsigned int y, unsigned int ch);

/*! \brief 
 *		LCD��ʾ�ַ���
 * 
 * \param x[IN]			- ����X
 * \param y[IN]			- ����Y
 * \param str[IN]		- ��ʾ�ַ��� 
 * \notes
 * \	�������ڵ���Һ��
 */
void lcd_draw_str(unsigned int x, unsigned int y, const unsigned char *str);

/*! \brief 
 *		LCD���ָ����������
 * 
 * \param line[IN]			- ������0~3
 * \param col[IN]			- ������0~20
 * \param width[IN]			- ��ȣ�0~20
 * \param height[IN]		- �߶ȣ�0~3
 * \notes
 * \	�������ڵ���Һ��
 */
void lcd_disp_line_clear(unsigned char line, unsigned char col, unsigned char width, unsigned char height);

/*! \brief ���� */
void lcd_disp_clrscr(void);

/*! \brief 
 *		��ʾһ����Ϣ������
 * 
 * \param line[IN]		- �к�
 * \param col[IN]		- �к�
 * \param width[IN]		- ���
 * \param height[IN]	- �߶�
 * \param pdata[IN]		- �ַ���
 * \notes
 * \	�������ڵ���Һ��
 */
void lcd_disp_line(unsigned char line, unsigned char col, unsigned char width, unsigned char height, const char *pdata);

/*! \brief 
 *		LCD��ʾ�ַ��������У�
 * 
 * \param line[IN]		- �к�
 * \param col[IN]		- �к�
 * \param width[IN]		- ���
 * \param pdata[IN]		- �ַ���
 * \notes
 * \	�������ڵ���Һ��
 */
void lcd_disp_line_center(unsigned char line, unsigned char col, unsigned char width, const char *pdata);


/*! \brief 
 *		LCD��ʾһ�����ݣ����ң�
 * 
 * \param line[IN]		- �к�
 * \param col[IN]		- �к�
 * \param width[IN]		- ���	
 * \param pdata[IN]		- �ַ���
 * \notes
 * \	�������ڵ���Һ��
 */
void lcd_disp_line_right(unsigned char line, unsigned char col, unsigned char width, const char *pdata);

/*! \brief 
 *		LCD��ʾͼƬ
 * 
 * \param x[IN]				- X������
 * \param y[IN]				- Y������
 * \param width[IN]			- ���
 * \param height[IN]		- �߶�
 * \param bitmap[IN]		- λͼ
 * \notes
 * \	�������ڵ���Һ��
 */
void lcd_disp_bitmap(unsigned char x, unsigned char y, unsigned char width, unsigned char height, const unsigned char *bitmap);

#elif defined(HAVE_LCD) || defined(HAVE_LCD_EXT)

void lcd_load_config(void *cfg);

void lcd_power_on(void);

void lcd_power_off(void);

void lcd_init(void);

void lcd_close(void);

void lcd_write_seg(unsigned char *disp_buf, unsigned char seg_id, unsigned char mode);

void lcd_update_screen(unsigned char *disp_buf, unsigned int size);

#endif

#endif

