#include "DisplayManager.h"

DisplayManager::DisplayManager(CharacterDisplay& display, GlobalDisplay& globalDisplay) :
        display_(display), globalDisplay_(globalDisplay) {}
 
void DisplayManager::displayFirstLineCircuitOfRobot2(CommunicationRS232& communication,Segment* top,uint8_t nTop) {
    const char* unicodeBorderCharacter = u8"\u2554";
    const char* unicodeBorderEndCharacter = u8"\u2557";
    uint8_t countCharacters = 0;
    communication.transmitText(unicodeBorderCharacter);
    for (uint8_t i = 0; i < nTop; i++ ) {
        uint8_t nVerticalEqualCharacter = top->verticalSegmentToCharacters(top[i].length);
        topVerticalProgress_[i] = nVerticalEqualCharacter;
        uint8_t nEqualCharacters = top[i].position - countCharacters;
        display_.drawTheEqualCharacter(communication,nEqualCharacters);
        display_.drawThreePathCharacter(communication);
        topSegmentPositions_[i] = nEqualCharacters;
        countCharacters += nEqualCharacters;
    }
    display_.drawTheEqualCharacter(communication,LENGTH_WITHOUT_SEGMENT - countCharacters - nTop);
    communication.transmitText(unicodeBorderEndCharacter);
}

void DisplayManager::displayTopCircuitOfRobot2(CommunicationRS232& communication,uint8_t nTop) {
    uint8_t spaceIfNoCharacter = 1;
    uint8_t countCharacters = 0;
    display_.drawVerticalEqualCharacter(communication);
    for (uint8_t j = 0; j < nTop; j++) {
        uint8_t nEqualCharacters = topSegmentPositions_[j];
        display_.drawEmptySpace(communication,nEqualCharacters);
        if (topVerticalProgress_[j] != 0) {
            display_.drawVerticalEqualCharacter(communication);
            --topVerticalProgress_[j];
        } else {
            display_.drawEmptySpace(communication,spaceIfNoCharacter);
        }
        countCharacters += nEqualCharacters;
    }
    display_.drawEmptySpace(communication,LENGTH_WITHOUT_SEGMENT-countCharacters-nTop);
    display_.drawVerticalEqualCharacter(communication);
}

void DisplayManager::displayMiddleBoxIfRobotInBottom(CommunicationRS232& communication) {
    globalDisplay_.drawEmptyLinesInBoxToRobotDown(communication);
    globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
}

void DisplayManager::initialiseBottomVerticalProgress(CommunicationRS232& communication,Segment* bottom,uint8_t nBottom) {
    uint8_t nTotalLines = 4;
    for (int8_t k = nBottom - 1; k >= 0; k--) {
        uint8_t nVerticalEqualCharacter = bottom[k].verticalSegmentToCharacters(bottom[k].length);
        bottomVerticalProgress_[k] = nVerticalEqualCharacter;
        linesToSkip_[k] = nTotalLines - nVerticalEqualCharacter;
    }
}

 void DisplayManager::displayBottomCircuitOfRobot2(CommunicationRS232& communication,Segment* bottom,uint8_t nBottom) {
    uint8_t spaceIfNoCharacter = 1;
    uint8_t countCharacters = 0;
    display_.drawVerticalEqualCharacter(communication);
    for (int8_t k = nBottom - 1; k >= 0; k--) {
        uint8_t nEqualCharacters = LENGTH_WITHOUT_SEGMENT - bottom[k].position - countCharacters;
        countCharacters += nEqualCharacters;
        display_.drawEmptySpace(communication,nEqualCharacters);
        if (linesToSkip_[k] == 0) {
            if (bottomVerticalProgress_[k] != 0) {
                display_.drawVerticalEqualCharacter(communication);
                --bottomVerticalProgress_[k];
            } else {
                display_.drawEmptySpace(communication, spaceIfNoCharacter);
            }
        } else {
            display_.drawEmptySpace(communication, spaceIfNoCharacter);
            --linesToSkip_[k];
        }
    }
        
        display_.drawEmptySpace(communication,LENGTH_WITHOUT_SEGMENT-countCharacters-nBottom);
        display_.drawVerticalEqualCharacter(communication);
        globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
}

void DisplayManager::iterateDisplayBottom(CommunicationRS232& communication,Segment* bottom, uint8_t nBottom) {
    for (uint8_t k = 0; k < MAX_SEGMENTS;k++) {
        displayBottomCircuitOfRobot2(communication,bottom,nBottom);
        globalDisplay_.drawEmptyLinesInBoxToRobotDown(communication);   
    }
}

void DisplayManager::iterateDisplayTop(CommunicationRS232& communication, uint8_t nTop) {
    uint8_t nRepetition = 2;
    for (uint8_t j = 0; j < MAX_SEGMENTS; j++) {
        globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
        display_.drawEmptySpace(communication,LENGTH_OF_BOX);
        display_.drawVerticalBoldCharacter(communication);
        display_.drawEmptySpace(communication,SPACE_BOX_CIRCUIT);
        displayTopCircuitOfRobot2(communication,nTop);
    }
    for (uint8_t i = 0; i < nRepetition; i++) {
        globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
        display_.drawEmptySpace(communication,LENGTH_OF_BOX);
        display_.drawVerticalBoldCharacter(communication);
        display_.drawEmptySpace(communication,SPACE_BOX_CIRCUIT);
        display_.drawVerticalEqualCharacter(communication);
        display_.drawEmptySpace(communication,LENGTH_WITHOUT_SEGMENT);
        display_.drawVerticalEqualCharacter(communication);
    }
    globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
}

void DisplayManager::displayLastLineOfCircuit(CommunicationRS232& communication,Segment* bottom,uint8_t nBottom) {
    const char* unicodeBorderCharacter = u8"\u255A";
    const char* unicodeBorderEndCharacter = u8"\u255D";
    uint8_t countCharacters = 0;
    communication.transmitText(unicodeBorderCharacter);
    for (int8_t i = nBottom - 1; i >= 0; i--) {
        uint8_t nEqualCharacters = LENGTH_WITHOUT_SEGMENT - bottom[i].position - countCharacters;
        display_.drawTheEqualCharacter(communication,nEqualCharacters);
        display_.drawThreePathCharacterUp(communication);
        countCharacters += nEqualCharacters;
    }
    display_.drawTheEqualCharacter(communication,LENGTH_WITHOUT_SEGMENT - countCharacters - nBottom);
    communication.transmitText(unicodeBorderEndCharacter);
}

void DisplayManager::updateDisplayOfRobotIfTopUp(CommunicationRS232& communication,uint8_t nTop,Segment* top ) {
    globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
    display_.drawEmptySpace(communication,SPACE_TO_HORIZONTAL_CHARACTER);
    display_.drawHorizontalCharacter(communication,N_CHARACTERS);
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_FROM_HORIZONTAL_TO_END,SPACE_BOX_CIRCUIT);
    displayTopCircuitOfRobot2(communication,nTop);

    globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
    display_.drawEmptySpace(communication,SPACE_TO_CHARACTER_SLASH);
    globalDisplay_.drawSlashesOfRobot(communication,SPACE_BETWEEN_CHARACTER_SLASH);
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_FROM_SLASH_TO_END,SPACE_BOX_CIRCUIT);
    displayTopCircuitOfRobot2(communication,nTop);

    globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
    display_.drawEmptySpace(communication,SPACE_TO_VERTICAL_CHARACTER);
    globalDisplay_.drawVerticalCharacterOfRobot(communication,SPACE_BETWEEN_VERTICAL_CHARACTER_OF_ROBOT);
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_TO_END_BOX,SPACE_BOX_CIRCUIT);
    displayTopCircuitOfRobot2(communication,nTop);

    globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
    display_.drawEmptySpace(communication,SPACE_TO_WHEELS);
    globalDisplay_.drawWheelsOfRobot(communication,SPACE_BETWEEN_WHEELS);
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_TO_END_BOX,SPACE_BOX_CIRCUIT);
    displayTopCircuitOfRobot2(communication,nTop);

    globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
    display_.drawEmptySpace(communication,SPACE_TO_VERTICAL_CHARACTER);
    globalDisplay_.drawVerticalCharacterOfRobot(communication,SPACE_BETWEEN_VERTICAL_CHARACTER_OF_ROBOT);
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_TO_END_BOX,SPACE_BOX_CIRCUIT);
    displayTopCircuitOfRobot2(communication,nTop);

    globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
    display_.drawEmptySpace(communication,SPACE_TO_CHARACTER_SLASH);
    display_.drawHorizontalCharacter(communication,HORIZONTAL_CHARACTERS);             
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_FROM_SLASH_TO_END,SPACE_BOX_CIRCUIT);
    displayTopCircuitOfRobot2(communication,nTop);

    globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
    globalDisplay_.drawMiddleBox(communication);  
    globalDisplay_.drawEmptyLinesInBoxToRobotDown(communication);
    display_.drawVerticalEqualCharacter(communication);
    display_.drawEmptySpace(communication,LENGTH_WITHOUT_SEGMENT);
    display_.drawVerticalEqualCharacter(communication);
    globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
    globalDisplay_.drawEmptyLinesInBoxToRobotDown(communication);
} 

void DisplayManager::updateDisplayOfRobotIfBottomUp(CommunicationRS232& communication,uint8_t nBottom,Segment* bottom) {   
    globalDisplay_.drawMiddleBox(communication);
    display_.drawEmptySpace(communication,SPACE_TO_HORIZONTAL_CHARACTER);
    display_.drawHorizontalCharacter(communication,N_CHARACTERS);
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_FROM_HORIZONTAL_TO_END,SPACE_BOX_CIRCUIT);
    display_.drawVerticalEqualCharacter(communication);
    display_.drawEmptySpace(communication,LENGTH_WITHOUT_SEGMENT);
    display_.drawVerticalEqualCharacter(communication);

    globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
    display_.drawEmptySpace(communication,SPACE_TO_CHARACTER_SLASH);
    globalDisplay_.drawSlashesOfRobot(communication,SPACE_BETWEEN_CHARACTER_SLASH);
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_FROM_SLASH_TO_END,SPACE_BOX_CIRCUIT);
    displayBottomCircuitOfRobot2(communication,bottom,nBottom);

    display_.drawEmptySpace(communication,SPACE_TO_VERTICAL_CHARACTER);
    globalDisplay_.drawVerticalCharacterOfRobot(communication,SPACE_BETWEEN_VERTICAL_CHARACTER_OF_ROBOT);
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_TO_END_BOX,SPACE_BOX_CIRCUIT);
    displayBottomCircuitOfRobot2(communication,bottom,nBottom);

    display_.drawEmptySpace(communication,SPACE_TO_WHEELS);
    globalDisplay_.drawWheelsOfRobot(communication,SPACE_BETWEEN_WHEELS);
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_TO_END_BOX,SPACE_BOX_CIRCUIT);
    displayBottomCircuitOfRobot2(communication,bottom,nBottom);

    display_.drawEmptySpace(communication,SPACE_TO_VERTICAL_CHARACTER);
    globalDisplay_.drawVerticalCharacterOfRobot(communication,SPACE_BETWEEN_VERTICAL_CHARACTER_OF_ROBOT);
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_TO_END_BOX,SPACE_BOX_CIRCUIT);
    displayBottomCircuitOfRobot2(communication,bottom,nBottom);

    display_.drawEmptySpace(communication,SPACE_TO_CHARACTER_SLASH);
    display_.drawHorizontalCharacter(communication,HORIZONTAL_CHARACTERS);             
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_FROM_SLASH_TO_END,SPACE_BOX_CIRCUIT);

}
 
void DisplayManager::updateDisplayOfRobotIfBottomDown(CommunicationRS232& communication,uint8_t nBottom,Segment* bottom) { 
    globalDisplay_.drawMiddleBox(communication);
    display_.drawEmptySpace(communication,SPACE_TO_CHARACTER_SLASH);
    display_.drawHorizontalCharacter(communication,HORIZONTAL_CHARACTERS);             
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_FROM_SLASH_TO_END,SPACE_BOX_CIRCUIT);
    display_.drawVerticalEqualCharacter(communication);
    display_.drawEmptySpace(communication,LENGTH_WITHOUT_SEGMENT);
    display_.drawVerticalEqualCharacter(communication);


    globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
    display_.drawEmptySpace(communication,SPACE_TO_VERTICAL_CHARACTER);
    globalDisplay_.drawVerticalCharacterOfRobot(communication,SPACE_BETWEEN_VERTICAL_CHARACTER_OF_ROBOT);
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_TO_END_BOX,SPACE_BOX_CIRCUIT);
    displayBottomCircuitOfRobot2(communication,bottom,nBottom);

    display_.drawEmptySpace(communication,SPACE_TO_WHEELS);
    globalDisplay_.drawWheelsOfRobot(communication,SPACE_BETWEEN_WHEELS);
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_TO_END_BOX,SPACE_BOX_CIRCUIT);
    displayBottomCircuitOfRobot2(communication,bottom,nBottom);

    display_.drawEmptySpace(communication,SPACE_TO_VERTICAL_CHARACTER);
    globalDisplay_.drawVerticalCharacterOfRobot(communication,SPACE_BETWEEN_VERTICAL_CHARACTER_OF_ROBOT);
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_TO_END_BOX,SPACE_BOX_CIRCUIT);
    displayBottomCircuitOfRobot2(communication,bottom,nBottom);

    display_.drawEmptySpace(communication,SPACE_TO_CHARACTER_SLASH);
    globalDisplay_.drawSlashesOfBottomOrientedRobot(communication,SPACE_BETWEEN_CHARACTER_SLASH);
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_FROM_SLASH_TO_END,SPACE_BOX_CIRCUIT);
    displayBottomCircuitOfRobot2(communication,bottom,nBottom);

    display_.drawEmptySpace(communication,SPACE_TO_HORIZONTAL_CHARACTER);
    display_.drawHorizontalCharacter(communication,SPACE_BETWEEN_CHARACTER_SLASH);             
    globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_FROM_HORIZONTAL_TO_END,SPACE_BOX_CIRCUIT);
}

void DisplayManager::updateDisplayOfRobotIfTopDown(CommunicationRS232& communication,uint8_t nTop,Segment* top) {
        globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
        display_.drawEmptySpace(communication,SPACE_TO_CHARACTER_SLASH);
        display_.drawHorizontalCharacter(communication,HORIZONTAL_CHARACTERS);             
        globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_FROM_SLASH_TO_END,SPACE_BOX_CIRCUIT);
        displayTopCircuitOfRobot2(communication,nTop);

        globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
        display_.drawEmptySpace(communication,SPACE_TO_VERTICAL_CHARACTER);
        globalDisplay_.drawVerticalCharacterOfRobot(communication,SPACE_BETWEEN_VERTICAL_CHARACTER_OF_ROBOT);
        globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_TO_END_BOX,SPACE_BOX_CIRCUIT);
        displayTopCircuitOfRobot2(communication,nTop);

        globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
        display_.drawEmptySpace(communication,SPACE_TO_WHEELS);
        globalDisplay_.drawWheelsOfRobot(communication,SPACE_BETWEEN_WHEELS);
        globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_TO_END_BOX,SPACE_BOX_CIRCUIT);
        displayTopCircuitOfRobot2(communication,nTop);

        globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
        display_.drawEmptySpace(communication,SPACE_TO_VERTICAL_CHARACTER);
        globalDisplay_.drawVerticalCharacterOfRobot(communication,SPACE_BETWEEN_VERTICAL_CHARACTER_OF_ROBOT);
        globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_TO_END_BOX,SPACE_BOX_CIRCUIT);
        displayTopCircuitOfRobot2(communication,nTop);

        globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
        display_.drawEmptySpace(communication,SPACE_TO_CHARACTER_SLASH);
        globalDisplay_.drawSlashesOfBottomOrientedRobot(communication,SPACE_BETWEEN_CHARACTER_SLASH);
        globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_FROM_SLASH_TO_END,SPACE_BOX_CIRCUIT);
        displayTopCircuitOfRobot2(communication,nTop);

        globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
        display_.drawEmptySpace(communication,SPACE_TO_HORIZONTAL_CHARACTER);
        display_.drawHorizontalCharacter(communication,SPACE_BETWEEN_CHARACTER_SLASH);             
        globalDisplay_.drawCharactersFromRobotToCircuit(communication,SPACE_FROM_HORIZONTAL_TO_END,SPACE_BOX_CIRCUIT);
        display_.drawVerticalEqualCharacter(communication);
        display_.drawEmptySpace(communication,LENGTH_WITHOUT_SEGMENT);
        display_.drawVerticalEqualCharacter(communication);
        globalDisplay_.drawCharactersToBox(communication,SPACE_TO_FINAL);
        globalDisplay_.drawMiddleBox(communication);
        globalDisplay_.drawEmptyLinesInBoxToRobotDown(communication);
    }

bool DisplayManager::isPositionGreaterThanMaxPositionForTop(CommunicationRS232& communication,Segment* top,uint8_t nTop) {
    for (uint8_t k = 0; k < nTop; k++) {
        if (top[k].position > MAX_POSITION) {
            return true;
        }
    }
    return false;
} 

bool::DisplayManager::isPositionGreaterThanMaxPositionForBottom(CommunicationRS232& communication,Segment* bottom,uint8_t nBottom) {
    for (int8_t j = nBottom - 1; j >=0; j--) {
        if (bottom[j].position > MAX_POSITION) {
            return true;
        }
    }
    return false;
}