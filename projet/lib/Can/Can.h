/*
 * Auteurs: Matthew Khouzam et Jerome Collin
 * 2005-2006
 * 
 * Adapté par Clément Lebeau
 * Mars 2024
 * 
 * Description: Classe permettant l'acces au convertisseur analogique/numerique
 * du microcontroleur ATMega16 de Atmel.
 *
 * Description matérielle: 
 * Seules les broches du port A peuvent être utilisées avec le Can
 */

#pragma once

#include <avr/io.h> 

/*
 * Classe Can:
 *   Le constructeur initialise le convertisseur.
 *   Une lecture enclanche une conversion et le resultat
 *   est retourne sur 16 bits.
 *
 */

class Can
{
public:

   Can();
   ~Can();

   // retourne la valeur numerique correspondant a la valeur
   // analogique sur le port A.  pos doit etre entre 0 et 7
   // inclusivement.  Seulement les 10 bits de poids faible
   // sont significatifs.
   uint16_t lecture(uint8_t pos);

private:
   // Donnees membres - aucun

};
