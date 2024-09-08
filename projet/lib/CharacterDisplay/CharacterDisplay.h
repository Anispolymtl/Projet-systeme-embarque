/*
 * Auteur: Joey Hasrouny
 *
 * Description: Définition de la classe ChracterDisplay qui implémente
 * des méthodes d'affichage des charactères unicodes, chacun implémenter
 * individuellement. Nous utilisons la classe CommunicationRS232 pour
 * la transmission.

 * Description matérielle:
 * Garder le cavalier DbgEn actif sur la carte mère.
 * Ports D0 D1 utilisés pour la transmission.
 * Utiliser le programme serieViaUSB (voir description TP5) pour la
 * transmission des données émises par RS232, de la carte mère vers
 * le câble USB.
 *
 */

#pragma once
#include "CommunicationRS232/CommunicationRS232.h"

const uint8_t ROWS_FROM_BORDER_TO_BOX = 2;
const uint8_t SPACE_FROM_BORDER_TO_BOX = 5;
const uint8_t LENGTH_OF_BOX = 25;
const uint8_t LENGTH_WITHOUT_SEGMENT = 48;
const uint8_t LENGTH_OF_TABLE = 100;
const uint8_t SPACE_BOTTOM_BOX_T0_FINAL = 68;
const uint8_t SPACE_BOX_CIRCUIT = 10;
const uint8_t SPACE_TO_FINAL = 8;
const uint8_t SPACE_BETWEEN_VERTICAL_CHARACTER_OF_ROBOT = 6;
const uint8_t SPACE_BETWEEN_WHEELS = 6;


class CharacterDisplay {
public:
    CharacterDisplay();
    void drawThreePathCharacter(CommunicationRS232& communication);
    void drawThreePathCharacterBeginningLeft(CommunicationRS232& communication);
    void drawThreePathCharacterUp(CommunicationRS232& communication);
    void drawLeftBoldBorderCharacter(CommunicationRS232& communication);
    void drawRightBoldBorderCharacter(CommunicationRS232& communication);
    void drawLeftBorderCharacter(CommunicationRS232& comnunication);
    void drawRightBorderCharacter(CommunicationRS232& communication);
    void drawHorizontalCharacter(CommunicationRS232& communication, uint8_t nCharacters);
    void drawBoldCharacter(CommunicationRS232& communication, uint8_t nCharacters);
    void drawVerticalBoldCharacter(CommunicationRS232& communication);
    void drawVerticalCharacter(CommunicationRS232& communication);
    void drawBorderRightEqualCharacter(CommunicationRS232& communication);
    void drawTheEqualCharacter(CommunicationRS232& communication, uint8_t nCharacters);
    void drawTheWeirdRobotCharacter(CommunicationRS232& communication);
    void drawVerticalEqualCharacter(CommunicationRS232& communication);
    void drawSlash(CommunicationRS232& communication);
    void drawBackSlash(CommunicationRS232& communication);
    void drawEmptyLine(CommunicationRS232& communication);
    void drawEmptySpace(CommunicationRS232& communication, uint8_t length);
};