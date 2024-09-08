#include "IrReceiver.h"

#ifdef DEBUG
# include "CommunicationRS232/CommunicationRS232.h"
# ifndef F_CPU
#  define F_CPU 8000000
# endif // F_CPU
# include <util/delay.h>

CommunicationRS232 communicationRS232;
#endif // DEBUG

IrReceiver::IrReceiver(Can& can): can_(&can) {
   *DATA_DDR &= ~(1 << DATA_PIN);
#ifdef DEBUG
   communicationRS232.enableTransmit();
#endif // DEBUG
}

uint8_t IrReceiver::receive() {
   configureTimer();
   waitForStartSignal();

   return receiveByte();
}

TransmissionPacket IrReceiver::receivePacket() {
   TransmissionPacket out = {};

   configureTimer();
   waitForStartSignal();

   uint8_t crcHigh = receiveByte();
   uint8_t crcLow = receiveByte();

   out.nTop = receiveByte();
   out.nBottom = receiveByte();

   for(uint8_t i = 0; i < out.nTop; ++i) {
      out.top[i].length = (SegmentLength) receiveByte();
      out.top[i].position = receiveByte();
   }

   for(uint8_t i = 0; i < out.nBottom; ++i) {
      out.bottom[i].length = (SegmentLength) receiveByte();
      out.bottom[i].position = receiveByte();
   }

   uint16_t validCrc = crcHigh << 8 | crcLow;
   uint16_t currentCrc = out.computeCrc();

   out.isValid = validCrc == currentCrc;

   return out;
}

uint8_t IrReceiver::receiveByte() {
   // uint16_t crc = 0;
   uint8_t data = 0;
   uint8_t nBitsReceived = 0;

   bool prevState = isPinHigh();

   while(nBitsReceived < 8) {
      bool currState = isPinHigh();
      if(prevState != currState) {
         // Front détecté
         prevState = currState;
         if(!currState) {
            // On est dans un pulse
            resetTimer();
         } else {
            // Un pulse vient de terminer, interpréter sa durée et passer au
            // suivant.
            uint16_t nCycles = getElapsedCycles();
            if(nCycles >= Infrared::LOGICAL_ONE_MIN_CYCLES &&
               nCycles <= Infrared::LOGICAL_ONE_MAX_CYCLES) {
               data |= (1 << nBitsReceived);
            } else if(nCycles >= Infrared::LOGICAL_ZERO_MIN_CYCLES &&
                      nCycles <= Infrared::LOGICAL_ZERO_MAX_CYCLES) {
            } else {
               // On ignore les IR pulses qui ne correspondent pas à notre
               // protocole de communication
               continue;
            }
            nBitsReceived++;
         }
      }
   }

   return data;
}

void IrReceiver::waitForStartSignal() {
   uint16_t nCycles = 0;

   while(nCycles < Infrared::START_MIN_CYCLES ||
         nCycles > Infrared::START_MAX_CYCLES) {
      // Attendre le début du start pulse
      while(isPinHigh())
         ;

      // Attendre la fin du start pulse
      resetTimer();
      while(!isPinHigh())
         ;

      nCycles = getElapsedCycles();
      // DEBUG_PRINTF("%dc\n", nCycles);
      /*
      #ifdef DEBUG
            if(nCycles >= Infrared::START_MIN_CYCLES &&
               nCycles <= Infrared::START_MAX_CYCLES) {
               DEBUG_PRINT("Good start pulse.\n");
            }
      #endif // DEBUG
      */
   }
}

void IrReceiver::configureTimer() {
   // Pas de sorties sur les broches (p. 128, Table 16-2)
   TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0));

   // Mode d'opération normal (p. 130 Table 16-5)
   TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
   TCCR1B &= ~((1 << WGM12) | (1 << WGM13));

   // Prescaler /1
   TCCR1B &= ~((1 << CS11) | (1 << CS12));
   TCCR1B |= (1 << CS10);

   resetTimer();
}

void IrReceiver::resetTimer() {
   TCNT1 = 0;
}

uint16_t IrReceiver::getElapsedCycles() {
   return TCNT1;
}

bool IrReceiver::isPinHigh() {
   uint8_t reading = can_->lecture(DATA_PIN) >> 2;
   return reading > Infrared::RECEPTION_VOLTAGE_THRESHOLD;
   // return (*DATA_PORT) & (1 << DATA_PIN);
}
