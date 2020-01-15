#include"main.h"
#include"GUI.h"
#include "GUI_Frame.h"

int lcd_enable = 1;
int lcd_flag = 0;

int lcd_place = -1;
void Lcd_Top_main(){
    if(lcd_enable == 0) return;
    if(lcd_flag == 0) return;
    lcd_flag = 0;
    show_system_time();

    //状态切换 重新刷框架
    if(lcd_place != HAL_GPIO_ReadPin(S1_GPIO_Port,S1_Pin)){
     lcd_place = (int) HAL_GPIO_ReadPin(S1_GPIO_Port,S1_Pin);
     GUI_Clear();drawMainFrame();
     if(lcd_place==0){now_state=MENU_NRF;show_state=MENU_NRF;}
     if(lcd_place==1){now_state=MENU_ROBOT_VARI;show_state=MENU_ROBOT_VARI;}
    }
    
    GUI_main();
}