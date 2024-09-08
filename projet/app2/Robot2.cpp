#include "Robot2.h"

Robot2::Robot2() {}

void Robot2::start() {
   while(true) {
      executeState();
      changeState();
   }
}

void Robot2::executeState() {
   switch(currentState_) {
      case State::DA:
         executeDAState();
         break;
      case State::AB:
         executeABState();
         break;
      case State::BF:
         executeBFState();
         break;
      case State::FE:
         executeFEState();
         break;
      case State::ED:
         executeEDState();
         break;
      case State::DC:
         executeDCState();
         break;
      case State::WAIT:
         executeWaitState();
         break;
      case State::BEEP:
         executeBeepState();
         break;
      case State::SEND_IR:
         executeIRState();
         break;
      case State::SEND_RS232:
         executeRS232State();
         break;
   }
}

void Robot2::changeState() {
   switch(currentState_) {
      case State::DA:
         currentState_ = State::AB;
         break;
      case State::AB:
         currentState_ = State::BF;
         break;
      case State::BF:
         currentState_ = State::FE;
         break;
      case State::FE:
         currentState_ = State::ED;
         break;
      case State::ED:
         currentState_ = State::DC;
         break;
      case State::DC:
         currentState_ = State::WAIT;
         break;
      case State::WAIT:
         if(Button::isD2Pressed()) {
            currentState_ = State::BEEP;
         } else if(Button::isA2Pressed()) {
            currentState_ = State::SEND_RS232;
         }
         break;
      case State::BEEP:
         currentState_ = State::SEND_IR;
         break;
      case State::SEND_IR:
         currentState_ = State::WAIT;
         break;
      case State::SEND_RS232:
         currentState_ = State::WAIT;
         break;
   }
}

void Robot2::executeDAState() {
   timer_.startTimer();
   nav_.impulsion(100);
   do {
      nav_.followLine();
   } while(nav_.isReadingLine());
   timer_.stopTimer();
   nav_.stop();

   nCyclesDA_ = TCNT1;
   nav_.turnRightJunction();
}

void Robot2::executeABState() {
   do {
      timer_.startTimer();

      do {
         nav_.followLine();
      } while(!nav_.shouldTurnRight());
      nav_.stop();

      nav_.forwardToTurn();

      // Fin d'état (il n'y a plus de segments)
      if(!nav_.isReadingLine()) {
         nav_.backwardToTurn();
         nav_.turnRightJunction();
         return;
      }

      timer_.stopTimer();
      segmentsTop[nTop++] = Segment(measureSegment(), TCNT1);
   } while(nTop <= 4);
}

SegmentLength Robot2::measureSegment() {
   nav_.turnRightRobot2();
   timer_.startTimer();

   _delay_ms(IGNORE_SEGMENT_BEFORE_DELAY_MS);
   // Tourne jusqu'à ce qu'on dépasse un délai (segment court) ou qu'on trouve
   // le segment
   while(!nav_.isReadingCenter() && TCNT1 <= SEGMENT_DETECTION_MAX_CYCLES)
      ;
   timer_.stopTimer();
   nav_.stop();

   SegmentLength returnValue;
   // Si on trouve pas, c'est un 4.5
   // Si on trouve et qu'il reste du segment plus loin c'est 8.5, s'il n'en
   // reste plus c'est 6.5
   if(TCNT1 > SEGMENT_DETECTION_MAX_CYCLES) {
      returnValue = SegmentLength::FOUR_FIVE;
   } else {
      if(!nav_.isReadingCenter()) {
         DEBUG_PRINT("ERROR: segment\n");
      }
      nav_.stop();
      _delay_ms(INERTIA_DELAY);

      // Edge case 8.5 et retour à la position initiale
      nav_.goForward();
      _delay_ms(SIX_FIVE_DETECTION_FORWARD_DELAY_MS);
      nav_.stop();
      _delay_ms(INERTIA_DELAY);
      if(nav_.isReadingLine()) {
         returnValue = SegmentLength::EIGHT_FIVE;
      } else {
         returnValue = SegmentLength::SIX_FIVE;
      }

      nav_.setSpeed2(false, 30, 20);
      nav_.goBackward();

      if(nav_.isReadingLine()) {
         _delay_ms(SIX_FIVE_DETECTION_BACKWARD_DELAY_MS);
      } else {
         while(!nav_.isReadingLine())
            ;
      }
      nav_.stop();
      _delay_ms(INERTIA_DELAY);
   }

   // Retourne sur le cadre
   nav_.turnLeftRobot2();
   if(returnValue != SegmentLength::FOUR_FIVE) {
      _delay_ms(IGNORE_LONGER_SEGMENTS_AFTER_DELAY_MS);
   } else {
      _delay_ms(IGNORE_SEGMENT_AFTER_DELAY_MS);
   }
   while(!nav_.isReadingLeftOuter())
      ;
   nav_.stop();
   _delay_ms(INERTIA_DELAY);
   nav_.adjustAfterTurn();

   return returnValue;
}

void Robot2::executeBFState() {
   do {
      nav_.followLine();
   } while(nav_.isReadingLine());
   nav_.stop();
   nav_.turnRightJunction();
}

void Robot2::executeFEState() {
   nav_.impulsion(75);
   do {
      timer_.startTimer();

      do {
         nav_.followLine();
      } while(!nav_.shouldTurnRight());
      nav_.stop();

      nav_.forwardToTurn();

      // Fin d'état (il n'y a plus de segments)
      if(!nav_.isReadingLine()) {
         timer_.stopTimer();
         nav_.backwardToTurn();
         nav_.turnRightJunction();
         return;
      }

      timer_.stopTimer();
      segmentsBottom[nBottom++] = Segment(measureSegment(), TCNT1);
   } while(nBottom <= 4);
}

void Robot2::executeEDState() {
   do {
      nav_.adjustAfterTurn();
   } while(!nav_.isStraight());
   nav_.stop();
   _delay_ms(INERTIA_DELAY);

   nav_.impulsion(SMALL_BOOST);

   do {
      nav_.followLine();
   } while(!nav_.shouldTurnLeft());

   nav_.stop();
   _delay_ms(INERTIA_DELAY);

   while(!(nav_.isReadingCenter() || nav_.isReadingLeftInner() ||
           nav_.isReadingRightInner()))
      ;

   // On tourne à gauche en prenant le délai en compte (il arrive que le robot
   // ne voit pas la ligne).
   timer_.startTimer();
   nav_.turnLeftJunction();
   timer_.stopTimer();
}

void Robot2::executeDCState() {
   // Corriger les positions des segments
   Segment::computePosition(nCyclesDA_, segmentsTop, nTop);
   Segment::computePosition(nCyclesDA_, segmentsBottom, nBottom);
}

void Robot2::executeWaitState() {
   led_.setRed();
}

void Robot2::executeBeepState() {
   for(uint8_t i = 1; i < 4; i++) {
      piezo_.playNote(SMALL_BOOST);
      _delay_ms(SOUND_DELAY);
      piezo_.stopSound();
      _delay_ms(SOUND_DELAY);
   }
   piezo_.stopSound();
}

void Robot2::executeIRState() {
   led_.setOff();
   _delay_ms(2000);
   TransmissionPacket packet{
      .top = {}, .nTop = nTop, .bottom = {}, .nBottom = nBottom};
   for(uint8_t i = 0; i < nTop; ++i) {
      packet.top[i] = segmentsTop[i];
   }
   for(uint8_t i = 0; i < nBottom; ++i) {
      packet.bottom[i] = segmentsBottom[i];
   }

   DEBUG_PRINTF("cDA: %u\n", nCyclesDA_);
   DEBUG_PRINTF("nT: %u, nB: %u\n", packet.nTop, packet.nBottom);

#ifdef DEBUG
   DEBUG_PRINT("Top:\n");
   for(uint8_t i = 0; i < packet.nTop; ++i) {
      DEBUG_PRINTF("  i: %u, l: %u, p: %u, c: %u\n",
                   i,
                   (uint8_t) packet.top[i].length,
                   packet.top[i].position,
                   packet.top[i].nCycles);
   }

   DEBUG_PRINT("Bottom:\n");
   for(uint8_t i = 0; i < packet.nBottom; ++i) {
      DEBUG_PRINTF("  i: %u, l: %u, p: %u, c: %u\n",
                   i,
                   (uint8_t) packet.bottom[i].length,
                   packet.bottom[i].position,
                   packet.bottom[i].nCycles);
   }
#endif // DEBUG

   irTransmitter_.transmit(packet);
}

void Robot2::executeRS232State() {
   // Activer blinking
   timer_.setMode(TimerMode::CTC);
   timer_.setDuration(100);

   // Display
   GlobalDisplay globalDisplay;
   CharacterDisplay characterDisplay;
   CommunicationRS232 communication;
   DisplayManager displayManager(characterDisplay, globalDisplay);
   globalDisplay.start(communication);
   displayManager.displayFirstLineCircuitOfRobot2(
       communication, segmentsTop, nTop);
   displayManager.iterateDisplayTop(communication, nTop);
   globalDisplay.drawMiddleBox(communication);
   globalDisplay.drawEmptyLinesInBoxToRobotDown(communication);
   displayManager.initialiseBottomVerticalProgress(
       communication, segmentsBottom, nBottom);
   displayManager.iterateDisplayBottom(communication, segmentsBottom, nBottom);
   displayManager.displayLastLineOfCircuit(
       communication, segmentsBottom, nBottom);
   globalDisplay.drawFinalLines(communication);

   timer_.setMode(TimerMode::NORMAL);
   timer_.setDuration(8100);
   timer_.stopTimer();
}

void Robot2::incrementBlinkCount() {
   ++blinkCount_;
   if(blinkCount_ % 2 == 0) {
      led_.setGreen();
   } else {
      led_.setOff();
   }
}
