#include "mbed.h"
#include "Global.h"
void follow_balle(int x,int z)// a definir ce qu'on recup de la cam
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
            }
