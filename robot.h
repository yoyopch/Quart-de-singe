
#ifndef _ROBOT_
#define _ROBOT_

#include "Header.h"
#include "partie.h"
#include "dico.h"

void trouve_Dico_Robot(Dico& idico, Partie& partie);


void ajoutLettre(Partie& partie);




void LettreAleatoireRobot(Partie& partie);





int LettreRobot(Dico& idico, Partie& partie, unsigned int indice, int& indexmotdudico);





int trouve_mot_DICO(Dico& idico, Partie& partie, int& indexmotdudico);







void resetListeLettre(char* listeLettre);






int VerifLettreUtil(char lettre, char* listeLettre);












int AjoutLettreUtil(char lettre, char* listeLettre);











int verifDebutMot(Dico& idico, Partie& partie, char mot[], unsigned int& nbNombre, char* listeLettre);








#endif



