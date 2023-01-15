#ifndef _HEADER_
#define _HEADER_

/**
 * @file Header.h
 * @author Yohann PECH - Mehdi BOUZIANE - Grp 106
 * @brief Tout les types et structures utiles au jeu.
 */

#include <iostream> 

using namespace std;

enum {
  MAX_CHAR = 26,
  MAX_LENMOT = 25,
};
#define FINISH1 '?'
#define FINISH2 '!'
#define HUMAIN 'H'
#define ROBOT 'R'
#define CHAINE_VIDE '\0'
#define VRAI 1
#define FAUX 0
#define QDS 0.25
#define MIN_JOUEURS 2
#define MAX 100
#define MIN_MOT 2
#define VALUE2 2

typedef int BOOL;

#define TRACE 0

#endif