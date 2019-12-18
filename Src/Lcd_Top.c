#include"main.h"
#include"GUI.h"
#include "GUI_Frame.h"

int lcd_enable = 1;
int lcd_flag = 0;

static int lcd_place = -1;
void Lcd_Top_main(){
    if(lcd_enable == 0) return;
    if(lcd_flag == 0) return;

    //状态切换 重新刷框架
    if(lcd_place != HAL_GPIO_ReadPin(S1_GPIO_Port,S1_Pin)){
     lcd_place = (int) HAL_GPIO_ReadPin(S1_GPIO_Port,S1_Pin);
     if(lcd_place==0){GUI_Clear();drawMainFrame();}
     if(lcd_place==1){GUI_Clear();}
    }



    if(lcd_place==0){GUI_main();}
    if(lcd_place==1){}

    lcd_flag = 0;

}