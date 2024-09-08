#include "Piezo.h"

Piezo::Piezo() {
   // Initialisation de la valeur initiale du compteur du timer 2 à 0.
   TCNT2 = 0;
   // Configure toggle on OCR2A match
   TCCR2A |= (1 << COM2A0);
   TCCR2A &= ~(1 << COM2A1);

   // Configure mode CTC
   TCCR2A |= (1 << WGM21);
   TCCR2A &= ~(1 << WGM20);
   TCCR2B &= ~(1 << WGM22);

   DDRD |= (1 << PD6) | (1 << PD7);
   PORTD &= ~(1 << PD6);
}

void Piezo::playNote(uint8_t note) {
   // Prescaler /256
   TCCR2B |= (1 << CS22) | (1 << CS21);
   TCCR2B &= ~(1 << CS20);

   // formule :  OCR2A = (F_CPU / frequency * (2 * PRESCALER)) - 1;
   uint8_t indexOfNote = note - VALUE_OF_FIRST_NOTE;
   if(indexOfNote >= INITIAL_INDEX && indexOfNote <= FINAL_INDEX) {
      OCR2A = VALUES_OF_OCR2A[indexOfNote];
   }
}

void Piezo::stopSound() {
   OCR2A = 0;

   // Arrêter timer
   TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
}
