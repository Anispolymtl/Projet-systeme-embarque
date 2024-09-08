/**
 * Auteur: Clément Lebeau
 *
 * Description: Classe Robot2 qui encapsule la machine à état du Robot2 pour
 * l'épreuve finale.
 */

#pragma once

#include "Button/Button.h"
#include "CharacterDisplay/CharacterDisplay.h"
#include "CommunicationRS232/CommunicationRS232.h"
#include "Debug/Debug.h"
#include "DisplayManager/DisplayManager.h"
#include "DistanceSensor/DistanceSensor.h"
#include "GlobalDisplay/GlobalDisplay.h"
#include "Infrared/IrTransmitter.h"
#include "Led/Led.h"
#include "Navigation/Navigation.h"
#include "Piezo/Piezo.h"
#include "Timer1/Timer1.h"

#include <avr/io.h>

class Robot2 {
public:
   Robot2();

   void start();
   void incrementBlinkCount();

private:
   Navigation nav_;
   Timer1 timer_{8100, TimerMode::NORMAL};
   Button buttonD2_;
   Button buttonA2_;
   Piezo piezo_;
   Led led_{&PORTA, &DDRA, PA0, PA1};
   IrTransmitter irTransmitter_;
   uint8_t blinkCount_ = 0;
#ifdef DEBUG
   CommunicationRS232 communicationRS232;
#endif // DEBUG

   enum class State {
      DA,
      AB,
      BF,
      FE,
      ED,
      DC,
      WAIT,
      BEEP,
      SEND_IR,
      SEND_RS232
   };

   State currentState_ = State::DA;
   uint16_t nCyclesDA_ = 0;
   Segment segmentsTop[4];
   uint8_t nTop = 0;
   Segment segmentsBottom[4];
   uint8_t nBottom = 0;

   static constexpr uint8_t SOUND_DELAY = 50;
   static constexpr uint8_t SMALL_BOOST = 75;
   static constexpr uint16_t SEGMENT_DETECTION_MAX_CYCLES = 13000;
   static constexpr uint16_t SIX_FIVE_DETECTION_FORWARD_DELAY_MS = 370;
   static constexpr uint16_t SIX_FIVE_DETECTION_BACKWARD_DELAY_MS = 370;
   static constexpr uint16_t IGNORE_SEGMENT_AFTER_DELAY_MS = 1300;
   static constexpr uint16_t IGNORE_LONGER_SEGMENTS_AFTER_DELAY_MS = 500;
   static constexpr uint16_t IGNORE_SEGMENT_BEFORE_DELAY_MS = 425;

   static constexpr uint16_t BORDER_CHECK_STEP_DURATION = 310;
   static constexpr uint16_t INERTIA_DELAY = 800;

   void executeState();
   void changeState();

   void executeDAState();
   void executeABState();
   void executeBFState();
   void executeFEState();
   void executeEDState();
   void executeDCState();
   void executeWaitState();
   void executeBeepState();
   void executeIRState();
   void executeRS232State();

   SegmentLength measureSegment();
};
