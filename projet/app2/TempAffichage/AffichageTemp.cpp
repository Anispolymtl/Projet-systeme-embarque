#define F_CPU 8000000
#include <avr/io.h>
#include "CommunicationRS232/CommunicationRS232.h"
#include "stdint.h"


// Code partiellement rempli non complété


const uint8_t ROWS_FROM_BORDER_TO_BOX = 2;
const uint8_t SPACE_FROM_BORDER_TO_BOX = 5;
const uint8_t LENGTH_OF_BOX = 25;
const uint8_t LENGTH_OF_TABLE = 100;

void drawAddedSegment(CommunicationRS232& communication, uint8_t lengthOfSegment) {
    communication.transmitText(u8"\u2566");
}

void drawThreePathCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2566");
}

void drawThreePathCharacterBeginningLeft(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2563");
}

void drawThreePathCharacterUp(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2569");
}

void drawLeftBorderCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u250F");
}

void drawRightBorderCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2513");
}

void drawHorizontalCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2500");
}

void drawBoldCharacter(CommunicationRS232& communication, uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        communication.transmitText(u8"\u2501");
    }
}

void drawVerticalBoldCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2503");
}

void drawVerticalCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2502");
}

void drawBorderRightEqualCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2557");
}

void drawTheEqualCharacter(CommunicationRS232& communication,uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        communication.transmitText(u8"\u2550");
    }
}

void drawTheWeirdRobotCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2593");
}

void drawVerticalEqualCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2551");
}

void drawBackSlash(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2572");
}

void drawEmptyLine(CommunicationRS232& communication) {
    communication.transmitText(u8"\u000A");
}

void drawEmptySpace(CommunicationRS232& communication, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        communication.transmitText(u8"\u0020");
    }
}

void drawInFirstAndLastColumn(CommunicationRS232& communication, uint8_t size) {
    drawVerticalCharacter(communication);
    drawEmptySpace(communication,size);
    drawVerticalCharacter(communication);
}

void drawCharactersToBox(CommunicationRS232& communication, uint8_t lengthOfSpacesToEnd) {
    drawEmptySpace(communication, lengthOfSpacesToEnd);
    drawVerticalCharacter(communication);
    drawEmptyLine(communication);
    drawVerticalCharacter(communication);
    drawEmptySpace(communication,SPACE_FROM_BORDER_TO_BOX);
}

void drawCharactersInsideBox(CommunicationRS232& communication) {
    drawVerticalBoldCharacter(communication);
    drawEmptySpace(communication,LENGTH_OF_BOX);
    drawVerticalBoldCharacter(communication);
}

void startDrawingBox(CommunicationRS232& communication) {
    uint8_t spaceFromBoxToEnd = 68;
    uint8_t nRepetition = 2;
    communication.transmitText(u8"\u250F");
    drawBoldCharacter(communication,LENGTH_OF_BOX);
    communication.transmitText(u8"\u2513");
    for (uint8_t k = 0; k < nRepetition; k++) {
        drawCharactersToBox(communication,spaceFromBoxToEnd);
        drawCharactersInsideBox(communication);
    }
}

void start(CommunicationRS232& communication, uint8_t size) {
    communication.transmitText(u8"\u250C");
    for (uint8_t i = 0; i < size; i++) {
        drawHorizontalCharacter(communication);
    }
    communication.transmitText(u8"\u2510");
    for (uint8_t j = 0; j < ROWS_FROM_BORDER_TO_BOX; j++) {
        drawEmptyLine(communication);
        drawInFirstAndLastColumn(communication,size);
    }
    drawEmptyLine(communication);
    drawVerticalCharacter(communication);
    drawEmptySpace(communication,SPACE_FROM_BORDER_TO_BOX);
    startDrawingBox(communication);
}

int main() {
    CommunicationRS232 communication;
    communication.enableTransmit();
    start(communication, LENGTH_OF_TABLE);
    return 0;
}
