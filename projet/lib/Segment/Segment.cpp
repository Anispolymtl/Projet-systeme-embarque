#include "Segment.h"

Segment::Segment(SegmentLength length, uint16_t nCycles, uint8_t position) {
   this->length = length;
   this->nCycles = nCycles;
   this->position = position;
}

void Segment::computePosition(uint16_t knownDistanceCycles,
                              Segment* segments,
                              uint8_t n) {
   // Utiles pour resize nos valeurs si elles sont impossibles
   uint8_t min = 255;
   uint8_t max = 0;

   for(uint8_t i = 0; i < n; ++i) {
      uint8_t prevPosition = i != 0 ? segments[i - 1].position : 0;
      segments[i].position =
          (uint32_t(segments[i].nCycles) * uint32_t(KNOWN_DISTANCE_INCHES)) /
              uint32_t(knownDistanceCycles) +
          prevPosition;
      if(segments[i].position > max) {
         max = segments[i].position;
      }
      if(segments[i].position < min) {
         min = segments[i].position;
      }
   }

#ifdef DEBUG
   CommunicationRS232 communicationRS232;
#endif // DEBUG
   DEBUG_PRINTF("min: %u, max: %u\n", min, max);

   uint32_t rangeMin = MIN_POS_INCHES;
   uint32_t rangeMax = MAX_POS_INCHES;

   // Si les mesures approximatives sont hors-range, on les rend in-range
   if(min < MIN_POS_INCHES || max > MAX_POS_INCHES) {
      min = (min < MIN_POS_INCHES) ? min : 9;
      for(uint8_t i = 0; i < n; ++i) {
         segments[i].position =
             rangeMin + (uint32_t(segments[i].position - min) *
                         uint32_t(rangeMax - rangeMin) / uint32_t(max - min));
         // newPos = start_2 + ((pos - start_1) * (end_2 - start_2) / (end_1
         // - start_1))
      }
   }
}

uint16_t TransmissionPacket::computeCrc() const {
   uint16_t crc = 0xFFFF;

   crc = _crc16_update(crc, nTop);
   crc = _crc16_update(crc, nBottom);

   for(uint8_t i = 0; i < nTop; ++i) {
      crc = _crc16_update(crc, (uint8_t) top[i].length);
      crc = _crc16_update(crc, top[i].position);
   }

   for(uint8_t i = 0; i < nBottom; ++i) {
      crc = _crc16_update(crc, (uint8_t) bottom[i].length);
      crc = _crc16_update(crc, bottom[i].position);
   }

   return crc;
}

uint8_t Segment::verticalSegmentToCharacters(SegmentLength length) {
   switch(length) {
      case SegmentLength::FOUR_FIVE:
         return 2;
      case SegmentLength::SIX_FIVE:
         return 3;
      case SegmentLength::EIGHT_FIVE:
         return 4;
      default:
         return 0;
   }
}
