//PROTOTYPE
#ifndef MOTEURSDEPLACEMENT_H
#define MOTEURSDEPLACEMENT_H

#include "Timer.h"
#include "mbed.h"
#define TRAJECTORY_CAL 0.0  //compensation de l'asymetrie dans la puissance des moteurs en ligne droite
#define AVANT 0
#define ARRIERE 1
#define MIN_CENTRE// calibrer la cam pour definir ce qu'on considere comme centree
#define MAX_CENTRE
#define LOIN//calibrer pour savoir ce qu'on considere comme proche ou loin
#define PROCHE
void Follow_balle(float,float,float);
int Force_virage;
int Vit_moy;

int etat=0;
int iVmoy;
int iTurnRate;
int tempo_ms=1000;//peut changer

void mooveRobot (int,int);
void ahead(int);        //entree: int[-100(full AR); +100(full AV)] - vmoy
                       

void turn(int, int);    //entrees: int[-100(full G); +100(full D)] - taux de virage
                        //  a terme -->     int[-100(full AR); +100(full AV)] - vmoy virage
                        //   
                        //
                        //
                        //
                        //
                        //

                                
void stop_mot (void);// arret moteur  

void rotation_complete (int);              

                        
void TEST_1 (void);
void test (void);
void Init(void);          
           
           
#endif
           
           
