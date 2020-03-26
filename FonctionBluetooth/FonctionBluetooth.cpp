#include "mbed.h"
#include "FonctionBluetooth.h"
#include "MoteursDeplacement.h"
Serial Bt(PC_10,PC_11);

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