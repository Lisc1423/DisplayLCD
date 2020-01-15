#include "frame_func.h"
#include "can_utils.h"
#include "GUI.h"
#include "string.h"

VARIABLE var[VAR_MAX_NUM]={0};
int var_num = 0;
int judge_var(can_msg* data){
    if(var_num >= VAR_MAX_NUM - 1){ return -1;}
    if(data->ch[0]!='F'&&data->ch[0]!='f'&&data->ch[0]!='i'&&data->ch[0]!='I'){ return -1;}
    
    for(int i = 0;i<=var_num;i++){
        if(data->ch[0] == var[i].tag[0] && data->ch[1] == var[i].tag[1]&&data->ch[2]==var[i].tag[2] &&data->ch[3] == var[i].tag[3]){ 
            return i;}
    }
    return 0;
}
void update_var(can_msg* data){
    int judge = judge_var(data);
    if(judge<0) return ;
    if(judge == 0){
        var_num ++;
        var[var_num].tag[0]=data->ch[0];
        var[var_num].tag[1]=data->ch[1];
        var[var_num].tag[2]=data->ch[2];
        var[var_num].tag[3]=data->ch[3];
        if(var[var_num].tag[0] =='F'|| var[var_num].tag[0] == 'f'){
            var[var_num].fl[1]=data->fl[1];
        }
        else{
            var[var_num].in[1]=data->in[1];
        }
    }
    if(judge > 0){
        if(var[var_num].tag[0] =='F'|| var[var_num].tag[0] == 'f'){
            var[var_num].fl[1]=data->fl[1];
        }
        else{
            var[var_num].in[1]=data->in[1];
        }
    }
}
void print_var(){
  GUI_SetColor(GUI_GREEN);
  GUI_SetFont(GUI_FONT_COMIC24B_ASCII);
  char ch[4]={0};
  for(int i=0;i<=var_num;i++){
    for(int j=0;j<4;j++){ch[j]=var[i].tag[j];}
    if(i<10){
        GUI_DispStringAt(ch,85,30*i+25);
        if(var[var_num].tag[0] =='F'|| var[var_num].tag[0] == 'f'){
            GUI_GotoXY(155 ,30*i+25);
            GUI_DispFloat(var[i].fl[1],7);
        }
        else{
            GUI_DispDecAt(var[i].in[1],155,30*i+25,7);
        }
        
    }
    if(i>=10){
        GUI_DispStringAt(ch,255,30*(i-10)+25);
        if(var[var_num].tag[0] =='F'|| var[var_num].tag[0] == 'f'){
            GUI_GotoXY(355 ,30*(i-10)+25);
            GUI_DispFloat(var[i].fl[1],7);
        }
        else{
            GUI_DispDecAt(var[i].in[1],355,30*(i-10)+25,7);
        }
    }
    for(int j=0;j<4;j++){ch[j]=0;}
  }
  GUI_SetFont(GUI_FONT_8X16X2X2);
  GUI_SetColor(GUI_WHITE);

}
void menu_robot_variable(){
    var[0].tag[0]='N';
    var[0].tag[1]='U';
    var[0].tag[2]='M';
    var[0].in[1]=var_num ;
    print_var();
}