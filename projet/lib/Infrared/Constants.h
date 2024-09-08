/**
 * Auteur: Clément Lebeau
 *
 * Description: Contient les constantes pertinentes à la communication
 * infrarouge.
 */

#pragma once

#include <avr/io.h>

namespace Infrared {
   static constexpr uint8_t N_BITS = 8;

   static constexpr uint16_t SPACER_US = 600;

   static constexpr uint16_t TOLERANCE_CYCLES = 1000;

   static constexpr uint16_t LOGICAL_ONE_US = 1200;
   static constexpr uint16_t LOGICAL_ONE_MIN_CYCLES = 9600 - TOLERANCE_CYCLES;
   static constexpr uint16_t LOGICAL_ONE_MAX_CYCLES = 9600 + TOLERANCE_CYCLES;

   static constexpr uint16_t LOGICAL_ZERO_US = 600;
   static constexpr uint16_t LOGICAL_ZERO_MIN_CYCLES = 4800 - TOLERANCE_CYCLES;
   static constexpr uint16_t LOGICAL_ZERO_MAX_CYCLES = 4800 + TOLERANCE_CYCLES;

   static constexpr uint16_t START_US = 2400;
   static constexpr uint16_t START_MIN_CYCLES = 19200 - TOLERANCE_CYCLES;
   static constexpr uint16_t START_MAX_CYCLES = 19200 + TOLERANCE_CYCLES;

   static constexpr uint8_t RECEPTION_VOLTAGE_THRESHOLD = 200;
}
