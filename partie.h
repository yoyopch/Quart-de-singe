#ifndef _PARTIE_
#define _PARTIE_

#include "Header.h"

struct Partie {
  char mot[MAX_CHAR];
  unsigned int taillemot;
  unsigned int nbJoueurs;
  unsigned int dernierJoueurPerdant;
  BOOL nouveauTour;
  char motJoueurDeviner[MAX_CHAR];
  char* ordre;
  float* score;
  char motRobot[1];
};


#include "partie.h"
#include "dico.h"






void EffacerJeu(Dico& idico, Partie& partie);


void AfficheGameOver();


unsigned int finduJeu( Partie& partie);


void init(Partie& partie, char pl[]);


int ajoutLettre(Partie& partie, unsigned int indice);


void nouvelleManche(Dico& idico, Partie& partie);





int verifMot(Partie& partie, char mot[], unsigned int indice);




void mancheJeu(Dico& idico, Partie& partie);




void resetMotJoueur(Partie& partie);




void detruireJeu(Partie& partie);



void saisirMotHumain(Dico& idico, Partie& partie, unsigned int indice);



#endif
