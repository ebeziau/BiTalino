
#include "bitalino.h"

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "fmod\fmod.h"
#include "fmod\fmod_common.h"
using namespace std;
#include <conio.h>

void fmodEssais()
{
    // ------------------------------ - Jouer un son----------------------------

    //puts("Appuie sur Entrees quand tu es pret\n");
    //cin.ignore(300, '\n');

    //FMOD::System* system;
    //FMOD::Sound* sound1;
    //FMOD::Channel* channel = 0;
    //FMOD_RESULT       result;
    //unsigned int      version;
    //void* extradriverdata = 0;

    //Common_Init(&extradriverdata);

    ///*
    //    Create a System object and initialize
    //*/
    //result = FMOD::System_Create(&system);
    //ERRCHECK(result);

    //result = system->getVersion(&version);
    //ERRCHECK(result);

    //if (version < FMOD_VERSION)
    //{
    //    Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
    //}

    //result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
    //ERRCHECK(result);

    //result = system->createSound(Common_MediaPath("grease.wav"), FMOD_DEFAULT, 0, &sound1);
    //ERRCHECK(result);

    //result = sound1->setMode(FMOD_LOOP_OFF);    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
    //ERRCHECK(result);                           /* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */
    //    
    ///*
    //    Main loop
    //*/
    //do
    //{
    //    Common_Update();

    //    if (Common_BtnPress(BTN_ACTION1))
    //    {
    //        result = system->playSound(sound1, 0, false, &channel);
    //        ERRCHECK(result);
    //    }

    //    result = system->update();
    //    ERRCHECK(result);

    //    {
    //        unsigned int ms = 0;
    //        unsigned int lenms = 0;
    //        bool         playing = 0;
    //        bool         paused = 0;
    //        int          channelsplaying = 0;

    //        if (channel)
    //        {
    //            FMOD::Sound* currentsound = 0;

    //            result = channel->isPlaying(&playing);
    //            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
    //            {
    //                ERRCHECK(result);
    //            }

    //            result = channel->getPaused(&paused);
    //            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
    //            {
    //                ERRCHECK(result);
    //            }

    //            result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
    //            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
    //            {
    //                ERRCHECK(result);
    //            }

    //            channel->getCurrentSound(&currentsound);
    //            if (currentsound)
    //            {
    //                result = currentsound->getLength(&lenms, FMOD_TIMEUNIT_MS);
    //                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
    //                {
    //                    ERRCHECK(result);
    //                }
    //            }
    //        }

    //        system->getChannelsPlaying(&channelsplaying, NULL);

    //        Common_Draw("==================================================");
    //        Common_Draw("Play Sound Example.");
    //        Common_Draw("Copyright (c) Firelight Technologies 2004-2020.");
    //        Common_Draw("==================================================");
    //        Common_Draw("");
    //        Common_Draw("Press %s to play a mono sound (drumloop)", Common_BtnStr(BTN_ACTION1));
    //        Common_Draw("Press %s to quit", Common_BtnStr(BTN_QUIT));
    //        Common_Draw("");
    //        Common_Draw("Time %02d:%02d:%02d/%02d:%02d:%02d : %s", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Paused " : playing ? "Playing" : "Stopped");
    //        Common_Draw("Channels Playing %d", channelsplaying);
    //    }

    //    Common_Sleep(50);
    //} while (!Common_BtnPress(BTN_QUIT));

    ///*
    //    Shut down
    //*/
    //result = sound1->release();
    //ERRCHECK(result);
    //result = system->close();
    //ERRCHECK(result);
    //result = system->release();
    //ERRCHECK(result);

    //Common_Close();


    /*FMOD_RESULT result;
    FMOD::Studio::System* system = NULL;

    result = FMOD::Studio::System::create(&system); // Create the Studio System object.
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }

    // Initialize FMOD Studio, which will also initialize FMOD Low Level
    result = system->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
    }*/


    /*FMOD_SYSTEM *system;
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL);
    FMOD_SOUND *tir = NULL;
    FMOD_System_CreateSound(system, "grease.wav", FMOD_CREATESAMPLE, 0, &tir);
    FMOD_System_PlaySound(system, tir, NULL, 0, NULL);
    FMOD_Sound_Release(tir);
    FMOD_System_Close(system);
    FMOD_System_Release(system);*/

    //-------------------------------------------------------------------------


}

int main()
{
    
    try
    {
        cout << "\nSalut ! Je lance la recherche Bluetooth...\n\n";

        BITalino::VDevInfo devs = BITalino::find();
        for (int i = 0; i < devs.size(); i++) {
            printf("%s - %s\n", devs[i].macAddr.c_str(), devs[i].name.c_str());
        }

        puts("Connecting to device...");
        BITalino dev("20:15:05:29:22:22"); 
        puts("Connected to device. Press Enter to exit.");

        string ver = dev.version(); 
        printf("BITalino version: %s\n", ver.c_str());

        dev.battery(10);

        dev.start(1000, { 0 }); //Channel A1        

        BITalino::VFrame frames(10); // initialize the frames vector with 10 frames PLUS OU MOINS VITE
               

        puts("\n----------------------------CALIBRATION----------------------------------\n");
        

        puts("Nous allons proceder a la calibration. Tendez votre bras, paume vers l'exterieur, et ne bougez plus.");
        puts("Quand vous etes prets, appuyez sur la touche Entree.\n\n");

        cin.ignore(300, '\n');

        puts("Effectuez DOUCEMENT une rotation du capteur a 360 degres.");
        puts("Quand c'est fait, appuyez sur une touche du clavier\n\n");

        int _maxCalibration(0);
        int _minCalibration(500);

        do {
            dev.read(frames);
            const BITalino::Frame f0 = frames[0];

            int max = f0.analog[0];
            int min = f0.analog[0];

            for (BITalino::Frame vecteur : frames) {
                if (vecteur.analog[0] > max) {
                    max = vecteur.analog[0];
                }
                if (vecteur.analog[0] < min) {
                    min = vecteur.analog[0];
                }
            }
            if (max > _maxCalibration) {
                _maxCalibration = max;
            }
            if (min < _minCalibration) {
                _minCalibration = min;
            }
        } while (!_kbhit());

        _getch();

        //retour aux valeurs par défaut si problème
        if ((_maxCalibration > 350)||(_minCalibration < 150)) {
            _maxCalibration = 312;
            _minCalibration = 208;
        }

        puts("Calibration effectuee  !\n");
        cout << "max : " << _maxCalibration << endl;
        cout << "min : " << _minCalibration << endl;



        puts("\n--------------------------------PLAY-----------------------------------------\n");
        
        puts("La seance va commencer ! Appuyez sur Entree quand vous etes pret.e.\n");
        cin.ignore(300, '\n');

        double valeurEnG;
        int valeurAbs;
        double MAX_GLOBAL = -5;
        double MIN_GLOBAL = 5;
        int time = 0;
        //bool applatisseur = true;

        int precedent = 300;

        do {
            dev.read(frames); //UN TABLEAU DE VECTEUR
            
            
            //-----------Explication des variables----------------------------------
                        
            /*
            frames : tableau de vecteurs
            const BITalino::Frame vecteur0 = frames[0] : premier vecteur du tableau
            vecteur0.analog[0] //valeur analogique du premier vecteur (une seule valeur par vecteur)
            */

            //-----------------------------------------------------------------------
      
            
            for (BITalino::Frame vecteur : frames) // VECTEUR
            {                
                valeurAbs = abs(vecteur.analog[0] - precedent);
                valeurEnG = (2 * ((double)vecteur.analog[0] - (double)_minCalibration) / ((double)_maxCalibration - (double)_minCalibration)) - 1;
                

                //test : les rebonds du dernier mouvement sont passés (méthode non retenue, voir rapport)
                /*if (valeurAbs < 10) {
                    applatisseur = true;
                }*/               
                
                //affichage (pour debug) : affiche à chaque fois que la valeur(acc) change
                /*if (vecteur.analog[0] != precedent) {
                    printf("Vecteur analog : %d \n", vecteur.analog[0]);
                }*/

                if (time > 100 && ((valeurAbs > 5) && (valeurAbs < 11)))
                {                
                    printf("valeur absolue (force) : %d \n", valeurAbs);
                    printf("-------------------------------------------------SMOOTH MOVE\n\n");
                    time = 0;
                }
                if (time > 100 && (valeurAbs >= 11))
                {
                    printf("valeur absolue (force) : %d \n", valeurAbs);
                    printf("---------------------------------------------------HARD MOVE\n\n");
                    time = 0;
                }
                precedent = vecteur.analog[0];
                if (MAX_GLOBAL < valeurEnG) MAX_GLOBAL = valeurEnG;
                if (MIN_GLOBAL > valeurEnG) MIN_GLOBAL = valeurEnG;
            }
            time = time + 1;
        }while (!_kbhit());



        printf("\n\nMAX_GLOBAL (en g): %lf \n", MAX_GLOBAL);
        printf("MIN_GLOBAL (en g): %lf \n", MIN_GLOBAL);


        dev.stop(); // stop acquisition
        puts("\nMerci d'avoir participe !\n");

    }
    catch (BITalino::Exception &e)
    {
        printf("BITalino exception: %s\n", e.getDescription());
    }

    return 0;
}
