#ifndef _HEADER_
#define _HEADER_

/**
 * @file Header.h
 * @author Yohann PECH - Mehdi BOUZIANE - Grp 106
 * @brief Tout les types et structures utiles au jeu.
 */

#include <iostream> // pour NULL

using namespace std;

enum { MAX_CHAR = 26 };
#define FINISH1 '?'
#define FINISH2 '!'
#define HUMAIN 'H'
#define ROBOT 'R'
#define CHAINE_VIDE '\0'
#define VRAI 1
#define FAUX 0
typedef int BOOL;

#define TRACE 0

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

struct Dico {
  int tailleDico;
  char** mots = NULL;
  char* listeLettre = new char[MAX_CHAR];
};

#endif