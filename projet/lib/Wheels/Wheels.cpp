#include "Wheels.h"

Wheels::Wheels() {
   DDRB |= (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5);

   // Sélectionner Mode PWM Phase Correct
   // Voir Table 15-8, p.103
   TCCR0A |= (1 << WGM00);
   TCCR0A &= ~(1 << WGM01);
   TCCR0B &= ~(1 << WGM02);

   // Prescaler /8
   // Voir Table 15-9, p. 104
   TCCR0B |= (1 << CS01);
   TCCR0B &= ~((1 << CS00) | (1 << CS02));

   // A et B à 1 quand on dépasse le point de comparaison, 0 en descendant
   // Voir Table 15-4, p.102 et Table 15-7, p.103
   TCCR0A |= (1 << COM0A0) | (1 << COM0A1) | (1 << COM0B0) | (1 << COM0B1);

   setPwmPercentage(0);
   setDirection(true);
}

uint8_t Wheels::getNumberOfCyclesFromPercentage(uint8_t percentage) {
   return PWM_TOP * (100 - percentage) / 100;
}

void Wheels::setPwmPercentage(uint8_t percentage) {
   const uint8_t nCycles = getNumberOfCyclesFromPercentage(percentage);
   OCR0A = nCycles;
   OCR0B = nCycles;
}

void Wheels::setPwmPercentageLeft(uint8_t percentage) {
   OCR0A = getNumberOfCyclesFromPercentage(percentage);
}

void Wheels::setPwmPercentageRight(uint8_t percentage) {
   OCR0B = getNumberOfCyclesFromPercentage(percentage);
}

void Wheels::setDirection(bool isForward) {
   setDirectionLeft(isForward);
   setDirectionRight(isForward);
}

void Wheels::setDirectionLeft(bool isForward) {
   if(isForward)
      PORTB &= ~(1 << PB2);
   else
      PORTB |= (1 << PB2);
}

void Wheels::setDirectionRight(bool isForward) {
   if(isForward)
      PORTB &= ~(1 << PB5);
   else
      PORTB |= (1 << PB5);
}

