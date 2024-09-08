/*
 * Auteur: Clément Lebeau
 * Février 2024
 * 
 * Description: Définition de la classe Wheels qui contrôle la configuration des
 * registres pour le PWM, la vitesse et la direction de chaque roue.
 *
 * Description matérielle:
 * Les broches B3 et B4 (logicielles) sont utilisées en sortie comme les deux
 * signaux PWM des roues (gauche et droite respectivement).
 *
 * Les broches B2 et B5 (logicielles) sont utilisées en sorties pour
 * contrôller la direction des roues (gauche et droite respectivement).
 *
 * Le Pont H doit être alimenté (9V, 1A sur la source de tension ou avec 6x
 * piles AA)
 *
 * La broche B3 (matérielle) est branchée au D de gauche du pont H
 * La broche B4 (matérielle) est branchée au E de gauche du pont H
 *
 * La broche B6 (matérielle) est branchée au D de droite du pont H
 * La broche B5 (matérielle) est branchée au E de droite du pont H
 */

#pragma once

#include <avr/io.h>

class Wheels {
public:
   Wheels();

   void setPwmPercentage(uint8_t percentage);
   void setPwmPercentageLeft(uint8_t percentage);
   void setPwmPercentageRight(uint8_t percentage);

   void setDirection(bool isForward);
   void setDirectionLeft(bool isForward);
   void setDirectionRight(bool isForward);

private:
   static constexpr uint8_t PWM_TOP = 0xFF;

   uint8_t getNumberOfCyclesFromPercentage(uint8_t percentage);
};
