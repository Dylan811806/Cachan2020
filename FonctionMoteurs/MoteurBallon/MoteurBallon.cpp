#include "mbed.h"
#include "MoteurBallon.h"

int Conv_Angle (int angle_voulu){
    degres=angle_voulu*16.66666666666667;
    angle_conv=1000+(int)degres;
    if(angle_conv<1000)
        angle_conv=1000;
    if(angle_conv>2000)
        angle_conv=2000;
    return angle_conv;
}


void Init_Ballon(void){
    angle.period_ms(20);
    angle.pulsewidth_us(angle_conv);
}


void Perce_Ballon (void){
    angle.pulsewidth_us(angle_conv);
}

