#include "CharacterDisplay.h"

CharacterDisplay::CharacterDisplay() {}

void CharacterDisplay::drawThreePathCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2566");
}

void CharacterDisplay::drawThreePathCharacterBeginningLeft(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2563");
}

void CharacterDisplay::drawThreePathCharacterUp(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2569");
}

void CharacterDisplay::drawLeftBoldBorderCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u250F");
}

void CharacterDisplay::drawRightBoldBorderCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2513");
}

void CharacterDisplay::drawLeftBorderCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u250C");
}

void CharacterDisplay::drawRightBorderCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2510");
}

void CharacterDisplay::drawHorizontalCharacter(CommunicationRS232& communication, uint8_t nCharacters) {
    for (uint8_t i = 0; i < nCharacters; i++)
        communication.transmitText(u8"\u2500");
}

void CharacterDisplay::drawBoldCharacter(CommunicationRS232& communication, uint8_t nCharacters) {
    for (uint8_t i = 0; i < nCharacters; i++) {
        communication.transmitText(u8"\u2501");
    }
}

void CharacterDisplay::drawVerticalBoldCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2503");
}

void CharacterDisplay::drawVerticalCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2502");
}

void CharacterDisplay::drawBorderRightEqualCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2557");
}

void CharacterDisplay::drawTheEqualCharacter(CommunicationRS232& communication,uint8_t nCharacters) {
    for (uint8_t i = 0; i < nCharacters; i++) {
        communication.transmitText(u8"\u2550");
    }
}

void CharacterDisplay::drawTheWeirdRobotCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2593");
}

void CharacterDisplay::drawVerticalEqualCharacter(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2551");
}

void CharacterDisplay::drawSlash(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2571");
}

void CharacterDisplay::drawBackSlash(CommunicationRS232& communication) {
    communication.transmitText(u8"\u2572");
}

void CharacterDisplay::drawEmptyLine(CommunicationRS232& communication) {
    communication.transmitText(u8"\u000A");
}

void CharacterDisplay::drawEmptySpace(CommunicationRS232& communication, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        communication.transmitText(u8"\u0020");
    }
}
