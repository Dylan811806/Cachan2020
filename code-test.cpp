//DEFINITION FONCTIONS DEPLACEMENT

#include "mbed.h"
#include "deplacement.h"
#include "Timer.h"

#define TRAJECTORY_CAL 0.0  //compensation de l'asymetrie dans la puissance des moteurs en ligne droite
#define AVANT 0
#define ARRIERE 1

           
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



void Init(void)
{
    MotL.period_us(100);
    MotR.period_us(100);
    
}


/////////////////////////////////////////////////////////////////////////
void test (void){ SensL.write(1);
    SensR.write(0);
    wait(0.5);
    SensL.write(0);
    SensR.write(1);
    }
void ahead(int iVmoy)
{
   
    if(iVmoy >= 0)
    {
        SensL.write(AVANT);
        SensR.write(AVANT);

        MotL.pulsewidth_us(iVmoy + TRAJECTORY_CAL);   
        MotR.pulsewidth_us(iVmoy - TRAJECTORY_CAL);
    }

    else if(iVmoy < 0)
    {
        SensL.write(ARRIERE);
        SensR.write(ARRIERE);

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
      SensL.write(AVANT);
      SensR.write(AVANT);
    }
    else
    {
        SensL.write(ARRIERE);
        SensR.write(ARRIERE);
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
    //printf("STOP\r\n ");
    SensL.write(AVANT);
    SensR.write(AVANT);
    MotL.pulsewidth(0);
    MotR.pulsewidth(0);
}

void rotation_complete (int sens)////1 rotation horaire, 0 antihoraire
{
    printf("ROTATION\r\n");
    if (sens==1)
    {
        SensL.write(AVANT);
        SensR.write(ARRIERE);
    }
    if (sens==0)
    {
        SensL.write(ARRIERE);
        SensR.write(AVANT);
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
                    turn(iTurnRate,iVmoy);
                    while(T1.read_ms()<=tempo_ms){}
                    T1.stop();
                    T1.reset();
                    stop_mot();
                    iVmoy=-50;
                    iTurnRate=50;
                    T1.start();
                    turn(iTurnRate,iVmoy);
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
                    turn(iTurnRate,iVmoy);
                    while(T1.read_ms()<=tempo_ms){}
                    T1.stop();
                    T1.reset();
                    stop_mot();
                    iVmoy=-50;
                    iTurnRate=-50;
                    T1.start();
                    turn(iTurnRate,iVmoy);
                    while(T1.read_ms()<=tempo_ms){}
                    T1.stop();
                    T1.reset();
                    stop_mot();
                    etat=4;
                    printf("etat 3\r\n");
                    wait(0.2);
                    break;
                    
            case 4: T1.start();
                    rotation_complete(1);
                    while(T1.read_ms()<=tempo_ms){}
                    T1.stop();
                    T1.reset();
                    stop_mot();
                    T1.start();
                    rotation_complete(0);
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
                printf("b\r\n");
                break;

            case 'c'://virage droite
                iVmoy=50;
                iTurnRate=50;
                turn(iTurnRate,iVmoy);
                printf("c\r\n");
                break;

            case 'd'://virage gauche
                iVmoy=50;
                iTurnRate=-50;
                turn(iTurnRate,iVmoy);
                printf("d\r\n");
                break;

            case 'e':// rotation horaire
                rotation_complete(1);
                printf("e\r\n");
                break;

            case 'f'://rotation anti horaire
                rotation_complete(0);
                printf("f\r\n");
                break;
            
            case 'g'://stop
                stop_mot();
                printf("g\r\n");
                break;

            default :
                break;
        }

        wait(0.02);
 
    
}     
    
