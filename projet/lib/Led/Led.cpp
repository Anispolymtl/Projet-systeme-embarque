#include "Led.h"

Led::Led(volatile uint8_t* portX,
         volatile uint8_t* ddrX,
         uint8_t pinPositive,
         uint8_t pinNegative):
    pinPositive_(pinPositive),
    pinNegative_(pinNegative),
    portX_(portX) {
   *ddrX |= (1 << pinPositive_);
   *ddrX |= (1 << pinNegative_);
}

void Led::setRed() {
   ledState_ = LedState::RED;
   *portX_ |= (1 << pinPositive_);
   *portX_ &= ~(1 << pinNegative_);
}

void Led::setGreen() {
   ledState_ = LedState::GREEN;
   *portX_ |= (1 << pinNegative_);
   *portX_ &= ~(1 << pinPositive_);
}

void Led::setAmbre() {
   setGreen();
   _delay_ms(DELAY_AMBER_GREEN);
   setRed();
   _delay_ms(DELAY_AMBER_RED);
}

void Led::setOff() {
   ledState_ = LedState::OFF;
   *portX_ &= ~(1 << pinPositive_);
   *portX_ &= ~(1 << pinNegative_);
}

LedState Led::getLedState() {
   return ledState_;
}
