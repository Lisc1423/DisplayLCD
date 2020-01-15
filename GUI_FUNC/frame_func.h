#ifndef _FRAME_FUNC_H
#define _FRAME_FUNC_H
#include "can_utils.h"

#define VAR_MAX_NUM 20
#define VAR_ID 121

typedef union {
    char tag[8];
    int in[2];
    float fl[2];
}VARIABLE;

void update_var(can_msg* data);
void menu_robot_variable();

#endif //_FRAME_FUNC_H