/**
 * Auteurs: Anis Menouar, Clément Lebeau
 *
 * Description: Classe permettant d'utiliser le capteur de distance SHARP2Y0A21.
 *
 * Description Matérielle:
 * Le capteur doit être alimenté: fil rouge branché sur Vcc du port A, fil noir
 * sur GND du port A
 *
 * Le fil blanc du capteur doit être relié à la broche A8 (matérielle).
 *
 * La référence analogique du CAN (Aref) doit être environ à 2.5V
 *
 *
 */

#include "Can/Can.h"

#include <avr/io.h>

#ifndef F_CPU
# define F_CPU 8000000
#endif // F_CPU
#include <util/delay.h>

class DistanceSensor {
public:
   DistanceSensor(Can& can);
   ~DistanceSensor() = default;

   // Retourne le voltage de sortie du capteur de distance dans une valeur entre
   // 0 et 255.
   uint16_t measureVoltage();

private:
   Can* can_;

   static constexpr uint8_t MAX_VOLTAGE = 255;
   static constexpr uint8_t READING_PORT = PA7;
   static constexpr uint8_t N_READINGS = 15;
   static constexpr uint8_t N_UNWANTED_BITS = 2;
};
