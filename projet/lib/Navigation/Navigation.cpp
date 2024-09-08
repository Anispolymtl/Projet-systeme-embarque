#include "Navigation.h"

Navigation::Navigation() {}

Navigation::~Navigation() {
   stop();
}

void Navigation::goForward() {
   wheels_.setDirection(true);
   wheels_.setPwmPercentageLeft(leftSpeed_);
   wheels_.setPwmPercentageRight(rightSpeed_);
}

void Navigation::goBackward() {
   wheels_.setDirection(false);
   wheels_.setPwmPercentageLeft(leftSpeed_);
   wheels_.setPwmPercentageRight(rightSpeed_);
}

void Navigation::turnLeftRobot1() {
   wheels_.setPwmPercentageLeft(TURN_SPEED_LEFT_ROBOT1);
   wheels_.setPwmPercentageRight(TURN_SPEED_RIGHT_ROBOT1);
   wheels_.setDirectionLeft(false);
   wheels_.setDirectionRight(true);
}

void Navigation::turnRightRobot1() {
   wheels_.setPwmPercentageLeft(TURN_SPEED_LEFT_ROBOT1);
   wheels_.setPwmPercentageRight(TURN_SPEED_RIGHT_ROBOT1);
   wheels_.setDirectionLeft(true);
   wheels_.setDirectionRight(false);
}

void Navigation::turnLeftRobot2() {
   wheels_.setDirectionLeft(false);
   wheels_.setDirectionRight(true);
   impulsion(100);
   wheels_.setPwmPercentageLeft(TURN_SPEED_LEFT_ROBOT2);
   wheels_.setPwmPercentageRight(TURN_SPEED_RIGHT_ROBOT2);
}

void Navigation::turnRightRobot2() {
   wheels_.setDirectionLeft(true);
   wheels_.setDirectionRight(false);
   wheels_.setPwmPercentageLeft(TURN_SPEED_LEFT_ROBOT2);
   wheels_.setPwmPercentageRight(TURN_SPEED_RIGHT_ROBOT2);
}

void Navigation::stop() {
   wheels_.setPwmPercentage(0);
}

void Navigation::turnLeft90() {
   turnLeftRobot1();
   _delay_ms(TURN_DURATION_LEFT);
   stop();
}

void Navigation::turnRight90() {
   turnRightRobot1();
   _delay_ms(TURN_DURATION_RIGHT);
   stop();
}

void Navigation::setLeftSpeed(uint8_t percentage) {
   if(percentage <= 100 && percentage >= 0) {
      leftSpeed_ = percentage;
      wheels_.setPwmPercentageLeft(leftSpeed_);
   }
}

void Navigation::setRightSpeed(uint8_t percentage) {
   rightSpeed_ = percentage;
   if(percentage <= 100 && percentage >= 0) {
      rightSpeed_ = percentage;
      wheels_.setPwmPercentageRight(rightSpeed_);
   }
}

void Navigation::setSpeed(uint8_t percentage) {
   if(percentage <= 100 && percentage >= 0) {
      leftSpeed_ = percentage;
      rightSpeed_ = percentage;
      setLeftSpeed(leftSpeed_);
      setRightSpeed(rightSpeed_);
   }
}

void Navigation::setSpeed2(bool direction,
                           uint8_t leftPercent,
                           uint8_t rightPercent) {
   wheels_.setDirection(direction);
   wheels_.setPwmPercentageLeft(leftPercent);
   wheels_.setPwmPercentageRight(rightPercent);
}

void Navigation::adjustToRight() {
   setSpeed2(true, 35, 30);
}

void Navigation::adjustToOuterRight() {
   setSpeed2(true, 40, 30);
}

void Navigation::adjustToLeft() {
   setSpeed2(true, 30, 42);
}

void Navigation::adjustToOuterLeft() {
   setSpeed2(true, 30, 45);
}

void Navigation::followLine() {
   if(!(sensor_->isReadingLine())) {
      _delay_ms(100);
      if(!(sensor_->isReadingLine())) {
         stop();
         return;
      }
   } else if(!(sensor_->isStraight())) {
      if(sensor_->readLeftOuter()) {
         adjustToOuterLeft();
      } else if(sensor_->readLeftInner()) {
         adjustToLeft();
      } else if(sensor_->readRightOuter()) {
         adjustToOuterRight();
      } else if(sensor_->readRightInner()) {
         adjustToRight();
      }
   } else {
      setSpeed2(true, 65, 61);
   }
}

void Navigation::adjustAfterTurn() {
   while(!(sensor_->isStraight())) {
      if(sensor_->readLeftOuter()) {
         adjustToOuterLeft();
      } else if(sensor_->readLeftInner()) {
         adjustToLeft();
      } else if(sensor_->readRightOuter()) {
         adjustToOuterRight();
      } else if(sensor_->readRightInner()) {
         adjustToRight();
      }
   }
}

void Navigation::impulsion(const uint16_t delayMs) {
   setSpeed(100);
   for(uint16_t i = 0; i < delayMs; i++) {
      _delay_ms(1);
   }
}

void Navigation::stopToAdjust(const uint16_t delayMs) {
   stop();
   for(uint16_t i = 0; i < delayMs; i++) {
      _delay_ms(1);
   }
}

void Navigation::forwardToTurn() {
   stopToAdjust(ONE_SEC_STOP);
   impulsion(SMALL_BOOST); // 75ms de boost
   goForward();
   _delay_ms(325); // Avancer un peu si aucune ligne n'est détecté
   stop();
   _delay_ms(200);
}

void Navigation::backwardToTurn() {
   stopToAdjust(ONE_SEC_STOP);
   impulsion(SMALL_BOOST);
   goBackward();
   _delay_ms(255); // Avancer un peu si aucune ligne n'est détecté
   stop();
   _delay_ms(200);
}

void Navigation::turnLeftJunction() {
   forwardToTurn();

   turnLeftRobot2();
   _delay_ms(TURN_IGNORE_DELAY);
   // On tourne jusqu'à ce qu'on voit la ligne ou qu'on dépasse le délai maximal
   // (si le flag est true)
   while(!(sensor_->readCenter() || sensor_->readLeftInner()))
      ;
   ;

   stopToAdjust(500);
   adjustAfterTurn();
   stop();
}

void Navigation::turnRightJunction() {
   forwardToTurn();

   turnRightRobot2();
   while(!sensor_->readRightInner())
      ;

   stopToAdjust(300);

   adjustAfterTurn();
   // peut-être tourner un petit peu à droite si !readCenter
   stop();
   _delay_ms(300);
}

bool Navigation::shouldTurnLeft() {
   return sensor_->readLeftTurn();
}

bool Navigation::shouldTurnRight() {
   return sensor_->readRightTurn();
}

bool Navigation::isReadingLine() {
   return sensor_->isReadingLine();
}

bool Navigation::isReadingLeftInner() {
   return sensor_->readLeftInner();
}

bool Navigation::isReadingLeftOuter() {
   return sensor_->readLeftOuter();
}

bool Navigation::isReadingRightInner() {
   return sensor_->readRightInner();
}

bool Navigation::isReadingCenter() {
   return sensor_->readCenter();
}

bool Navigation::isStraight() {
   return sensor_->isStraight();
}
