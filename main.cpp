#include <iostream>
#include "Header.h"
#include "dico.h"
#include "partie.h"

/**
 * @file main.cpp
 * @author Yohann PECH - Mehdi BOUZIANE - Grp 106
 * @brief fichier source.
 */

int main(int argc, char* argv[]) {
  srand((unsigned int)time(NULL));
  Dico dico;
  Partie p;
  remplirDico(dico);

  init(p, argv[1]);
  mancheJeu(dico, p);
}
