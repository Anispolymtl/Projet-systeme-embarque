/*
 * Auteur: Joey Hasrouny
 *
 * Description: Définition de la classe CommunicationRS232 qui permet
 * la transmission de messages de la carte mère à l'écran, par l'intermédiaire
 * d'un câble USB.
 * On suppose que la longueur des messages sera au maximum 2**16, soit 65536
 * charactères.
 *
 * Description matérielle:
 * Garder le cavalier DbgEn actif sur la carte mère.
 * Utiliser le programme serieViaUSB (voir description TP5) pour la
 * transmission des données émises par RS232, de la carte mère vers
 * le câble USB.
 *
 */

#pragma once
#ifndef F_CPU
# define F_CPU 8000000
#endif // F_CPU
#include <avr/io.h>
#include <stdio.h>

class CommunicationRS232 {
public:
   CommunicationRS232();

   // Transmet un tableau d'octets
   void transmit(const uint8_t* data);

   // Transmet une chaine de caractères jusqu'à la fin de la chaine ('\0')
   void transmitText(const char* message);

   // Transmet une chaine de caractères formattée de la même manière qu'un appel
   // à printf(). La chaine finale (formattée) ne peut contenir plus de 128
   // caractères incluant le null terminator.
   template<typename... Args>
   void transmitFormatted(const char* format, Args... args) {
      // Le template permet le transfert des arguments variables (...) à
      // snprintf(). Syntaxe tirée de
      // https://stackoverflow.com/questions/3530771/passing-variable-arguments-to-another-function-that-accepts-a-variable-argument

      static constexpr int FORMATTED_STRING_BUFFER_SIZE = 128;
      char formattedStringBuffer[FORMATTED_STRING_BUFFER_SIZE];

      snprintf(
          formattedStringBuffer, FORMATTED_STRING_BUFFER_SIZE, format, args...);

      transmitText(formattedStringBuffer);
   }

   unsigned char receive();

   void enableTransmit();

   void enableReceive();

   void transmit(uint8_t data);

private:
};
