#include "partie.h"
#include "dico.h"

/**
 * @brief Afficher le score de la partie
 * @param[in] partie : La partie en cours
 * @param[in] indice : Indice du joueur prenant un quart de singe
 */
void afficheScore(const Partie& partie, const unsigned int indice) {
  partie.score[indice] += 0.25;
  for (unsigned int i = 0; i < partie.nbJoueurs - 1; ++i) {
    cout << i + 1 << partie.ordre[i] << " : " << partie.score[i] << "; ";
  }
  cout << partie.nbJoueurs << partie.ordre[partie.nbJoueurs - 1] << " : " << partie.score[partie.nbJoueurs - 1] << endl;
}

/**
 * @brief Afficher le mot formé.
 * @param[in] partie : La partie en cours.
 */
void afficheTexte(const Partie& partie) {
  unsigned int i = 0;
  while (partie.mot[i] != CHAINE_VIDE) {
    cout << partie.mot[i];
    i++;
  }
}

/**
 * @brief Afficher le message d'abandon du joueur .
 * @param[in] partie : La partie en cours.
 * @param[in] indice : Indice du joueur qui abandonne
 */
void afficheAbandonJoueur(Partie& partie, unsigned int indice) {
  if (indice == partie.nbJoueurs)
    indice -= (partie.nbJoueurs - 1);
  cout << "le joueur " << indice + 1 << partie.ordre[indice] << " abandonne la manche et prend un quart de singe" << endl; // si l'utilisateur rentre '!'
  partie.dernierJoueurPerdant = indice;
}

/**
 * @brief Afficher le message disant que le mot saisi n'existe pas
 * @param[in] partie: La partie en cours
 * @param[in] indice : Indice du joueur prenant un quart de singe
 * @param[in] mot : Mot qui n'existe pas dans le dictionnaire.
 */
void AfficheMotExistePas(Partie& partie, unsigned int indice, char mot[]) {
  if (indice + 1 == 1) {
    indice = partie.nbJoueurs;
  }
  cout << "le mot " << mot << " n'existe pas, " << indice << partie.ordre[indice - 1] << " prend un quart de singe" << endl;
  partie.dernierJoueurPerdant = indice - 1;
}

/**
 * @brief Affiche le message disant que le mot existe dans le dictionnaire
 * @param[in] partie: La partie en cours
 * @param[in] indice : Indice du joueur qui va prendre un quart de singe
 * @param[in] trouve_mot : Mot qui existe dans le dictionnaire.
 */
void afficheMotExiste(Partie& partie, unsigned int indice, const char trouve_mot[]) {
  // compare le mot saisi par l'utilisateur et le dico

  if (indice == partie.nbJoueurs) {
    indice -= (partie.nbJoueurs);
  }
  cout << "le mot " << trouve_mot << " existe, le joueur " << indice + 1 << partie.ordre[indice] << " prend un quart de singe" << endl;
  partie.dernierJoueurPerdant = indice;
}

/**
 * @brief Afficher le message disant que le mot saisi ne commence pas par les lettres attendues
 * @param[in] partie: La partie en cours
 * @param[in] indice : Indice du joueur qui prend un quart de singe
 * @param[in] mot : Mot incorrect
 */
void AfficheDebutMotFaux(Partie& partie, unsigned int indice, const char mot[]) {
  if (indice + 1 == 1) indice = partie.nbJoueurs;
  cout << "le mot " << mot << " ne commence pas par les lettres attendues, le joueur " << indice << partie.ordre[indice - 1] << " prend un quart de singe" << endl;
  partie.dernierJoueurPerdant = indice - 1;
}

/**
 * @brief Afficher la fin du jeu.
 */
void AfficheGameOver() {
  cout << "La partie est finie" << endl;
}
