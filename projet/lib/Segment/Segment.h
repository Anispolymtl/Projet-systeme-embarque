/**
 * Auteur: Clément Lebeau
 *
 * Description: Contient la classe Segment qui représente un segment ajouté au
 * circuit en code. Contient aussi la classe TransmissionPacket, qui contiendra
 * les informations sur les segments pour la communication IR.
 */

#pragma once

#include "Debug/Debug.h"

#include <avr/io.h>
#include <util/crc16.h>

enum class SegmentLength {
   RESERVED = 0,
   FOUR_FIVE = 1,
   SIX_FIVE = 2,
   EIGHT_FIVE = 3
};

class Segment {
public:
   Segment(SegmentLength length = SegmentLength::RESERVED,
           uint16_t nCycles = 0,
           uint8_t position = 0);

   SegmentLength length;
   uint16_t nCycles;
   uint8_t position = 0;

   static void
   computePosition(uint16_t knownDistanceCycles, Segment* segments, uint8_t n);
   static uint8_t verticalSegmentToCharacters(SegmentLength length);

private:
   static constexpr uint16_t KNOWN_DISTANCE_INCHES = 15;
   static constexpr uint8_t MIN_POS_INCHES = 9;
   static constexpr uint8_t MAX_POS_INCHES = 39;
};

struct TransmissionPacket {
   Segment top[4];
   uint8_t nTop;
   Segment bottom[4];
   uint8_t nBottom;

   bool isValid;

   uint16_t computeCrc() const;
};
