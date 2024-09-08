/*
 * Auteur: Anis Menouar
 *
 * Description: Classe Led qui sert à l'allumer et eteindre la del
 * bioluminescente. Cette dernière peut prendre n'importe quelle broche non
 * non utilisée.
 *
 * Description matérielle: Pour le branchement, il faut simplement respecter la
 * borne positive et négative de la LED.
 */

#pragma once
#include <avr/io.h>

#ifndef F_CPU
# define F_CPU 8000000
#endif // F_CPU

#include <util/delay.h>

enum class LedState {
   OFF,
   RED,
   GREEN
};

class Led {
public:
   Led(volatile uint8_t* portX = &PORTA,
       volatile uint8_t* ddrX = &DDRA,
       uint8_t pinPositive = PA0,
       uint8_t pinNegative = PA1);

   void setRed();
   void setGreen();
   void setAmbre();
   void setOff();
   LedState getLedState();

   ~Led() = default;

private:
   uint8_t pinPositive_;
   uint8_t pinNegative_;

   volatile uint8_t* portX_;

   static constexpr uint8_t DELAY_AMBER_RED = 5;
   static constexpr uint8_t DELAY_AMBER_GREEN = 10;

   LedState ledState_ = LedState::OFF;
};
