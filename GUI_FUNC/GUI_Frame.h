#include "GUI.h"
#include "main.h"
#include "stm32f407xx.h"
#include "ILI93xx.h"

typedef enum {
  MENU_NONE,
  MENU_NRF,
  MENU_CAN,
  MENU_USART,
  MENU_MOTOR,
  MENU_XY,
  MENU_OTHER,

  MENU_ROBOT_VARI,
  MENU_ROBOT_SENSOR,
  MENU_ROBOT_POS,
  MENU_ROBOT_CAN,
  MENU_ROBOT_TEST,
  MENU_ROBOT_OTHER,

} MENU_STATE;
extern MENU_STATE now_state ;
extern MENU_STATE show_state;
extern int time_1s_flag;
extern int time_1s_cnt;
extern int time_1ms_cnt;

void drawCoordiantes(int x0,int y0,int x1,int y1);//����xy����ϵ
void drawMainFrame(void);//���������
void menu_function(void);//�����л�����
void menu_update(MENU_STATE state,int mode);//���ڸ���
void menu_pageup(void);//�����Ϸ�ҳ
void menu_pagedown(void);//�����·�ҳ
void menu_clear_window(void);//�������
void show_time(signed short x,signed short y);//ʱ����ʾ
void show_system_time(void);
void usart_window_update(char *text);//���ڿ�����ʾ
void can_window_update(uint32_t Std_ID,uint8_t aData[]);//can������ʾ
void GUI_main();//GUI������
void GUI_Reload();//���³�ʼ����Ļ���������ʱ�ָ���ʾ
void draw_point_onMap(float x,float y);//��XYͼ�ϻ���
void show_rate();//��ʾ��������
void clear_rate();//ÿ�����һ�����ʼ�¼

//lsw
void test_pos();//nrfȫ����λ��ʾ��������
