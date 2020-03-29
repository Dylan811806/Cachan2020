#include "mbed.h"
#include "MoteursDeplacement.h"
int Force_virage;
int Vit_moy;
int iVmoy;
int iTurnRate;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UPDATE KURA 26.03
// TODO : SET DEFINE VALUE !
#define DEF_MOT_FORWARD 0
#define DEF_MOT_REVERSE 1
// follow_balle() n'a rien à faire ici
// Réorganiser fonction moteur autour d'une fonction principale (voir proposition)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PwmOut MotL(PC_6);//2eme connecteur
PwmOut MotR(PC_8);//1er connecteur , 3eme sur pc9, le 4eme sur pc8,5eme pc1 pc0 analogin,6eme pc2 et pc3
DigitalOut SensL(PC_14,0);
DigitalOut SensR(PC_15,0);//sens mot 3 ,4eme ph1
//DigitalOut SensTest(PC_13,0);
//DigitalOut SensL1(PC_14,1);
//DigitalOut SensR1(PC_15,1);
///DigitalOut TestPinPh(PH_0,1);// MARCHE PAS a oublier
DigitalOut TestPinPH1(PH_1,1);
Timer T1;     


/*void follow_balle(int x,int z)// a definir ce qu'on recup de la cam
    {
        switch(x){//covertion de ce qui l'envoie obligatoire entre -100 et 100
        
            case (x<MIN_CENTRE):    //MIN_CENTRE variable, savoir ce qu'on considere comme centre donc a regler
                                Force_virage=       ;
                                break;
            case (x>MAX_CENTRE):    //MAX_CENTRE variable, savoir ce qu'on considere comme centre donc a regler
                                Force_virage=       ;
                                break;
            case (x>MIN_CENTRE && x<MAX_CENTRE):
                                Force_virage        ;
                                break;
            default:break;
        }
        if(x>MIN_CENTRE && x<MAX_CENTRE){
            switch(z){//convertion probable: 0 balle hors cam juste devant robot 100 balle a plus de ... m a regler
                                        // centrer la balle en x avant de diminuer z
                                        
            case (z>LOIN): // a definir la limite de distance
                            Vit_Moy=        ;
                            break;
            case (z<LOIN): // a definir la limite de distance
                            Vit_Moy=        ;
                            break;
            case (z>PROCHE): // Avancer doucement pour verifier le centrage
                            Vit_moy=        ;
                            break;
            case (z<PROCHE): // balle hors cam et centree
                            Vit_moy=        ;
                            break;
             default:break;
            }*/

/////////////////////////////////////////////////////////////////////////
void test (void){ //
    SensL.write(1);
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// KURA EDIT 26.03

void mooveRobot(int iMotLeft, int iMotRight)
{
    /*
    DATE : 26.03
    This fonction directly write output on the motor control pin based on value -100 to 100
    Value under 0 are for reverse speed, 0 is standy value and above 0 is forward speed
    This fonction is made to be used by other FUNCTION or by the user without manualy setting the
    output pins value.
    
    TODO :  Calculation part before writing output
            Making individual fonction for each part for clarity
    */
    
  // PART 0 - Private var
    int iMotLeftSense;
    int iMotLeftOutput;
    int iMotRightSense;
    int iMotRightOutput;

  // PART 1 - DEBUG ARG
    //Debug on argument value iMotLeft
    if(iMotLeft > 100)
    {
        iMotLeft = 100;
        if(iMotLeft > 100)
        {
        printf("!!! Unexpected error iMotLeft value to high ! iMotLeft = %d !!!", iMotLeft);
        }
        else
        {
        printf("! Error iMotLeft value to high set to max [+100] by default !");
        }
    }
    else if(iMotLeft < -100)
    {
        iMotLeft = -100;
        if(iMotLeft < -100)
        {
        printf("!!! Unexpected error iMotLeft value to low. Failed to set minimal value ! iMotLeft = %d !!!", iMotLeft);
        }
        else
        {
        printf("! Error iMotLeft value to low set to min [-100] by default !");
        }
    }
    
    //Debug on argument value iMotRight
    if(iMotRight > 100)
    {
        iMotRight = 100;
        if(iMotRight > 100)
        {
        printf("!!! Unexpected error iMotRight value to high. Failed to set max value ! iMotRight = %d !!!", iMotRight);
        }
        else
        {
        printf("! Error iMotRight value to high set to max [+100] by default !");
        }
    }
    else if(iMotRight < -100)
    {
        iMotRight = -100;
        if(iMotRight < -100)
        {
        printf("!!! Unexpected error iMotRight value to low. Failed to set min value ! iMotRight = %d !!!", iMotRight);
        }
        else
        {
        printf("! Error iMotLeft value to low set to min [-100] by default !");
        }
    }
    
  // PART 2 - PROCESSING SENSE
    //int iMotRightSense;
    // Sense left motor
    if(iMotLeft < 0)
    {
        iMotLeftSense = DEF_MOT_REVERSE;
    }
    else if(iMotLeft >= 0)
    {
        iMotLeftSense = DEF_MOT_FORWARD;
    }
    else
    {
        printf("!!! Unexpected error on iMotLeft value when writing sense. iMotLeft = %d !!!", iMotLeft);
    }
    
    // Sense Right Motor
    if(iMotRight < 0)
    {
        iMotRightSense = DEF_MOT_REVERSE;
    }
    else if(iMotRight >= 0)
    {
        iMotRightSense = DEF_MOT_FORWARD;
    }
    else
    {
        printf("!!! Unexpected error on iMotRight value when writing sense. iMotRight = %d !!!", iMotRight);
    }
    
  // PART 3 - PROCESSING SPEED
    // Step 1 - Setting positive value
    if(iMotLeft < 0)
    {
        iMotRightOutput = iMotLeft*(-1);
    }
    else
    {
        iMotRightOutput = iMotLeft;
    }
    if(iMotRight < 0)
    {
        iMotRightOutput = iMotRight*(-1);
    }
    else
    {
        iMotRightOutput = iMotRight;
    }
    // !!! TODO !!!
    // Step 2 - Balancing mecanical differential 
    // iMotLeftOutput = ?
    // iMotRightOutput = ?
    
  // PART 4 - WRITING OUTPUT
    SensL.write(iMotLeftSense);
    SensR.write(iMotRightSense);
    MotL.pulsewidth_us(iMotLeftOutput);   
    MotR.pulsewidth_us(iMotRightOutput);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
printf("Robot mooving..\r\n");
}

/////////////////////////////////////////////////////////////////////////

void Init(void)
{
    MotL.period_us(100);
    MotR.period_us(100);
    
}

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
    int tempo_ms=1000;//peut changer
    int etat=0;
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
 
    
