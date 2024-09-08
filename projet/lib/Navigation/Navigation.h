/*
 * Auteur: Clément Lebeau
 *
 * Description: Définition de la classe Navigation qui contrôlle les
 * déplacements du robot.
 *
 * Description matérielle:
 * Idem à la classe Wheels (voir ../Wheels/Wheels.h)
 */

#pragma once

#include "../MakerLine/MakerLine.h"
#include "../Wheels/Wheels.h"

#ifndef F_CPU
# define F_CPU 8000000
#endif
#include <util/delay.h>

class Navigation {
public:
   Navigation();
   ~Navigation();

   void goForward();
   void goBackward();

   void turnLeftRobot1();
   void turnRightRobot1();

   void turnLeftRobot2();
   void turnRightRobot2();

   void turnRight90();
   void turnLeft90();

   void setLeftSpeed(uint8_t percentage);
   void setRightSpeed(uint8_t percentage);
   void setSpeed(uint8_t percentage);
   void stop();

   void setSpeed2(bool direction, uint8_t leftPercent, uint8_t rightPercent);
   void adjustToRight();
   void adjustToOuterRight();
   void adjustToLeft();
   void adjustToOuterLeft();
   void followLine();
   void adjustAfterTurn();
   void adjustNoDetection();

   void forwardToTurn();
   void backwardToTurn();

   void turnLeftJunction();
   void turnRightJunction();

   bool shouldTurnLeft();
   bool shouldTurnRight();
   bool isReadingLine();
   bool isReadingLeftInner();
   bool isReadingLeftOuter();
   bool isReadingRightInner();
   bool isReadingCenter();
   bool isStraight();

   void impulsion(uint16_t delayMs);
   void stopToAdjust(uint16_t delayMs);

private:
   Wheels wheels_;
   MakerLine* sensor_;

   uint8_t percentage_;
   uint8_t leftSpeed_;
   uint8_t rightSpeed_;

   static constexpr uint8_t TURN_SPEED_LEFT_ROBOT1 = 75;
   static constexpr uint8_t TURN_SPEED_RIGHT_ROBOT1 = 75;

   static constexpr uint8_t TURN_SPEED_LEFT_ROBOT2 = 35;
   static constexpr uint8_t TURN_SPEED_RIGHT_ROBOT2 = 48;

   static constexpr uint8_t MAX_SPEED = 100;
   static constexpr uint8_t NORMAL_SPEED = 50;
   static constexpr uint8_t FAST_MANEUVER = 45;
   static constexpr uint8_t PRECISE_MANEUVER = 38;
   static constexpr uint8_t ADJUSTMENT_SPEED = 36;
   static constexpr uint8_t SMALL_BOOST = 75;

   static constexpr uint8_t IMPULSION_DELAY = 25;
   static constexpr uint8_t STOP_ADJUSTMENT_DELAY = 175;
   static constexpr uint8_t TURN_STOP_ADJUSTMENT_DELAY = 125;
   static constexpr uint16_t PEAK_ALIGNMENT_DELAY = 675;
   static constexpr uint16_t AVERAGE_ROTATION_DELAY = 375;
   static constexpr uint16_t ONE_SEC_STOP = 1000;
   static constexpr uint16_t TURN_DURATION_LEFT = 765;
   static constexpr uint16_t TURN_DURATION_RIGHT = 765;
   static constexpr uint16_t TURN_IGNORE_DELAY = 800;

   static constexpr uint16_t TURN_LEFT_MAX_CYCLES = 17000;
};
