#include "Button.h"

Button::Button(InteruptButton interuptButton): _interuptButton(interuptButton) {
   DDRD &= ~(1 << PD2);
   DDRA &= ~(1 << PA2);
}

void Button::initialize() {
   if(_interuptButton == InteruptButton::NO_INTERRUPT) {
      return;
   }
   cli();
   switch(_interuptButton) {
      case InteruptButton::BUTTON_D2:
         DDRD &= ~(1 << PD2);
         EIMSK |= (1 << INT0);
         EICRA |= (1 << ISC01) | (1 << ISC00); // Any edge
         break;
      case InteruptButton::BUTTON_A2:
         DDRA &= ~(1 << PA2);
         EIMSK |= (1 << INT2);
         EICRA |= (1 << ISC21) | (1 << ISC20);
         break;
      case InteruptButton::NO_INTERRUPT:
         break;
   }
   sei();
}

bool Button::isD2Pressed() {
   if(PIND & MASK_D2) {
      _delay_ms(15); // Anti-rebond
      return (PIND & MASK_D2);
   }
   return false;
};

bool Button::isA2Pressed() {
   if(!(PINA & MASK_A2)) {
      _delay_ms(15);
      return !(PINA & MASK_A2);
   }
   return false;
}
