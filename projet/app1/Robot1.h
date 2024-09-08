/**
 * Auteur: Clément Lebeau
 *
 * Description: Classe Robot1 qui encapsule la machine à état du Robot1 dans
 * l'épreuve.
 */

#pragma once

#include "Button/Button.h"
#include "CharacterDisplay/CharacterDisplay.h"
#include "CommunicationRS232/CommunicationRS232.h"
#include "Debug/Debug.h"
#include "DisplayManager/DisplayManager.h"
#include "DistanceSensor/DistanceSensor.h"
#include "GlobalDisplay/GlobalDisplay.h"
#include "Infrared/IrReceiver.h"
#include "Led/Led.h"
#include "Navigation/Navigation.h"
#include "Piezo/Piezo.h"
#include "Timer1/Timer1.h"

#include <avr/io.h>

class Robot1 {
public:
   Robot1();

   void start();

   enum class StartingPosition {
      BOTTOM_FACING_UP,
      BOTTOM_FACING_DOWN,
      TOP_FACING_UP,
      TOP_FACING_DOWN
   };

   StartingPosition getStartingPosition() const {
      return startingPosition_;
   }

   void incrementBlinkCounter();

private:
#ifdef DEBUG
   CommunicationRS232 communicationRS232;
#endif // DEBUG

   enum class State {
      INIT,
      MOVEMENT,
      FIND_OPENING,
      WAIT,
      BEEP,
      IR_RECEPTION,
      IR_ERROR,
      READY_TO_SEND
   };

   static constexpr uint8_t BACKWARD_ON_CENTER_VOLTAGE_MIN = 98;
   static constexpr uint8_t BACKWARD_ON_CENTER_VOLTAGE_MAX = 105;

   static constexpr uint8_t FORWARD_ON_CENTER_VOLTAGE_MIN = 70;
   static constexpr uint8_t FORWARD_ON_CENTER_VOLTAGE_MAX = 78;

   static constexpr uint8_t FACING_OPENING_VOLTAGE_THRESHOLD = 60; // 28;

   static constexpr uint8_t LEFT_WHEEL_PWM = 50;
   static constexpr uint8_t RIGHT_WHEEL_PWM = 58;

   static constexpr uint16_t IMPULSE_DURATION = 250;
   static constexpr uint16_t MOVEMENT_PAUSE_DURATION = 700;

   Button button_;
   Can can_;
   CommunicationRS232 communicationRS232_;
   DistanceSensor distanceSensor_;
   IrReceiver irReceiver_;
   Led led_;
   Navigation navigation_;
   Piezo piezo_;
   Timer1 timer_;

   uint16_t firstPositionReading_;
   uint8_t blinkCount_;
   bool isFacingCenter_;
   bool isOpening90Away_;
   State currentState_;
   StartingPosition startingPosition_;
   TransmissionPacket receivedInformation_;

   void executeState();
   void changeState();

   void executeInitState();
   void executeMovementState();
   void executeFindOpeningState();
   void executeWaitState();
   void executeBeepState();
   void executeIrReceptionState();
   void executeIrErrorState();
   void executeReadyToSendState();

   void determineInitialPosition();

   bool shouldKeepMoving();
   bool isFacingOpening();
};
