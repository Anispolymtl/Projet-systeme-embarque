#include "CommunicationRS232.h"

CommunicationRS232::CommunicationRS232() {
   // Configuration de la vitesse de transmission (voir description TP5)
   UBRR0H = 0;
   UBRR0L = 0xCF;

   // Format des trames:8 bits (UCSZ01 et UCSZ00 à 1), 1 stop bits (USBS0 = 0)
   // et sans parité (UPM00 et UPM01 à 0)
   UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);

   enableTransmit();
}

void CommunicationRS232::enableTransmit() {
   UCSR0B &= ~(1 << RXEN0);
   UCSR0B |= (1 << TXEN0);
}

void CommunicationRS232::enableReceive() {
   UCSR0B |= (1 << RXEN0);
   UCSR0B &= ~(1 << TXEN0);
}

void CommunicationRS232::transmit(const uint8_t* data) {
   uint8_t size = sizeof(&data) / sizeof(uint8_t);
   for(uint8_t i = 0; i < size; i++) {
      transmit(data[i]);
   }
}

void CommunicationRS232::transmitText(const char* message) {
   const char endOfText = '\0';
   for(uint16_t i = 0; message[i] != endOfText; ++i) {
      transmit(message[i]);
   }
}

unsigned char CommunicationRS232::receive() {
   /* Wait for data to be received */
   while(!(UCSR0A & (1 << RXC0)))
      ;
   /* Get and return received data from buffer */
   return UDR0;
}

void CommunicationRS232::transmit(uint8_t data) {
   // voir table 19.7.1, p.174
   // UDRE0 = 1 quand le buffer est vide et qu'on peut écrire dans UDR0
   while(!(UCSR0A & (1 << UDRE0)))
      ;

   // On écrit dans UDR0 pour transmettre l'octet
   UDR0 = data;
}
