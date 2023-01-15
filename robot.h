#ifndef _ROBOT_
#define _ROBOT_

/**
 * @file robot.h
 * @author Yohann PECH - Mehdi BOUZIANE - Grp 106
 * @brief Toutes les fonctions relatives au robot.
 */

#include "header.h"
#include "dico.h"
#include "partie.h"

/**
 * @brief Trouver un mot pour le robot si le joueur précédent a entré '?', et l'afficher
 * @param[in-out] idico : Le dictionnaire
 * @param[in-out] partie: La partie en cours
 */
void trouveMotDico_Robot(Dico& idico, Partie& partie);

/**
 * @brief Ajouter la lettre du robot au mot de la partie
 * @param[in-out] partie : La partie en cours.
 * @param[in] LettreAleatoire : La lettre generee par le robot
 */
void ajoutLettreRobot(Partie& partie, const char LettreAleatoire);

/**
 * @brief Générer une lettre aléatoire si le robot joue en premier
 * @param[in-out] partie: La partie en cours
 */
void LettreAleatoireRobot(Partie& partie);

/**
 * @brief Permet au robot de joueur une lettre ou de demander au joueur precedent le mot qu'il pensait
 * @param[in-out] idico : Le dictionnaire
 * @param[in-out] partie : La partie en cours
 * @param[in] indice : Indice du robot
 * @param[in-out] indexmotdudico : Index du mot dans le dictionnaire
 * @return num : 0 si le robot a pu genere une lettre, sinon 1.
 */
int LettreRobot(Dico& idico, Partie& partie, unsigned int indice, int& indexmotdudico);

/**
 * @brief Permet au robot de chercher une lettre qui completera le mot deja forme.
 * @param[in-out] idico : Le dictionnaire
 * @param[in-out] partie : La partie en cours
 * @param[in-out] indexmotdudico : Index du mot dans le dictionnaire
 * @return oreturn : 1 si le robot a reussi a trouve une lettre, sinon 0
 */
int ChercherMotDico_Robot(Dico& idico, Partie& partie, int& indexmotdudico);

/**
 * @brief Reinitialiser la liste qui comporte les lettres generees aleatoirement
 * @param[in-out] listeLettre : La liste .
 */
void resetListeLettre(char* listeLettre);

/**
 * @brief Verifier si les lettres generees aleatoirement n'ont pas encore ete generes
 * @param[in] lettre : La lettre generee aleatoirement
 * @param[in-out] listeLettre : La liste de lettres
 * @return oreturn : 1 si la lettre a deja ete generee, sinon 0.
 */
int VerifLettreUtil(char lettre, char* listeLettre);

/**
 * @brief Ajouter la lettre alatoire a listeLettre
 * @param[in] lettre : La lettre aleatoire
 * @param[in-out] listeLettre : La liste de lettres
 * @return oreturn : 1 si la lettre a deja ete generee, sinon 0.
 */
int AjoutLettreUtil(char lettre, char* listeLettre);

/**
 * @brief Permet de generer une lettre aleatoire et de tester si la lettre construit un mot existant.
 *
 * @param[in-out] idico : Le dicctionnaire
 * @param[in-out] partie : La partie en cours
 * @param[in-out] mot : le mot du dictionnaire qui commence par les memes lettres que le mot forme dans la partie
 * @param[in-out] nbNombre : Nombre de fois que la fonction va s'executer si la lettre generee n'est pas bonne
 * @param[in-out] listeLettre : La liste de lettres
 * @return oreturn : 1 si le robot a reussi a construire un mot avec une lettre, sinon 0.
 */
int construireMot_Robot(Dico& idico, Partie& partie, char mot[], unsigned int& nbNombre, char* listeLettre);

#endif