#include "robot.h"
#include "partie.h"
#include "dico.h"

#pragma warning(disable: 4996)

/**
 * @brief Trouver un mot pour le robot si le joueur précédent a entré '?', et l'afficher
 * @param[in-out] idico : Le dictionnaire
 * @param[in-out] partie: La partie en cours
 */
void trouveMotDico_Robot(Dico& idico, Partie& partie) {
  int i = 0;
  for (i = 0; i < idico.tailleDico; ++i) {
    if (strncmp(idico.mots[i], partie.mot, partie.taillemot) == 0) {
      resetMotJoueur(partie);
      strcpy(partie.motJoueurDeviner, idico.mots[i]);
      cout << idico.mots[i] << endl;
      return;
    }
  }
  if (i == idico.tailleDico) {
    resetMotJoueur(partie);
    strcpy(partie.motJoueurDeviner, partie.mot);
    cout << partie.mot << endl;
  }

}

/**
 * @brief Ajouter la lettre du robot au mot de la partie
 * @param[in-out] partie : La partie en cours.
 */
void ajoutLettreRobot(Partie& partie) {
  unsigned int i = 0;
  while (partie.mot[i] != CHAINE_VIDE) {
    i++;
  }
  partie.taillemot++;
  partie.mot[i] = partie.motRobot[0];
  partie.motRobot[0] = CHAINE_VIDE;
}

/**
 * @brief Générer une lettre aléatoire si le robot joue en premier
 * @param[in-out] partie: La partie en cours
 */
void LettreAleatoireRobot(Partie& partie) {
  char LettreAleatoire = 'A' + rand() % MAX_CHAR;
  cout << LettreAleatoire << endl;
  partie.motRobot[0] = LettreAleatoire;
  ajoutLettreRobot(partie);
}

/**
 * @brief Permet au robot de joueur une lettre ou de demander au joueur precedent le mot qu'il pensait
 * @param[in-out] idico : Le dictionnaire
 * @param[in-out] partie : La partie en cours
 * @param[in] indice : Indice du robot
 * @param[in-out] indexmotdudico : Index du mot dans le dictionnaire
 * @return num : 0 si le robot a pu genere une lettre, sinon 1.
 */
int LettreRobot(Dico& idico, Partie& partie, unsigned int indice, int& indexmotdudico) {
  if (partie.taillemot == 0) {
    LettreAleatoireRobot(partie);
    return 0;
  }
  int num = ChercherMotDico_Robot(idico, partie, indexmotdudico);
  if (num == 0) {
    cout << partie.motRobot[0] << endl;
    ajoutLettreRobot(partie);
  }
  else {
    cout << "?" << endl;
  }
  return num;
}

/**
 * @brief Permet au robot de chercher une lettre qui completera le mot deja forme.
 * @param[in-out] idico : Le dictionnaire
 * @param[in-out] partie : La partie en cours
 * @param[in-out] indexmotdudico : Index du mot dans le dictionnaire
 * @return oreturn : 0 si le robot a reussi a trouve une lettre, sinon 1
 */
int ChercherMotDico_Robot(Dico& idico, Partie& partie, int& indexmotdudico) {
  unsigned int oreturn = 1;
  int i = indexmotdudico;
  while (i < idico.tailleDico) {
    char* pMotdudico = idico.mots[i];
    if (strlen(pMotdudico) > partie.taillemot) {
      char* motDico = new char[MAX_CHAR];
      strncpy(motDico, pMotdudico, partie.taillemot);

      if (strncmp(motDico, partie.mot, partie.taillemot) == 0) {
        indexmotdudico = i;

        if (TRACE)
          cout << "motDico trouve = " << motDico << " indexmotdudico: " << indexmotdudico << endl;
        unsigned int Compteur = 0;

        char* listeLettre = new char[MAX_CHAR];
        resetListeLettre(listeLettre);

        int motExiste = construireMot_Robot(idico, partie, motDico, Compteur, listeLettre);
        delete[] listeLettre;

        if (motExiste) {
          delete[] motDico;
          oreturn = 0;
          break;
        }
        else {
          delete[] motDico;
          oreturn = 0;
          break;
        }
      }
      delete[] motDico;
    }
    i++;
  }
  return oreturn;   // return 1 si le mot existe pas
}

/**
 * @brief Reinitialiser la liste qui comporte les lettres generees aleatoirement
 * @param[in-out] listeLettre : La liste .
 */
void resetListeLettre(char* listeLettre) {
  for (int i = 0; i < MAX_CHAR; ++i) {
    listeLettre[i] = CHAINE_VIDE;
  }
}

/**
 * @brief Verifier si les lettres generees aleatoirement n'ont pas encore ete generes
 * @param[in] lettre : La lettre generee aleatoirement
 * @param[in-out] listeLettre : La liste de lettres
 * @return oreturn : 1 si la lettre a deja ete generee, sinon 0.
 */
int VerifLettreUtil(char lettre, char* listeLettre) {
  unsigned int oreturn = 0;
  for (int i = 0; i < MAX_CHAR; ++i) {
    if (listeLettre[i] == lettre) {
      oreturn = 1;
      break;
    }
  }
  return oreturn;
}

/**
 * @brief Ajouter la lettre alatoire a listeLettre
 * @param[in] lettre : La lettre aleatoire
 * @param[in-out] listeLettre : La liste de lettres
 * @return oreturn : 1 si la lettre a deja ete generee, sinon 0.
 */
int AjoutLettreUtil(char lettre, char* listeLettre) {
  unsigned int oreturn = 0;
  unsigned int i = 0;
  while (listeLettre[i] != CHAINE_VIDE) {
    i++;
  }
  if (VerifLettreUtil(lettre, listeLettre)) {
    oreturn = 1;
  }
  else {
    listeLettre[i] = lettre;


    if (TRACE)
      cout << "AjoutLettreUtil lettre : " << lettre << " et index : " << i << endl;

    oreturn = 0;
  }
  return oreturn;
}

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
int construireMot_Robot(Dico& idico, Partie& partie, char mot[], unsigned int& nbNombre, char* listeLettre) {


  unsigned int oreturn = 0;
  char lettreRand = 'A' + rand() % MAX_CHAR;
  int lettreExiste = AjoutLettreUtil(lettreRand, listeLettre);


  if (TRACE)
    cout << "verifDebutMot lettreRand = " << lettreRand << " et nbNombre = " << nbNombre << endl;

  int nbRand = 0;

  // lettreExiste == 1 si la lettre a deja été générée
  while (lettreExiste) {
    if (nbRand == MAX_CHAR)
      return 1;
    lettreRand = 'A' + rand() % MAX_CHAR;
    nbRand++;
    lettreExiste = AjoutLettreUtil(lettreRand, listeLettre);


    if (TRACE)
      cout << "verifDebutMot lettreExiste = " << lettreRand << endl;

  }

  if (mot) {
    mot[partie.taillemot] = lettreRand;
  }
  partie.motRobot[0] = lettreRand;
  if (nbNombre == MAX_CHAR)
    return 1;

  unsigned int motExiste = motDebutExiste(idico, partie, mot);
  // voir si il y a un mot dans le dictionnaire qui commencence par "mot"
  if (motExiste) {

    int motTrouve = trouverMotDansDico(idico, mot);
    if (motTrouve) {

      nbNombre++;
      oreturn = construireMot_Robot(idico, partie, mot, nbNombre, listeLettre);
    }
    else {

      return 1;
    }
  }
  else {
    nbNombre++;
    oreturn = construireMot_Robot(idico, partie, mot, nbNombre, listeLettre);
  }

  return oreturn;
}