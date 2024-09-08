/*
 * Auteur: Antoine Trémouilloux
 *
 * Description: Définition de la classe Timer1 qui configure le timer 1 (le mode, 
 * le prescaler, la valeur de comparaison) et permet de de l'utiliser
 *
 * Description matérielle:
 * Pas besoin d'avoir une configuration matérielle spécifique.
 */

#pragma once
#include <avr/io.h>

#define F_CPU 8000000
#include <avr/interrupt.h>

enum class TimerMode {
   CTC,
   NORMAL,
   PWM
};

enum class Prescaler {
    ONE = 1,
    TWO = 8,
    THREE = 64,
    FOUR = 256,
    FIVE = 1024
};

class Timer1
{
public:
   Timer1(uint16_t durationMs, TimerMode mode = TimerMode::CTC);
   void startTimer();
   void setDuration(uint16_t durationMs);
   void setMode(TimerMode mode);
   void stopTimer();

   const uint16_t TIMER_MAX_VALUE = 65535;
   const uint16_t SECOND_TO_MS = 1000;
   const uint16_t TIME_MAX_1 = 8;
   const uint16_t TIME_MAX_2 = 65;
   const uint16_t TIME_MAX_3 = 524;
   const uint16_t TIME_MAX_4 = 2097;
   const uint16_t TIME_MAX_5 = 8388;
private:
   TimerMode mode_;
   Prescaler prescaler_;
   uint16_t durationMs_;

};
