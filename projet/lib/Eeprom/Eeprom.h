/*
 * Auteur: Isidore Lauzier
 * 9 juillet 2005
 *
 * Adapté par Clément Lebeau
 * Mars 2024
 *
 * Description: Classe qui simplifie la communication avec la mémoire EEPROM
 * externe sur la carte-mère du robot. Emploie le protocole de communication I2C
 *
 * Description matérielle:
 * Les broches C0 et C1 sont utilisées lors de la communication I2C.
 */

#pragma once

#ifndef F_CPU
# define F_CPU 8000000UL
#endif // F_CPU

#include <avr/io.h>
#include <util/twi.h>

class Eeprom {
public:
   Eeprom(); // le constructeur appelle init() decrit plus bas
   ~Eeprom();

   // procedure d'initialisation appelee par le constructeur
   // Donc, ne pas le refaire a moins de changements en cours
   // d’utilisation.
   void init();

   // la procedure init() initialize a zero le "memory bank".
   // appeler cette methode uniquement si l'adresse doit changer
   static uint8_t choisir_banc(const uint8_t banc);

   // deux variantes pour la lecture, celle-ci et la suivante
   // une donnee a la fois
   uint8_t lecture(const uint16_t adresse, uint8_t* donnee);
   // bloc de donnees : longueur doit etre de 127 et moins
   uint8_t
   lecture(const uint16_t adresse, uint8_t* donnee, const uint8_t longueur);

   // deux variantes pour la l'ecriture egalement:
   // une donnee a la fois
   uint8_t ecriture(const uint16_t adresse, const uint8_t donnee);
   // bloc de donnees : longueur doit etre de 127 et moins
   uint8_t
   ecriture(const uint16_t adresse, uint8_t* donnee, const uint8_t longueur);

private:
   // pour l'ecriture
   uint8_t
   ecrire_page(const uint16_t adresse, uint8_t* donnee, const uint8_t longueur);

private:
   // donnees membres
   static uint8_t m_adresse_peripherique;
   const uint8_t PAGE_SIZE;
};
