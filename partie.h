#ifndef _PARTIE_
#define _PARTIE_

/**
 * @file partie.h
 * @author Yohann PECH - Mehdi BOUZIANE - Grp 106
 * @brief Toutes les fonctions relatives au bon fonctionnement du jeu.
 */

#include "Header.h"

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

/**
 * @brief Desallouer les zones memoires allouees en memoire dynamique
 * @param[in-out] idico : Le dictonnaire
 * @param[in-out] partie: La partie en cours .
 */
void EffacerJeu(Dico& idico, Partie& partie);

/**
 * @brief Verifier si un joueur a obtenu quatre quarts de singe
 * @param[in-out] partie: La partie en cours.
 * @return oreturn : 1 si un joueur a obtenu quatre quarts de singe, sinon 0
 */
unsigned int finduJeu(Partie& partie);

/**
 * @brief Initialiser les structure
 * @param[in-out] partie : La partie en cours
 * @parame[in] pl : Chaine de caracteres entree sur la ligne de commande.
 */
void init(Partie& partie, char pl[]);

/**
 * @brief Permet a l'humain de jouer et de saisir une lettre ou '?' ou '!'
 * @param[in-out] partie : La partie en cours
 * @return oreturn : 0 si le joueur a saisi une lettre, 1 si le joueur a saisi '?' ou 2 si le joueur a saisi '!'.
 */
int ajoutLettre(Partie& partie);

/**
 * @brief Afficchage et gestion de la nouvelle manche
 * @param[in-out] idico : Le dictionnaire
 * @param[in-out] partie : La partie en cours.
 */
void nouvelleManche(Dico& idico, Partie& partie);

/**
 * @brief cherchez si deux mots commencent par les memes lettres
 * @param[in-out] partie : La partie en cours
 * @param[in] mot : le mot a compare avec le mot de la partie
 * @return oreturn : 1 si les deux mots ne commencent pas par les memes lettres, sinon 0.
 */
int verifMot(Partie& partie, const char mot[]);

/**
 * @brief Manche de la partie en cours
 * @param[in-out] idico : Le dictionnaire
 * @param[in-out] partie: La partie en cours.
 */
void mancheJeu(Dico& idico, Partie& partie);

/**
 * @brief Reinitialiser le mot a deviner dans la structure
 * @param[in-out] partie : La partie en cours.
 */
void resetMotJoueur(Partie& partie);

/**
 * @brief Desallouer les zones memoires allouees en memoire dynamique dans la strucutre 'partie'
 * @param partie[in-out] : La partie en cours .
 */
void detruireJeu(Partie& partie);


/**
 * @brief Saisir un mot si le joueur précédent a saisi '?'
 * @param[in-out] idico : Le dictionnaire
 * @param[in-out] partie : La partie en cours
 * @param[in] indice : Indice du joueur qui doit saisir le mot.
 */
void saisirMot(Dico& idico, Partie& partie, unsigned int indice);

#endif