/*
 * Auteur: Joey Hasrouny
 *
 * Description: Définition de la classe GlobalDisplay qui affiche l'ensemble des 
 * charactères unicode du schéma qui se répète ou ne change pas dans le circuit. Cette 
 * classe utilise à la fois CharacterDisplay et CommunicationRS232 pour la 
 * transmission. Cette classe implémente aussi les fonctionnalités pour afficher 
 * les charactères du robot, qui ne change pas.
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
#include "CommunicationRS232/CommunicationRS232.h"
#include "CharacterDisplay/CharacterDisplay.h"

class GlobalDisplay {
public:
    GlobalDisplay();
    void start(CommunicationRS232& communication);
    void drawCharactersFromRobotToCircuit(CommunicationRS232& communication,uint8_t spaceFromRobotToEndBox, uint8_t spaceFromBoxToCircuit);
    void drawSlashesOfRobot(CommunicationRS232& communication,uint8_t nSpace);
    void drawSlashesOfBottomOrientedRobot(CommunicationRS232& communication,uint8_t nSpace);
    void drawVerticalCharacterOfRobot(CommunicationRS232& communication,uint8_t spaceBetweenCharacters);
    void drawWheelsOfRobot(CommunicationRS232& communication,uint8_t spaceBetweenWheels);
    void drawCharactersToBox(CommunicationRS232& communication,uint8_t lengthOfSpacesToEnd);
    void drawEmptyLinesInBoxToRobotDown(CommunicationRS232& communication);
    void drawMiddleBox(CommunicationRS232& communication);
    void drawFinalLines(CommunicationRS232& communication);
    void writeNameOfRobot(CommunicationRS232& communication);    
    
private:
    void drawInFirstAndLastColumn(CommunicationRS232& communication, uint8_t size);
    void drawEmptyCharactersInsideBox(CommunicationRS232& communication);
    void startDrawingBox(CommunicationRS232& communication);
    CharacterDisplay characters_;
};