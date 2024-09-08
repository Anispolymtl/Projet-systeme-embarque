/**
 * Auteur: Clément Lebeau
 *
 * Description: Transmet de l'information via infrarouge en suivant une version
 * modifiée du protocole SIRC.
 *
 * Description matérielle:
 * La broche négative de la diode IR doit être branchée à PD4
 * La broche positive de la diode IR doit être branchée à PD5
 */

#pragma once

#include "Constants.h"

#include <avr/io.h>

#ifndef F_CPU
# define F_CPU 8000000
#endif // F_CPU
#include "Segment/Segment.h"

#include <util/delay.h>

class IrTransmitter {
public:
   IrTransmitter();

   void transmit(uint8_t data);

   void transmit(const TransmissionPacket& data);

private:
#ifdef DEBUG
   CommunicationRS232 communicationRS232;
#endif // DEBUG

   void sendStartPulse();
   void sendLogicalOne();
   void sendLogicalZero();

   void transmitByte(uint8_t byte);

   void configureTimer();
   void startTimer();
   void stopTimer();
};
