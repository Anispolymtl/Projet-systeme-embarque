#include "Robot1.h"

Robot1::Robot1():
    button_(InteruptButton::NO_INTERRUPT),
    can_(),
    distanceSensor_(can_),
    irReceiver_(can_),
    led_(&PORTA, &DDRA, PA0, PA1),
    timer_(100, TimerMode::CTC),
    firstPositionReading_(0),
    blinkCount_(0),
    isFacingCenter_(false),
    isOpening90Away_(false),
    currentState_(State::INIT) {
   timer_.stopTimer();
}

void Robot1::start() {
   currentState_ = State::INIT;
   while(true) {
      executeState();
      changeState();
   }
}

void Robot1::incrementBlinkCounter() {
   ++blinkCount_;
   if(blinkCount_ % 2 == 0) {
      led_.setGreen();
   } else {
      led_.setOff();
   }
}

void Robot1::executeState() {
   switch(currentState_) {
      case State::INIT:
         executeInitState();
         break;
      case State::MOVEMENT:
         executeMovementState();
         break;
      case State::FIND_OPENING:
         executeFindOpeningState();
         break;
      case State::WAIT:
         executeWaitState();
         break;
      case State::BEEP:
         executeBeepState();
         break;
      case State::IR_RECEPTION:
         executeIrReceptionState();
         break;
      case State::IR_ERROR:
         executeIrErrorState();
         break;
      case State::READY_TO_SEND:
         executeReadyToSendState();
         break;
      default:
         DEBUG_PRINT("ERROR: Unknown state.\n");
         break;
   }
}

void Robot1::changeState() {
   switch(currentState_) {
      case State::INIT:
         currentState_ = State::MOVEMENT;
         break;
      case State::MOVEMENT:
         currentState_ = State::FIND_OPENING;
         break;
      case State::FIND_OPENING:
         currentState_ = State::WAIT;
         break;
      case State::WAIT:
         currentState_ = State::BEEP;
         break;
      case State::BEEP:
         currentState_ = State::IR_RECEPTION;
         break;
      case State::IR_RECEPTION:
         if(receivedInformation_.isValid) {
            currentState_ = State::READY_TO_SEND;
         } else {
            currentState_ = State::IR_ERROR;
         }
         break;
      case State::IR_ERROR:
         currentState_ = State::WAIT;
         break;
      case State::READY_TO_SEND:
         currentState_ = State::READY_TO_SEND;
         break;
      default:
         DEBUG_PRINT("ERROR: Unknown state.\n");
         break;
   }
}

void Robot1::executeInitState() {
   _delay_ms(300);
   firstPositionReading_ = distanceSensor_.measureVoltage();
   if(firstPositionReading_ < FORWARD_ON_CENTER_VOLTAGE_MIN) {
      // Le voltage est trop bas, alors la distance est trop grande
      // => on est face au centre
      isFacingCenter_ = true;
   } else {
      isFacingCenter_ = false;
   }
   DEBUG_PRINTF("V=%d, f=%u\n", firstPositionReading_, isFacingCenter_);
}

void Robot1::executeMovementState() {
   // Face au point: avance
   // Dos au point: recule
   if(isFacingCenter_) {
      navigation_.goForward();
   } else {
      navigation_.goBackward();
   }

   // Impulsion
   navigation_.setSpeed(100);
   _delay_ms(IMPULSE_DURATION);

   navigation_.setLeftSpeed(LEFT_WHEEL_PWM);
   navigation_.setRightSpeed(RIGHT_WHEEL_PWM);

   while(shouldKeepMoving())
      ;
}

void Robot1::executeFindOpeningState() {
   // Se positionner face au trou
   navigation_.stop();
   _delay_ms(MOVEMENT_PAUSE_DURATION);
   navigation_.turnRight90();
   _delay_ms(MOVEMENT_PAUSE_DURATION);
   if(isFacingOpening()) {
      isOpening90Away_ = true;
   } else {
      isOpening90Away_ = false;
      navigation_.turnRight90();
      _delay_ms(MOVEMENT_PAUSE_DURATION);
      navigation_.turnRight90();

      if(!isFacingOpening()) {
         DEBUG_PRINT("ERROR: Expected opening.\n");
      }
   }

   determineInitialPosition();
}

void Robot1::executeWaitState() {
   led_.setRed();

   while(!button_.isD2Pressed())
      ;
}

void Robot1::executeBeepState() {
   for(uint8_t i = 0; i < 3; ++i) {
      piezo_.playNote(80);
      _delay_ms(50);
      piezo_.stopSound();
      _delay_ms(50);
   }
   piezo_.stopSound();
}

void Robot1::executeIrReceptionState() {
   led_.setOff();
   receivedInformation_ = irReceiver_.receivePacket();

   DEBUG_PRINTF("nT: %u, nB: %u\n",
                receivedInformation_.nTop,
                receivedInformation_.nBottom);
   DEBUG_PRINTF("Valid: %u\n", receivedInformation_.isValid);

#ifdef DEBUG
   for(uint8_t i = 0; i < receivedInformation_.nTop; ++i) {
      DEBUG_PRINTF("  i: %u, l: %u, p: %u\n",
                   i,
                   (uint8_t) receivedInformation_.top[i].length,
                   receivedInformation_.top[i].position);
   }
   for(uint8_t i = 0; i < receivedInformation_.nBottom; ++i) {
      DEBUG_PRINTF("  i: %u, l: %u, p: %u\n",
                   i,
                   (uint8_t) receivedInformation_.bottom[i].length,
                   receivedInformation_.bottom[i].position);
   }
#endif // DEBUG
}

void Robot1::executeIrErrorState() {
   piezo_.playNote(48);
   _delay_ms(1000);
   piezo_.stopSound();
}

void Robot1::executeReadyToSendState() {
   // Attendre qu'on appuie sur Interrupt avant la communication
   led_.setGreen();
   while(!Button::isD2Pressed())
      ;

   // Activer le blinking
   timer_.startTimer();

   GlobalDisplay globalDisplay;
   CharacterDisplay characterDisplay;
   CommunicationRS232 communication;
   DisplayManager displayManager(characterDisplay, globalDisplay);
   globalDisplay.start(communication);
   if(!displayManager.isPositionGreaterThanMaxPositionForBottom(
          communication,
          receivedInformation_.bottom,
          receivedInformation_.nBottom) &&
      !displayManager.isPositionGreaterThanMaxPositionForTop(
          communication, receivedInformation_.top, receivedInformation_.nTop)) {
      displayManager.displayFirstLineCircuitOfRobot2(
          communication, receivedInformation_.top, receivedInformation_.nTop);
      switch(startingPosition_) {
         case Robot1::StartingPosition::TOP_FACING_UP:
            displayManager.updateDisplayOfRobotIfTopUp(
                communication,
                receivedInformation_.nTop,
                receivedInformation_.top);
            displayManager.initialiseBottomVerticalProgress(
                communication,
                receivedInformation_.bottom,
                receivedInformation_.nBottom);
            displayManager.iterateDisplayBottom(communication,
                                                receivedInformation_.bottom,
                                                receivedInformation_.nBottom);
            displayManager.displayLastLineOfCircuit(
                communication,
                receivedInformation_.bottom,
                receivedInformation_.nBottom);
            break;
         case Robot1::StartingPosition::BOTTOM_FACING_UP:
            displayManager.initialiseBottomVerticalProgress(
                communication,
                receivedInformation_.bottom,
                receivedInformation_.nBottom);
            displayManager.iterateDisplayTop(communication,
                                             receivedInformation_.nTop);
            displayManager.updateDisplayOfRobotIfBottomUp(
                communication,
                receivedInformation_.nBottom,
                receivedInformation_.bottom);
            displayManager.displayLastLineOfCircuit(
                communication,
                receivedInformation_.bottom,
                receivedInformation_.nBottom);
            globalDisplay.drawCharactersToBox(communication, SPACE_TO_FINAL);
            characterDisplay.drawEmptySpace(communication, LENGTH_OF_BOX);
            characterDisplay.drawVerticalBoldCharacter(communication);
            characterDisplay.drawEmptySpace(
                communication, SPACE_BOTTOM_BOX_T0_FINAL - SPACE_TO_FINAL);
            break;
         case Robot1::StartingPosition::BOTTOM_FACING_DOWN:
            displayManager.initialiseBottomVerticalProgress(
                communication,
                receivedInformation_.bottom,
                receivedInformation_.nBottom);
            displayManager.iterateDisplayTop(communication,
                                             receivedInformation_.nTop);
            displayManager.updateDisplayOfRobotIfBottomDown(
                communication,
                receivedInformation_.nBottom,
                receivedInformation_.bottom);
            displayManager.displayLastLineOfCircuit(
                communication,
                receivedInformation_.bottom,
                receivedInformation_.nBottom);
            globalDisplay.drawCharactersToBox(communication, SPACE_TO_FINAL);
            characterDisplay.drawEmptySpace(communication, LENGTH_OF_BOX);
            characterDisplay.drawVerticalBoldCharacter(communication);
            characterDisplay.drawEmptySpace(
                communication, SPACE_BOTTOM_BOX_T0_FINAL - SPACE_TO_FINAL);
            break;
         default:
            displayManager.updateDisplayOfRobotIfTopDown(
                communication,
                receivedInformation_.nTop,
                receivedInformation_.top);
            displayManager.initialiseBottomVerticalProgress(
                communication,
                receivedInformation_.bottom,
                receivedInformation_.nBottom);
            displayManager.iterateDisplayBottom(communication,
                                                receivedInformation_.bottom,
                                                receivedInformation_.nBottom);
            displayManager.displayLastLineOfCircuit(
                communication,
                receivedInformation_.bottom,
                receivedInformation_.nBottom);
            break;
      }
   } else {
      Segment segments[2];
      segments[0] = Segment(SegmentLength::SIX_FIVE, 100, 15);
      segments[1] = Segment(SegmentLength::EIGHT_FIVE, 200, 33);
      Segment segmentBottom[3];
      segmentBottom[0] = Segment(SegmentLength::FOUR_FIVE, 250, 10);
      segmentBottom[1] = Segment(SegmentLength::EIGHT_FIVE, 200, 20);
      segmentBottom[2] = Segment(SegmentLength::EIGHT_FIVE, 200, 35);
      uint8_t nTop = 2;
      uint8_t nBottom = 3;
      displayManager.displayFirstLineCircuitOfRobot2(
          communication, segments, nTop);
      switch(startingPosition_) {
         case Robot1::StartingPosition::TOP_FACING_UP:
            displayManager.updateDisplayOfRobotIfTopUp(
                communication, nTop, segments);
            displayManager.initialiseBottomVerticalProgress(
                communication, segmentBottom, nBottom);
            displayManager.iterateDisplayBottom(
                communication, segmentBottom, nBottom);
            displayManager.displayLastLineOfCircuit(
                communication, segmentBottom, nBottom);

            break;
         case Robot1::StartingPosition::BOTTOM_FACING_UP:
            displayManager.initialiseBottomVerticalProgress(
                communication, segmentBottom, nBottom);
            displayManager.iterateDisplayTop(communication, nTop);
            displayManager.updateDisplayOfRobotIfBottomUp(
                communication, nBottom, segmentBottom);
            displayManager.displayLastLineOfCircuit(
                communication, segmentBottom, nBottom);
            globalDisplay.drawCharactersToBox(communication, SPACE_TO_FINAL);
            characterDisplay.drawEmptySpace(communication, LENGTH_OF_BOX);
            characterDisplay.drawVerticalBoldCharacter(communication);
            characterDisplay.drawEmptySpace(
                communication, SPACE_BOTTOM_BOX_T0_FINAL - SPACE_TO_FINAL);
            break;
         case Robot1::StartingPosition::BOTTOM_FACING_DOWN:
            displayManager.initialiseBottomVerticalProgress(
                communication, segmentBottom, nBottom);
            displayManager.iterateDisplayTop(communication, nTop);
            displayManager.updateDisplayOfRobotIfBottomDown(
                communication, nBottom, segmentBottom);
            displayManager.displayLastLineOfCircuit(
                communication, segmentBottom, nBottom);
            globalDisplay.drawCharactersToBox(communication, SPACE_TO_FINAL);
            characterDisplay.drawEmptySpace(communication, LENGTH_OF_BOX);
            characterDisplay.drawVerticalBoldCharacter(communication);
            characterDisplay.drawEmptySpace(
                communication, SPACE_BOTTOM_BOX_T0_FINAL - SPACE_TO_FINAL);
            break;

         default:
            displayManager.updateDisplayOfRobotIfTopDown(
                communication, nTop, segments);
            displayManager.initialiseBottomVerticalProgress(
                communication, segmentBottom, nBottom);
            displayManager.iterateDisplayBottom(
                communication, segmentBottom, nBottom);
            displayManager.displayLastLineOfCircuit(
                communication, segmentBottom, nBottom);
            break;
      }
   }
   globalDisplay.drawFinalLines(communication);
   globalDisplay.writeNameOfRobot(communication);

   // Désactiver blinking
   timer_.stopTimer();
}

bool Robot1::shouldKeepMoving() {
   uint8_t voltage = distanceSensor_.measureVoltage();
   if(isFacingCenter_) {
      return voltage < FORWARD_ON_CENTER_VOLTAGE_MIN ||
             voltage > FORWARD_ON_CENTER_VOLTAGE_MAX;
   } else {
      return voltage < BACKWARD_ON_CENTER_VOLTAGE_MIN ||
             voltage > BACKWARD_ON_CENTER_VOLTAGE_MAX;
   }
}

bool Robot1::isFacingOpening() {
   uint8_t voltage = distanceSensor_.measureVoltage();

   return voltage < FACING_OPENING_VOLTAGE_THRESHOLD;
}

void Robot1::determineInitialPosition() {
   if(isFacingCenter_) {
      if(isOpening90Away_) {
         startingPosition_ = StartingPosition::BOTTOM_FACING_UP;
      } else {
         startingPosition_ = StartingPosition::TOP_FACING_DOWN;
      }
   } else {
      if(isOpening90Away_) {
         startingPosition_ = StartingPosition::TOP_FACING_UP;
      } else {
         startingPosition_ = StartingPosition::BOTTOM_FACING_DOWN;
      }
   }
}
