
#ifndef _AFFICHAGE_
#define _AFFICHAGE_

#include "partie.h"
#include "dico.h"







void afficheScore(Dico& idico, Partie& partie);





void affichageTexte(const Partie& partie);






void abandonJoueur(Dico& idico, Partie& partie, unsigned int indice);







void AffichemotExistePas(Dico& idico, Partie& partie, unsigned int indice, char mot[]);






void afficheMotExiste(Dico& idico, Partie& partie, unsigned int indice, char trouve_mot[]);





void debutMotFaux(Dico& idico, Partie& partie, unsigned int indice, char mot[]);




#endif