
#ifndef _DICO_
#define _DICO_

#include "Header.h"

struct Dico {
  int tailleDico;
  char** mots = NULL;
  char* listeLettre = new char[MAX_CHAR];
};

#include "partie.h"

/**
 * @brief Remplir le dictionnaire
 * @param[in-out] idico : Le dictionnaire.
 */
void remplirDico(Dico& idico);

/**
 * @brief verifie si le mot entré par le joueur existe dans le dictionnaire
 * @param[in-out] idico : Le dictionnaire
 * @param[in] trouve_mot : Le mot a comparer avec les mots du dictionnaire
 * @return oreturn : 1 si le mot a ete trouve dans le dictionnaire, sinon 0 .
 */
unsigned int trouverMotDansDico(Dico& idico, char trouve_mot[]);

/**
 * @brief Verifier s'il existe un mot dans le dictionnaire qui commence par les memes lettres que le mot passe en parametre
 * @param[in-out] idico : Le dictionnaire
 * @param[in-out] partie : La partie en cours
 * @param[in] mot : Le mot a tester
 * @return oreturn : 1 s'il existe un mot commencant par les memes lettres, sinon 0.
 */
unsigned int motDebutExiste(Dico& idico, Partie& partie, const char mot[]);

/**
 * @brief Desallouer les zones memoires allouees en memoire dynamique
 * @param[in-out] idico : Le dictionnaire.
 */
void desallouerDico(Dico& idico);

#endif