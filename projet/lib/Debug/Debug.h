/**
 * Auteur: Clément Lebeau
 *
 * Description: Fichier d'en-tête Debug.h qui implémente des macros pour des
 * fins de débogage seulement si la macro DEBUG est définie. Si ce n'est pas le
 * cas, les macros deviendront du code mort qui sera optimisé par le
 * compilateur.
 *
 * Description matérielle:
 * Idem à Communication RS232 (voir ../CommunicationR2322/CommunicationR2322.h)
 *
 * Description logicielle:
 * Les macros DEBUG_PRINT(x) assument l'existence d'une instance de
 * CommunicationRS232 appellée communicationRS232 accessible là ou
 * DEBUG_PRINT(x) est appellée
 */

#pragma once

#include "CommunicationRS232/CommunicationRS232.h"

#ifdef DEBUG
# define DEBUG_PRINT(x) communicationRS232.transmitText(x)
# define DEBUG_PRINTF(format, ...) \
    communicationRS232.transmitFormatted(format, __VA_ARGS__)
#else // ndef DEBUG
# define DEBUG_PRINT(x) \
    do { \
    } while(false);
# define DEBUG_PRINTF(x, ...) \
    do { \
    } while(false);
#endif // DEBUG
