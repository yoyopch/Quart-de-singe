
#ifndef _DICO_
#define _DICO_

#include "Header.h"

struct Dico {
  int tailleDico;
  char** mots = NULL;
  char* listeLettre = new char[MAX_CHAR];
  const char motConnus[13] = "ESARTINULODC";
};

#include "partie.h"


void buildDico(Dico& idico);



unsigned int trouve_Dico(Dico& idico, char trouve_mot[]);







unsigned int motDebutExiste(Dico& idico, Partie& partie, const char mot[]);







void freeDico(Dico& idico);







#endif










