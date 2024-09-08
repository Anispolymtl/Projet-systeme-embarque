/*
Auteur: Joey Hasrouny
Date: 16-03-2024

Description: Ce programme permet au robot d'émettre des sons à l'aide des
fréquences des notes du tableau 3 (voir description TP9).

Description matérielle:
La broche PD7 est utilisée en sortie comme sortie PWM au piezo.
La broche PD6 est utilisée en sortie comme ground branchée au piezo.

Le piezo doit être relié au port PD7 et PD6.
*/

#pragma once

#ifndef F_CPU
# define F_CPU 8000000
#endif // F_CPU

#include <avr/io.h>

// const uint8_t  (nommé les constantes 12 et 69 de la formule WIKIPEDIA)
// formule :  OCR2A = (F_CPU / frequency * (2 * PRESCALER)) - 1;
// Ici nous avons opté pour PRESCALER = 256 afin d'obtenir des valeurs de
// fréquences distinctes pour chaque note.
const uint8_t VALUES_OF_OCR2A[] = {141, 133, 126, 118, 112, 105, 99, 94, 88, 83,
                                   79,  74,  70,  66,  62,  59,  55, 52, 49, 46,
                                   44,  41,  39,  37,  35,  33,  31, 29, 27, 26,
                                   24,  23,  21,  20,  19,  18,  17};

const uint8_t INITIAL_INDEX = 0;
const uint8_t FINAL_INDEX = 36;

const uint8_t VALUE_OF_FIRST_NOTE = 45;

class Piezo {
public:
   Piezo();
   void playNote(uint8_t note);
   void stopSound();
};
