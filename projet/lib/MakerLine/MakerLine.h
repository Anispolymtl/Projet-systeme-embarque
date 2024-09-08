/*
 * Auteur: Anis Menouar
 *
 * Identifications matérielles :
 *  - C0 à C4 sont en entrée et le MakerLine utilise le GND et le VCC du PORTC
 *
 *
 */

#pragma once

#define SENSOR_S1 PC0
#define SENSOR_S2 PC1
#define SENSOR_S3 PC2
#define SENSOR_S4 PC3
#define SENSOR_S5 PC4

#include <avr/io.h>

class MakerLine {
public:
   MakerLine();

   uint8_t readLeftOuter();
   uint8_t readLeftInner();
   uint8_t readCenter();
   uint8_t readRightInner();
   uint8_t readRightOuter();

   uint8_t readRightTurn();
   uint8_t readLeftTurn();

   bool isMiddleReading();
   bool isReadingLine();
   bool isStraight();

private:
   uint8_t sensor_;
};
