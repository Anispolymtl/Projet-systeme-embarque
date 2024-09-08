/**
 * Auteur: Clément Lebeau
 *
 * Description: Utilise le capteur PNA4602 pour recevoir de l'information par
 * infrarouge selon une version adaptée du protocole SIRC.
 *
 * Description matérielle:
 * Le fil de donnée du capteur doit être branché a PA3
 * (logicielle)
 *
 * Cette classe reconfigure le Timer1 lors de la reception de données.
 *
 */

#pragma once

#include "Can/Can.h"
#include "Constants.h"
#include "Debug/Debug.h"
#include "Segment/Segment.h"
#include "Timer1/Timer1.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/crc16.h>

class IrReceiver {
public:
   IrReceiver(Can& can);

   uint8_t receive();

   TransmissionPacket receivePacket();

private:
   static constexpr uint8_t DATA_PIN = PA3;
   volatile uint8_t* DATA_PORT = &PINA;
   volatile uint8_t* DATA_DDR = &DDRA;

   Can* can_;

   uint8_t receiveByte();

   void waitForStartSignal();

   void configureTimer();
   void resetTimer();
   uint16_t getElapsedCycles();

   bool isPinHigh();
};
