
#ifndef _AFFICHAGE_
#define _AFFICHAGE_

#include "partie.h"
#include "dico.h"

/**
 * @brief Afficher le score de la partie
 * @param[in-out] partie : La partie en cours
 * @param[in] indice : Indice du joueur prenant un quart de singe
 */
void afficheScore(const Partie& partie, const unsigned int indice);

/**
 * @brief Afficher le mot formé.
 * @param[in-out] partie : La partie en cours.
 */
void afficheTexte(const Partie& partie);

/**
 * @brief Afficher le message d'abandon du joueur .
 * @param[in-out] partie : La partie en cours.
 * @param[in] indice : Indice du joueur qui abandonne
 */
void afficheAbandonJoueur(Partie& partie, unsigned int indice);

/**
 * @brief Afficher le message disant que le mot saisi n'existe pas
 * @param[in-out] partie: La partie en cours
 * @param[in] indice : Indice du joueur prenant un quart de singe
 * @param[in] mot : Mot qui n'existe pas dans le dictionnaire.
 */
void AfficheMotExistePas(Partie& partie, unsigned int indice, char mot[]);

/**
 * @brief Affiche le message disant que le mot existe dans le dictionnaire
 * @param[in-out] partie: La partie en cours
 * @param[in] indice : Indice du joueur qui va prendre un quart de singe
 * @param[in] trouve_mot : Mot qui existe dans le dictionnaire.
 */
void afficheMotExiste(Partie& partie, unsigned int indice, const char trouve_mot[]);

/**
 * @brief Afficher le message disant que le mot saisi ne commence pas par les lettres attendues
 * @param[in-out] partie: La partie en cours
 * @param[in] indice : Indice du joueur qui prend un quart de singe
 * @param[in] mot : Mot incorrect
 */
void AfficheDebutMotFaux(Partie& partie, unsigned int indice, const char mot[]);

/**
 * @brief Afficher la fin du jeu.
 */
void AfficheGameOver();

#endif