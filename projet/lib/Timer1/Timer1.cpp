#include "Timer1.h"

Timer1::Timer1(uint16_t durationMs, TimerMode mode) {
   mode_ = mode;
   durationMs_ = durationMs;
}

void Timer1::startTimer() {
   cli();
   setMode(mode_);
   setDuration(durationMs_);
   sei();
}

void Timer1::setMode(TimerMode mode) {
   cli();
   mode_ = mode;
   TCCR1A &= ~((1 << WGM10) | (1 << WGM11));
   TCCR1B &= ~((1 << WGM12) | (1 << WGM13));
   switch(mode) {
      case TimerMode::NORMAL:
         break;
      case TimerMode::CTC:
         TCCR1B |= (1 << WGM12);
         break;
      case TimerMode::PWM:
         TCCR1A |= (1 << WGM10);
         break;
   }
   sei();
}

void Timer1::setDuration(uint16_t durationMs) {
   cli();
   durationMs_ = durationMs;
   TCNT1 = 0;

   TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
   if(durationMs_ == 0) {
      ;
   } else if(durationMs_ <= TIME_MAX_1) {
      prescaler_ = Prescaler::ONE;
      TCCR1B |= (1 << CS10);
   } else if(durationMs_ <= TIME_MAX_2) {
      prescaler_ = Prescaler::TWO;
      TCCR1B |= (1 << CS11);
   } else if(durationMs_ <= TIME_MAX_3) {
      prescaler_ = Prescaler::THREE;
      TCCR1B |= (1 << CS11) | (1 << CS10);
   } else if(durationMs_ <= TIME_MAX_4) {
      prescaler_ = Prescaler::FOUR;
      TCCR1B |= (1 << CS12);
   } else if(durationMs_ <= TIME_MAX_5) {
      prescaler_ = Prescaler::FIVE;
      TCCR1B |= (1 << CS12) | (1 << CS10);
   }

   OCR1A = (durationMs_ * (F_CPU / SECOND_TO_MS)) / ((uint16_t) prescaler_);

   TCCR1C = 0;

   if(mode_ != TimerMode::NORMAL) {
      TIMSK1 |= (1 << OCIE1A); // On veut lancer une interruption à la comp A
   }
   sei();
}

void Timer1::stopTimer() {
   cli();
   TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
   sei();
}
