#include "mbed.h"
#include "Global.h"
#include "MoteursDeplacement.h"
#include "MoteurBalais.h"
#include "FonctionRasp.h"
#include "FonctionCapteur.h"
#include "FonctionBluetooth.h"

int main()
{
    Init();//Init des moteurs
    while(1){
    bluetooth();// programme de test des fonctions moteur via bluetooth
    //TEST_1(); // programme avec mouvement prédefinit
   //test();
    }
}
