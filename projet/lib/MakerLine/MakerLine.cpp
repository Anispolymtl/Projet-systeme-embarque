
#include "MakerLine.h"

MakerLine::MakerLine() {
   DDRC &= ~((1 << SENSOR_S1) | (1 << SENSOR_S2) | (1 << SENSOR_S3) |
             (1 << SENSOR_S4) | (1 << SENSOR_S5));
}

uint8_t MakerLine::readLeftOuter() {
   return (PINC & (1 << SENSOR_S1));
}

uint8_t MakerLine::readLeftInner() {
   return (PINC & (1 << SENSOR_S2));
}

uint8_t MakerLine::readCenter() {
   return (PINC & (1 << SENSOR_S3));
}

uint8_t MakerLine::readRightInner() {
   return (PINC & (1 << SENSOR_S4));
}

uint8_t MakerLine::readRightOuter() {
   return (PINC & (1 << SENSOR_S5));
}

uint8_t MakerLine::readRightTurn() {
   return (readRightOuter() && readCenter() && readRightInner());
}

uint8_t MakerLine::readLeftTurn() {
   return (readLeftOuter() && readCenter() && readLeftInner());
}

bool MakerLine::isMiddleReading() {
   return (readCenter());
}

bool MakerLine::isReadingLine() {
   return (readLeftOuter() || readLeftInner() || readCenter() ||
           readRightInner() || readRightOuter());
}

bool MakerLine::isStraight() {
   return (readCenter() && !(readRightOuter()) && !(readLeftOuter()));
}
