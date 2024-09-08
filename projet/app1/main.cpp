#include "CommunicationRS232/CommunicationRS232.h"
#include "GlobalDisplay/GlobalDisplay.h"
#include "Robot1.h"

Robot1 gRobot1;

int main(void) {
   gRobot1.start();
   return 0;
}

ISR(TIMER1_COMPA_vect) {
   gRobot1.incrementBlinkCounter();
}
