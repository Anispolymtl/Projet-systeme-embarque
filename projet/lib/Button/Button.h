/*
 * Auteur: Anis Menouar
 *
 * Identifications matérielles (Broches I/O) :
 *  - Le bouton interrupt est connecté à la broche D3 (PD2) en entrée.
 *  - Le bouton de validation sur le breadboard est connecté à la broche A3
 *    (PA2) en entrée via le fil de données.
 *
 * Le bouton sur le breadboard est en low enable :
 *  - à 0 (bouton relaché), le courant passe
 *  - à 1 (bouton appuyé), aucun courant ne passe
 *
 * Le mode des interruptions est falling edge.
 */

#pragma once
#include <stdint.h>
#pragma once
#include <stdint.h>
#define F_CPU 8000000
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

const uint8_t MASK_D2 = (1 << PD2);
const uint8_t MASK_A2 = (1 << PA2);

typedef volatile uint8_t* Register;

enum class InteruptButton {
   NO_INTERRUPT,
   BUTTON_D2,
   BUTTON_A2
};

class Button {
public:
   Button(InteruptButton interuptButton = InteruptButton::NO_INTERRUPT);
   void initialize();

   static bool isD2Pressed();
   static bool isA2Pressed();

private:
   InteruptButton _interuptButton;
};
