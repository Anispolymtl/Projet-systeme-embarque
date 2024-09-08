#include "IrTransmitter.h"

IrTransmitter::IrTransmitter() {
   DDRD |= (1 << DD4) | (1 << DD5);
   PORTD &= ~(1 << PD4);
}

void IrTransmitter::transmit(uint8_t data) {
   configureTimer();
   sendStartPulse();
   transmitByte(data);
}

void IrTransmitter::transmitByte(uint8_t byte) {
   uint8_t nTransmittedBits = 0;
   while(nTransmittedBits < 8) {
      uint8_t masked = byte & (1 << nTransmittedBits++);
      if(masked) {
         sendLogicalOne();
      } else {
         sendLogicalZero();
      }
   }
}

void IrTransmitter::transmit(const TransmissionPacket& data) {
   uint16_t crc = data.computeCrc();
   uint8_t crcHigh = crc >> 8;
   uint8_t crcLow = crc;

   configureTimer();
   sendStartPulse();

   transmitByte(crcHigh);
   transmitByte(crcLow);

   transmitByte(data.nTop);
   transmitByte(data.nBottom);

   for(uint8_t i = 0; i < data.nTop; ++i) {
      transmitByte(uint8_t(data.top[i].length));
      transmitByte(data.top[i].position);
   }

   for(uint8_t i = 0; i < data.nBottom; ++i) {
      transmitByte(uint8_t(data.bottom[i].length));
      transmitByte(data.bottom[i].position);
   }
}

void IrTransmitter::sendStartPulse() {
   startTimer();
   _delay_us(Infrared::START_US);
   stopTimer();
   _delay_us(Infrared::SPACER_US);
}

void IrTransmitter::sendLogicalZero() {
   startTimer();
   _delay_us(Infrared::LOGICAL_ZERO_US);
   stopTimer();
   _delay_us(Infrared::SPACER_US);
}

void IrTransmitter::sendLogicalOne() {
   startTimer();
   _delay_us(Infrared::LOGICAL_ONE_US);
   stopTimer();
   _delay_us(Infrared::SPACER_US);
}

void IrTransmitter::configureTimer() {
   // Toggle OC1A on compare match (Table 16-2, p.128)
   TCCR1A &= ~(1 << COM1A1);
   TCCR1A |= (1 << COM1A0);

   // OC1B disconnected (Table 16-2, p.128)
   TCCR1A &= ~((1 << COM1B0) | (1 << COM1B1));

   // Mode 4: CTC (Table 16-5, p.130)
   TCCR1A &= ~((1 << WGM10) | (1 << WGM11));
   TCCR1B |= (1 << WGM12);
   TCCR1B &= ~(1 << WGM13);

   // Prescaler /1 (Table 16-6, p.131)
   TCCR1B &= ~((1 << CS12) | (1 << CS11));
   TCCR1B |= 1 << CS10;

   // Fréquence PWM de 38kHz => T = 26us => OCR1A = 208
   OCR1A = 104;
}

void IrTransmitter::startTimer() {
   // Prescaler /1 (Table 16-6, p.131)
   TCCR1B &= ~((1 << CS12) | (1 << CS11));
   TCCR1B |= 1 << CS10;
}

void IrTransmitter::stopTimer() {
   // Prescaler * 0 (Table 16-6, p.131)
   TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
   PORTD &= ~(1 << PD5);
}
