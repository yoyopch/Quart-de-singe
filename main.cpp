#include <iostream>
#include <cassert>

#include "header.h"
#include "dico.h"
#include "partie.h"
#include "robot.h"

#pragma warning(disable:4996)

/**
 * @file main.cpp
 * @author Yohann PECH - Mehdi BOUZIANE - Grp 106
 * @brief fichier source.
 */

int main(int argc, char* argv[]) {
  srand((unsigned int)time(NULL));

  Dico dico;
  Partie p;
  remplirDico(dico, NULL);

  init(p, argv[1]);
  mancheJeu(dico, p);

}

