#include "Robot2.h"

#include <avr/interrupt.h>

Robot2 gRobot;

int main() {
#ifdef DEBUG
   CommunicationRS232 communicationRS232;
#endif // DEBUG
   DEBUG_PRINT("Program start.\n");
   gRobot.start();
}

ISR(TIMER1_COMPA_vect) {
   gRobot.incrementBlinkCount();
}
