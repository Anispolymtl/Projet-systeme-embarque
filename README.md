Construction en équipe d'un système matériel et logiciel basé sur une carte à microcontrôleur pour le cours INF1900 enseigné par Jérôme Collin.







<img width="426" alt="Screenshot 2024-09-08 at 3 11 18 PM" src="https://github.com/user-attachments/assets/b77e7d2a-371f-4063-9cb0-bf41bb83b954">



# Projet Initial de Système Embarqué - INF1900

## Auteurs :
Joey Hasrouny, Clément Lebeau, Anis Menouar

## Équipe 132-133: Atlas

---

Notre projet consiste à utiliser nos deux robots afin d'effectuer différentes tâches sur une table de 4 par 8 pieds.

1. **Robot 1 :**
   - Selon la position que l'évaluateur attribuera au robot, celui-ci devra réussir, tout en suivant la ligne jaune, à se positionner sur le point rouge et à pointer vers l'ouverture de la boîte.
   - Il aura préalablement enregistré sa position initiale et attendra que le robot deux termine son parcours pour recevoir des données par le robot 2 via communication infrarouge.
   - Pour finir l'épreuve, ce robot enverra via RS232 au PC l'affichage complet du circuit.


2. **Robot 2 :**
   - Ce robot va utiliser le MakerLine (Le capteur de ligne) pour réussir à naviguer à travers le cadre et les nouveaux segments ajoutés par l'évaluateur.
   - Après avoir terminé la navigation à travers le cadre et tous les segments, il va se positionner sur le segment DC en pointant vers l'ouverture.
   - Il pourra ensuite commencer la transmission infrarouge des informations du cadre et des nouveaux segments au Robot 1
   - Si un problème survient au niveau de la commuincation infrarouge, il sera possible au robot 2 d'afficher un circuit par défaut via communication RS232 

--- 

**Les branchements additionnelles aux deux robots :**

1. Robot 1: 
   A7 pour le capteur de distance
   A3 (Logiciel) pour le récepteur infrarouge 

2. Robot 2:
   C0 à C4 ainsi que le GND et VCC du PORTC pour le MakerLine
   D5 et D6 (logiciel) pour la Led Infra-Rouge


3. Pour les deux robots:
   Il est important que la deuxième moitié du port B soit libre lors du `make install` (broches 5-8 matérielles, 4-8 logicielles). Lors du rebranchement sur le Robot1, le fil noir doit être sur la broche B5 (matérielle) et le blanc sur B6 (matérielle). Pour le Robot2, il faut rebrancher le fil mauve sur la broche B5 (matérielle) et le fil vert sur B6 (matérielle). 


**Informations importantes :**
- **Robot1.cpp et Robot2.cpp :** Contient les machines à états pour chacun des robots. Permet de n'appeler que la méthode start dans le main de app1 et app2  
- **L'affichage :** . La classe CharacterDisplay gère l’affichage Unicode des caractères du schéma. GlobalDisplay affiche les parties du schéma qui se répètent ou qui ne changent pas, puis DisplayManager en gros s’occupe de trouver les bonnes distances entre les segments puis la bonne orientation du robot (dans le cas où le robot 1 fait l’affichage) et les affiche.


Merci beaucoup 

Équipe 132-133

17 avril 2024
