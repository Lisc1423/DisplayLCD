#include "GUI_Frame.h"
#include "main.h"
#include "Lcd_Top.h"
#include "frame_func.h"

MENU_STATE now_state = 1;
MENU_STATE show_state = 1;

int time_1s_flag = 0;
int time_1s_cnt = 0;
int time_1ms_cnt = 0;
uint8_t usart_text_cnt = 0;
uint32_t usart_rx_rate = 0;
uint8_t can_text_cnt = 0;
uint32_t can_rx_rate = 0;

extern GUI_BITMAP bmroboconnew;
void show_robocon_image(){
  GUI_DrawBitmapEx(&bmroboconnew, 90, 100, 0, 0, 800, 800);
}
extern GUI_BITMAP bmmap;
void show_robocon_map(){
  GUI_DrawBitmap(&bmmap, 80, 20);
}
//绘制坐标系
void drawCoordiantes(int x0, int y0, int x1, int y1){
  int i, j;
  GUI_SetColor(GUI_LIGHTGREEN);
  GUI_SetBkColor(GUI_BLACK);
  GUI_SetPenSize(1);
  for (i = x0 + 20; i <= x1; i += 20)
    GUI_DrawLine(i, y0, i, y1);
  for (j = y0 + 20; j <= y1; j += 20)
    GUI_DrawLine(x0, j, x1, j);
  
  GUI_SetColor(GUI_WHITE);
  /*横轴坐标*/
  int count = 0;
  j = -4; //起始值
  for (i = x0 + 20; i <= x1; i += 20)
  {
    count++;
    if (count % 2 == 0)
      continue;
    GUI_SetFont(GUI_FONT_8_ASCII);
    GUI_SetTextMode(GUI_TM_NORMAL);
    if (j < 0)
      GUI_DispDecAt(j++, i + 8, (y0 + y1) / 2 + 5, 2); //15 and 10 are offset
    else
      GUI_DispDecAt(j++, i + 10, (y0 + y1) / 2 + 5, 1); //15 and 10 are offset
  }
  
  /*纵轴坐标*/
  count = 0;
  i = 4;
  for (j = y0 + 20; j <= y1; j += 20)
  {
    count++;
    if (count % 2 == 0)
      continue;
    GUI_SetFont(GUI_FONT_8_ASCII);
    GUI_SetTextMode(GUI_TM_NORMAL);
    if (i < 0)
      GUI_DispDecAt(i--, (x0 + x1) / 2 - 14, j - 16, 2); //15 and 10 are offset
    else
      GUI_DispDecAt(i--, (x0 + x1) / 2 - 9, j - 16, 1); //15 and 10 are offset
  }
  GUI_SetPenSize(3);
  GUI_SetColor(GUI_GREEN);
  GUI_DrawLine((x0 + x1) / 2, y0, (x0 + x1) / 2, y1);
  GUI_DrawLine(x0, (y0 + y1) / 2, x1, (y0 + y1) / 2);
  //GUI_DrawLine()
}
//绘制主界面
GUI_RECT menu1Rect = {0, 20, 79, 69};
GUI_RECT menu2Rect = {0, 70, 79, 119};
GUI_RECT menu3Rect = {0, 120, 79, 169};
GUI_RECT menu4Rect = {0, 170, 79, 219};
GUI_RECT menu5Rect = {0, 220, 79, 269};
GUI_RECT menu6Rect = {0, 270, 79, 319};
void drawMainFrame(){
  GUI_SetColor(GUI_WHITE);
  GUI_SetPenSize(3);
  GUI_DrawHLine(19, 0, 480);  //上横线
  GUI_DrawVLine(80, 19, 320); //左竖线
  GUI_DrawHLine(69, 0, 80);   //第一格
  GUI_DrawHLine(119, 0, 80);  //第二格
  GUI_DrawHLine(169, 0, 80);  //第三格
  GUI_DrawHLine(219, 0, 80);  //第四格
  GUI_DrawHLine(269, 0, 80);  //第五格
  GUI_DrawHLine(319, 0, 80);  //第六格
  
  if(lcd_place == 0){
  menu_update(MENU_NRF, GUI_TM_NORMAL);
  menu_update(MENU_CAN, GUI_TM_NORMAL);
  menu_update(MENU_USART, GUI_TM_NORMAL);
  menu_update(MENU_MOTOR, GUI_TM_NORMAL);
  menu_update(MENU_XY, GUI_TM_NORMAL);
  menu_update(MENU_OTHER, GUI_TM_NORMAL);
  }

  if(lcd_place == 1){
  menu_update(MENU_ROBOT_VARI, GUI_TM_NORMAL);
  menu_update(MENU_ROBOT_SENSOR, GUI_TM_NORMAL);
  menu_update(MENU_ROBOT_POS, GUI_TM_NORMAL);
  menu_update(MENU_ROBOT_CAN, GUI_TM_NORMAL);
  menu_update(MENU_ROBOT_TEST, GUI_TM_NORMAL);
  menu_update(MENU_ROBOT_OTHER, GUI_TM_NORMAL);
  }  
}
void menu_pagedown(){
  if(lcd_place==0){
  if (now_state == MENU_OTHER)
    show_state = MENU_NRF;
  else
    show_state = now_state + 1;
  }
  if(lcd_place==1){
  if (now_state == MENU_ROBOT_OTHER)
    show_state = MENU_ROBOT_VARI;
  else
    show_state = now_state + 1;
  }
}
void menu_pageup(){
  if(lcd_place == 0){
  if (now_state == MENU_NRF || now_state == 0)
    show_state = MENU_OTHER;
  else
    show_state = now_state - 1;
  }
  if(lcd_place == 1){
  if (now_state == MENU_ROBOT_VARI || now_state == 0)
    show_state = MENU_ROBOT_OTHER;
  else
    show_state = now_state - 1;
  }
  
}
void menu_update(MENU_STATE state, int mode){
  GUI_SetColor(GUI_WHITE);
  GUI_SetBkColor(GUI_BLACK);
  GUI_SetFont(GUI_FONT_8X16X2X2);
  GUI_SetTextMode(mode);
  switch (state){
  case MENU_NRF:{
      GUI_DispStringInRect("NRF", &menu1Rect, GUI_TA_VCENTER | GUI_TA_HCENTER);
      break;
    }
  case MENU_CAN:{
      GUI_DispStringInRect("CAN", &menu2Rect, GUI_TA_VCENTER | GUI_TA_HCENTER);
      break;
    }
  case MENU_USART:{
      GUI_DispStringInRect("USART", &menu3Rect, GUI_TA_VCENTER | GUI_TA_HCENTER);
      break;
    }
  case MENU_MOTOR:{
      GUI_DispStringInRect("MOTOR", &menu4Rect, GUI_TA_VCENTER | GUI_TA_HCENTER);
      break;
    }  
  case MENU_XY:{
      GUI_DispStringInRect("X-Y", &menu5Rect, GUI_TA_VCENTER | GUI_TA_HCENTER);
      break;
    }
  case MENU_OTHER:{
      GUI_DispStringInRect("OTHER", &menu6Rect, GUI_TA_VCENTER | GUI_TA_HCENTER);
      break;
    }
 //mode 2
  case MENU_ROBOT_VARI:{
      GUI_DispStringInRect("VAR ", &menu1Rect, GUI_TA_VCENTER | GUI_TA_HCENTER);
      break;
    }
  case MENU_ROBOT_SENSOR:{
      GUI_DispStringInRect("SESOR", &menu2Rect, GUI_TA_VCENTER | GUI_TA_HCENTER);
      break;
    }
  case MENU_ROBOT_POS:{
      GUI_DispStringInRect("POS", &menu3Rect, GUI_TA_VCENTER | GUI_TA_HCENTER);
      break;
    }
  case MENU_ROBOT_CAN:{
      GUI_DispStringInRect("CAN", &menu4Rect, GUI_TA_VCENTER | GUI_TA_HCENTER);
      break;
    }  
  case MENU_ROBOT_TEST:{
      GUI_DispStringInRect("TEST", &menu5Rect, GUI_TA_VCENTER | GUI_TA_HCENTER);
      break;
    }
  case MENU_ROBOT_OTHER:{
      GUI_DispStringInRect("OTHER", &menu6Rect, GUI_TA_VCENTER | GUI_TA_HCENTER);
      break;
    }
  default:
    break;
  }
}
void menu_clear_window(){
  GUI_SetBkColor(GUI_BLACK);
  GUI_ClearRect(81, 20, 479, 319);
}
void menu_function(){
  switch (show_state){
  case MENU_NONE:{
    if (now_state != MENU_NONE)
    {
      menu_update(now_state, GUI_TM_NORMAL);
      now_state = MENU_NONE;
      
    }
    break;
  }
  case MENU_NRF:{
    test_pos();      
    if (now_state != MENU_NRF)
    {
      menu_update(now_state, GUI_TM_NORMAL);
      now_state = MENU_NRF;
      menu_update(now_state, GUI_TM_REV);
      menu_clear_window();     
    }
    break;
  }  
  case MENU_CAN:{
    if (now_state != MENU_CAN)
    {
      menu_update(now_state, GUI_TM_NORMAL);
      now_state = MENU_CAN;
      menu_update(now_state, GUI_TM_REV);
      menu_clear_window();
    }
    break;
  }
  case MENU_USART:{
    if (now_state != MENU_USART)
    {
      menu_update(now_state, GUI_TM_NORMAL);
      now_state = MENU_USART;
      menu_update(now_state, GUI_TM_REV);
      menu_clear_window();
      usart_text_cnt = 0;
    }
    break;
  }
  case MENU_MOTOR:{
    if (now_state != MENU_MOTOR)
    {
      menu_update(now_state, GUI_TM_NORMAL);
      now_state = MENU_MOTOR;
      menu_update(now_state, GUI_TM_REV);
      menu_clear_window();
    }
    break;
  }
  case MENU_XY:{
    if (now_state != MENU_XY)
    {
      menu_update(now_state, GUI_TM_NORMAL);
      now_state = MENU_XY;
      menu_update(now_state, GUI_TM_REV);
      menu_clear_window();
      drawCoordiantes(81, 20, 479, 319 + 20); //因为中线没有对齐，增加了20的偏移量
    }
    break;
  }
  case MENU_OTHER:{
    if (now_state != MENU_OTHER)
    {
      menu_update(now_state, GUI_TM_NORMAL);
      now_state = MENU_OTHER;
      menu_update(now_state, GUI_TM_REV);
      menu_clear_window();
      show_robocon_map();
    }
    break;
  }
 //
  case MENU_ROBOT_VARI:{    
    if (now_state != MENU_ROBOT_VARI)
    {
      menu_update(now_state, GUI_TM_NORMAL);
      now_state = MENU_ROBOT_VARI;
      menu_update(now_state, GUI_TM_REV);
      menu_clear_window();
      GUI_DrawLine(280,20,280,319);
    }
    menu_robot_variable();
    break;
  }  
  case MENU_ROBOT_SENSOR:{
    if (now_state != MENU_ROBOT_SENSOR)
    {
      menu_update(now_state, GUI_TM_NORMAL);
      now_state = MENU_ROBOT_SENSOR;
      menu_update(now_state, GUI_TM_REV);
      menu_clear_window();
    }
    break;
  }
  case MENU_ROBOT_POS:{
    if (now_state != MENU_ROBOT_POS)
    {
      menu_update(now_state, GUI_TM_NORMAL);
      now_state = MENU_ROBOT_POS;
      menu_update(now_state, GUI_TM_REV);
      menu_clear_window();
    }
    break;
  }
  case MENU_ROBOT_CAN:{
    if (now_state != MENU_ROBOT_CAN)
    {
      menu_update(now_state, GUI_TM_NORMAL);
      now_state = MENU_ROBOT_CAN;
      menu_update(now_state, GUI_TM_REV);
      menu_clear_window();
    }
    break;
  }
  case MENU_ROBOT_TEST:{
    if (now_state != MENU_ROBOT_TEST)
    {
      menu_update(now_state, GUI_TM_NORMAL);
      now_state = MENU_ROBOT_TEST;
      menu_update(now_state, GUI_TM_REV);
      menu_clear_window();
    }
    break;
  }
  case MENU_ROBOT_OTHER:{
    if (now_state != MENU_ROBOT_OTHER)
    {
      menu_update(now_state, GUI_TM_NORMAL);
      now_state = MENU_ROBOT_OTHER;
      menu_update(now_state, GUI_TM_REV);
      menu_clear_window();
    }
    break;
  }
  default:
    break;
  }
}

void usart_window_update(char *text){
  usart_rx_rate = usart_rx_rate + sizeof(text);
  if (now_state != MENU_USART)
    return;
  if (usart_text_cnt == 0)
    menu_clear_window();
  GUI_SetBkColor(GUI_BLACK);
  GUI_SetColor(GUI_LIGHTGREEN);
  GUI_SetFont(GUI_FONT_8X18);
  show_time(81, 21 + 20 * usart_text_cnt);
  GUI_DispStringAtCEOL(text, 150, 21 + 20 * usart_text_cnt);
  usart_text_cnt++;
  if (usart_text_cnt == 15)
    usart_text_cnt = 0;
}
void can_window_update(uint32_t Std_ID, uint8_t aData[]){
  can_rx_rate++;
  if (now_state != MENU_CAN)
    return;
  if (can_text_cnt == 0)
    menu_clear_window();
  GUI_SetBkColor(GUI_BLACK);
  GUI_SetColor(GUI_LIGHTGREEN);
  GUI_SetFont(GUI_FONT_8X18);
  show_time(81, 21 + 20 * can_text_cnt);
  GUI_DispDecAt(Std_ID, 150, 21 + 20 * can_text_cnt, 9);
  //GUI_DispStringAt(pHeader->IDE, 150, 21 + 20 * can_text_cnt);
  GUI_DispStringAtCEOL(aData, 300, 21 + 20 * can_text_cnt);
  can_text_cnt++;
  if (can_text_cnt == 15)
    can_text_cnt = 0;
}
void show_time(signed short x, signed short y){
  GUI_SetColor(GUI_ORANGE);
  GUI_SetBkColor(GUI_BLACK);
  GUI_SetFont(GUI_FONT_8X18);

  GUI_SetTextMode(GUI_TM_NORMAL);
  GUI_DispDecAt(time_1s_cnt / 60, x + 15, y, 2);
  GUI_DispStringAt(":", x + 17 + 15, y);
  GUI_DispDecAt(time_1s_cnt % 60, x + 26 + 15, y, 2);
}
void show_system_time(){
  if (time_1s_flag){
    time_1s_cnt++;
    show_time(4, 0);
    clear_rate();
    time_1s_flag = 0;
  }
}
void draw_point_onMap(float x, float y){
  if (now_state != MENU_XY)
    return;
  int covert_x = (int)(x * 40);
  int covert_y = (int)(y * 40);
  //原点坐标：280，179
  GUI_SetColor(GUI_RED);
  GUI_SetPenSize(3);
  //GUI_DrawPoint(400,10); //测试用
  GUI_DrawPoint(280 + covert_x, 179 - covert_y);
  
  GUI_SetFont(GUI_FONT_8X18);
  GUI_DispStringAt("x:", 423, 287);
  GUI_DispFloat(x, 5);
  GUI_DispStringAt("y:", 423, 305);
  GUI_DispFloat(y, 5);
}
void GUI_main(){
  show_rate();
  menu_function();
}
void GUI_Reload(){
  LCD_ReInit();
  drawMainFrame();
}
void show_rate(){  
  if (time_1ms_cnt % 1000 == 0){
    GUI_SetColor(GUI_ORANGE);
    GUI_SetBkColor(GUI_BLACK);
    GUI_SetFont(GUI_FONT_8X18);
    GUI_SetTextMode(GUI_TM_NORMAL);
    GUI_DispStringAt("U:", 150, 0);
    GUI_DispDecMin(usart_rx_rate);
    GUI_DispStringAt("C:", 200, 0);
    GUI_DispDecMin(can_rx_rate);
  }
}
void clear_rate(){
  can_rx_rate = 0;
  usart_rx_rate = 0;
}
void test_pos(){
  GUI_SetColor(GUI_GRAY);
  
  GUI_DrawLine(81,20,479,20);
  GUI_DrawLine(81,70,479,70);
  GUI_DrawLine(81,140,479,140);
  GUI_DrawLine(81,210,479,210);
  GUI_DrawLine(81,280,479,280);
  GUI_DrawLine(81,319,479,319);
  
  GUI_DrawLine(80,20,80,319);
  GUI_DrawLine(110,20,110,280);
  GUI_DrawLine(110+123,20,110+123,280);
  GUI_DrawLine(110+123+123,20,110+123+123,280);
  GUI_DrawLine(479,20,479,319);
  
  GUI_SetFont(GUI_FONT_8X16X2X2);
  GUI_DispStringAt("A",90,85);
  GUI_DispStringAt("X",90,155);
  GUI_DispStringAt("Y",90,225);
  
  GUI_DispStringAt("BUPT",135,30);
  GUI_DispStringAt("ACTION",120+123+5,30);
  GUI_DispStringAt("B-A",130+123+123+5,30);
  
  GUI_SetColor(GUI_GREEN);
  GUI_SetFont(GUI_FONT_8X18);
  GUI_GotoXY(115 ,85);
  GUI_DispFloat(NRF_Data[0],10);
  GUI_GotoXY(115+123 ,85);
  GUI_DispFloat(NRF_Data[3],10);
  GUI_GotoXY(115+123+123 ,85);
  GUI_DispFloat(NRF_Data[0]-NRF_Data[3],10);
  
  GUI_GotoXY(115 ,155);
  GUI_DispFloat(NRF_Data[1],10);
  GUI_GotoXY(115+123 ,155);
  GUI_DispFloat(NRF_Data[4],10);
  GUI_GotoXY(115+123+123 ,155);
  GUI_DispFloat(NRF_Data[1]-NRF_Data[4],10);
  
  GUI_GotoXY(115 ,225);
  GUI_DispFloat(NRF_Data[2],10);
  GUI_GotoXY(115+123 ,225);
  GUI_DispFloat(NRF_Data[5],10);
  GUI_GotoXY(115+123+123 ,225);
  GUI_DispFloat(NRF_Data[2]-NRF_Data[5],10);
  GUI_SetFont(GUI_FONT_8X16X2X2);
}

