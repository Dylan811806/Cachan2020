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
Serial Bt(PC_10,PC_11);
PwmOut MotL(PC_6);//2eme connecteur
PwmOut MotR(PC_8);//1er connecteur , 3eme sur pc9, le 4eme sur pc8,5eme pc1 pc0 analogin,6eme pc2 et pc3
DigitalOut SensL(PC_14,0);
DigitalOut SensR(PC_15,0);//sens mot 3 ,4eme ph1
//DigitalOut SensTest(PC_13,0);
//DigitalOut SensL1(PC_14,1);
//DigitalOut SensR1(PC_15,1);
///DigitalOut TestPinPh(PH_0,1);// MARCHE PAS a oublier
DigitalOut TestPinPH1(PH_1,1);
int etat=0;
int iVmoy;
int iTurnRate;
int tempo_ms=1000;//peut changer
Timer T1;     
char commande_bt='g';

void ahead(int);        //entree: int[-100(full AR); +100(full AV)] - vmoy
                       

void turn(int, int);    //entrees: int[-100(full G); +100(full D)] - taux de virage
                        //  a terme -->     int[-100(full AR); +100(full AV)] - vmoy virage
                        //   
                        //
                        //
                        //
                        //
                        //

                                
void stop (void);// arret moteur  

void rotation_complete (int);              

                        
void TEST_1 (void);
void bluetooth(void);
void test (void);
void Init(void);          
           
           
#endif
           
           
