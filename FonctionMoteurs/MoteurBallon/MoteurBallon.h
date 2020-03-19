#ifndef MOTEUR_BALLON_H
#define MOTEUR_BALLON_H

#include "mbed.h"
#define ANGLE_D 0
#define ANGLE_F 180

PwmOut angle(PA_0);

void Init_Ballon(void);
void Perce_Ballon(void);

int Conv_Angle (void);

int angle_conv;
double degres;//variable pour chaque degres
#endif