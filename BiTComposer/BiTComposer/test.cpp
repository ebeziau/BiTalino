
#include "bitalino.h"

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "fmod\fmod.h"
#include <fmod_common.h>
using namespace std;



#ifdef _WIN32

#include <conio.h>

bool keypressed(void)
{
	return (_kbhit() != 0);
}

#else // Linux or Mac OS

#include <sys/select.h>
#include "fmod/fmod_common.h"

bool keypressed(void)
{
   fd_set   readfds;
   FD_ZERO(&readfds);
   FD_SET(0, &readfds);

   timeval  readtimeout;
   readtimeout.tv_sec = 0;
   readtimeout.tv_usec = 0;

   return (select(FD_SETSIZE, &readfds, NULL, NULL, &readtimeout) == 1);
}

#endif

int main()
{
   try
   {


       //-------------------------------Jouer un son-----------------------------

       
       FMOD_SYSTEM* system;
       FMOD_System_Create(&system);
       FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL);

       FMOD_SOUND* tir = NULL;
       FMOD_System_CreateSound(system, "pan.wav", FMOD_CREATESAMPLE, 0, &tir);

       //FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, tir, 0, NULL);


       FMOD_Sound_Release(tir);



       FMOD_System_Close(system);
       FMOD_System_Release(system);



       //------------------------------------------------------------------------


       cout << "Salut Eva ! Je lance la recherche Bluetooth...\n";

      // uncomment this block to search for Bluetooth devices (Windows and Linux)
      
      BITalino::VDevInfo devs = BITalino::find();
      

      for(int i = 0; i < devs.size(); i++)
      	printf("%s - %s\n", devs[i].macAddr.c_str(), devs[i].name.c_str());
      //return 0;
      

      puts("Connecting to device...");
      
      // use one of the lines below
      BITalino dev("20:15:05:29:22:22");  // device MAC address (Windows and Linux)
      
      //BITalino dev("COM5");  // Bluetooth virtual COM port or USB-UART COM port (Windows)
      
      //BITalino dev("/dev/ttyUSB0");  // USB-UART device (Linux)
      //BITalino dev("/dev/rfcomm0");  // Bluetooth virtual serial port (Linux) 
      
      //BITalino dev("/dev/tty.usbserial-A1000QIz");  // USB-UART device (Mac OS)
      //BITalino dev("/dev/tty.bitalino-DevB");  // Bluetooth virtual serial port (Mac OS) 
      
      puts("Connected to device. Press Enter to exit.");

      std::string ver = dev.version();    // get device version string
      printf("BITalino version: %s\n", ver.c_str());

      dev.battery(10);  // set battery threshold (optional)

      //dev.start(100, {0, 1, 2, 3, 4, 5});   // start acquisition of all channels at 1000 Hz
      dev.start(1000, {0}); //Channel A1
      // use block below if your compiler doesn't support vector initializer lists
      /*
      BITalino::Vint chans;
      chans.push_back(0);
      chans.push_back(1);
      chans.push_back(2);
      chans.push_back(3);
      chans.push_back(4);
      chans.push_back(5);
      dev.start(1000, chans);
      */

      //dev.trigger({false, false, true, false});  // for original BITalino
      //dev.trigger({true, false});                // for BITalino 2
      // use block below if your compiler doesn't support vector initializer lists
      /*
      BITalino::Vbool outputs;
      outputs.push_back(false);
      outputs.push_back(false);
      outputs.push_back(true);
      outputs.push_back(false);
      dev.trigger(outputs);
      */

      BITalino::VFrame frames(10); // initialize the frames vector with 100 frames PLUS OU MOINS VITE
      int deltaTemps = 0;
      do //A CHAQUE do ON PREND UN NOUVEAU VECTEUR DE FRAMES
      {
         dev.read(frames); // get 100 frames from device
         const BITalino::Frame &f = frames[0];  // get a reference to the first frame of each 100 frames block
         const BITalino::Frame &f2 = frames[1]; //deuxieme mesure

         //pour atteindre directement la mesure qu'on veut
         const int& mes1 = f.analog[0];
         const int& mes2 = f2.analog[0];

         /*printf("%d : %d %d %d %d ; %d %d %d %d %d %d\n",   // dump the first frame
                f.seq,
                f.digital[0], f.digital[1], f.digital[2], f.digital[3],
                f.analog[0], f.analog[1], f.analog[2], f.analog[3], f.analog[4], f.analog[5]);*/

         //--------------------------COUPS----------------------------------------------

         deltaTemps++;

         //COUPS    
         /*if ((f.analog[0] != f2.analog[0]) && deltaTemps > 20) {
             puts("--------------------------------YOU HIT IT !");
             deltaTemps = 0;
         }*/

         //ACCELERATION VERTICALE (MODULE ACC A PLAT)
         /*if ((abs(f.analog[0] - f2.analog[0]) > 40) && deltaTemps > 20) {
             puts("--------------------------------YOU HIT IT !");
             deltaTemps = 0;
         }*/



         //--------------------------AFFICHAGE----------------------------------------------


         //affichage des 2 premières frames d'un bloc
         /*printf("%d %d ; %d %d\n",   // dump the first frame
             f.seq, f2.seq,
             f.analog[0], f2.analog[0]);*/

         //affichage en continu (changement d'affichage si changement dans la mesure (mouvement))
         int precedent = f.analog[0];
         for (BITalino::Frame mesure : frames) {
             if (mesure.analog[0] != precedent) {
                 printf("%d \n", mesure.analog[0]);
                 precedent = mesure.analog[0];
             }
         }

         


      } while (!keypressed()); // until a key is pressed

      dev.stop(); // stop acquisition
   } // dev is destroyed here (it goes out of scope)
   catch(BITalino::Exception &e)
   {
      printf("BITalino exception: %s\n", e.getDescription());
   }
   
   return 0;
}
