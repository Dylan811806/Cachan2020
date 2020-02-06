//DEFINITION FONCTIONS DEPLACEMENT

#include "mbed.h"
#include "deplacement.h"
#include "Timer.h"

#define TRAJECTORY_CAL 0.0  //compensation de l'asymetrie dans la puissance des moteurs en ligne droite

           
Serial Bt(PC_10,PC_11);

PwmOut MotL(PC_6);
PwmOut MotR(PC_8);
DigitalOut SensL(PC_14);
DigitalOut SensR(PC_15);

int etat=0;
int iVmoy;
int iTurnRate;
int tempo_ms=1000;//peut changer
Timer T1;     
char commande_bt;

/////////////////////////////////////////////////////////////////////////

void ahead(int iVmoy)
{
    MotL.period(0.001);
    MotR.period_us(100);
    if(iVmoy >= 0)
    {
        SensL.write(true);
        SensR.write(true);

        MotL.pulsewidth_us(iVmoy + TRAJECTORY_CAL);   
        MotR.pulsewidth_us(iVmoy - TRAJECTORY_CAL);
    }

    else if(iVmoy < 0)
    {
        SensL.write(false);
        SensR.write(false);

        MotL.pulsewidth_us(-iVmoy - TRAJECTORY_CAL);   
        MotR.pulsewidth_us(-iVmoy + TRAJECTORY_CAL);
    }
    printf("ahead\r\n");
}

/////////////////////////////////////////////////////////////////////////

void turn(int iTurnRate, int iVmoyTurn)
{
    if(iVmoyTurn>=0)
    {
      SensL.write(true);
      SensR.write(true);
    }
    else
    {
        SensL.write(false);
        SensR.write(false);
    }  
    

   if((iVmoyTurn + iTurnRate + TRAJECTORY_CAL) > 100)
   {
       MotL.pulsewidth_us(100);
   }
   else
   {
       MotL.pulsewidth_us(iVmoy + iTurnRate + TRAJECTORY_CAL);
   }


   if((iVmoyTurn - iTurnRate - TRAJECTORY_CAL) < 0)
   {
        MotR.pulsewidth_us(0);
   }
   else
   {
       MotL.pulsewidth_us(iVmoy - iTurnRate - TRAJECTORY_CAL);
   }
printf("TURN\r\n");
}

//le code pourra etre modifié pour permettre au robot de tourner sur lui meme

/////////////////////////////////////////////////////////////////////////

void stop_mot (void)
{
    printf("STOP\r\n ");
    MotL.pulsewidth(0);
    MotR.pulsewidth(0);
}

void rotation_complete (bool sens)////true rotation horaire, false antihoraire
{
    printf("ROTATION\r\n");
    if (sens==true)
    {
        SensL.write(true);
        SensR.write(false);
    }
    if (sens==false)
    {
        SensL.write(false);
        SensR.write(true);
    }
    MotL.pulsewidth(50);
    MotR.pulsewidth(50);
}
void TEST_1 (void)
{
        T1.stop();
    T1.reset();
    switch(etat)
    {
            case 0: T1.start();
                    iVmoy=50;
                    ahead(iVmoy);
                    while(T1.read_ms()<=tempo_ms){}
                    T1.stop();
                    T1.reset();
                    stop_mot();
                    etat=1;
                    printf("ETAT 0\r\n");
                    wait(0.2);
                    break;
            
            case 1: T1.start();
                    iVmoy=-50;
                    ahead(iVmoy);
                    while(T1.read_ms()<=tempo_ms){}
                    T1.stop();
                    T1.reset();
                    stop_mot();
                    etat=2;
                    printf("etat 1\r\n");
                    wait(0.2);
                    break;
                    
            case 2: T1.start();
                    iVmoy=50;
                    iTurnRate=50;
                    turn(iVmoy,iTurnRate);
                    while(T1.read_ms()<=tempo_ms){}
                    T1.stop();
                    T1.reset();
                    stop_mot();
                    iVmoy=-50;
                    iTurnRate=50;
                    T1.start();
                    turn(iVmoy,iTurnRate);
                    while(T1.read_ms()<=tempo_ms){}
                    T1.stop();
                    T1.reset();
                    stop_mot();
                    etat=3;
                    printf("etat 2\r\n");
                    wait(0.2);
                    break;
                    
            case 3: T1.start();
                    iVmoy=50;
                    iTurnRate=-50;
                    turn(iVmoy,iTurnRate);
                    while(T1.read_ms()<=tempo_ms){}
                    T1.stop();
                    T1.reset();
                    stop_mot();
                    iVmoy=-50;
                    iTurnRate=-50;
                    T1.start();
                    turn(iVmoy,iTurnRate);
                    while(T1.read_ms()<=tempo_ms){}
                    T1.stop();
                    T1.reset();
                    stop_mot();
                    etat=4;
                    printf("etat 3\r\n");
                    wait(0.2);
                    break;
                    
            case 4: T1.start();
                    rotation_complete(true);
                    while(T1.read_ms()<=tempo_ms){}
                    T1.stop();
                    T1.reset();
                    stop_mot();
                    T1.start();
                    rotation_complete(false);
                    while(T1.read_ms()<=tempo_ms){}
                    T1.stop();
                    T1.reset();
                    stop_mot();
                    etat=0;
                    printf("etat 4\r\n");
                    wait(0.2);
                    break;
                    
            default:break;
    }
}
 
void bluetooth(void)
{
        //mmande_bt=NULL;
        wait(0.02);
        if(Bt.readable()==1) {
            commande_bt=Bt.getc();
            printf("%c",commande_bt);
        }
        switch(commande_bt) {
            case 'a'://avant
                iVmoy=50;
                ahead(iVmoy);
                printf("a\r\n");
                break;

            case 'b'://arriere
                iVmoy=-50;
                ahead(iVmoy);
                break;

            case 'c'://virage droite
                iVmoy=50;
                iTurnRate=50;
                turn(iVmoy,iTurnRate);
                break;

            case 'd'://virage gauche
                iVmoy=50;
                iTurnRate=-50;
                turn(iVmoy,iTurnRate);
                break;

            case 'e':// rotation horaire
                rotation_complete(true);
                break;

            case 'f'://rotation anti horaire
                rotation_complete(false);
                break;
            
            case 'g'://stop
                stop_mot();
                break;

            default :
                break;
        }

        wait(0.02);
 
    
}     
    
