# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes

Identification:

- Travail : Projet
- Section # : 6
- Équipe # : 132133
- Correcteur : Ghali Chraibi

# LISIBILITÉ

## En-têtes en début de programme

| Pénalité par erreur                       | -1.5          |
| ----------------------------------------- | ------------- |
| Noms des auteurs                          |               |
| Description du programme                  |               |
| Identifications matérielles (Broches I/O) |               |
| Table des états ou autres s'il y a lieu   |               |
| **Résultat partiel**                      | **(1.5/1.5)** |

Des descriptions détaillées étaient attendues pour chaque programme dans les dossier `app*`, mais je vous ai accordé les points vu que tous les fichiers de votre librairie contiennent des en-têtes détaillées et que les descriptions matérielles complètes des deux robots sont présentes dans le README.

## Identificateurs significatifs (Autodocumentation)

| Points importants                       | Poids         |
| --------------------------------------- | ------------- |
| Absence de _chiffres magiques_          | (0/0.5)       |
| Noms de variables décrivent l'intention | (0.3/0.5)     |
| Noms de fonctions décrivent l'intention | (/0.5)        |
| **Résultat partiel**                    | **(0.8/1.5)** |

- Plusieurs nombres magiques dans `Robot1.cpp`. (-0.5)
- Les variables et constantes doivent être encapsulées dans des classes ou des namespace afin de ne pas polluer l'espace global. (-0.2)
- Excellents choix de noms de variables et de fonctions. Bravo!

## Commentaires pertinents

Bonnes raisons d'un commentaire

- Explication d'un algorithme
- Procédure peu évidente (ou _hack_)
- Référence d'extraits de code copiés d'Internet
- Détail du POURQUOI d'un extrait de code

| Pénalité par erreur  | -0.5          |
| -------------------- | ------------- |
| **Résultat partiel** | **(0.5/1.0)** |

- Plusieurs commentaires auraient pu être évités par des noms de variables significatifs ou des noms de fonctions implémentant le bloc commenté. (-0.5)

## Indentation

| Points importants                      | Poids       |
| -------------------------------------- | ----------- |
| Indentation structurée                 | (/0.5)      |
| Indentation uniforme dans le programme | (/0.5)      |
| **Résultat partiel**                   | **(1/1.0)** |

# MODULARITÉ ET COMPRÉHENSION

## Fonctions bien définies

| Pénalité par erreur                  | -0.5          |
| ------------------------------------ | ------------- |
| Responsabilité unique d'une fonction |               |
| Maximum de 4 paramètres              |               |
| Absence de code dupliqué             |               |
| etc                                  |               |
| **Résultat partiel**                 | **(0.5/1.0)** |

- Quelques fonctions auraient pu être divisées en plusieurs fonctions plus petites (ex: `updateDisplayOfRobotIfTopUp`, `executeReadyToSendState`, etc.). (-0.5)

- En général, vous avez une excellente modularité dans votre code. Super bel effort!

## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0        |
| -------------------------------------------- | ----------- |
| Utilisation appropriée des registres         |             |
| Machine à états codée clairement             |             |
| Délais et minuteries utilisés judicieusement |             |
| PWM bien établi                              |             |
| Scrutation et interruptions bien utilisées   |             |
| etc                                          |             |
| **Résultat partiel**                         | **(4/4.0)** |

- Très bonne gestion des interruptions et des minuteries. Aussi, bonne utilisation des machines à états.

# FONCTIONNALITÉS

## Git

| Points importants            | Poids       |
| ---------------------------- | ----------- |
| Fichiers aux bons endroits   | (/1.5)      |
| Absence de fichiers inutiles | (/1.5)      |
| **Résultat partiel**         | **(3/3.0)** |

## Compilation

| Points importants                            | Poids       |
| -------------------------------------------- | ----------- |
| Absence de messages d'erreurs de compilation | (/1.5)      |
| Absence de messages d'attention (_warning_)  | (/0.5)      |
| **Résultat partiel**                         | **(2/2.0)** |

## Évaluation boîte noire

| Points importants            | Poids       |
| ---------------------------- | ----------- |
| Cas normal de fonctionnement | (/2.5)      |
| Cas limites observables      | (/2.5)      |
| **Résultat partiel**         | **(5/5.0)** |

# Résultat

__Total des points: 18.3/20__

# Commentaires du correcteur :

Excellent travail. Vous avez déployé beaucoup d'efforts dans l'auto-documentation et la modularité de votre code. Vous pouvez être fiers de votre travail. Félicitations!

# Basé sur le commit suivant

```
commit 64ced286fb596ddcc80d4a2d23eccb3e260df820
Author: Clément Lebeau <clement.lebeau@polymtl.ca>
Date:   Wed Apr 17 00:37:13 2024 -0400

    Commit final.
```

# Fichiers indésirables pertinents

Aucun

# Tous les fichiers indésirables

```
equipe-132/tp/.DS_Store
equipe-132/tp/tp5/pb1/memoire_24.h.gch
```

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `projet/lib`

```
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Button/Button.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Can/Can.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c CharacterDisplay/CharcterDisplay.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c CommunicationRS232/CommunicationRS232.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c DisplayManager/DisplayManager.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c DistanceSensor/DistanceSensor.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Eeprom/Eeprom.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c GlobalDisplay/GlobalDisplay.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Infrared/IrReceiver.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Infrared/IrTransmitter.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Led/Led.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c MakerLine/MakerLine.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Navigation/Navigation.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Piezo/Piezo.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Segment/Segment.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Timer1/Timer1.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Wheels/Wheels.cpp
avr-ar crs libstatique.a Button.o Can.o CharcterDisplay.o CommunicationRS232.o DisplayManager.o DistanceSensor.o Eeprom.o GlobalDisplay.o IrReceiver.o IrTransmitter.o Led.o MakerLine.o Navigation.o Piezo.o Segment.o Timer1.o Wheels.o

```

## Sortie de `make` dans `projet/app1`

```
avr-gcc -I. -I/usr/include/simavr -MMD -I../lib  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c main.cpp
avr-gcc -I. -I/usr/include/simavr -MMD -I../lib  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Robot1.cpp
avr-gcc -Wl,-Map,app1.elf.map -mmcu=atmega324pa -o app1.elf  main.o Robot1.o \
	-lm -lstatique -L../lib
avr-objcopy -j .text -j .data -O ihex app1.elf app1.hex

```

## Sortie de `make` dans `projet/app2`

```
avr-gcc -I. -I/usr/include/simavr -MMD -I../lib -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c main.cpp
avr-gcc -I. -I/usr/include/simavr -MMD -I../lib -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Robot2.cpp
avr-gcc -Wl,-Map,projet.elf.map -mmcu=atmega324pa -o projet.elf  main.o Robot2.o \
	-lm -lstatique -L../lib
avr-objcopy -j .text -j .data -O ihex projet.elf projet.hex

```
