#include "GlobalDisplay.h"


GlobalDisplay::GlobalDisplay() {}


void GlobalDisplay::drawInFirstAndLastColumn(CommunicationRS232& communication, uint8_t size) {
    characters_.drawVerticalCharacter(communication);
    characters_.drawEmptySpace(communication,size);
    characters_.drawVerticalCharacter(communication);
}

void GlobalDisplay::drawCharactersToBox(CommunicationRS232& communication, uint8_t lengthOfSpacesToEnd) {
    characters_.drawEmptySpace(communication, lengthOfSpacesToEnd);
    characters_.drawVerticalCharacter(communication);
    characters_.drawEmptyLine(communication);
    characters_.drawVerticalCharacter(communication);
    characters_.drawEmptySpace(communication,SPACE_FROM_BORDER_TO_BOX);
    characters_.drawVerticalBoldCharacter(communication);
}


void GlobalDisplay::drawEmptyCharactersInsideBox(CommunicationRS232& communication) {
    characters_.drawEmptySpace(communication,LENGTH_OF_BOX);
    characters_.drawVerticalBoldCharacter(communication);
}

void GlobalDisplay::startDrawingBox(CommunicationRS232& communication) {
    uint8_t spaceFromBoxToEnd = 68;
    uint8_t nRepetition = 2; 
    characters_.drawLeftBoldBorderCharacter(communication);
    characters_.drawBoldCharacter(communication,LENGTH_OF_BOX);
    characters_.drawRightBoldBorderCharacter(communication);
    for (uint8_t k = 0; k < nRepetition; k++) {
        drawCharactersToBox(communication,spaceFromBoxToEnd);
        drawEmptyCharactersInsideBox(communication);
    }
}

void GlobalDisplay::drawEmptyLinesInBoxToRobotDown(CommunicationRS232& communication) {
    characters_.drawEmptySpace(communication,LENGTH_OF_BOX);
    characters_.drawVerticalBoldCharacter(communication);
    characters_.drawEmptySpace(communication,SPACE_BOX_CIRCUIT);    
}

void GlobalDisplay::drawMiddleBox(CommunicationRS232& communication) {
    uint8_t spaceToBeforeCircuit = 30;
    uint8_t lengthOfEqualCharacters = 6;
    uint8_t lengthBoxBeforeCircuit = 36;
    characters_.drawEmptySpace(communication,lengthBoxBeforeCircuit);
    characters_.drawVerticalEqualCharacter(communication);
    characters_.drawEmptySpace(communication,LENGTH_WITHOUT_SEGMENT);
    characters_.drawVerticalEqualCharacter(communication);
    drawCharactersToBox(communication,SPACE_TO_FINAL);
    characters_.drawEmptySpace(communication,spaceToBeforeCircuit);
    characters_.drawTheEqualCharacter(communication,lengthOfEqualCharacters);
    characters_.drawThreePathCharacterBeginningLeft(communication);
    characters_.drawEmptySpace(communication,LENGTH_WITHOUT_SEGMENT);
    characters_.drawVerticalEqualCharacter(communication);
    drawCharactersToBox(communication,SPACE_TO_FINAL);
    characters_.drawEmptySpace(communication,lengthBoxBeforeCircuit);
    characters_.drawVerticalEqualCharacter(communication);
    characters_.drawEmptySpace(communication,LENGTH_WITHOUT_SEGMENT);
    characters_.drawVerticalEqualCharacter(communication);
    drawCharactersToBox(communication,SPACE_TO_FINAL);
}

void GlobalDisplay::start(CommunicationRS232& communication) {
    characters_.drawLeftBorderCharacter(communication);
    characters_.drawHorizontalCharacter(communication,LENGTH_OF_TABLE);
    characters_.drawRightBorderCharacter(communication);
    for (uint8_t j = 0; j < ROWS_FROM_BORDER_TO_BOX; j++) {
        characters_.drawEmptyLine(communication);
        drawInFirstAndLastColumn(communication,LENGTH_OF_TABLE);
    }
    characters_.drawEmptyLine(communication);
    characters_.drawVerticalCharacter(communication);
    characters_.drawEmptySpace(communication,SPACE_FROM_BORDER_TO_BOX);
    startDrawingBox(communication);
    characters_.drawEmptySpace(communication,SPACE_BOX_CIRCUIT);
}

void GlobalDisplay::drawCharactersFromRobotToCircuit(CommunicationRS232& communication,uint8_t spaceFromRobotToEndBox, uint8_t spaceFromBoxToCircuit) {
    characters_.drawEmptySpace(communication,spaceFromRobotToEndBox);
    characters_.drawVerticalBoldCharacter(communication);
    characters_.drawEmptySpace(communication,SPACE_BOX_CIRCUIT);    
}

void GlobalDisplay::writeNameOfRobot(CommunicationRS232& communication) {
    const char* nameOfRobot = "Produit par: Atlas";
    communication.transmitText(nameOfRobot);
}

void GlobalDisplay::drawFinalLines(CommunicationRS232& communication) {
    uint8_t nEmptyLineSpaces = 2;
    const char* borderLeftCharacter = u8"\u2517";
    const char* borderRightCharacter = u8"\u251B";
    drawCharactersToBox(communication,SPACE_TO_FINAL);
    characters_.drawEmptySpace(communication,LENGTH_OF_BOX);
    characters_.drawVerticalBoldCharacter(communication);
    characters_.drawEmptySpace(communication,SPACE_BOTTOM_BOX_T0_FINAL);
    characters_.drawVerticalCharacter(communication);
    characters_.drawEmptyLine(communication);
    characters_.drawVerticalCharacter(communication);
    characters_.drawEmptySpace(communication,SPACE_FROM_BORDER_TO_BOX);
    communication.transmitText(borderLeftCharacter);
    characters_.drawBoldCharacter(communication,LENGTH_OF_BOX);
    communication.transmitText(borderRightCharacter);
    characters_.drawEmptySpace(communication,SPACE_BOTTOM_BOX_T0_FINAL);
    characters_.drawVerticalCharacter(communication);

    for (uint8_t j = 0; j < nEmptyLineSpaces; j++) {
        characters_.drawEmptyLine(communication);
        characters_.drawVerticalCharacter(communication);
        characters_.drawEmptySpace(communication,LENGTH_OF_TABLE);
        characters_.drawVerticalCharacter(communication);
    }
    characters_.drawEmptyLine(communication);
    communication.transmitText(u8"\u2514");
    characters_.drawHorizontalCharacter(communication,LENGTH_OF_TABLE);
    communication.transmitText(u8"\u2518");
    characters_.drawEmptyLine(communication);
}

void GlobalDisplay::drawSlashesOfRobot(CommunicationRS232& communication,uint8_t nSpace) {
    characters_.drawSlash(communication);
    characters_.drawEmptySpace(communication,nSpace);
    characters_.drawBackSlash(communication);
}

void GlobalDisplay::drawSlashesOfBottomOrientedRobot(CommunicationRS232& communication,uint8_t nSpace) {
    characters_.drawBackSlash(communication);
    characters_.drawEmptySpace(communication,nSpace);
    characters_.drawSlash(communication);
}

void GlobalDisplay::drawVerticalCharacterOfRobot(CommunicationRS232& communication,uint8_t spaceBetweenCharacters) {
    characters_.drawVerticalCharacter(communication);
    characters_.drawEmptySpace(communication,spaceBetweenCharacters);
    characters_.drawVerticalCharacter(communication);
}

void GlobalDisplay::drawWheelsOfRobot(CommunicationRS232& communication,uint8_t spaceBetweenWheels) {
    characters_.drawTheWeirdRobotCharacter(communication);
    characters_.drawEmptySpace(communication,spaceBetweenWheels);
    characters_.drawTheWeirdRobotCharacter(communication);
}