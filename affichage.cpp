

#include "partie.h"
#include "dico.h"



/**
 * @brief Afficher le score des quarts de singe.
 */
void afficheScore(Dico& idico, Partie& partie) {
  for (unsigned int i = 0; i < partie.nbJoueurs - 1; ++i) {
    cout << i + 1 << partie.ordre[i] << " : " << partie.score[i] << "; ";
  }
  cout << partie.nbJoueurs << partie.ordre[partie.nbJoueurs - 1] << " : " << partie.score[partie.nbJoueurs - 1] << endl;
  finduJeu( partie);
}

/**
 * @brief Afficher le mot formé.
 */
void affichageTexte(const Partie& partie) {
  unsigned int i = 0;
  while (partie.mot[i] != CHAINE_VIDE) {
    cout << partie.mot[i];
    i++;
  }
}







void abandonJoueur(Dico& idico, Partie& partie, unsigned int indice) {
  if (indice == partie.nbJoueurs)
    indice -= (partie.nbJoueurs - 1);
  cout << "le joueur " << indice + 1 << partie.ordre[indice] << " abandonne la manche et prend un quart de singe" << endl; // si l'utilisateur rentre '!'
  partie.dernierJoueurPerdant = indice;
  partie.score[indice] += 0.25;
  afficheScore(idico, partie);
  finduJeu( partie);
}







void AffichemotExistePas(Dico& idico, Partie& partie, unsigned int indice, char mot[]) {
  if (indice + 1 == 1) {
    indice = partie.nbJoueurs;
  }
  cout << "le mot " << mot << " n'existe pas, " << indice << partie.ordre[indice - 1] << " prend un quart de singe" << endl;
  partie.dernierJoueurPerdant = indice - 1;
  partie.score[indice - 1] += 0.25;
  afficheScore(idico, partie);
  finduJeu( partie);
}









void afficheMotExiste(Dico& idico, Partie& partie, unsigned int indice, char trouve_mot[]) {
  // compare le mot saisi par l'utilisateur et le dico
  cout << "le mot " << trouve_mot << " existe, ";
  if (indice == partie.nbJoueurs) {
    indice -= (partie.nbJoueurs);
  }
  cout << "le joueur " << indice + 1 << partie.ordre[indice] << " prend un quart de singe" << endl;
  partie.dernierJoueurPerdant = indice;
  partie.score[indice] += 0.25;
  afficheScore(idico, partie);
  finduJeu( partie);

}









/**
 * @brief afficher le mot ne commence pas par les lettres attendues
 */
void debutMotFaux(Dico& idico, Partie& partie, unsigned int indice, char mot[]) {
  if (indice + 1 == 1) indice = partie.nbJoueurs;
  cout << "le mot " << mot << " ne commence pas par les lettres attendues, le joueur " << indice << partie.ordre[indice - 1] << " prend un quart de singe" << endl;
  partie.dernierJoueurPerdant = indice - 1;
  partie.score[indice - 1] += 0.25;
  afficheScore(idico, partie);
}


