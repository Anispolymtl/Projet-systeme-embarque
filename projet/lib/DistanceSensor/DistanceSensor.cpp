#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(Can& can) {
   can_ = &can;
   DDRA &= ~(1 << READING_PORT);
}

uint16_t DistanceSensor::measureVoltage() {
   uint16_t sum = 0;
   for(uint8_t i = 0; i < N_READINGS; i++) {
      uint8_t voltage = can_->lecture(READING_PORT) >> N_UNWANTED_BITS;
      sum += voltage;
      _delay_ms(10);
   }
   sum /= N_READINGS;

   return sum;
}
