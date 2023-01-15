#include <fstream> // pour ifstream
#include <iomanip> // pour setw

#include "dico.h"

/**
 * @brief Remplir le dictionnaire
 * @param[in-out] idico : Le dictionnaire.
 * @param[in] fileName : Le fichier contenant le dictionnaire, si NULL le fichier est ods4.txt.
 */
void remplirDico(Dico& idico, const char* fileName) {
  int TailleFixe = MAX;
  int Max = TailleFixe;
  int index = 0;
  char** pListMots = new char* [Max];

  if (fileName == NULL) {
    fileName = "ods4.txt";
  }
  ifstream in(fileName); // on ouvre le fichier

  char* pMot = new char[MAX_CHAR];
  in >> setw(MAX_CHAR) >> pMot;

  while (in) {
    if (strlen(pMot) > MIN_MOT) {
      for (unsigned int i = 0; i < strlen(pMot); i++) {
        pMot[i] = toupper(pMot[i]);
      }
      pListMots[index] = pMot;
      index++;
    }

    if (index == Max) {
      // On a atteind ma taille max, on réalloue un autre tableau avec la taille 2 x Max
      int NewMaw = Max + TailleFixe;
      char** pNewListMots = new char* [NewMaw];

      // On copie les anciens
      for (int i = 0; i < Max; i++)
        pNewListMots[i] = pListMots[i];
      // On detruit l'ancien
      delete[] pListMots;
      // On réaffecte le nouveau
      pListMots = pNewListMots;
      Max = NewMaw;
    }
    pMot = new char[MAX_CHAR];
    in >> setw(MAX_CHAR) >> pMot;
    if (!in)break;
  }
  idico.tailleDico = index;
  idico.mots = pListMots;
  in.close(); // on ferme le fichier
}

/**
 * @brief verifie si le mot entré par le joueur existe dans le dictionnaire
 * @param[in-out] idico : Le dictionnaire
 * @param[in] trouve_mot : Le mot a comparer avec les mots du dictionnaire
 * @return oreturn : 1 si le mot a ete trouve dans le dictionnaire, sinon 0 .
 */
unsigned int trouverMotDansDico(Dico& idico, char trouve_mot[]) {
  unsigned int oreturn = 0;
  for (unsigned int i = 0; i < strlen(trouve_mot); ++i)
    trouve_mot[i] = toupper(trouve_mot[i]);

  if (TRACE)
    cout << "trouve_Dico trouve_mot = " << trouve_mot << endl;

  for (int i = 0; i < idico.tailleDico; i++) {
    if (strncmp(trouve_mot, idico.mots[i], strlen(idico.mots[i])) == 0) {
      oreturn = 1;
      break;
    }
  }
  return oreturn;   // return 0 si le mot existe pas
}

/**
 * @brief Verifier s'il existe un mot dans le dictionnaire qui commence par les memes lettres que le mot passe en parametre
 * @param[in-out] idico : Le dictionnaire
 * @param[in-out] partie : La partie en cours
 * @param[in] mot : Le mot a tester
 * @return oreturn : 1 s'il existe un mot commencant par les memes lettres, sinon 0.
 */
unsigned int motDebutExiste(Dico& idico, Partie& partie, const char mot[]) {
  unsigned int oreturn = 0;
  for (int i = 0; i < idico.tailleDico; ++i) {
    char* motDico = idico.mots[i];
    if (strncmp(mot, motDico, partie.taillemot + 1) == 0) {
      oreturn = 1;
      break;
    }
  }
  return oreturn;
}

/**
 * @brief Desallouer les zones memoires allouees en memoire dynamique
 * @param[in-out] idico : Le dictionnaire.
 */
void desallouerDico(Dico& idico) {
  for (int i = 0; i < idico.tailleDico; i++)
    delete[] idico.mots[i];
  delete[] idico.mots;
  idico.mots = NULL;

}