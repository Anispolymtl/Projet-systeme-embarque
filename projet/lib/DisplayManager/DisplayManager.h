/*
 * Auteur: Joey Hasrouny
 *
 * Description: Définition de la classe DisplayManager qui s'occupe d'afficher
 * correctement le nombres de charactères correspondant entre les différents
 * segments du circuit. Cette classe s'occupe aussi de mettre le robot à sa bonne 
 * position de départ et de bien afficher son orientation selon cette position.
 * 
 *
 * Description matérielle:
 * Garder le cavalier DbgEn actif sur la carte mère.
 * Ports D0 D1 utilisés pour la transmission.
 * Utiliser le programme serieViaUSB (voir description TP5) pour la
 * transmission des données émises par RS232, de la carte mère vers
 * le câble USB.
 *
 */

#pragma once
#include "GlobalDisplay/GlobalDisplay.h"
#include "Segment/Segment.h"

class DisplayManager {
public:

    DisplayManager(CharacterDisplay& display, GlobalDisplay& globalDisplay);
    void displayFirstLineCircuitOfRobot2(CommunicationRS232& communication,Segment* top,uint8_t nTop);
    void displayTopCircuitOfRobot2(CommunicationRS232& communication,uint8_t nTop);
    void displayMiddleBoxIfRobotInBottom(CommunicationRS232& communication);
    void updateDisplayOfRobotIfTopUp(CommunicationRS232& communication,uint8_t nTop,Segment* top);
    void updateDisplayOfRobotIfTopDown(CommunicationRS232& communication,uint8_t nTop,Segment* top);
    void updateDisplayOfRobotIfBottomUp(CommunicationRS232& communication,uint8_t nBottom,Segment* bottom);
    void updateDisplayOfRobotIfBottomDown(CommunicationRS232& communication,uint8_t nBottom,Segment* bottom);
    void displayLastLineOfCircuit(CommunicationRS232& communication,Segment* bottom,uint8_t nBottom);
    void initialiseBottomVerticalProgress(CommunicationRS232& communication,Segment* bottom,uint8_t nBottom);
    void iterateDisplayBottom(CommunicationRS232& communication,Segment* bottom, uint8_t nBottom);
    void iterateDisplayTop(CommunicationRS232& communication,uint8_t nTop);
    bool isPositionGreaterThanMaxPositionForTop(CommunicationRS232& communication,Segment* top,uint8_t nTop);
    bool isPositionGreaterThanMaxPositionForBottom(CommunicationRS232& communication,Segment* bottom,uint8_t nBottom);

private:
    CharacterDisplay display_;
    GlobalDisplay globalDisplay_;
    void displayBottomCircuitOfRobot2(CommunicationRS232& communication,Segment* bottom, uint8_t nBottom);
    static const size_t MAX_SEGMENTS = 4;
    uint8_t topSegmentPositions_[MAX_SEGMENTS];
    uint8_t topVerticalProgress_[MAX_SEGMENTS];
    uint8_t bottomVerticalProgress_[MAX_SEGMENTS];
    uint8_t linesToSkip_[MAX_SEGMENTS];
    static constexpr uint8_t SPACE_TO_CHARACTER_SLASH = 10;
    static constexpr uint8_t SPACE_TO_HORIZONTAL_CHARACTER = 11;
    static constexpr uint8_t SPACE_FROM_HORIZONTAL_TO_END = 10;
    static constexpr uint8_t SPACE_FROM_SLASH_TO_END = 9;
    static constexpr uint8_t N_CHARACTERS = 4;
    static constexpr uint8_t SPACE_BETWEEN_CHARACTER_SLASH = 4;
    static constexpr uint8_t SPACE_TO_VERTICAL_CHARACTER = 9;
    static constexpr uint8_t SPACE_TO_WHEELS = 9;
    static constexpr uint8_t SPACE_TO_END_BOX = 8;
    static constexpr uint8_t HORIZONTAL_CHARACTERS = 6;
    static constexpr uint8_t MAX_POSITION = 48;
};