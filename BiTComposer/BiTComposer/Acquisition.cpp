#include <iostream>
#include <conio.h>
#include "bitalino.h"
#include <stdio.h>
#include <stdlib.h>
#include "fmod\fmod.h"
#include "fmod\fmod_common.h"
using namespace std;


class Acquisition {

private:

	int _maxCalibration;
	int _minCalibration;
	BITalino::VFrame frames;
	

public:

	Acquisition() {
		_maxCalibration = 0;
		_minCalibration = 500;
		//_maxCalibration = 310;
		//_minCalibration = 320;
		//BITalino::VFrame frames(10);
	}

	int getMaxCalibration() {
		return _maxCalibration;
	}

	int getMinCalibration() {
		return _minCalibration;
	}

	void calibration(BITalino dev, BITalino::VFrame frames) {

		puts("7Nous allons proceder a la calibration. Tendez votre bras, paume vers l'exterieur, et ne bougez plus.");
		puts("Quand vous etes prets, appuyez sur la touche Entree.\n\n");

		//string verif;
		//cin >> verif;
		//getchar();

		cin.ignore(300, '\n');

		puts("Effectuez DOUCEMENT une rotation de votre poignet a 360 degres.");
		puts("Quand c'est fait, appuyez sur une touche du clavier\n\n");

		do {
			dev.read(frames);
			const BITalino::Frame f0 = frames[0]; 
			//const BITalino::Frame f1 = frames[1];

			int max = f0.analog[0];
			int min = f0.analog[0];



			for (BITalino::Frame mesure : frames) {
				if (mesure.analog[0] > max) {
					max = mesure.analog[0];
				}
				if (mesure.analog[0] < min) {
					min = mesure.analog[0];
				}
			}
			if (max > _maxCalibration) {
				_maxCalibration = max;
			}
			if (min < _minCalibration) {
				_minCalibration = min;
			}
		} while (!_kbhit());

		puts("Avant getch\n");
		_getch();
		puts("Apres getch\n");

		puts("Calibration effectuee  !\n");
		cout << "max : " << _maxCalibration << endl;
		cout << "min : " << _minCalibration << endl;
	}

	double valeurAccG(double valeurChannel) {
		double cMin = _minCalibration;
		double cMax = _maxCalibration;

		double valeurAccG = (2 * (valeurChannel - cMin) / (cMax - cMin)) - 1;

		return valeurAccG;
	}

	void play(BITalino dev, BITalino::VFrame frames) {
		cout << "Entree dans play" << endl;
		int verif = 1;		
		do {			
			cout << "Entree dans doWhil\n" << endl;
			dev.read(frames);
			const BITalino::Frame f0 = frames[0];
			const BITalino::Frame f1 = frames[1];

			//printf("f0.analog[0] : %d", f0.analog[0]);

			double valeurG;

			//affichage en continu (changement d'affichage si changement dans la mesure (mouvement))
			int precedent = f0.analog[0];
			for (BITalino::Frame mesure : frames)
			{
				if (mesure.analog[0] != precedent)
				{
					valeurG = valeurAccG(mesure.analog[0]);
					printf("%f \n", valeurG);
					precedent = mesure.analog[0];
				}
			}
			verif = verif + 1;
		}while (!_kbhit());

		cout << verif << endl;
	}
};