#include "dico.h"
#include "Header.h"


#include <fstream> // pour ifstream
#include <iomanip> // pour setw



void buildDico(Dico& idico) {
  int TailleFixe = 1000;
  int Max = TailleFixe;
  int index = 0;
  char** pListMots = new char* [Max];

  ifstream in("ods4.txt"); // on ouvre le fichier

  char* pMot = new char[MAX_CHAR];
  in >> setw(MAX_CHAR) >> pMot;

  while (in) {
    if (strlen(pMot) > 2) {
      pListMots[index] = pMot;
      index++;
    }

    if (index == Max) {
      // On a atteind ma taille max, on réalloue un autre tableau avec la taille 2 x Max
      int NewMaw = Max + TailleFixe;
      char** pNewListMots = new char* [NewMaw];

      // On copie les anciens
      for (int i = 0; i < Max; i++) {
        pNewListMots[i] = pListMots[i];
      }
      // On detruit l'ancien
      delete[] pListMots;

      // On réaffecte le nouveau
      pListMots = pNewListMots;

      Max = NewMaw;
    }
    //
    pMot = new char[MAX_CHAR];
    in >> setw(MAX_CHAR) >> pMot;
    if (!in)break;
  }
  idico.tailleDico = index;
  idico.mots = pListMots;

  in.close(); // on ferme le fichier
}








/**
 * @brief verifie si le mot entré par le joueur existe
 */
unsigned int trouve_Dico(Dico& idico, char trouve_mot[])
{

  for (int i = 0; i < strlen(trouve_mot); ++i)
    trouve_mot[i] = toupper(trouve_mot[i]);

  if (TRACE)
    cout << "trouve_Dico trouve_mot = " << trouve_mot << endl;

  for (int i = 0; i < idico.tailleDico; i++) {
    char* pmot = idico.mots[i];

    if (strncmp(trouve_mot, pmot, strlen(pmot)) == 0) {

      if (TRACE)
        cout << "trouve_Dico mot trouve = " << pmot << endl;

      return 1;
    }
  }
  return 0;   // return 0 si le mot existe pas
}








/**
 * @biref Verifier si le debut du mot existe dans le dictionnaire
 */
unsigned int motDebutExiste(Dico& idico, Partie& partie, const char mot[]) {

  for (int i = 0; i < idico.tailleDico; ++i) {
    char* motDico = idico.mots[i];
    if (strncmp(mot, motDico, partie.taillemot + 1) == 0) {
      return 1;
    }

  }
  return 0;
}





void freeDico(Dico& idico) {
  for (int i = 0; i < idico.tailleDico; i++)
    delete[] idico.mots[i];
  delete[] idico.mots;
}




