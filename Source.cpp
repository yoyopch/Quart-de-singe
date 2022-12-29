#include <iostream>
#include "dico.h"
#include "Header.h"
#include "partie.h"


int main(int argc, char* argv[]) {
  srand((unsigned int)time(NULL));
  Dico dico;
  Partie p;
  remplirDico(dico);

  init(p, argv[1]);
  mancheJeu(dico, p);
}
